#include "Network.h"
#include "NetConnection.h"


BEGIN_NAMESPACE_CORE
{

	CNetwork::CNetwork()
		: m_started(false)
	{
		m_select_time.tv_sec = 0;
		m_select_time.tv_usec = 0;
	}

	CNetwork::~CNetwork()
	{
		shutdown();
	}

	bool CNetwork::startup()
	{
#ifdef OS_WINDOWS
		WSADATA t_wsa;

		if (!m_started &&
			WSAStartup(MAKEWORD(2, 2), &t_wsa) == 0)
		{
			m_started = true;
			return true;
		}
		else
		{
			return false;
		}
#elif defined OS_LINUX
		return true;
#else
		return false;
#endif
	}

	bool CNetwork::shutdown()
	{
		FOR_EACH (m_conns, i)
		{
			delete m_conns[i];
		}

		m_conns.clear();

		if (isStarted())
		{
#ifdef OS_WINDOWS
			WSACleanup();
#endif
			m_started = false;
		}

		return true;
	}

	void CNetwork::setWaitingTime(u32 _time_ms)
	{
		m_select_time.tv_sec = (_time_ms / 1000);
		m_select_time.tv_usec = (_time_ms % 1000) * 1000;
	}

	bool CNetwork::run()
	{
		u32 t_clientsdone = 0;

		FD_ZERO(&m_fdset);

		u32 i, //counting m_clients
			c, //count of m_clients = m_clients.size()
			b = 0; //index of first selected m_clients-Member

		for (i = 0, c = m_conns.size(); i < c; ++i)
		{
			if (m_conns[i]->isConnected())
			{
				FD_SET(m_conns[i]->m_socket, &m_fdset);

				++t_clientsdone;
			}

			if (t_clientsdone == FD_SETSIZE ||
				(t_clientsdone > 0 &&
				i + 1 == c))
			{
				if (::select(0, &m_fdset, NULL, NULL, &m_select_time) == SOCKET_ERROR)
				{
					return false;
				}

				t_clientsdone = 0;

				while (b <= i)
				{
					if (FD_ISSET(m_conns[b]->m_socket, &m_fdset))
					{
						switch (m_conns[b]->getType())
						{
						case CONN_ACCEPTOR:
							{
								sockaddr t_clientinfo;
								memset(&t_clientinfo, 0, sizeof(t_clientinfo));
								socklen_t t_ci_size = sizeof(t_clientinfo);

								CNetClient *t_newclient = new CNetClient();
								t_newclient->m_socket = ::accept(m_conns[b]->m_socket, &t_clientinfo, &t_ci_size);
								t_newclient->m_connected = true;

								static char t_ip[256];
#ifdef _MSC_VER
								sprintf_s(t_ip, sizeof(t_ip), "%u.%u.%u.%u",
#else
								sprintf(t_ip, "%u.%u.%u.%u",
#endif
									static_cast<u32>(t_clientinfo.sa_data[2]) & 0xff,
									static_cast<u32>(t_clientinfo.sa_data[3]) & 0xff,
									static_cast<u32>(t_clientinfo.sa_data[4]) & 0xff,
									static_cast<u32>(t_clientinfo.sa_data[5]) & 0xff);
								t_newclient->m_ip = t_ip;
								t_newclient->m_port = m_conns[b]->getPort();

								m_conns.push_back(t_newclient);
								dynamic_cast<CNetAcceptor*>(m_conns[b])->m_newClients.push_back(t_newclient);
								break;
							}

						case CONN_CLIENT:
						case CONN_CONNECTOR:
							if (!dynamic_cast<CNetClient*>(m_conns[b])->receive())
							{
								m_conns[b]->close();
							}
							break;

                        default:
                            (void(0));
						}
					}

					++b;
				}

				FD_ZERO(&m_fdset);
			}
		}

		for (i = 0, c = m_conns.size(); i < c; ++i)
		{
			if (m_conns[i]->isFree())
			{
				delete m_conns[i];
				m_conns.erase_fast(i);
				--c;
			}
		}

		return true;
	}

	CNetAcceptor *CNetwork::createAcceptor(PORT _port)
	{
		CNetAcceptor *t_newAcceptor = new CNetAcceptor();
		if (t_newAcceptor->bind(_port))
		{
			m_conns.push_back(t_newAcceptor);
			return t_newAcceptor;
		}
		else
		{
			delete t_newAcceptor;
			return 0;
		}
	}

	CNetConnector *CNetwork::createConnector()
	{
		CNetConnector *t_newConnector = new CNetConnector();
		m_conns.push_back(t_newConnector);
		return t_newConnector;
	}

	s32 CNetwork::getLastError() const
	{
#ifdef OS_WINDOWS
		return WSAGetLastError();
#elif defined OS_LINUX
		return 0;
#endif
	}

	sdk::stringc CNetwork::getHostName() const
	{
		char t_buffer[256];

		if (gethostname(t_buffer, 256) != SOCKET_ERROR)
		{
			return t_buffer;
		}

		return "";
	}

}
