#ifndef COMMANDSCRIPTENV_H
#define COMMANDSCRIPTENV_H


#include "WorldMain.h"
#include "PlayerScriptInterface.h"
#include "../shared/Account.h"

#include "../libs/angelscript/include/angelscript.h"
#include "../libs/angelscript/add_on/scriptstring/scriptstring.h"
#include "../libs/angelscript/add_on/scriptbuilder/scriptbuilder.h"


class ICommandScriptEnv;
class IPlayerObject;
class IChatHandler;
class IWorldSettings;
class IWorldPlayer;


class ICommandScript
{
public:

	ICommandScript(asIScriptModule *_module, s32 _functionId, const char *_name, const char *_fileName,
		IAccount::E_ACCESS_LEVEL _accLvl);

	IAccount::E_ACCESS_LEVEL getAccessLevel() const;

	const char *getName() const;

	bool execute(const PlayerObjectPtr &_user, const char *_arguments);

	static const PlayerObjectPtr &currentPlayer();

	static IPlayerScriptInterface *playerInterface();

	static const CArray<sdk::stringc> &arguments();

private:

	asIScriptModule *m_module;

	s32 m_entryFunction;

	sdk::stringc m_name;

	sdk::stringc m_fileName;

	IAccount::E_ACCESS_LEVEL m_accessLevel;

	static CArray<sdk::stringc> ms_args;

	static IPlayerScriptInterface ms_playerInterface;

};


class ICommandScriptEnv
{
public:

	ICommandScriptEnv();

	~ICommandScriptEnv();

	bool loadScripts(IChatHandler *_chat, IWorldSettings *_settings);

	bool command(const PlayerObjectPtr &_player, const char *_message);

	asIScriptEngine *getEngine();

	asIScriptContext *getContext();

	IChatHandler *getChatHandler();

	ICommandScript *getCommand(const char *_name);

	static ICommandScriptEnv *instance();

private:

	asIScriptEngine *m_engine;

	asIScriptContext *m_context;

	CScriptBuilder m_builder;

	IChatHandler *m_chat;

	CArray<ICommandScript*> m_scripts;

	static ICommandScriptEnv ms_instance;

};


#endif //COMMANDSCRIPTENV_H
