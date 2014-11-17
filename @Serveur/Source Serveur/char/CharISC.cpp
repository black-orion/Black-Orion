#include "CharISC.h"
#include "CharServer.h"
#include "../shared/ISCPacketCreator.h"
#include "../shared/ISCPacketReader.h"
#include "../shared/Log.h"


//// CHARISC ////
//////////////////

ICharISC::ICharISC(ICharISCSettings *_settings, ICharServer *_server)
	: m_settings(_settings)
	, m_pserver(_server)
{
}

ICharISC::~ICharISC()
{
}

bool ICharISC::init(CNetwork *_network)
{
	FDASSERT(_network);

	m_connection.Connector = _network->createConnector();

	return m_connection.Connector != 0;
}

bool ICharISC::run()
{
	FDASSERT(m_connection.Connector);

	//check if connector is connected
	if (!m_connection.Connector->isConnected())
	{
		//inform the user
		if (m_connection.NextConnect == 0)
		{
			Log::write(LOG_ISC, "Lost the connection to the login server!");

			m_connection.NextConnect = CTime::seconds() + 3;
		}

		//time to reconnect
		if (CTime::seconds() > m_connection.NextConnect)
		{
			//connect
			if (m_connection.Connector->connect(m_settings->Host.c_str(), m_settings->Port) &&

			//send authentication
				m_connection.Connector->send(IISCPacketCreator::auth(ISC_CLIENT_CLUSTER,
					m_settings->Password.c_str(), m_settings->Name.c_str(), m_settings->ThisIP.c_str(),
					m_settings->ExternalId, 0)))
			{
				m_connection.IsWaitingForAuthAnswer = true;

				m_connection.NextConnect = 0;
			}

			//error
			else
			{
				Log::write(LOG_ERROR, "Could not connect to the login server!");

				m_connection.NextConnect = CTime::seconds() + 3;
			}
		}
	}

	//is connected and new data
	else if (m_connection.Connector->isNew())
	{
		while (_handlePacket(m_connection.Connector));

		m_connection.Connector->incoming().clear();
	}

	return true;
}

bool ICharISC::_handlePacket(CNetConnector *_client)
{
	FDASSERT(_client);

	E_ISC_COMMAND t_command = IISCPacketReader::readHeader(_client->incoming());

	if (t_command == ISCC_NONE)
		return false;

	switch (t_command)
	{
	case ISCC_AUTH_ANSWER:
		return _cmdHandler_authAnswer(_client);

	default:
		Log::write(LOG_ISC, "Unknown ISC command 0x%x", t_command);

		return false;
	};
}

bool ICharISC::_cmdHandler_authAnswer(CNetConnector *_client)
{
	FDASSERT(_client);

	if (!m_connection.IsWaitingForAuthAnswer)
		return false;

	m_connection.IsWaitingForAuthAnswer = false;

	CByteArray &t_packet = _client->incoming();

	//sid
	m_connection.Id = t_packet.getInt();

	//answer
	IISCPacketCreator::E_AUTH_ANSWER t_answer = IISCPacketCreator::E_AUTH_ANSWER(t_packet.getInt());

	switch (t_answer)
	{
	case IISCPacketCreator::ANSWER_WRONG_PASSWORD:
		Log::write(LOG_ERROR, "Wrong ISC password!");
		break;

	case IISCPacketCreator::ANSWER_ERROR:
		Log::write(LOG_ERROR, "ISC auth error!");
		break;

	case IISCPacketCreator::ANSWER_OK:
		Log::write(LOG_ISC, "Successfully connected.");
		break;

	default:
		break;
	};

	return !t_packet.end();
}
