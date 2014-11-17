#ifndef PACKETRECEIVER_H
#define PACKETRECEIVER_H


#include "WorldMain.h"


class IWorldServer;
class IWorldPlayer;
class IPlayerObject;


class IPacketReceiver
{
public:

	IPacketReceiver(IWorldServer *_server);

	bool handlePacket(IWorldPlayer *_player);

private:

	enum
	{
		BUF_SIZE = 1024
	};

	char m_buffer[BUF_SIZE];

	IWorldServer *m_server;

	//command handlers
	bool _login(IWorldPlayer *_player);

	bool _chat(IWorldPlayer *_player);

	bool _attack(IWorldPlayer *_player);

	bool _mouseControl(IWorldPlayer *_player);

	bool _keyboardControl(IWorldPlayer *_player);

	bool _motion(IWorldPlayer *_player);

	bool _invMoveItem(IWorldPlayer *_player);

	bool _invUnequip(IWorldPlayer *_player);

	bool _invDropItem(IWorldPlayer *_player);

	bool _invDeleteItem(IWorldPlayer *_player);

	bool _useItem(IWorldPlayer *_player);

	bool _targetChange(IWorldPlayer *_player);

	bool _follow(IWorldPlayer *_player);

	bool _querygetpos(IWorldPlayer *_player);

	bool _getpos(IWorldPlayer *_player);

	bool _talkToNpc(IWorldPlayer *_player);

	bool _tradeNpc(IWorldPlayer *_player);

	bool _buyNpc(IWorldPlayer *_player);

	bool _sellNpc(IWorldPlayer *_player);

	bool _upgrade(IWorldPlayer *_player);

	bool _buffEvent(IWorldPlayer *_player);

	bool _addFriend(IWorldPlayer *_player);

	bool _addFriendPerClick(IWorldPlayer *_player);

	bool _messengerStatus(IWorldPlayer *_player);

	bool _statChange(IWorldPlayer *_player);

	bool _skillChange(IWorldPlayer *_player);

	bool _specialOptionScroll(IWorldPlayer *_player);

	bool _request_ranking_guild(IWorldPlayer *_player);

	bool _shopAddItem(IWorldPlayer *_player);

	bool _shopRemoveItem(IWorldPlayer *_player);

	bool _shopChat(IWorldPlayer *_player);

	bool _shopOpen(IWorldPlayer *_player);

	bool _shopClose(IWorldPlayer *_player);

	bool _shopChatEnter(IWorldPlayer *_player);

	bool _shopChatLeave(IWorldPlayer *_player);

	bool _in_GuildCombat(IWorldPlayer *_player);

	bool _mailBox(IWorldPlayer *_player);

	bool _mailRead(IWorldPlayer *_player);

	bool _mailTakeMoney(IWorldPlayer *_player);

	bool _mailTakeItem(IWorldPlayer *_player);

	bool _sendMail(IWorldPlayer *_player);

	bool _mailDelete(IWorldPlayer *_player);

	bool _characterInfos(IWorldPlayer *_player);

	bool _partyInvitation(IWorldPlayer *_player);

	bool _cheer(IWorldPlayer *_player);

	bool _viewEquipment(IWorldPlayer *_player);

	bool _trade(IWorldPlayer *_player);

	bool _partyAccept(IWorldPlayer *_player);

	bool _partyReject(IWorldPlayer *_player);

	bool _loadStar(IWorldPlayer *_player);

	bool _unknown_0(IWorldPlayer *_player);

	bool _unknown_1(IWorldPlayer *_player);

};


#endif //PACKETRECEIVER_H
