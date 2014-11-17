#include "ConfigReader.h"


BEGIN_NAMESPACE_CORE
{

	CConfigReader::CConfigReader()
	{
	}

	CConfigReader::~CConfigReader()
	{
		for (u32 i = 0; i < m_categories.size(); ++i)
		{
			delete m_categories[i];
		}
	}

	bool CConfigReader::load(const char *_fileName)
	{
		FDASSERT(_fileName);

		m_fileName = _fileName;

		FILE *file;
		fopen_s(&file, m_fileName.c_str(), "r");
		if (file)
		{
			const u32 T_BUFSIZE = 8192;
			char t_buffer[T_BUFSIZE];
			char *t_pos = &(t_buffer[0]);
			char *t_lastpos = t_pos;

			CConfigReader::category t_newcat;
			CConfigReader::value t_newval;

			CConfigReader::category *t_currentcat = 0;

			while (t_pos = fgets(t_buffer, T_BUFSIZE - 1, file))
			{
				_skipSpaces(&t_pos);
				t_lastpos = t_pos;

				//line is a comment
				if (*t_pos == '#' || *t_pos == '\n')
					continue;

				//line is a category
				if (*t_pos == '[')
				{
					while (*t_pos != ']' &&
						*t_pos != '\n')
					{
						t_pos++;
					}

					*t_pos = '\0';

					t_lastpos++;
					t_newcat.name = t_lastpos;

					if (t_newcat.name.size() > 0)
					{
						t_currentcat = new CConfigReader::category(t_newcat);
						m_categories.push_back(t_currentcat);
						t_newcat.name.clear();
						t_newcat.values.clear();
					}
				}

				//value
				else if (t_currentcat)
				{
					while (*t_pos != '=' &&
						*t_pos != '\n')
					{
						t_pos++;
					}

					*t_pos = '\0';

					t_newval.name = t_lastpos;
					t_pos++;
					t_lastpos = t_pos;
					t_pos += strlen(t_pos) - 1;
					if (*t_pos == '\n')
					{
						*t_pos = '\0';
					}
					t_pos = t_lastpos;
					t_newval.val = t_pos;

					t_currentcat->values.push_back(t_newval);
				}
			}

			fclose(file);
			return true;
		}
		return false;
	}

	bool CConfigReader::save(const char *_fileName)
	{
		if (_fileName)
		{
			m_fileName = _fileName;
		}

		FILE *file;
		fopen_s(&file, m_fileName.c_str(), "w");
		if (file)
		{
			u32 i, j, c, d;
			for (i = 0, c = m_categories.size(); i < c; ++i)
			{
				if (i > 0)
				{
					fprintf_s(file, "\n");
				}

				fprintf_s(file, "[%s]\n", m_categories[i]->name.c_str());
				for (j = 0, d = m_categories[i]->values.size(); j < d; ++j)
				{
					fprintf_s(file, "%s=%s\n", m_categories[i]->values[j].name.c_str(),
						m_categories[i]->values[j].val.c_str());
				}
			}
			fclose(file);
			return true;
		}
		return false;
	}

	u32 CConfigReader::getCategoryCount()
	{
		return m_categories.size();
	}

	u32 CConfigReader::getValueCount()
	{
		u32 r_count = 0;
		for (u32 i = 0, c = m_categories.size(); i < c; ++i)
		{
			r_count += m_categories[i]->values.size();
		}
		return r_count;
	}

	void CConfigReader::clear()
	{
		for (u32 i = 0, c = m_categories.size(); i < c; ++i)
		{
			delete m_categories[i];
		}
		m_categories.clear();
	}

	CArray<sdk::stringc> CConfigReader::getCategoryNames()
	{
		CArray<sdk::stringc> r_names;
		for (u32 i = 0; i < m_categories.size(); ++i)
		{
			r_names.push_back(m_categories[i]->name);
		}
		return r_names;
	}

	CArray<sdk::stringc> CConfigReader::getCategoryValues(const char *_categoryName)
	{
		CArray<sdk::stringc> r_values;
		category *t_cat = _getCategory(_categoryName);
		if (t_cat)
		{
			for (u32 i = 0; i < t_cat->values.size(); ++i)
			{
				r_values.push_back(t_cat->values[i].name);
			}
		}
		return r_values;
	}

	sdk::stringc CConfigReader::getValueString(const char *_categoryName, const char *_valueName, const char *_default)
	{
		category *t_cat = _getCategory(_categoryName);
		if (t_cat)
		{
			value *t_value = _getValue(t_cat, _valueName);
			if (t_value)
			{
				return t_value->val;
			}
			else
			{
				return _default ? _default : "";
			}
		}
		return _default ? _default : "";
	}

	s32 CConfigReader::getValueInt(const char *_categoryName, const char *_valueName, s32 _default)
	{
		CConfigReader::category *t_cat = _getCategory(_categoryName);
		if (t_cat)
		{
			value *t_value = _getValue(t_cat, _valueName);
			if (t_value)
			{
				return xtoi(t_value->val.c_str());
			}
			else
			{
				return _default;
			}
		}
		return _default;
	}

	u32 CConfigReader::getValueUInt(const char *_categoryName, const char *_valueName, u32 _default)
	{
		CConfigReader::category *t_cat = _getCategory(_categoryName);
		if (t_cat)
		{
			value *t_value = _getValue(t_cat, _valueName);
			if (t_value)
			{
				return xtou(t_value->val.c_str());
			}
			else
			{
				return _default;
			}
		}
		return _default;
	}

	s64 CConfigReader::getValueInt64(const char *_categoryName, const char *_valueName, s64 _default)
	{
		CConfigReader::category *t_cat = _getCategory(_categoryName);
		if (t_cat)
		{
			value *t_value = _getValue(t_cat, _valueName);
			if (t_value)
			{
				return xtoi64(t_value->val.c_str());
			}
			else
			{
				return _default;
			}
		}
		return _default;
	}

	u64 CConfigReader::getValueUInt64(const char *_categoryName, const char *_valueName, u64 _default)
	{
		CConfigReader::category *t_cat = _getCategory(_categoryName);
		if (t_cat)
		{
			value *t_value = _getValue(t_cat, _valueName);
			if (t_value)
			{
				return xtou64(t_value->val.c_str());
			}
			else
			{
				return _default;
			}
		}
		return _default;
	}

	f32 CConfigReader::getValueFloat(const char *_categoryName, const char *_valueName, f32 _default)
	{
		CConfigReader::category *t_cat = _getCategory(_categoryName);
		if (t_cat)
		{
			value *t_value = _getValue(t_cat, _valueName);
			if (t_value)
			{
				return xtof(t_value->val.c_str());
			}
			else
			{
				return _default;
			}
		}
		return _default;
	}

	f64 CConfigReader::getValueDouble(const char *_categoryName, const char *_valueName, f64 _default)
	{
		CConfigReader::category *t_cat = _getCategory(_categoryName);
		if (t_cat)
		{
			value *t_value = _getValue(t_cat, _valueName);
			if (t_value)
			{
				return xtod(t_value->val.c_str());
			}
			else
			{
				return _default;
			}
		}
		return _default;
	}

	bool CConfigReader::getValueBool(const char *_categoryName, const char *_valueName, bool _default)
	{
		CConfigReader::category *t_cat = _getCategory(_categoryName);
		if (t_cat)
		{
			value *t_value = _getValue(t_cat, _valueName);
			if (t_value)
			{
				if (xstricmp("true", t_value->val.c_str()) == 0)
					return true;

				if (xstricmp("false", t_value->val.c_str()) == 0)
					return false;

				return (xtoi(t_value->val.c_str()) != 0);
			}
			else
			{
				return _default;
			}
		}
		return _default;
	}

	bool CConfigReader::changeCategoryName(const char *_current, const char *_new)
	{
		for (u32 i = 0, c = m_categories.size(); i < c; ++i)
		{
			if (strcmp(m_categories[i]->name.c_str(), _current) == 0)
			{
				m_categories[i]->name = _new;
				return true;
			}
		}
		return false;
	}

	bool CConfigReader::changeValueName(const char *_category, const char *_current, const char *_new)
	{
		for (u32 i = 0, c = m_categories.size(); i < c; ++i)
		{
			if (strcmp(m_categories[i]->name.c_str(), _category) == 0)
			{
				u32 j;
				for (j = 0, c = m_categories[i]->values.size(); j < c; ++j)
				{
					if (strcmp(m_categories[i]->values[j].name.c_str(), _current) == 0)
					{
						m_categories[i]->values[j].name = _new;
						return true;
					}
				}
				break;
			}
		}
		return false;
	}

	bool CConfigReader::setValue(const char *_categoryName, const char *_valueName, const char *_value_str)
	{
		category *t_cat = 0;
		for (u32 i = 0, c = m_categories.size(); i < c; ++i)
		{
			if (strcmp(m_categories[i]->name.c_str(), _categoryName) == 0)
			{
				t_cat = m_categories[i];
				break;
			}
		}

		if (t_cat == 0)
		{
			t_cat = _addCategory(_categoryName);
		}

		if (t_cat != 0)
		{
			for (u32 i = 0, c = t_cat->values.size(); i < c; ++i)
			{
				if (strcmp(t_cat->values[i].name.c_str(), _valueName) == 0)
				{
					t_cat->values[i].val = _value_str;
					return true;
				}
			}

			return _addValue(t_cat, _valueName, _value_str);
		}

		return false;
	}

	bool CConfigReader::setValue(const char *_categoryName, const char *_valueName, s32 _value_int)
	{
		return (setValue(_categoryName, _valueName, itox(m_buffer, BUF_SIZE, _value_int)));
	}

	bool CConfigReader::setValue(const char *_categoryName, const char *_valueName, u32 _value_uint)
	{
		return (setValue(_categoryName, _valueName, utox(m_buffer, BUF_SIZE, _value_uint)));
	}

	bool CConfigReader::setValue(const char *_categoryName, const char *_valueName, s64 _value_int64)
	{
		return (setValue(_categoryName, _valueName, i64tox(m_buffer, BUF_SIZE, _value_int64)));
	}

	bool CConfigReader::setValue(const char *_categoryName, const char *_valueName, u64 _value_uint64)
	{
		return (setValue(_categoryName, _valueName, u64tox(m_buffer, BUF_SIZE, _value_uint64)));
	}

	bool CConfigReader::setValue(const char *_categoryName, const char *_valueName, f32 _value_float)
	{
		return (setValue(_categoryName, _valueName, ftox(m_buffer, BUF_SIZE, _value_float)));
	}

	bool CConfigReader::setValue(const char *_categoryName, const char *_valueName, f64 _value_double)
	{
		return (setValue(_categoryName, _valueName, dtox(m_buffer, BUF_SIZE, _value_double)));
	}

	bool CConfigReader::removeCategory(const char *_categoryName)
	{
		for (u32 i = 0, c = m_categories.size(); i < c; ++i)
		{
			if (strcmp(m_categories[i]->name.c_str(), _categoryName) == 0)
			{
				delete m_categories[i];
				m_categories.erase(i);
				return true;
			}
		}
		return false;
	}

	bool CConfigReader::removeValue(const char *_categoryName, const char *_valueName)
	{
		for (u32 i = 0, c = m_categories.size(); i < c; ++i)
		{
			if (strcmp(m_categories[i]->name.c_str(), _categoryName) == 0)
			{
				u32 j;
				for (j = 0, c = m_categories[i]->values.size(); j < c; ++j)
				{
					if (strcmp(m_categories[i]->values[j].name.c_str(), _valueName) == 0)
					{
						m_categories[i]->values.erase(j);
						return true;
					}
				}
				break;
			}
		}
		return false;
	}

	CConfigReader::category *CConfigReader::_getCategory(const char *_name)
	{
		for (u32 i = 0, c = m_categories.size(); i < c; ++i)
		{
			if (strcmp(m_categories[i]->name.c_str(), _name) == 0)
			{
				return m_categories[i];
			}
		}
		return 0;
	}

	CConfigReader::category *CConfigReader::_addCategory(const char *_name)
	{
		if (_getCategory(_name) == 0)
		{
			category *newCat = new category();
			newCat->name = _name;
			m_categories.push_back(newCat);
			return newCat;
		}
		return 0;
	}

	CConfigReader::value *CConfigReader::_getValue(category *_category, const char *_name)
	{
		for (u32 i = 0; i < _category->values.size(); ++i)
		{
			if (strcmp(_category->values[i].name.c_str(), _name) == 0)
			{
				return &_category->values[i];
			}
		}
		return 0;
	}

	bool CConfigReader::_addValue(const char *_categoryName, const char *_valueName,
		const char *_value)
	{
		category *t_cat = _getCategory(_categoryName);
		if (t_cat == 0)
		{
			t_cat = _addCategory(_categoryName);
		}

		return _addValue(t_cat, _valueName, _value);
	}

	bool CConfigReader::_addValue(category *_category, const char *_valueName, const char *_value)
	{
		if (_category != 0)
		{
			if (!_getValue(_category, _valueName))
			{
				value t_val;
				t_val.name = _valueName;
				t_val.val = _value;
				_category->values.push_back(t_val);
				return true;
			}
		}
		return false;
	}

	void CConfigReader::_skipSpaces(char **_pos)
	{
		while (
			**_pos == ' ' ||
			**_pos == '\t')
		{
			++(*_pos);
		}
	}

};
