#include "CommandScriptEnv.h"
#include "PlayerObject.h"
#include "WorldPlayer.h"
#include "ChatHandler.h"
#include "WorldSettings.h"
#include "PlayerScriptInterface.h"
#include "../shared/Log.h"
#include "../shared/Account.h"
#include "../shared/Character.h"
#include "../shared/PacketCreator.h"


/// ICommandScript ///
//////////////////////

CArray<sdk::stringc> ICommandScript::ms_args;

IPlayerScriptInterface ICommandScript::ms_playerInterface;

ICommandScript::ICommandScript(asIScriptModule *_module, s32 _functionId, const char *_name,
							   const char *_fileName, IAccount::E_ACCESS_LEVEL _accLvl)
	: m_module(_module)
	, m_entryFunction(_functionId)
	, m_accessLevel(_accLvl)
	, m_name(_name)
	, m_fileName(_fileName)
{
	FDASSERT(m_module);
}

IAccount::E_ACCESS_LEVEL ICommandScript::getAccessLevel() const
{
	return m_accessLevel;
}

const char *ICommandScript::getName() const
{
	return m_name.c_str();
}

bool ICommandScript::execute(const PlayerObjectPtr &_user, const char *_arguments)
{
	FDASSERT(_user);
	FDASSERT(_arguments);

	asIScriptContext *t_ctx = ICommandScriptEnv::instance()->getContext();

	s32 t_rc = t_ctx->Prepare(m_entryFunction);
	if (t_rc < 0)
	{
		return false;
	}

	ms_playerInterface.setPlayer(_user);

	u32 m_timeOut = CTime::system() + 500;

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
		return true;
	}

	ms_playerInterface.setPlayer(0);
	return false;
}

const PlayerObjectPtr &ICommandScript::currentPlayer()
{
	return ms_playerInterface.getPlayer();
}

IPlayerScriptInterface *ICommandScript::playerInterface()
{
	return &ms_playerInterface;
}

const CArray<sdk::stringc> &ICommandScript::arguments()
{
	return ms_args;
}


/// ICommandScriptEnvironment ///
/////////////////////////////////

void messageCallback(const asSMessageInfo *msg, void *param);
void lineCallback(asIScriptContext *ctx, u32 *timeOut);

ICommandScriptEnv ICommandScriptEnv::ms_instance;

ICommandScriptEnv::ICommandScriptEnv()
	: m_chat(0)
	, m_context(0)
	, m_engine(0)
{
}

ICommandScriptEnv::~ICommandScriptEnv()
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

IPlayerScriptInterface &command_getUser()
{
	FDASSERT(ICommandScript::playerInterface());

	return *ICommandScript::playerInterface();
}

bool ICommandScriptEnv::loadScripts(IChatHandler *_chat, IWorldSettings *_settings)
{
	FDASSERT(_settings);
	FDASSERT(_chat);

	m_chat = _chat;

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
	bool t_success = IPlayerScriptInterface::registerAll(m_engine) &&

		m_engine->RegisterGlobalFunction("IPlayer &getUser()",
		asFUNCTION(command_getUser), asCALL_CDECL) >= 0;

	if (!t_success)
	{
		return false;
	}

	//load the script list
	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	if (t_file.open(_settings->Commands.ScriptDefinitionFileName.c_str(), true))
	{
		char t_name[256];
		char t_fileName[256];
		s32 t_accessLevel = 0;

		stringstream t_sstr;

		while (!t_file.end())
		{
			//command name
			t_file.readNext(t_name, sizeof(t_name));

			//script file name
			t_file.readString(t_fileName, sizeof(t_fileName));

			//access level
			t_accessLevel = IAccount::accessLevel(t_file.readInt());

			if (getCommand(t_name))
			{
				Log::write(LOG_ERROR, "Script command \"%s\" is already defined!", t_name);
				continue;
			}

			t_sstr.str("");
			t_sstr << _settings->Commands.ScriptFolder << t_fileName;

			//if (m_builder.BuildScriptFromFile(m_engine, t_fileName, t_sstr.str().c_str()) < 0)
			if (m_builder.StartNewModule(m_engine, t_fileName) < 0 ||
                m_builder.AddSectionFromFile(t_sstr.str().c_str()) < 0 ||
                m_builder.BuildModule() < 0)
			{
				Log::write(LOG_ERROR, "Could not build command script file \"%s\"!", t_sstr.str().c_str());
				continue;
			}

			asIScriptModule *t_module = m_engine->GetModule(t_fileName);

			s32 t_entryFunction = t_module->GetFunctionIdByDecl("void main()");

			if (t_entryFunction >= 0)
			{
				ICommandScript *t_script =
					new ICommandScript(t_module, t_entryFunction, t_name, t_fileName,
					IAccount::accessLevel(t_accessLevel));

				m_scripts.push_back(t_script);
			}
			else
			{
				Log::write(LOG_ERROR, "Did not find 'void main()' in command script file \"%s\"!",
					t_sstr.str().c_str());
			}
		}

		if (!m_scripts.empty())
		{
			Log::write(LOG_SUCCESS, "Loaded %u command scripts", m_scripts.size());
		}

		return true;
	}

	return false;
}

bool ICommandScriptEnv::command(const PlayerObjectPtr &_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	static char ts_cmd[256];

	s32 t_n = 0;
	sscanf(_message, "%s%n", ts_cmd, &t_n);

	Log::write(LOG_DEBUG, "Script command '%s'", ts_cmd);

	ICommandScript *t_script = getCommand(ts_cmd);

	if (t_script)
	{
		if (_player->getPlayer()->getAccount()->getAccessLevel() >= t_script->getAccessLevel())
		{
			return t_script->execute(_player, _message + t_n);
		}
		else
		{
			_player->getPlayer()->getClient()->send(IPacketCreator::greenText("Your access level is too low"));
		}
	}
	else
	{
		_player->getPlayer()->getClient()->send(IPacketCreator::greenText("Unknown command"));
	}

	return false;
}

asIScriptEngine *ICommandScriptEnv::getEngine()
{
	return m_engine;
}

asIScriptContext *ICommandScriptEnv::getContext()
{
	return m_context;
}

IChatHandler *ICommandScriptEnv::getChatHandler()
{
	return m_chat;
}

ICommandScript *ICommandScriptEnv::getCommand(const char *_name)
{
	FDASSERT(_name);

	FOR_EACH (m_scripts, i)
	{
		if (xstricmp(m_scripts[i]->getName(), _name) == 0)
		{
			return m_scripts[i];
		}
	}

	return 0;
}

ICommandScriptEnv *ICommandScriptEnv::instance()
{
	return &ms_instance;
}
