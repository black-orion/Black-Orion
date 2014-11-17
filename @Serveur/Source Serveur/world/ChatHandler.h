#ifndef CHATHANDLER_H
#define CHATHANDLER_H


#include "WorldMain.h"
#include "WorldSettings.h"
#include "CommandScriptEnv.h"


class IWorldServer;
class IWorldPlayer;
class IWorldDataManager;


class IChatHandler
{
public:

	IChatHandler();
	~IChatHandler();

	bool init(IWorldServer *_server);
	void chat(IWorldPlayer *_player, const char *_message);
	bool shout(IWorldPlayer *_player, const char *_msg);
	bool notice(IWorldPlayer *_player, const char *_msg);

private:

	IWorldServer *m_pserver;

	enum
	{
		BUF_COMMAND_SIZE = 256,
		BUF_SIZE = 2048
	};

	char m_command[BUF_COMMAND_SIZE];

	char m_buffer[BUF_SIZE];

	s32 m_command_size;

	typedef void (IChatHandler::*CommandFunction)(IWorldPlayer *, const char *);

	struct CommandHandle
	{
		IWorldSettings::CommandSettings::Cmd *Command;
		CommandFunction Function;

		CommandHandle()
			: Command(0)
			, Function(0)
		{
		}

		CommandHandle(IWorldSettings::CommandSettings::Cmd *_cmd, const CommandFunction &_function)
			: Command(_cmd)
			, Function(_function)
		{
		}
	};

	CArray<CommandHandle> m_cmdHandles;

	IWorldSettings *_getSettings();

	IWorldDataManager *_getWorldDataMngr();

	bool _command(IWorldCommand &_cmd, const char *_str, IWorldPlayer *_player, bool &_out_usable);

	//Flyff commands
	void _fCmd_Shout(IWorldPlayer *_player, const char *_message);
	void _fCmd_Say(IWorldPlayer *_player, const char *_message);
	void _fCmd_Whisper(IWorldPlayer *_player, const char *_message);
	void _fCmd_PartyInvite(IWorldPlayer *_player, const char *_message);
	void _fCmd_Teleport(IWorldPlayer *_player, const char *_message);

	//blackorion commands
	void _sCmd_Info(IWorldPlayer *_player, const char *_message);
	void _sCmd_Coin(IWorldPlayer *_player, const char *_message);
	void _sCmd_Dice(IWorldPlayer *_player, const char *_message);
	void _sCmd_Penya(IWorldPlayer *_player, const char *_message);
	void _sCmd_Level(IWorldPlayer *_player, const char *_message);
	void _sCmd_AccessLevel(IWorldPlayer *_player, const char *_message);
	void _sCmd_ClearInv(IWorldPlayer *_player, const char *_message);
	void _sCmd_DropInv(IWorldPlayer *_player, const char *_message);
	void _sCmd_Shout(IWorldPlayer *_player, const char *_message);
	void _sCmd_Item(IWorldPlayer *_player, const char *_message);
	void _sCmd_Stat(IWorldPlayer *_player, const char *_message);
	void _sCmd_Notice(IWorldPlayer *_player, const char *_message);
	void _sCmd_Pos(IWorldPlayer *_player, const char *_message);
	void _sCmd_Name(IWorldPlayer *_player, const char *_message);
	void _sCmd_Exp(IWorldPlayer *_player, const char *_message);
	void _sCmd_AddExp(IWorldPlayer *_player, const char *_message);
	void _sCmd_Kill(IWorldPlayer *_player, const char *_message);
	void _sCmd_Job(IWorldPlayer *_player, const char *_message);
	void _sCmd_Points(IWorldPlayer *_player, const char *_message);
	void _sCmd_GetPoints(IWorldPlayer *_player, const char *_message);
	void _sCmd_PlayerInfo(IWorldPlayer *_player, const char *_message);
	void _sCmd_Immortal(IWorldPlayer *_player, const char *_message);
	void _sCmd_OneHit(IWorldPlayer *_player, const char *_message);
	void _sCmd_God(IWorldPlayer *_player, const char *_message);
	void _sCmd_SetAccessLevel(IWorldPlayer *_player, const char *_message);
	void _sCmd_Mob(IWorldPlayer *_player, const char *_message);
	void _sCmd_CreateSpawn(IWorldPlayer *_player, const char *_message);
	void _sCmd_CreateItemList(IWorldPlayer *_player, const char *_message);
	void _sCmd_Place(IWorldPlayer *_player, const char *_message);
	void _sCmd_Ban(IWorldPlayer *_player, const char *_message);
	void _sCmd_PvpPoints(IWorldPlayer *_player, const char *_message);
	void _sCmd_PkPoints(IWorldPlayer *_player, const char *_message);
	void _sCmd_Disposition(IWorldPlayer *_player, const char *_message);
	void _sCmd_Weather(IWorldPlayer *_player, const char *_message);
	void _sCmd_Revive(IWorldPlayer *_player, const char *_message);

};


#endif //CHATHANDLER_H
