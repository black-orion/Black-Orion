#ifndef H_FNETWORKCONNECTION
#define H_FNETWORKCONNECTION


#include "CoreBase.h"
#include "Array.h"
#include "ByteArray.h"
#include "String.h"
#include "Time.h"


#ifdef OS_WINDOWS

#include <winsock2.h>
#define socklen_t int

#elif defined OS_LINUX

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#ifndef SOCKET
#define SOCKET int
#endif
#ifndef closesocket
#define closesocket close
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif

#endif


BEGIN_NAMESPACE_CORE
{
	class CNetwork;

	class CNetConnection;
	class CNetAcceptor;
	class CNetClient;
	class CNetConnector;


	enum E_CONNECTION_TYPE
	{
		CONN_BASE,
		CONN_ACCEPTOR,
		CONN_CLIENT,
		CONN_CONNECTOR
	};

	class CNetConnection
	{
	public:

		CNetConnection();

		virtual ~CNetConnection();

		virtual E_CONNECTION_TYPE getType() const = 0;

		SOCKET getSocket() const;

		PORT getPort() const;

		bool isFree() const;

		void free();

		bool isNew() const;

		bool isConnected() const;

		void close();

	protected:

		friend class CNetwork;

		bool m_free;

		bool m_connected;

		SOCKET m_socket;

		PORT m_port;

	};


	class CNetAcceptor : public CNetConnection
	{
	public:

		CNetAcceptor();

		~CNetAcceptor();

		E_CONNECTION_TYPE getType() const
		{
			return CONN_ACCEPTOR;
		}

		bool bind(PORT _port);

		bool isNew() const;

		u32 getNumberOfNewClients() const;

		CNetClient *getNewClient(u32 _num);

		CNetClient *popClient();

	private:

		friend class CNetwork;

		CArray<CNetClient*> m_newClients;

	};


	class CNetClient : public CNetConnection
	{
	public:

		CNetClient();

		~CNetClient();

		E_CONNECTION_TYPE getType() const
		{
			return CONN_CLIENT;
		}

		const char *getIp() const;

		bool send(const CByteArray &_bytes);

		bool send(const Byte *_bytes, u32 _count);

		bool receive();

		bool isNew() const;

		CByteArray &incoming();

		const CByteArray &incoming() const;

	protected:

		friend class CNetwork;

		sdk::stringc m_ip;

		CByteArray m_incoming;

	};


	class CNetConnector : public CNetClient
	{
	public:

		CNetConnector();

		~CNetConnector();

		E_CONNECTION_TYPE getType() const
		{
			return CONN_CONNECTOR;
		}

		bool connect(const char *_host, PORT _port, u32 _retries = 0);

	private:

		friend class CNetwork;

	};

}


#endif //H_FNETWORKCONNECTION
