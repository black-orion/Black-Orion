#include "FileReader.h"


BEGIN_NAMESPACE_CORE
{

	char CFileReader::m_buffer[BUF_SIZE];
	char CFileReader::m_buffer_2[BUF_2_SIZE];

	CFileReader::CFileReader()
		: m_file(NULL)
		, m_opensuccess(false)
		, m_pos(NULL)
		, m_end(NULL)
		, m_readingpos(0)
		, m_options(0)
	{
	}

	CFileReader::CFileReader(const char *_filename, bool _closeafterreading)
		: m_file(NULL)
		, m_opensuccess(false)
		, m_pos(NULL)
		, m_end(NULL)
		, m_readingpos(0)
		, m_options(0)
	{
		open(_filename, _closeafterreading);
	}

	CFileReader::~CFileReader()
	{
		if (m_file)
		{
			fclose(m_file);
		}
	}

	bool CFileReader::open(const char *_filename, bool _closeafterreading)
	{
		FDASSERT(_filename != NULL);

		m_filename = _filename;

		if (m_file)
		{
			fclose(m_file);
		}

		m_content.clear();
		m_pos = 0;
		m_end = 0;

		//open the file
		fopen_s(&m_file, m_filename.c_str(), "rb");
		if (m_file)
		{
			m_opensuccess = _load();

			if (_closeafterreading)
			{
				close();
			}

			m_opensuccess = true;
		}
		else
		{
			m_opensuccess = false;
		}

		return m_opensuccess;
	}

	bool CFileReader::isOpen()
	{
		return (m_opensuccess || m_file);
	}

	bool CFileReader::end()
	{
		return (m_pos >= m_end);
	}

	void CFileReader::quit()
	{
		m_pos = m_end;
	}

	void CFileReader::close()
	{
		if (m_file)
		{
			fclose(m_file);
			m_file = NULL;
		}
		else
		{
			m_opensuccess = false;
		}
	}

	bool CFileReader::reload()
	{
		if (m_file)
		{
			clearContent();
			_load();
			return true;
		}
		else
		{
			return open(m_filename.c_str(), true);
		}
	}

	void CFileReader::setContent(const char *_content)
	{
		m_content = _content;
		m_opensuccess = true;
		_updatePos();
	}

	const char *CFileReader::getContent()
	{
		return m_content.c_str();
	}

	const char *CFileReader::getContentRest()
	{
		_updatePos();
		return m_pos;
	}

	void CFileReader::clearContent()
	{
		m_content.clear();
		m_pos = NULL;
		m_end = NULL;
		m_readingpos = 0;
	}

	void CFileReader::rewind()
	{
		m_readingpos = 0;
		_updatePos();
	}

	u32 CFileReader::getSize()
	{
		return m_content.size();
	}

	const char *CFileReader::getFileName()
	{
		return m_filename.c_str();
	}

	bool CFileReader::getOption(u32 _option)
	{
		return (m_options & _option) != 0;
	}

	void CFileReader::setOption(u32 _option, bool _on)
	{
		if (_on)
		{
			m_options |= _option;
		}
		else
		{
			m_options &= ~_option;
		}
	}

	char CFileReader::readChar(bool _skipwhitespaceandcomments)
	{
		if (_skipwhitespaceandcomments)
		{
			_toNextToken();
		}

		return *(m_pos++);
	}

	sdk::stringc CFileReader::readNext(u32 _count)
	{
		if (_count == 0)
		{
			return "";
		}

		_toNextToken();

		sdk::stringc r_str;
		char *t_dest;
		u32 t_destsize;
		while (!end())
		{
			t_dest = &m_buffer[0];
			t_destsize = BUF_SIZE - 1;

			while (*m_pos &&
				!xisspace(*m_pos))
			{
				if (t_destsize == 0)
				{
					*t_dest = '\0';
					r_str.append(m_buffer);
					t_destsize = BUF_SIZE - 1;
					t_dest = m_buffer;
				}

				*(t_dest++) = *(m_pos++);
				t_destsize--;
			}

			*t_dest = '\0';
			r_str.append(m_buffer);

			if (_count == 1)
				break;

			r_str.append(" ");
			_count--;
		}
		return r_str;
	}

	char *CFileReader::readNext(char *_dest, u32 _destsize, u32 _count)
	{
		if (_count)
		{
			_toNextToken();

			--_destsize;

			char *t_dest = _dest;

			while (!end())
			{
				while (*m_pos &&
					!xisspace(*m_pos))
				{
					if (_destsize)
					{
						*(t_dest++) = *(m_pos);
						--_destsize;
					}
					++m_pos;
				}

				if (_count == 1)
					break;

				*(t_dest++) = ' ';
				--_destsize;

				--_count;
			}
			*(t_dest) = '\0';
		}
		else
		{
			_dest[0] = '\0';
		}

		return _dest;
	}

	void CFileReader::skipNext(u32 _count)
	{
		_toNextToken();

		if (_count)
		{
			while (*m_pos &&
				!xisspace(*m_pos))
			{
				++m_pos;
			}

			skipNext(_count - 1);
		}
	}

	sdk::stringc CFileReader::readString(char _delim)
	{
		_toNextToken();

		if (*m_pos == _delim)
		{
			++m_pos;

			sdk::stringc r_str;

			m_currentbytesread = 0;
			while (true)
			{
				m_buffer[m_currentbytesread++] = *m_pos;
				++m_pos;

				if (m_currentbytesread == BUF_SIZE - 1 ||
					!*m_pos ||
					*m_pos == _delim)
				{
					m_buffer[m_currentbytesread] = '\0';
					r_str.append(m_buffer);

					if (*m_pos == _delim)
					{
						++m_pos;
						break;
					}
					else if (!*m_pos)
					{
						break;
					}

					m_currentbytesread = 0;
				}
			}

			return r_str;
		}
		else
		{
			return readNext();
		}
	}

	char *CFileReader::readString(char *_dest, u32 _destsize, char _delim)
	{
		_toNextToken();

		if (*m_pos == _delim)
		{
			++m_pos;

			--_destsize; //last byte is for '\0'

			char *t_dest = _dest;

			while (*m_pos)
			{
				if (*m_pos == _delim)
				{
					++m_pos;
					break;
				}

				if (_destsize)
				{
					*(t_dest++) = *m_pos;
					_destsize--;
				}

				++m_pos;
			}

			*t_dest = '\0';

			return _dest;
		}
		else
		{
			return readNext(_dest, _destsize);
		}
	}

	void CFileReader::skipString(char _delim)
	{
		_toNextToken();

		if (*m_pos == _delim)
		{
			m_pos++;

			while (*m_pos)
			{
				if (*m_pos == _delim)
				{
					++m_pos;
					break;
				}

				++m_pos;
			}
		}
		else
		{
			skipNext(1);
		}
	}

	void CFileReader::skipString(const char *_delim)
	{
		_toNextToken();

		u32 t_delimsize = strlen(_delim);

		if (strncmp(m_pos, _delim, t_delimsize) == 0)
		{
			m_pos += t_delimsize;

			while (*m_pos)
			{
				if (strncmp(m_pos, _delim, t_delimsize) == 0)
				{
					m_pos += t_delimsize;
					break;
				}

				++m_pos;
			}
		}
		else
		{
			skipNext(1);
		}
	}

	s32 CFileReader::readInt()
	{
		return xtoi(readNext(m_buffer_2, BUF_2_SIZE));
	}

	u32 CFileReader::readUInt()
	{
		return xtou(readNext(m_buffer_2, BUF_2_SIZE));
	}

	s64 CFileReader::readInt64()
	{
		return xtoi64(readNext(m_buffer_2, BUF_2_SIZE));
	}

	u64 CFileReader::readUInt64()
	{
		return xtou64(readNext(m_buffer_2, BUF_2_SIZE));
	}

	f32 CFileReader::readFloat()
	{
		return xtof(readNext(m_buffer_2, BUF_2_SIZE));
	}

	f64 CFileReader::readDouble()
	{
		return xtod(readNext(m_buffer_2, BUF_2_SIZE));
	}

	bool CFileReader::readBool()
	{
		readNext(m_buffer_2, BUF_2_SIZE);
		if (xtoi(m_buffer_2) ||
			xstricmp("true", m_buffer_2) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	sdk::stringc CFileReader::readLine()
	{
		sdk::stringc r_str;
		char *t_dest;
		u32 t_destsize;

		t_dest = &m_buffer[0];
		t_destsize = BUF_SIZE - 1;

		while (*m_pos &&
			*m_pos != '\n')
		{
			if (t_destsize == 0)
			{
				*t_dest = '\0';
				r_str.append(m_buffer);
				t_destsize = BUF_SIZE - 1;
				t_dest = m_buffer;
			}

			*(t_dest++) = *(m_pos++);
			--t_destsize;
		}

		++m_pos; //skip \r

		*t_dest = '\0';
		r_str.append(m_buffer);

		return r_str;
	}

	char *CFileReader::readLine(char *_dest, u32 _destsize)
	{
		char *t_dest = _dest;
		while (*m_pos &&
			*m_pos != '\n')
		{
			if (_destsize)
			{
				*(t_dest++) = *m_pos;
				--_destsize;
			}

			++m_pos;
		}

		++m_pos;

		*t_dest = '\0';
		return _dest;
	}

	void CFileReader::skipLine()
	{
		while (*m_pos &&
			*m_pos != '\n')
		{
			++m_pos;
		}
		++m_pos;
	}

	CFileReader &CFileReader::operator = (const CFileReader &_other)
	{
		if (this != &_other)
		{
			close();
			m_opensuccess = _other.m_opensuccess;
			m_filename = _other.m_filename;
			m_content = _other.m_content;
			m_readingpos = _other.m_readingpos;
		}
		return *this;
	}

	bool CFileReader::_load()
	{
		if (!m_content.fromFile(m_file))
			return false;

		rewind();
		return true;
	}

	void CFileReader::_updatePos()
	{
		if (!m_pos)
			m_pos = &m_content[0];

		if (!m_end)
			m_end = &m_content[m_content.size()];
	}

	void CFileReader::_toNextToken()
	{
		FDASSERT(m_pos != NULL);

		while (xisspace(*m_pos))
		{
			++m_pos;
		}

		if (getOption(opt_comments))
		{
			_skipComments();
		}
	}

	void CFileReader::_skipComments()
	{
		while (*m_pos)
		{
			//one line comments
			if (m_pos[0] == '/' &&
				m_pos[1] == '/')
			{
				do
				{
					m_pos++;
				}
				while (*m_pos &&
					*m_pos != '\n');

				++m_pos; //skip \n

				while (xisspace(*m_pos))
				{
					++m_pos;
				}

				continue;
			}

			//multi line comments
			if (*m_pos == '/' &&
				*(++m_pos) &&
				*m_pos == '*')
			{
				do
				{
					++m_pos;

					if (!*m_pos)
					{
						break;
					}
					else
					{
						if (*m_pos == '*')
						{
							if (!*(++m_pos))
								break;
							else
							{
								if (*m_pos == '/')
								{
									while (xisspace(*m_pos))
									{
										++m_pos;
									}
									break;
								}
							}
						}
					}
				}
				while (true);

				continue;
			}

			break;
		}
	}

};
