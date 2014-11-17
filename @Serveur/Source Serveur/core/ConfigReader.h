#ifndef CORE_CONFIGREADER_H
#define CORE_CONFIGREADER_H


#include "CoreBase.h"
#include "Array.h"
#include "String.h"


BEGIN_NAMESPACE_CORE
{

	class CConfigReader
	{
	public:

		CConfigReader();

		~CConfigReader();

		bool load(const char *_fileName);

		bool save(const char *_fileName = 0);

		u32 getCategoryCount();

		u32 getValueCount();

		void clear();

		CArray<sdk::stringc> getCategoryNames();

		CArray<sdk::stringc> getCategoryValues(const char *_categoryName);

		sdk::stringc getValueString(const char *_categoryName, const char *_valueName, const char *_default = 0);

		s32 getValueInt(const char *_categoryName, const char *_valueName, s32 _default = 0);

		u32 getValueUInt(const char *_categoryName, const char *_valueName, u32 _default = 0);

		s64 getValueInt64(const char *_categoryName, const char *_valueName, s64 _default = 0);

		u64 getValueUInt64(const char *_categoryName, const char *_valueName, u64 _default = 0);

		f32 getValueFloat(const char *_categoryName, const char *_valueName, f32 _default = 0);

		f64 getValueDouble(const char *_categoryName, const char *_valueName, f64 _default = 0);

		bool getValueBool(const char *_categoryName, const char *_valueName, bool _default = false);

		bool changeCategoryName(const char *_current, const char *_new);

		bool changeValueName(const char *_category, const char *_current, const char *_new);

		bool setValue(const char *_categoryName, const char *_valueName, const char *_value_str);

		bool setValue(const char *_categoryName, const char *_valueName, s32 _value_int);

		bool setValue(const char *_categoryName, const char *_valueName, u32 _value_uint);

		bool setValue(const char *_categoryName, const char *_valueName, s64 _value_int64);

		bool setValue(const char *_categoryName, const char *_valueName, u64 _value_uint64);

		bool setValue(const char *_categoryName, const char *_valueName, f32 _value_float);

		bool setValue(const char *_categoryName, const char *_valueName, f64 _value_double);

		bool removeCategory(const char *_categoryName);

		bool removeValue(const char *_categoryName, const char *_valueName);

	private:

		sdk::stringc m_fileName;

		struct value
		{
			sdk::stringc name;

			sdk::stringc val;
		};

		struct category
		{
			sdk::stringc name;

			CArray<value> values;
		};

		CArray<category*> m_categories;

		enum
		{
			BUF_SIZE = 1024
		};

		char m_buffer[BUF_SIZE];

		category *_getCategory(const char *_name);

		category *_addCategory(const char *_name);

		value *_getValue(category *_category, const char *_name);

		bool _addValue(const char *_categoryName, const char *_valueName, const char *_value);

		bool _addValue(category *_category, const char *_valueName, const char *_value);

		void _skipSpaces(char **_pos);

	};

};


#endif //CORE_CONFIGREADER_H
