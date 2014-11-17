#include "E_CHAR.h"
#include "Log.h"


//// JobType ////
/////////////////

struct IJobTypeInfo
{
	E_JOB_TYPE Id;

	const char *Title;
};

const IJobTypeInfo JOB_TYPE_INFOS[] =
{
	{JTYPE_BASE, "JTYPE_BASE"},
	{JTYPE_EXPERT, "JTYPE_EXPERT"},
	{JTYPE_PRO, "JTYPE_PRO"},
	{JTYPE_TROUPE, "JTYPE_TROUPE"},
	{JTYPE_COMMON, "JTYPE_COMMON"},
	{JTYPE_MASTER, "JTYPE_MASTER"},
	{JTYPE_HERO, "JTYPE_HERO"}
};

E_JOB_TYPE jobType(const char *_title)
{
	for (u32 i = 0; i < ARRAY_SIZE(JOB_TYPE_INFOS); ++i)
	{
		if (strcmp(JOB_TYPE_INFOS[i].Title, _title) == 0)
		{
			return JOB_TYPE_INFOS[i].Id;
		}
	}

	return JTYPE_BASE;
}

E_JOB_TYPE jobType(s32 _id)
{
	return E_JOB_TYPE(Limit(_id, 0, COUNT_OF_JOB_TYPES - 1));
}

const char *jobTypeTitle(E_JOB_TYPE _type)
{
	FDASSERT(_type == jobType(_type));

	return JOB_TYPE_INFOS[_type].Title;
}


//// Job ////
/////////////

struct IJobInfo
{
	E_JOB Id;

	const char *Title;

	E_JOB_TYPE Type;
};

const IJobInfo JOB_INFOS[] =
{
	{JOB_VAGRANT, "JOB_VAGRANT", JTYPE_BASE}, //0

	{JOB_MERCENARY, "JOB_MERCENARY", JTYPE_EXPERT}, //1
	{JOB_ACROBAT, "JOB_ACROBAT", JTYPE_EXPERT}, //2
	{JOB_ASSIST, "JOB_ASSIST", JTYPE_EXPERT}, //3
	{JOB_MAGICIAN, "JOB_MAGICIAN", JTYPE_EXPERT}, //4
	{JOB_PUPPETEER, "JOB_PUPPETEER", JTYPE_EXPERT}, //5

	{JOB_KNIGHT, "JOB_KNIGHT", JTYPE_PRO}, //6
	{JOB_BLADE, "JOB_BLADE", JTYPE_PRO}, //7
	{JOB_JESTER, "JOB_JESTER", JTYPE_PRO}, //8
	{JOB_RANGER, "JOB_RANGER", JTYPE_PRO}, //9
	{JOB_RINGMASTER, "JOB_RINGMASTER", JTYPE_PRO}, //10
	{JOB_BILLPOSTER, "JOB_BILLPOSTER", JTYPE_PRO}, //11
	{JOB_PSYKEEPER, "JOB_PSYKEEPER", JTYPE_PRO}, //12
	{JOB_ELEMENTOR, "JOB_ELEMENTOR", JTYPE_PRO}, //13
	{JOB_GATEKEEPER, "JOB_GATEKEEPER", JTYPE_PRO}, //14
	{JOB_DOPPLER, "JOB_DOPPLER", JTYPE_PRO}, //15

	{JOB_KNIGHT_MASTER, "JOB_KNIGHT_MASTER", JTYPE_MASTER}, //16
	{JOB_BLADE_MASTER, "JOB_BLADE_MASTER", JTYPE_MASTER}, //17
	{JOB_JESTER_MASTER, "JOB_JESTER_MASTER", JTYPE_MASTER}, //18
	{JOB_RANGER_MASTER, "JOB_RANGER_MASTER", JTYPE_MASTER}, //19
	{JOB_RINGMASTER_MASTER, "JOB_RINGMASTER_MASTER", JTYPE_MASTER}, //20
	{JOB_BILLPOSTER_MASTER, "JOB_BILLPOSTER_MASTER", JTYPE_MASTER}, //21
	{JOB_PSYKEEPER_MASTER, "JOB_PSYKEEPER_MASTER", JTYPE_MASTER}, //22
	{JOB_ELEMENTOR_MASTER, "JOB_ELEMENTOR_MASTER", JTYPE_MASTER}, //23

	{JOB_KNIGHT_HERO, "JOB_KNIGHT_HERO", JTYPE_HERO}, //24
	{JOB_BLADE_HERO, "JOB_BLADE_HERO", JTYPE_HERO}, //25
	{JOB_JESTER_HERO, "JOB_JESTER_HERO", JTYPE_HERO}, //26
	{JOB_RANGER_HERO, "JOB_RANGER_HERO", JTYPE_HERO}, //27
	{JOB_RINGMASTER_HERO, "JOB_RINGMASTER_HERO", JTYPE_HERO}, //28
	{JOB_BILLPOSTER_HERO, "JOB_BILLPOSTER_HERO", JTYPE_HERO}, //29
	{JOB_PSYKEEPER_HERO, "JOB_PSYKEEPER_HERO", JTYPE_HERO}, //30
	{JOB_ELEMENTOR_HERO, "JOB_ELEMENTOR_HERO", JTYPE_HERO} //31
};

E_JOB job(const char *_title)
{
	for (u32 i = 0; i < ARRAY_SIZE(JOB_INFOS); ++i)
	{
		if (strcmp(JOB_INFOS[i].Title, _title) == 0)
		{
			return JOB_INFOS[i].Id;
		}
	}

	return JOB_VAGRANT;
}

E_JOB job(s32 _id)
{
	return E_JOB(Limit(_id, 0, COUNT_OF_JOBS - 1));
}

const char *jobTitle(E_JOB _job)
{
	FDASSERT(_job == job(_job));

	return JOB_INFOS[_job].Title;
}

bool isMaster(E_JOB _job)
{
	FDASSERT(_job == job(_job));

	return JOB_INFOS[_job].Type == JTYPE_MASTER;
}

bool isHero(E_JOB _job)
{
	FDASSERT(_job == job(_job));

	return JOB_INFOS[_job].Type == JTYPE_HERO;
}

bool isMasterOrHero(E_JOB _job)
{
	FDASSERT(_job == job(_job));

	return isMaster(_job) || isHero(_job);
}


IJobStats::IJobStats()
	: Name()
	, MaxLevel(120)
	, FirstJob(JOB_VAGRANT)
	, HpRate(1.0f)
	, MpRate(1.0f)
	, FpRate(1.0f)
	, HpRegRate(1.0f)
	, MpRegRate(1.0f)
	, FpRegRate(1.0f)
	, DefStaRate(1.0f)
	, DefLevelRate(1.0f)
	, BaseDef(0)
	, Sword(4.5f)
	, Axe(5.5f)
	, Staff(0.8f)
	, Stick(3.0f)
	, Knuckle(5.0f)
	, Wand(6.0f)
	, Block(1.0f)
	, Yoyo(4.2f)
	, Crit(1.0f)
	, Bow(3.0f)
{
}

IJobStats JOB_STATS[COUNT_OF_JOBS];

bool loadJobStats(const char *_fileName)
{
	FDASSERT(_fileName);

	const u32 T_BUF_SIZE = 1024;
	char t_buffer[T_BUF_SIZE];

	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	if (t_file.open(_fileName))
	{
		for (u32 i = 0; i < COUNT_OF_JOBS; ++i)
		{
			if (t_file.end())
			{
				Log::write(LOG_ERROR, "Error in job file \"%s\": Unexpected end of file in line %u!",
					_fileName, i + 1);
				return false;
			}

			//Job title
			t_file.readNext(t_buffer, T_BUF_SIZE);

			E_JOB t_jobId = job(t_buffer);

			if (t_jobId != i)
			{
				Log::write(LOG_ERROR, "Error in job file \"%s\": Unexpected job \"%s\"!",
					_fileName, t_buffer);
			}

			IJobStats &t_job = JOB_STATS[t_jobId];

			//name
			t_job.Name = t_file.readString(t_buffer, T_BUF_SIZE);

			//unknown f32
			t_file.skipNext();

			//hp, mp, fp
			t_job.HpRate = t_file.readFloat();
			t_job.MpRate = t_file.readFloat();
			t_job.FpRate = t_file.readFloat();

			//hp, mp, fp reg
			t_job.HpRegRate = t_file.readFloat();
			t_job.MpRegRate = t_file.readFloat();
			t_job.FpRegRate = t_file.readFloat();

			//unknown f32
			t_file.skipNext();

			//def
			t_job.DefStaRate = t_file.readFloat();
			t_job.DefLevelRate = t_file.readFloat();
			t_job.BaseDef = t_file.readInt();

			//Weapons, Crit and Block
			t_job.Sword = t_file.readFloat();
			t_job.Axe = t_file.readFloat();
			t_job.Staff = t_file.readFloat();
			t_job.Stick = t_file.readFloat();
			t_job.Knuckle = t_file.readFloat();
			t_job.Wand = t_file.readFloat();
			t_job.Block = t_file.readFloat();
			t_job.Yoyo = t_file.readFloat();
			t_job.Crit = t_file.readFloat();
			t_job.Bow = t_file.readFloat();

			//Max Level
			t_job.MaxLevel = t_file.readInt();

			//job before
			t_job.FirstJob = job(t_file.readNext(t_buffer, T_BUF_SIZE));
		}

		return true;
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open job file \"%s\"!", _fileName);
		return false;
	}
}

const IJobStats &jobStats(E_JOB _job)
{
	FDASSERT(_job == job(_job));
	FDASSERT(_job < ARRAY_SIZE(JOB_STATS));

	return JOB_STATS[_job];
}

bool isCompatibleJob(E_JOB _required, E_JOB _char)
{
	if (_required == _char ||
		_required == JOB_VAGRANT)
	{
		return true;
	}
	else
	{
		for (u32 i = 0; i < 3; ++i)
		{
			_char = jobStats(_char).FirstJob;
			if (_char == _required)
			{
				return true;
			}

			if (_char == JOB_VAGRANT)
			{
				return false;
			}
		}
	}

	return false;
}


//// Sex ////
/////////////

E_SEX sex(const char *_name)
{
	if (strcmp("SEX_MALE", _name) == 0)
		return SEX_MALE;

	if (strcmp("SEX_FEMALE", _name) == 0)
		return SEX_FEMALE;

	return SEX_SEXLESS;
}

E_SEX sex(s32 _id)
{
	switch (_id)
	{
	case SEX_MALE:
	case SEX_FEMALE:
	case SEX_SEXLESS:
		return E_SEX(_id);
	};

	return SEX_SEXLESS;
}

const char *sexTitle(E_SEX _sex)
{
	switch (_sex)
	{
	case SEX_MALE:
		return "SEX_MALE";

	case SEX_FEMALE:
		return "SEX_FEMALE";

	default:
		return "SEX_SEXLESS";
	};
}

bool isCompatibleSex(E_SEX _required, E_SEX _char)
{
	return (_required == SEX_SEXLESS ||
		_required == _char);
}

E_FACE face(s32 _id)
{
	return E_FACE(_id);
}

E_HAIR hair(s32 _id)
{
	return E_HAIR(_id);
}