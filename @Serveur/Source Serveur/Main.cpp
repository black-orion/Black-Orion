#include "Main.h"


#ifdef _MSC_VER

#ifdef SETTING_MYSQL_STATIC_LINK
#pragma comment(lib, "libs/mysql/mysqlclient.lib")
#else
#pragma comment(lib, "libs/mysql/libmysql.lib")
#endif

#ifdef SDEBUG
#pragma comment(lib, "libs/angelscript/lib/angelscriptd.lib")
#else
#pragma comment(lib, "libs/angelscript/lib/angelscript.lib")
#endif

#endif


#include "login/LoginServer.h"
#include "char/CharServer.h"
#include "world/WorldServer.h"
#include "shared/Log.h"
#include "shared/PacketCreator.h"
#include "shared/ISCPacketCreator.h"
#include "shared/Timed.h"
#include "shared/ItemData.h"

#include "core/MemoryLeak.h"


s32 main(s32 argc, char **argv)
{
	E_SERVER_TYPE t_srvType = ST_NONE;

	while (true)
	{
		if (t_srvType == ST_NONE)
		{
			if (argc >= 2)
			{
				if (xstricmp("/login", argv[1]) == 0)
				{
					t_srvType = ST_LOGIN;
				}
				else if (xstricmp("/char", argv[1]) == 0)
				{
					t_srvType = ST_CHAR;
				}
				else if (xstricmp("/world", argv[1]) == 0)
				{
					t_srvType = ST_WORLD;
				}
				else
				{
					Log::write(LOG_ERROR, "Serveur Invalide. Utliser /login, /char or /world");
					break;
				}
			}
			else
			{
#if SERVER_TYPE != 0
				t_srvType = E_SERVER_TYPE(SERVER_TYPE);
				continue;
#else
				Log::write(LOG_ERROR, "Serveur Invalide. Utliser /login, /char or /world");
				break;
#endif
			}
		}
		else
		{
			switch (t_srvType)
			{
			case ST_LOGIN:
				ILoginServer().start();
				break;

			case ST_CHAR:
				ICharServer().start();
				break;

			case ST_WORLD:
				IWorldServer().start();
				break;

            default:
                Log::write(LOG_ERROR, "Serveur Invalide. Utliser /login, /char or /world");
			}

			break;
		}
	}

	Log::close();
	IPacketCreator::cleanup();
	IISCPacketCreator::cleanup();
	ITimed::cleanup();
	IItemData::cleanup();

#ifdef _MSC_VER
#ifndef NDEBUG
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ) );
#endif
#endif
}
