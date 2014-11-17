#ifndef NPCDIALOGENVIRONMENT_H
#define NPCDIALOGENVIRONMENT_H


#include "WorldMain.h"
#include "PlayerScriptInterface.h"

#include "../libs/angelscript/include/angelscript.h"
#include "../libs/angelscript/add_on/scriptstring/scriptstring.h"
#include "../libs/angelscript/add_on/scriptbuilder/scriptbuilder.h"


class IWorldSettings;
class IPlayerObject;
class INpcObject;


class INpcDialogScript
{
public:

	INpcDialogScript(asIScriptModule *_module, const char *_fileName, s32 _onDialogActionId);

	~INpcDialogScript();

	bool init(INpcObject *_npc);

	INpcObject *getNpc();

	asIScriptModule *getModule();

	const char *getFileName() const;

	bool OnDialogAction(const PlayerObjectPtr &_pObj, const char *_str, s32 _action);

	static INpcDialogScript *currentScript();

	static const PlayerObjectPtr &currentPlayer();

	static IPlayerScriptInterface *playerInterface();

private:

	INpcObject *m_npc;

	asIScriptModule *m_module;

	sdk::stringc m_fileName;

	TimeMs m_timeOut;

	s32 m_onDialogActionId;

	static INpcDialogScript *ms_currScript;

	static PlayerObjectPtr ms_currPlayerObj;

	static IPlayerScriptInterface ms_playerInterface;

};


class INpcDialogEnv
{
public:

	INpcDialogEnv();

	~INpcDialogEnv();

	asIScriptEngine *getEngine();

	asIScriptContext *getContext();

	bool init(IWorldSettings *_settings);

	INpcDialogScript *loadScript(const char *_fileName);

	u32 getScriptCount() const;

	static INpcDialogEnv *instance();

private:

	asIScriptEngine *m_engine;

	asIScriptContext *m_context;

	CScriptBuilder m_builder;

	IWorldSettings *m_settings;

	CArray<INpcDialogScript*> m_scripts;

	static INpcDialogEnv ms_instance;

};


#endif //NPCDIALOGENVIRONMENT_H