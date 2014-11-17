#ifndef LOGINISC_H
#define LOGINISC_H


#include "LoginMain.h"
#include "LoginSettings.h"


class ILoginServer;


class ILoginISC
{
public:

	struct ServerList
	{
		struct Channel
		{
			CNetClient *Client;

			ID Id;

			sdk::stringc Name;

			sdk::stringc IP;

			s32 CurrentPlayers;

			s32 MaxPlayers;

			Channel(CNetClient *_client = 0, ID _id = 0, const char *_name = "", const char *_ip = "")
				: Client(_client)
				, Id(_id)
				, Name(_name)
				, IP(_ip)
				, CurrentPlayers(0)
				, MaxPlayers(16)
			{
			}
		};

		struct Cluster
		{
			CNetClient *Client;

			ID Id;

			sdk::stringc Name;

			sdk::stringc IP;

			u32 MaxChannels;

			CArray<Channel> Channels;

			Cluster(CNetClient *_client = 0, ID _id = 0, const char *_name = "", const char *_ip = "",
				u32 _maxchannels = 0)
				: Client(_client)
				, Id(_id)
				, Name(_name)
				, IP(_ip)
				, MaxChannels(_maxchannels)
			{
			}

			void disconnectChannels();
		};

		u32 MaxClusters;

		CArray<Cluster> Clusters;

		ServerList()
			: MaxClusters(1)
		{
		}

		s32 getServerCount() const;
	};

	ILoginISC(ILoginISCSettings *_settings, ILoginServer *_server);

	~ILoginISC();

	bool init(CNetwork *_network);

	bool run();

	ServerList &getServerList();

private:

	//Settings
	ILoginISCSettings *m_settings;

	//Server
	ILoginServer *m_pserver;

	//Clients and Acceptor
	CNetAcceptor *m_acceptor;

	struct Unauthorized
	{
		CNetClient *Client;

		bool Remove;

		Unauthorized(CNetClient *_client = 0)
			: Client(_client)
			, Remove(false)
		{
		}
	};

	CArray<Unauthorized> m_unauths; //unauthorized clients

	ServerList m_serverlist;

	//General connections
	bool _handlePacket(Unauthorized *_unauth);

	bool _cmdHandler_auth(Unauthorized *_unauth);

	//Clusters
	bool _handlePacket(ServerList::Cluster *_cluster);

	//Channels
	bool _handlePacket(ServerList::Channel *_channel);

	bool _cmdHandler_channelInfos(ServerList::Channel *_channel);

};


#endif //LOGINISC_H
