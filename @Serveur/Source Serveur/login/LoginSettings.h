#ifndef LOGINSETTINGS_H
#define LOGINSETTINGS_H


#include "LoginMain.h"
#include "../shared/Account.h"


class ILoginSettings
{
public:

	struct ISCSettings
	{
		PORT Port;
		sdk::stringc Password;
		u32 MaxClusters;
	} ISC;

	struct GameSettings
	{
		PORT Port;
		u32 MaxPlayers;
		TimeMs SaveInterval;
		bool LoginRegister;
		IAccount::E_ACCESS_LEVEL RequiredAccessLevel;
		sdk::stringc ClientCompileDate;
		sdk::stringc Checksum;
	} Game;

	struct DatabaseSettings
	{
		sdk::stringc Host;
		PORT Port;
		sdk::stringc User;
		sdk::stringc Password;
		sdk::stringc Database;
	} Database;

	struct ProgramSettings
	{
		sdk::stringc LogFileName;
	} Program;

	ILoginSettings();
	bool load(const char *_filename);

private:

	CConfigReader m_file;

};

typedef ILoginSettings::ISCSettings ILoginISCSettings;

typedef ILoginSettings::GameSettings ILoginGameSettings;


#endif //LOGINSETTINGS_H
