#ifndef CHARSETTINGS_H
#define CHARSETTINGS_H


#include "CharMain.h"
#include "../shared/E_CHAR.h"
#include "../shared/E_ELEMENT.h"
#include "../shared/ItemPack.h"
#include "../shared/ItemDataManager.h"


class ICharSettings
{
public:

	struct ISCSettings
	{
		sdk::stringc Host;
		PORT Port;
		sdk::stringc Password;
		sdk::stringc ThisIP;
		ID ExternalId;
		sdk::stringc Name;
	} ISC;

	struct GameSettings
	{
		PORT Port;
		TimeMs SaveInterval;
	} Game;

	struct DatabaseSettings
	{
		sdk::stringc Host;
		PORT Port;
		sdk::stringc User;
		sdk::stringc Password;
		sdk::stringc Database;
	} Database;

	struct DataSettings
	{
		IItemDataManagerSettings Items;
	} Data;

	struct CharacterSettings
	{
		struct StartItem : public IItemProperties
		{
		public:

			StartItem()
				: m_place(0)
				, m_sex(SEX_SEXLESS)
			{
			}

			s32 getPlace() const
			{
				return m_place;
			}

			E_SEX getSex() const
			{
				return m_sex;
			}

		private:

			friend struct CharacterSettings;

			s32 m_place;
			E_SEX m_sex;

		};

		s32 BaseStr;
		s32 BaseSta;
		s32 BaseDex;
		s32 BaseInt;
		s32 BaseStatPoints;
		LVL Level;
		PENYA Penya;
		E_JOB Job;
		sdk::stringc StartItemFileName;
		CArray<StartItem> StartItems;

		bool loadStartItems(IItemDataManager *_itemMngr);
	} Character;

	struct ProgramSettings
	{
		sdk::stringc LogFileName;
	} Program;

	ICharSettings();
	bool load(const char *_filename);

private:

	CConfigReader m_file;

};

typedef ICharSettings::ISCSettings ICharISCSettings;

typedef ICharSettings::GameSettings ICharGameSettings;

typedef ICharSettings::DatabaseSettings ICharDatabaseSettings;

typedef ICharSettings::CharacterSettings ICharCharacterSettings;

typedef ICharSettings::CharacterSettings::StartItem IStartItem;


#endif //CHARSETTINGS_H
