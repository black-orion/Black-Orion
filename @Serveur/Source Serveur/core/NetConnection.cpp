#include "NetConnection.h"


BEGIN_NAMESPACE_CORE
{

	//// NetConnection ////

	CNetConnection::CNetConnection()
		: m_free(false)
		, m_connected(false)
		, m_socket(0)
		, m_port(0)
	{
	}

	CNetConnection::~CNetConnection()
	{
		close();
	}

	SOCKET CNetConnection::getSocket() const
	{
		return m_socket;
	}

	PORT CNetConnection::getPort() const
	{
		return m_port;
	}

	bool CNetConnection::isFree() const
	{
		return m_free;
	}

	void CNetConnection::free()
	{
		m_free = true;
	}

	bool CNetConnection::isNew() const
	{
		return false;
	}

	bool CNetConnection::isConnected() const
	{
		return m_connected;
	}

	void CNetConnection::close()
	{
		if (isConnected())
		{
			::closesocket(m_socket);
			m_connected = false;
		}
	}


	//// NetAcceptor ////

	CNetAcceptor::CNetAcceptor()
	{
	}

	CNetAcceptor::~CNetAcceptor()
	{
	}

	bool CNetAcceptor::bind(PORT _port)
	{
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		m_port = _port;

		sockaddr_in t_addr;
		memset(&t_addr, 0, sizeof(sockaddr_in));
		t_addr.sin_family = AF_INET;
		t_addr.sin_port = htons(static_cast<u16>(m_port));
		t_addr.sin_addr.s_addr = htonl(INADDR_ANY);

		if (::bind(m_socket, (sockaddr*)&t_addr, sizeof(sockaddr_in)) == 0 &&
			::listen(m_socket, 64) == 0)
		{
			m_connected = true;
		}
		else
		{
			m_connected = false;
		}

		return m_connected;
	}

	bool CNetAcceptor::isNew() const
	{
		return !m_newClients.empty();
	}

	u32 CNetAcceptor::getNumberOfNewClients() const
	{
		return m_newClients.size();
	}

	CNetClient *CNetAcceptor::getNewClient(u32 _num)
	{
		if (_num < m_newClients.size())
		{
			return m_newClients[_num];
		}

		return 0;
	}

	CNetClient *CNetAcceptor::popClient()
	{
		if (m_newClients.empty())
			return 0;

		CNetClient *r_client = m_newClients.last();
		m_newClients.pop_back();
		return r_client;
	}


	//// NetClient ////

	CNetClient::CNetClient()
		: m_ip("0.0.0.0")
	{
	}

	CNetClient::~CNetClient()
	{
	}

	const char *CNetClient::getIp() const
	{
		return m_ip.c_str();
	}

	bool CNetClient::send(const CByteArray &_bytes)
	{
		return send(_bytes.data(), _bytes.size());
	}

	bool CNetClient::send(const Byte *_bytes, u32 _count)
	{
		u32 t_bytesSent = 0;
		s32 t_rc = 0;

		while (t_bytesSent < _count)
		{
			t_rc = ::send(m_socket, _bytes + t_bytesSent, static_cast<s32>(_count - t_bytesSent), 0);

			if (t_rc >= 0)
			{
				t_bytesSent += static_cast<u32>(t_rc);
			}
			else
			{
				return false;
			}
		}

		return true;
	}

	bool CNetClient::receive()
	{
		static const u32 BUF_SIZE = 1024;
		static Byte ts_buf[BUF_SIZE];

		static s32 r_code = 0;

		while (true)
		{
			r_code = recv(m_socket, (char*)ts_buf, BUF_SIZE, 0);

			if (r_code <= 0)
				return false;

			m_incoming.addBytes(ts_buf, r_code);

			if (r_code != BUF_SIZE)
				break;
		}

		return true;
	}

	bool CNetClient::isNew() const
	{
		return !m_incoming.empty();
	}

	CByteArray &CNetClient::incoming()
	{
		return m_incoming;
	}

	const CByteArray &CNetClient::incoming() const
	{
		return m_incoming;
	}


	//// NetConnector ////

	CNetConnector::CNetConnector()
	{
	}

	CNetConnector::~CNetConnector()
	{
	}

	bool CNetConnector::connect(const char *_host, PORT _port, u32 _retries)
	{
		FDASSERT(_host);

		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		m_port = _port;

		sockaddr_in t_addr;
		memset(&t_addr, 0, sizeof(sockaddr_in));
		t_addr.sin_family = AF_INET;
		t_addr.sin_port = htons(_port);
		t_addr.sin_addr.s_addr = inet_addr(_host);

		m_ip = _host;

		//_host is no IP address
		if (t_addr.sin_addr.s_addr == INADDR_NONE)
		{
			hostent *t_he = gethostbyname(_host);

			if (!t_he)
			{
				return false;
			}

			memcpy(&(t_addr.sin_addr), t_he->h_addr_list[0], 4);
		}

		m_connected = (::connect(m_socket, (sockaddr*)&t_addr, sizeof(sockaddr)) != SOCKET_ERROR);
		return m_connected;
	}

}
