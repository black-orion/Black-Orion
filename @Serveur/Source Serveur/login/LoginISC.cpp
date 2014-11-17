#include "LoginISC.h"
#include "LoginServer.h"
#include "../shared/ISCPacketCreator.h"
#include "../shared/ISCPacketReader.h"
#include "../shared/Log.h"


//// SERVERLIST ////
////////////////////

s32 ILoginISC::ServerList::getServerCount() const
{
	u32 r_count = Clusters.size();

	FOR_EACH (Clusters, i)
	{
		r_count += Clusters[i].Channels.size();
	}

	return static_cast<s32>(r_count);
}

void ILoginISC::ServerList::Cluster::disconnectChannels()
{
	FOR_EACH (Channels, i)
	{
		Channels[i].Client->free();
	}

	Channels.clear();
}


//// LOGINISC ////
//////////////////

ILoginISC::ILoginISC(ILoginISCSettings *_settings, ILoginServer *_server)
	: m_settings(_settings)
	, m_acceptor(0)
	, m_pserver(_server)
{
}

ILoginISC::~ILoginISC()
{
}

bool ILoginISC::init(CNetwork *_network)
{
	FDASSERT(_network);

	m_acceptor = _network->createAcceptor(m_settings->Port);

	if (!m_acceptor)
	{
		Log::write(LOG_ERROR, "ISC port %u could not be used!", m_settings->Port);

		return false;
	}

	return true;
}

bool ILoginISC::run()
{
	FDASSERT(m_acceptor);

	//accept all connections
	while (m_acceptor->isNew())
	{
		m_unauths.push_back(Unauthorized(m_acceptor->popClient()));
	}

	//check connections for new data
	FOR_EACH (m_unauths, i)
	{
		//disconnected
		if (!m_unauths[i].Client->isConnected())
		{
			Log::write(LOG_ISC, "Unaccepted ISC connection lost (%s)",
				m_unauths[i].Client->getIp());

			m_unauths[i].Client->free();
			m_unauths.erase_fast(i);

			continue;
		}

		else if (!m_unauths[i].Client->incoming().empty())
		{
			while (_handlePacket(&m_unauths[i]));

			if (m_unauths[i].Remove)
			{
				m_unauths.erase_fast(i);

				continue;
			}

			m_unauths[i].Client->incoming().clear();
		}
	}

	//handle clusters and channels
	ServerList::Cluster *t_cluster = 0;
	ServerList::Channel *t_channel = 0;

	FOR_EACH (m_serverlist.Clusters, i)
	{
		t_cluster = &m_serverlist.Clusters[i];

		//cluster connection lost
		if (!t_cluster->Client->isConnected())
		{
			Log::write(LOG_ISC, "Lost connection to cluster \"%s\"", t_cluster->Name.c_str());

			t_cluster->disconnectChannels();

			t_cluster->Client->free();

			m_serverlist.Clusters.erase(i);

			continue;
		}

		//new data?
		else if (!t_cluster->Client->incoming().empty())
		{
			while (_handlePacket(t_cluster));

			t_cluster->Client->incoming().clear();
		}

		//channels, too
		FOR_EACH (t_cluster->Channels, j)
		{
			t_channel = &t_cluster->Channels[j];

			//channel connection lost
			if (!t_channel->Client->isConnected())
			{
				Log::write(LOG_ISC, "Lost connection to channel \"%s\"", t_channel->Name.c_str());

				t_channel->Client->free();

				t_cluster->Channels.erase(j);

				continue;
			}

			//new data
			else if (!t_channel->Client->incoming().empty())
			{
				while (_handlePacket(t_channel));

				t_channel->Client->incoming().clear();
			}
		}
	}

	return true;
}

ILoginISC::ServerList &ILoginISC::getServerList()
{
	return m_serverlist;
}

bool ILoginISC::_handlePacket(Unauthorized *_unauth)
{
	FDASSERT(_unauth);
	FDASSERT(_unauth->Client);

	E_ISC_COMMAND t_command = IISCPacketReader::readHeader(_unauth->Client->incoming());

	if (t_command == ISCC_NONE)
		return false;

	switch (t_command)
	{
	case ISCC_AUTH:
		return _cmdHandler_auth(_unauth);

	default:
		Log::write(LOG_ISC, "Unknown ISC command 0x%x", t_command);

		return false;
	};
}

bool ILoginISC::_cmdHandler_auth(Unauthorized *_unauth)
{
	static const u32 T_BUF_SIZE = 256;
	static char t_buffer_pw[T_BUF_SIZE];
	static char t_buffer_name[T_BUF_SIZE];
	static char t_buffer_ip[T_BUF_SIZE];

	FDASSERT(_unauth);
	FDASSERT(_unauth->Client);

	CByteArray &t_packet = _unauth->Client->incoming();

	//client type
	E_ISC_CLIENT_TYPE t_type = E_ISC_CLIENT_TYPE(t_packet.getInt());

	if (t_type != ISC_CLIENT_CHANNEL &&
		t_type != ISC_CLIENT_CLUSTER)
	{
		Log::write(LOG_ISC, "Unknown client type (%s)", _unauth->Client->getIp());
		return false;
	}

	//ISC password
	t_packet.getString(t_buffer_pw, T_BUF_SIZE);

	if (xstricmp(m_settings->Password.c_str(), t_buffer_pw) != 0)
	{
		Log::write(LOG_ISC, "Wrong password (%s)", _unauth->Client->getIp());

		_unauth->Client->send(IISCPacketCreator::authAnswer(0, IISCPacketCreator::ANSWER_WRONG_PASSWORD));

		return false;
	}

	//client name
	t_packet.getString(t_buffer_name, T_BUF_SIZE);

	//client IP
	t_packet.getString(t_buffer_ip, T_BUF_SIZE);

	if (t_buffer_ip[0] == 0)
	{
		Log::write(LOG_ISC, "No ip address \"%s\" (%s)", _unauth->Client->getIp());

		xstrcpy(t_buffer_ip, T_BUF_SIZE, "127.0.0.1");
	}

	//server ID
	ID t_id = t_packet.getInt();

	//additional param
	s32 t_additional = t_packet.getInt();

	bool t_success = false;

	switch (t_type)
	{
	case ISC_CLIENT_CLUSTER:
		if (m_serverlist.Clusters.size() < m_serverlist.MaxClusters)
		{
			m_serverlist.Clusters.push_back(
				ServerList::Cluster(_unauth->Client, t_id, t_buffer_name, t_buffer_ip, t_additional));

			t_success = true;

			Log::write(LOG_ISC, "New cluster \"%s\" (%s)", t_buffer_name,
				_unauth->Client->getIp());
		}
		else
		{
			Log::write(LOG_WARNING, "Max channel count (%u) is already reached", m_serverlist.MaxClusters);
		}

		break;

	case ISC_CLIENT_CHANNEL:
		ServerList::Cluster *t_cluster = 0;

		FOR_EACH (m_serverlist.Clusters, i)
		{
			if (m_serverlist.Clusters[i].Id == t_additional)
			{
				t_cluster = &m_serverlist.Clusters[i];
				break;
			}
		}

		if (t_cluster)
		{
			t_cluster->Channels.push_back(
				ServerList::Channel(_unauth->Client, t_id, t_buffer_name, t_buffer_ip));

			t_success = true;

			Log::write(LOG_ISC, "New channel \"%s\" (%s)", t_buffer_name,
				_unauth->Client->getIp());
		}
		else
		{
			Log::write(LOG_WARNING, "Channel (%s) tried to connect to an inexistant cluster",
				_unauth->Client->getIp());
		}

		break;
	}

	if (t_success)
	{
		_unauth->Remove = true;
		_unauth->Client->send(IISCPacketCreator::authAnswer(0,
			IISCPacketCreator::ANSWER_OK));

		t_packet.clear();
		return false;
	}
	else
	{
		_unauth->Client->send(IISCPacketCreator::authAnswer(0,
			IISCPacketCreator::ANSWER_ERROR));
	}

	return !t_packet.end();
}

bool ILoginISC::_handlePacket(ServerList::Cluster *_cluster)
{
	FDASSERT(_cluster);

	E_ISC_COMMAND t_command = IISCPacketReader::readHeader(_cluster->Client->incoming());

	if (t_command == ISCC_NONE)
		return false;

	switch (t_command)
	{
	case 0:
		return false;

	default:
		return false;
	}
}

bool ILoginISC::_handlePacket(ServerList::Channel *_channel)
{
	FDASSERT(_channel);

	E_ISC_COMMAND t_command = IISCPacketReader::readHeader(_channel->Client->incoming());

	if (t_command == ISCC_NONE)
		return false;

	switch (t_command)
	{
	case ISCC_CHANNEL_INFOS:
		return _cmdHandler_channelInfos(_channel);

	default:
		return false;
	}
}

bool ILoginISC::_cmdHandler_channelInfos(ServerList::Channel *_channel)
{
	FDASSERT(_channel);

	CByteArray &t_packet = _channel->Client->incoming();

	//read id and sid
	if (t_packet.getInt() != _channel->Id)
	{
		Log::write(LOG_ISC, "Invalid channel Id on update from channel \"%s\"", _channel->Name.c_str());

		return false;
	}

	//read new infos
	_channel->CurrentPlayers = t_packet.getInt();
	_channel->MaxPlayers = t_packet.getInt();

	return !t_packet.end();
}
