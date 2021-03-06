#include "NpcDialogEnv.h"
#include "WorldSettings.h"
#include "WorldPlayer.h"
#include "PlayerObject.h"
#include "NpcObject.h"
#include "../shared/PacketCreator.h"
#include "../shared/Log.h"


/// INpcDialogScript ///
////////////////////////

INpcDialogScript *INpcDialogScript::ms_currScript = 0;

PlayerObjectPtr INpcDialogScript::ms_currPlayerObj;

IPlayerScriptInterface INpcDialogScript::ms_playerInterface;

INpcDialogScript::INpcDialogScript(asIScriptModule *_module, const char *_fileName, s32 _onDialogActionId)
	: m_module(_module)
	, m_npc(0)
	, m_fileName(_fileName)
	, m_timeOut(0)
	, m_onDialogActionId(_onDialogActionId)
{
}

INpcDialogScript::~INpcDialogScript()
{
}

bool INpcDialogScript::init(INpcObject *_npc)
{
	m_npc = _npc;

	return (m_npc != 0);
}

INpcObject *INpcDialogScript::getNpc()
{
	return m_npc;
}

asIScriptModule *INpcDialogScript::getModule()
{
	return m_module;
}

const char *INpcDialogScript::getFileName() const
{
	return m_fileName.c_str();
}

bool INpcDialogScript::OnDialogAction(const PlayerObjectPtr &_pObj, const char *_str, s32 _action)
{
	FDASSERT(_pObj);
	FDASSERT(_str);

	ms_currPlayerObj = _pObj;
	ms_currScript = this;

	asIScriptContext *t_ctx = INpcDialogEnv::instance()->getContext();

	s32 t_rc = t_ctx->Prepare(m_onDialogActionId);
	if (t_rc < 0)
	{
		return false;
	}

	ms_playerInterface.setPlayer(ms_currPlayerObj);

	std::string t_argStr = _str;
	t_ctx->SetArgObject(0, &t_argStr);
	t_ctx->SetArgDWord(1, _action);

	m_timeOut = CTime::system() + 500;

	t_rc = t_ctx->Execute();

	if (t_rc != asEXECUTION_FINISHED)
	{
		if (t_rc == asEXECUTION_ABORTED)
		{
			printf("Aborted.\n");
		}
		else if (t_rc == asEXECUTION_EXCEPTION )
		{
			printf("The script ended with an exception.\n");

			/*int funcID = t_ctx->GetExceptionFunction();
			asIScriptFunction *func = t_engine->GetFunctionDescriptorById(funcID);
			cout << "func: " << func->GetDeclaration() << endl;
			cout << "modl: " << func->GetModuleName() << endl;
			cout << "sect: " << func->GetScriptSectionName() << endl;
			cout << "line: " << t_ctx->GetExceptionLineNumber() << endl;
			cout << "desc: " << t_ctx->GetExceptionString() << endl;*/
		}
		else
		{
			printf("The script ended for some unforeseen reason %d\n", t_rc);
		}
	}
	else
	{
		ms_playerInterface.setPlayer(0);
		return t_ctx->GetReturnDWord() != 0;
	}

	ms_playerInterface.setPlayer(0);
	return false;
}

INpcDialogScript *INpcDialogScript::currentScript()
{
	return ms_currScript;
}

const PlayerObjectPtr &INpcDialogScript::currentPlayer()
{
	return ms_currPlayerObj;
}

IPlayerScriptInterface *INpcDialogScript::playerInterface()
{
	return &ms_playerInterface;
}


/// INpcDialogEnv ///
/////////////////////////////

void messageCallback(const asSMessageInfo *msg, void *param);
void lineCallback(asIScriptContext *ctx, u32 *timeOut);

INpcDialogEnv INpcDialogEnv::ms_instance;

INpcDialogEnv::INpcDialogEnv()
	: m_engine(0)
	, m_context(0)
	, m_settings(0)
{
}

INpcDialogEnv::~INpcDialogEnv()
{
	FOR_EACH (m_scripts, i)
	{
		delete m_scripts[i];
	}

	if (m_engine)
	{
		m_engine->Release();
	}

	if (m_context)
	{
		m_context->Release();
	}
}

asIScriptEngine *INpcDialogEnv::getEngine()
{
	return m_engine;
}

asIScriptContext *INpcDialogEnv::getContext()
{
	return m_context;
}

bool checkParams(const char *_function, asIScriptGeneric *_param, s32 _req)
{
	FDASSERT(_param);

	if (_param->GetArgCount() == _req)
	{
		return true;
	}
	else
	{
		Log::write(LOG_WARNING, "NPC dialog script: %s does not take %d arguments (%d required)!",
			_function, _param->GetArgCount(), _req);
		return false;
	}
}

void dialog_showText(asIScriptGeneric *_param)
{
	if (!checkParams("showText()", _param, 1))
		return;

	const PlayerObjectPtr &t_pObj = INpcDialogScript::currentPlayer();
	INpcObject *t_npc = INpcDialogScript::currentScript()->getNpc();

	FDASSERT(t_pObj);
	FDASSERT(t_npc);

	t_pObj->getPlayer()->getClient()->send(
		IPacketCreator::npcDialogText(t_npc, (*(string*)_param->GetArgObject(0)).c_str()));
}

void dialog_addLink(asIScriptGeneric *_param)
{
	if (!checkParams("addLink()", _param, 3))
		return;

	const PlayerObjectPtr &t_pObj = INpcDialogScript::currentPlayer();
	INpcObject *t_npc = INpcDialogScript::currentScript()->getNpc();

	FDASSERT(t_pObj);
	FDASSERT(t_npc);

	const char *t_text = (*(string*)_param->GetArgObject(0)).c_str();
	const char *t_internal = (*(string*)_param->GetArgObject(1)).c_str();
	s32 t_action = _param->GetArgDWord(2);

	t_pObj->getPlayer()->getClient()->send(
		IPacketCreator::npcDialogLink(t_npc, t_text, t_internal, t_action, 0));
}

void dialog_buff(asIScriptGeneric *_param)
{
	if (!checkParams("buff()", _param, 3))
		return;

	const PlayerObjectPtr &t_pObj = INpcDialogScript::currentPlayer();
	INpcObject *t_npc = INpcDialogScript::currentScript()->getNpc();

	FDASSERT(t_pObj);
	FDASSERT(t_npc);

	ID  t_buff = _param->GetArgDWord(0);
	s32 t_lvl = _param->GetArgDWord(1);
	s32 t_temps = _param->GetArgDWord(2);

	t_pObj->getPlayer()->getClient()->send(
		IPacketCreator::buff(t_pObj, t_buff, t_lvl, t_temps));

}

void dialog_addButton(asIScriptGeneric *_param)
{
	if (!checkParams("addButton()", _param, 3))
		return;

	const PlayerObjectPtr &t_pObj = INpcDialogScript::currentPlayer();
	INpcObject *t_npc = INpcDialogScript::currentScript()->getNpc();

	FDASSERT(t_pObj);
	FDASSERT(t_npc);

	const char *t_text = (*(string*)_param->GetArgObject(0)).c_str();
	const char *t_internal = (*(string*)_param->GetArgObject(1)).c_str();
	s32 t_action = _param->GetArgDWord(2);

	t_pObj->getPlayer()->getClient()->send(
		IPacketCreator::npcDialogButton(t_npc, t_text, t_internal, t_action, 0));
}

void dialog_clearDialog(asIScriptGeneric *_param)
{
	if (!checkParams("clearDialog()", _param, 0))
		return;

	const PlayerObjectPtr &t_pObj = INpcDialogScript::currentPlayer();
	INpcObject *t_npc = INpcDialogScript::currentScript()->getNpc();

	FDASSERT(t_pObj);
	FDASSERT(t_npc);

	t_pObj->getPlayer()->getClient()->send(
		IPacketCreator::npcDialogClear(t_npc));
}

void dialog_closeDialog(asIScriptGeneric *_param)
{
	if (!checkParams("closeDialog()", _param, 0))
		return;

	const PlayerObjectPtr &t_pObj = INpcDialogScript::currentPlayer();
	INpcObject *t_npc = INpcDialogScript::currentScript()->getNpc();

	FDASSERT(t_pObj);
	FDASSERT(t_npc);

	t_pObj->getPlayer()->getClient()->send(
		IPacketCreator::npcDialogClose(t_npc));
}

IPlayerScriptInterface &dialog_getUser(/*asIScriptGeneric *_param*/)
{
	FDASSERT(INpcDialogScript::playerInterface());

	return *INpcDialogScript::playerInterface();
}

bool INpcDialogEnv::init(IWorldSettings *_settings)
{
	FDASSERT(_settings);

	m_settings = _settings;

	m_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

	if (!m_engine ||
		m_engine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_CDECL) < 0)
	{
		return false;
	}

	m_context = m_engine->CreateContext();

	if (!m_context)
	{
		return false;
	}

	RegisterScriptString(m_engine);

	//register functions
	if (m_engine->RegisterGlobalFunction("void showText(const string &text)",
		asFUNCTION(dialog_showText), asCALL_GENERIC) >= 0 &&

		m_engine->RegisterGlobalFunction("void addLink(const string &text, const string &internal, int action)",
		asFUNCTION(dialog_addLink), asCALL_GENERIC) >= 0 &&

		m_engine->RegisterGlobalFunction("void addButton(const string &text, const string &internal, int action)",
		asFUNCTION(dialog_addButton), asCALL_GENERIC) >= 0 &&

		m_engine->RegisterGlobalFunction("void buff(int buff, int lvl, int temps)",
		asFUNCTION(dialog_buff), asCALL_GENERIC) >= 0 &&

		m_engine->RegisterGlobalFunction("void clearDialog()",
		asFUNCTION(dialog_clearDialog), asCALL_GENERIC) >= 0 &&

		m_engine->RegisterGlobalFunction("void closeDialog()",
		asFUNCTION(dialog_closeDialog), asCALL_GENERIC) >= 0)
	{
		if (IPlayerScriptInterface::registerAll(m_engine))
		{
			return (
				m_engine->RegisterGlobalFunction("IPlayer &getUser()",
				asFUNCTION(dialog_getUser), asCALL_CDECL) >= 0);
		}
	}

	return false;
}

INpcDialogScript *INpcDialogEnv::loadScript(const char *_fileName)
{
	FDASSERT(_fileName);

	std::stringstream t_sstr;
	t_sstr << m_settings->Data.NpcDialogFolder.c_str();
	t_sstr << _fileName;

	//if (m_builder.BuildScriptFromFile(m_engine, _fileName, t_sstr.str().c_str()) < 0)
	if (m_builder.StartNewModule(m_engine, _fileName) < 0 ||
        m_builder.AddSectionFromFile(t_sstr.str().c_str()) < 0 ||
        m_builder.BuildModule() < 0)
	{
		return 0;
	}

	asIScriptModule *t_module = m_engine->GetModule(_fileName);

	s32 t_onDialogActionId =
		t_module->GetFunctionIdByDecl("int OnDialogAction(const string &str, int action)");

	if (t_onDialogActionId < 0)
	{
		return 0;
	}

	INpcDialogScript *t_newScript = new INpcDialogScript(t_module, _fileName, t_onDialogActionId);
	m_scripts.push_back(t_newScript);
	return t_newScript;
}

u32 INpcDialogEnv::getScriptCount() const
{
	return m_scripts.size();
}

INpcDialogEnv *INpcDialogEnv::instance()
{
	return &ms_instance;
}

void messageCallback(const asSMessageInfo *msg, void *param)
{
	const char *type = "ERR ";
	if (msg->type == asMSGTYPE_WARNING)
		type = "WARN";
	else if (msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";

	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

void lineCallback(asIScriptContext *ctx, u32 *timeOut)
{
	if (*timeOut < CTime::system())
	{
		ctx->Suspend(); //or Abort
	}
}
