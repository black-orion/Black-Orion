#ifndef CORE_NETWORK_H
#define CORE_NETWORK_H


#include "CoreBase.h"
#include "Array.h"
#include "String.h"


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

	class CNetConnection;
	class CNetAcceptor;
	class CNetClient;
	class CNetConnector;
	class CNetCaptor;


	class CNetwork
	{
	public:

		CNetwork();

		~CNetwork();

		bool startup();

		bool isStarted() const
		{
			return m_started;
		}

		bool shutdown();

		void setWaitingTime(TimeMs _time);

		bool run();

		CNetAcceptor *createAcceptor(PORT _port);

		CNetConnector *createConnector();

		s32 getLastError() const;

		sdk::stringc getHostName() const;

	private:

		enum
		{
			SELECT_MAX_CONNECTIONS = FD_SETSIZE
		};

		bool m_started;

		fd_set m_fdset;

		timeval m_select_time;

		CArray<CNetConnection*> m_conns;

	};

}


#endif //CORE_NETWORK_H
