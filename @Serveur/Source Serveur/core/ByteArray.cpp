#include "ByteArray.h"
#include "Debug.h"


#include <cstdarg>


#define HEXTONUM(c) (((c) >= '0' && (c) <= '9') ? ((c) - '0') : (((c) >= 'a' && (c) <= 'f') ? ((c) - 'a' + 10) : (0)))


BEGIN_NAMESPACE_CORE
{

	char CByteArray::m_buffer[CByteArray::BUF_SIZE];

	CByteArray::CByteArray() : m_readingpos(0)
	{
	}

	CByteArray::CByteArray(const Byte *_buffer, u32 _count) : m_readingpos(0)
	{
		m_content.resize(_count);
		memcpy(&m_content[0], _buffer, _count);
	}

	CByteArray::CByteArray(const char *_str)
	{
		u32 t_strsize = strlen(_str) + 1;
		m_content.resize(t_strsize);
		memcpy(&m_content[0], _str, t_strsize);
	}

	u32 CByteArray::size() const
	{
		return m_content.size();
	}

	bool CByteArray::empty() const
	{
		return m_content.empty();
	}

	void CByteArray::clear()
	{
		m_content.clear();
		m_readingpos = 0;
	}

	Byte *CByteArray::data()
	{
		if (!empty())
			return &m_content[0];
		else
			return NULL;
	}

	const Byte *CByteArray::data() const
	{
		if (!empty())
			return &m_content[0];
		else
			return NULL;
	}

	CArray<Byte> &CByteArray::content()
	{
		return m_content;
	}

	const CArray<Byte> &CByteArray::content() const
	{
		return m_content;
	}

	bool CByteArray::end() const
	{
		return m_readingpos + 1 >= m_content.size();
	}

	void CByteArray::quit()
	{
		m_readingpos = m_content.size() - 1;
	}

	void CByteArray::resize(u32 _size)
	{
		m_content.resize(_size);
	}

	void CByteArray::addByte(Byte _byte)
	{
		m_content.push_back(_byte);
	}

	void CByteArray::addBytes(const Byte *_bytes, u32 _count)
	{
		addBuffer(_bytes, _count);
	}

	void CByteArray::addBuffer(const Byte *_buffer, u32 _count)
	{
		if (_count == 0)
			return;

		u32 t_newsize = m_content.size() + _count;
		if (t_newsize)
		{
			m_content.resize(t_newsize);
			memcpy(&m_content[t_newsize - _count], _buffer, _count);
		}
	}

	void CByteArray::addSByte(s8 _sbyte)
	{
		m_content.push_back(static_cast<Byte>(_sbyte));
	}

	void CByteArray::addUByte(u8 _ubyte)
	{
		m_content.push_back(static_cast<Byte>(_ubyte));
	}

	void CByteArray::addShort(s16 _short)
	{
		addType(_short);
	}

	void CByteArray::addUShort(u16 _ushort)
	{
		addType(_ushort);
	}

	void CByteArray::addInt(s32 _int)
	{
		addType(_int);
	}

	void CByteArray::addUInt(u32 _uint)
	{
		addType(_uint);
	}

	void CByteArray::addInt64(s64 _int_64)
	{
		addType(_int_64);
	}

	void CByteArray::addUInt64(u64 _uint_64)
	{
		addType(_uint_64);
	}

	void CByteArray::addFloat(f32 _float)
	{
		addType(_float);
	}

	void CByteArray::addDouble(f64 _double)
	{
		addType(_double);
	}

	void CByteArray::addString(const char *_str)
	{
		u32 t_strlen = strlen(_str);
		addInt(static_cast<s32>(t_strlen));
		addBuffer(_str, t_strlen);
	}

	void CByteArray::addString(const char *_str, u32 _count)
	{
		addInt(_count);
		addBuffer(_str, _count);
	}

	void CByteArray::addString(const sdk::stringc &_str)
	{
		u32 t_strsize = _str.size();
		addInt(t_strsize);
		addBuffer(_str.c_str(), t_strsize);
	}

	void CByteArray::addStringRaw(const char *_str)
	{
		addBuffer(_str, strlen(_str));
	}

	void CByteArray::addHex(const char *_hexstr)
	{
		Byte t_newbyte;
		while (*_hexstr &&
			*(_hexstr + 1))
		{
			t_newbyte = ((HEXTONUM(*(_hexstr)) << 4) + HEXTONUM(*(_hexstr+1)));
			m_content.push_back(t_newbyte);
			_hexstr += 2;
		}
	}

	CByteArray &CByteArray::operator << (s8 _sbyte)
	{
		addSByte(_sbyte);
		return *this;
	}

	CByteArray &CByteArray::operator << (u8 _ubyte)
	{
		addUByte(_ubyte);
		return *this;
	}

	CByteArray &CByteArray::operator << (s16 _short)
	{
		addShort(_short);
		return *this;
	}

	CByteArray &CByteArray::operator << (u16 _ushort)
	{
		addUShort(_ushort);
		return *this;
	}

	CByteArray &CByteArray::operator << (s32 _int)
	{
		addInt(_int);
		return *this;
	}

	CByteArray &CByteArray::operator << (u32 _uint)
	{
		addUInt(_uint);
		return *this;
	}

	CByteArray &CByteArray::operator << (s64 _int_64)
	{
		addInt64(_int_64);
		return *this;
	}

	CByteArray &CByteArray::operator << (u64 _uint_64)
	{
		addUInt64(_uint_64);
		return *this;
	}

	CByteArray &CByteArray::operator << (f32 _float)
	{
		addFloat(_float);
		return *this;
	}

	CByteArray &CByteArray::operator << (f64 _double)
	{
		addDouble(_double);
		return *this;
	}

	CByteArray &CByteArray::operator << (const char *_str)
	{
		addString(_str);
		return *this;
	}

	CByteArray &CByteArray::operator << (const stringc &_str)
	{
		addString(_str);
		return *this;
	}

	CByteArray &CByteArray::operator << (const CByteArray &_bytes)
	{
		(*this) += _bytes;
		return *this;
	}

	u32 CByteArray::getReadingPos() const
	{
		return m_readingpos;
	}

	void CByteArray::setReadingPos(u32 _pos)
	{
		m_readingpos = Limit<u32>(_pos, 0, m_content.size() - 1);
	}

	void CByteArray::resetReadingPos()
	{
		m_readingpos = 0;
	}

	void CByteArray::skip(u32 _number)
	{
		m_readingpos += _number;
	}

	void CByteArray::traceBack(u32 _bytes)
	{
		FDASSERT(_bytes <= m_readingpos);
		m_readingpos -= _bytes;
	}

	Byte CByteArray::getByte()
	{
		if (m_readingpos < m_content.size())
		{
			return m_content[m_readingpos++];
		}
		return 0;
	}

	Byte &CByteArray::getByte(u32 _pos)
	{
		FDASSERT(_pos < m_content.size());
		return *(Byte*)&m_content[_pos];
	}

	Byte CByteArray::getByte(u32 _pos) const
	{
		FDASSERT(_pos < m_content.size());
		return *(Byte*)&m_content[_pos];
	}

	s8 CByteArray::getSByte()
	{
		if (m_readingpos < m_content.size())
		{
			return *(s8*)&m_content[m_readingpos++];
		}
		return 0;
	}

	s8 &CByteArray::getSByte(u32 _pos)
	{
		FDASSERT(_pos < m_content.size());
		return *(s8*)&m_content[_pos];
	}

	s8 CByteArray::getSByte(u32 _pos) const
	{
		FDASSERT(_pos < m_content.size());
		return *(s8*)&m_content[_pos];
	}

	u8 CByteArray::getUByte()
	{
		if (m_readingpos < m_content.size())
		{
			return *(u8*)&m_content[m_readingpos++];
		}
		return 0;
	}

	u8 &CByteArray::getUByte(u32 _pos)
	{
		FDASSERT(_pos < m_content.size());
		return *(u8*)&m_content[_pos];
	}

	u8 CByteArray::getUByte(u32 _pos) const
	{
		FDASSERT(_pos < m_content.size());
		return *(u8*)&m_content[_pos];
	}

	s16 CByteArray::getShort()
	{
		return (isReadable<s16>() ? getType<s16>() : 0);
	}

	s16 &CByteArray::getShort(u32 _pos)
	{
		return getType<s16>(_pos);
	}

	s16 CByteArray::getShort(u32 _pos) const
	{
		return getType<s16>(_pos);
	}

	u16 CByteArray::getUShort()
	{
		return (isReadable<u16>() ? getType<u16>() : 0);
	}

	u16 &CByteArray::getUShort(u32 _pos)
	{
		return getType<u16>(_pos);
	}

	u16 CByteArray::getUShort(u32 _pos) const
	{
		return getType<u16>(_pos);
	}

	s32 CByteArray::getInt()
	{
		return (isReadable<s32>() ? getType<s32>() : 0);
	}

	s32 &CByteArray::getInt(u32 _pos)
	{
		return getType<s32>(_pos);
	}

	s32 CByteArray::getInt(u32 _pos) const
	{
		return getType<s32>(_pos);
	}

	u32 CByteArray::getUInt()
	{
		return (isReadable<u32>() ? getType<u32>() : 0);
	}

	u32 &CByteArray::getUInt(u32 _pos)
	{
		return getType<u32>(_pos);
	}

	u32 CByteArray::getUInt(u32 _pos) const
	{
		return getType<u32>(_pos);
	}

	s64 CByteArray::getInt64()
	{
		return (isReadable<s64>() ? getType<s64>() : 0);
	}

	s64 &CByteArray::getInt64(u32 _pos)
	{
		return getType<s64>(_pos);
	}

	s64 CByteArray::getInt64(u32 _pos) const
	{
		return getType<s64>(_pos);
	}

	u64 CByteArray::getUInt64()
	{
		return (isReadable<u64>() ? getType<u64>() : 0);
	}

	u64 &CByteArray::getUInt64(u32 _pos)
	{
		return getType<u64>(_pos);
	}

	u64 CByteArray::getUInt64(u32 _pos) const
	{
		return getType<u64>(_pos);
	}

	f32 CByteArray::getFloat()
	{
		return (isReadable<f32>() ? getType<f32>() : 0);
	}

	f32 &CByteArray::getFloat(u32 _pos)
	{
		return getType<f32>(_pos);
	}

	f32 CByteArray::getFloat(u32 _pos) const
	{
		return getType<f32>(_pos);
	}

	f64 CByteArray::getDouble()
	{
		return (isReadable<f64>() ? getType<f64>() : 0);
	}

	f64 &CByteArray::getDouble(u32 _pos)
	{
		return getType<f64>(_pos);
	}

	f64 CByteArray::getDouble(u32 _pos) const
	{
		return getType<f64>(_pos);
	}

	bool CByteArray::getBytes(Byte *_out, u32 _count)
	{
		if (!_count)
		{
			return true;
		}

		u32 t_oldPos = m_readingpos;
		m_readingpos += _count;
		if (m_readingpos <= m_content.size())
		{
			sdk::copy(_out, &m_content[t_oldPos], _count);
			return true;
		}
		else
		{
			return false;
		}
	}

	CByteArray &CByteArray::operator >> (s8 &_sbyte)
	{
		_sbyte = getSByte();
		return (*this);
	}

	CByteArray &CByteArray::operator >> (u8 &_ubyte)
	{
		_ubyte = getUByte();
		return (*this);
	}

	CByteArray &CByteArray::operator >> (s16 &_short)
	{
		_short = getShort();
		return (*this);
	}

	CByteArray &CByteArray::operator >> (u16 &_ushort)
	{
		_ushort = getUShort();
		return (*this);
	}

	CByteArray &CByteArray::operator >> (s32 &_int)
	{
		_int = getInt();
		return (*this);
	}

	CByteArray &CByteArray::operator >> (u32 &_uint)
	{
		_uint = getUInt();
		return (*this);
	}

	CByteArray &CByteArray::operator >> (s64 &_int_64)
	{
		_int_64 = getInt64();
		return (*this);
	}

	CByteArray &CByteArray::operator >> (u64 &_uint_64)
	{
		_uint_64 = getUInt64();
		return (*this);
	}

	CByteArray &CByteArray::operator >> (f32 &_float)
	{
		_float = getFloat();
		return (*this);
	}

	CByteArray &CByteArray::operator >> (f64 &_double)
	{
		_double = getDouble();
		return (*this);
	}

	CByteArray &CByteArray::operator >> (stringc &_str)
	{
		_str = getString();
		return (*this);
	}

	sdk::stringc CByteArray::getString()
	{
		sdk::stringc r_str;
		u32 t_strSize = getInt();
		r_str.resize(t_strSize);

		getStringRaw(r_str.data(), t_strSize);

		return r_str;
	}

	sdk::stringc CByteArray::getStringRaw(u32 _strlen)
	{
		sdk::stringc r_str;
		r_str.reserve(_strlen);
		getStringRaw(r_str.data(), _strlen);
		r_str.count();

		return r_str;
	}

	bool CByteArray::getString(char *_dest, u32 _destsize)
	{
		u32 t_strSize = getInt();

		if (t_strSize < _destsize)
		{
			return getStringRaw(_dest, t_strSize);
		}

		else
		{
			skip(t_strSize);
		}

		return false;
	}

	bool CByteArray::getStringRaw(char *_dest, u32 _strlen)
	{
		if (getBytes(_dest, _strlen))
		{
			_dest[_strlen] = '\0';
			return true;
		}

		return false;
	}

	void CByteArray::setByte(u32 _pos, Byte _byte)
	{
		setType(_pos, _byte);
	}

	void CByteArray::setSByte(u32 _pos, s8 _sbyte)
	{
		setType(_pos, _sbyte);
	}

	void CByteArray::setUByte(u32 _pos, u8 _ubyte)
	{
		setType(_pos, _ubyte);
	}

	void CByteArray::setShort(u32 _pos, s16 _short)
	{
		setType(_pos, _short);
	}

	void CByteArray::setUShort(u32 _pos, u16 _ushort)
	{
		setType(_pos, _ushort);
	}

	void CByteArray::setInt(u32 _pos, s32 _int)
	{
		setType(_pos, _int);
	}

	void CByteArray::setUInt(u32 _pos, u32 _uint)
	{
		setType(_pos, _uint);
	}

	void CByteArray::setInt64(u32 _pos, s64 _int_64)
	{
		setType(_pos, _int_64);
	}

	void CByteArray::setUInt64(u32 _pos, u64 _uint_64)
	{
		setType(_pos, _uint_64);
	}

	void CByteArray::setFloat(u32 _pos, f32 _float)
	{
		setType(_pos, _float);
	}

	void CByteArray::setDouble(u32 _pos, f64 _double)
	{
		setType(_pos, _double);
	}

	void CByteArray::copy(u32 _pos, Byte *_dest, u32 _count) const
	{
		if (_pos + _count <= size())
		{
			sdk::copy(_dest, &m_content[_pos], _count);
		}
	}

	void CByteArray::copy(u32 _pos, CByteArray &_out_dest, u32 _count) const
	{
		if (_pos + _count <= size())
		{
			_out_dest.m_content.resize(_count);

			sdk::copy(&_out_dest.m_content[0], &m_content[_pos], _count);
		}
	}

	void CByteArray::cut(u32 _pos, Byte *_opt_dest, u32 _count)
	{
		FDASSERT(_opt_dest);
		FDASSERT(_pos + _count <= size());

		sdk::copy(_opt_dest, &m_content[_pos], _count);
		m_content.erase(_pos, _count);
	}

	void CByteArray::insert(u32 _pos, const Byte *_bytes, u32 _count)
	{
		if (_pos < m_content.size())
		{
			while (_count--)
			{
				m_content.insert(_pos, *(_bytes--));
			}
		}
	}

	void CByteArray::operator += (const CByteArray &_other)
	{
		addBuffer(_other.data(), _other.size());
	}

	bool CByteArray::saveFormatted(const char *_filename) const
	{
		FILE *t_file;
		fopen_s(&t_file, _filename, "a");
		if (t_file != 0)
		{
			u32 i;
			u32 c = m_content.size();
			//original data
			fwrite(data(), sizeof(Byte), size(), t_file);
			fprintf_s(t_file, "\n\n");

			//decimal
			for (i = 0; i < c; i++)
			{
				fprintf_s(t_file, "%02d ", m_content[i]);
			}
			fprintf_s(t_file, "\n\n");

			//hexadecimal
			sdk::stringc t_buf;
			for (i = 0; i < c; i++)
			{
#ifdef _MSC_VER
				sprintf_s(m_buffer, sizeof(m_buffer), "%02x ", m_content[i]);
#else
				sprintf(m_buffer, "%02x ", m_content[i]);
#endif
				t_buf = m_buffer;
				fprintf_s(t_file, "%s", t_buf.substr(t_buf.size()-3, 3).c_str());
			}
			fprintf_s(t_file, "\n\n");

			fclose(t_file);
			return true;
		}
		return false;
	}

	bool CByteArray::fromFile(const char *_filename)
	{
		static const u32 READING_COUNT = 8192;

		clear();

		FILE *t_file;
		fopen_s(&t_file, _filename, "rb");
		if (t_file)
		{
			u32 t_bytesread = 0;
			u32 t_totalbytesread = 0;

			//Speicher entsprechend der Dateigröße bereitstellen
			m_content.resize(filesize(t_file));

			//Datei auslesen
			if (!empty())
			{
				freadall(data(), size(), t_file);
			}

			fclose(t_file);
			return true;
		}

		return false;
	}

	bool CByteArray::toFile(const char *_filename) const
	{
		FILE *t_file;
		fopen_s(&t_file, _filename, "wb");
		if (t_file)
		{
			u32 t_totalbyteswritten = 0;
			u32 t_currentbyteswritten;

			while ((t_totalbyteswritten < m_content.size()) &&
				(t_currentbyteswritten = fwrite(&m_content[t_totalbyteswritten],
				sizeof(Byte), Min<u32>(m_content.size() - t_totalbyteswritten, BUF_SIZE),
				t_file)) &&
				!ferror(t_file))
			{
				t_totalbyteswritten += t_currentbyteswritten;
			}

			fclose(t_file);
			return true;
		}
		return false;
	}

	void CByteArray::destroy()
	{
		m_content.destroy();
	}

	Byte &CByteArray::operator [] (u32 _pos)
	{
		FDASSERT(_pos < m_content.size());

		return m_content[_pos];
	}

	Byte CByteArray::operator [] (u32 _pos) const
	{
		FDASSERT(_pos < m_content.size());

		return m_content[_pos];
	}

	bool CByteArray::operator == (const CByteArray &_other) const
	{
		u32 t_size = m_content.size();

		if (t_size != _other.m_content.size())
			return false;

		const Byte *t_c1 = &m_content[0];
		const Byte *t_c2 = &_other.m_content[0];

		return compare(t_c1, t_c2, t_size / sizeof(Byte)) == 0;
	}

	bool CByteArray::operator != (const CByteArray &_other) const
	{
		return !(*this == _other);
	}

}
