#include "LoginSettings.h"


ILoginSettings::ILoginSettings()
{
}

bool ILoginSettings::load(const char *_filename)
{
	bool r_opened = m_file.load(_filename);

	//ISC

	ISC.Port = m_file.getValueUInt("ISC", "port", ISC_STANDARD_PORT);
	ISC.Password = m_file.getValueString("ISC", "password", "");
	ISC.MaxClusters = m_file.getValueUInt("ISC", "maxclusters", 1);

	//Game

	Game.Port = m_file.getValueUInt("GAME", "port", LOGIN_STANDARD_PORT);
	Game.MaxPlayers = m_file.getValueUInt("GAME", "maxplayers", 32);
	Game.SaveInterval = m_file.getValueUInt("GAME", "saveinterval", 60000);
	Game.LoginRegister = m_file.getValueBool("GAME", "loginregister", false);
	Game.RequiredAccessLevel = IAccount::E_ACCESS_LEVEL(
		m_file.getValueInt("GAME", "reqacclvl", IAccount::ACC_MINIMUM));
	Game.ClientCompileDate = m_file.getValueString("GAME", "ccd", "");
	Game.Checksum = m_file.getValueString("GAME", "checksum", "");

	//Database

	Database.Host = m_file.getValueString("DATABASE", "host", "127.0.0.1");
	Database.Port = m_file.getValueUInt("DATABASE", "port", 3306);
	Database.User = m_file.getValueString("DATABASE", "user", "root");
	Database.Password = m_file.getValueString("DATABASE", "password", "");
	Database.Database = m_file.getValueString("DATABASE", "database", "blackorion_0");

	//Program

	Program.LogFileName = m_file.getValueString("PROGRAM", "log", "login.log");

	return r_opened;
}