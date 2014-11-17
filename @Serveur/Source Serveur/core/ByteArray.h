#ifndef CORE_BYTEARRAY_H
#define CORE_BYTEARRAY_H


#include "CoreBase.h"
#include "Util.h"
#include "Array.h"
#include "String.h"
#include "Vec3D.h"


BEGIN_NAMESPACE_CORE
{

	class CByteArray
	{
	public:

		CByteArray();

		CByteArray(const Byte *_buffer, u32 _count);

		CByteArray(const char *_str);

		//returns the byte count
		u32 size() const;

		bool empty() const;

		void clear();

		//returns a pointer to the content
		Byte *data();

		const Byte *data() const;

		CArray<Byte> &content();

		const CArray<Byte> &content() const;

		//returns true if all bytes were read
		bool end() const;

		//sets the reading marker to the end
		void quit();

		void resize(u32 _size);

		void addByte(Byte _byte);

		void addBytes(const Byte *_bytes, u32 _count);

		void addBuffer(const Byte *_buffer, u32 _count);

		void addSByte(s8 _sbyte);

		void addUByte(u8 _ubyte);

		void addShort(s16 _short);

		void addUShort(u16 _ushort);

		void addInt(s32 _int);

		void addUInt(u32 _uint);

		void addInt64(s64 _int_64);

		void addUInt64(u64 _uint_64);

		void addFloat(f32 _float);

		void addDouble(f64 _double);

		//adds [int]size, [char*]str
		void addString(const char *_str);

		//adds [int]_count, [char*]str
		void addString(const char *_str, u32 _count);

		void addString(const sdk::stringc &_str);

		//adds [char*]str
		void addStringRaw(const char *_str);

		template <class T>
		void addCoordinates(const CVec3D<T> &_pos)
		{
			addType(_pos.X);
			addType(_pos.Y);
			addType(_pos.Z);
		}

		void addHex(const char *_hexstr);

		template <class T>
		void addMultiple(const T &_value, u32 _count)
		{
			u32 t_oldSize = size();
			m_content.resize(size() + sizeof(T) * _count);
			for (; t_oldSize < size(); t_oldSize += sizeof(T))
			{
				sdk::copy((T*)&m_content[t_oldSize], &_value, 1);
			}
		}

		template <class T>
		void addType(const T &_type)
		{
			u32 t_size = m_content.size();
			m_content.resize(t_size + sizeof(T));
			*(T*)&m_content[t_size] = _type;
		}

		CByteArray &operator << (s8 _sbyte);

		CByteArray &operator << (u8 _ubyte);

		CByteArray &operator << (s16 _short);

		CByteArray &operator << (u16 _ushort);

		CByteArray &operator << (s32 _int);

		CByteArray &operator << (u32 _uint);

		CByteArray &operator << (s64 _int_64);

		CByteArray &operator << (u64 _uint_64);

		CByteArray &operator << (f32 _float);

		CByteArray &operator << (f64 _double);

		CByteArray &operator << (const char *_str);

		CByteArray &operator << (const stringc &_str);

		CByteArray &operator << (const CByteArray &_bytes);

		u32 getReadingPos() const;

		void setReadingPos(u32 _pos);

		void resetReadingPos();

		void skip(u32 _number);

		void traceBack(u32 _bytes);

		template <class T>
		bool isReadable()
		{
			return (getReadingPos() + sizeof(T) <= size());
		}

		Byte getByte();

		Byte &getByte(u32 _pos);

		Byte getByte(u32 _pos) const;

		s8 getSByte();

		s8 &getSByte(u32 _pos);

		s8 getSByte(u32 _pos) const;

		u8 getUByte();

		u8 &getUByte(u32 _pos);

		u8 getUByte(u32 _pos) const;

		s16 getShort();

		s16 &getShort(u32 _pos);

		s16 getShort(u32 _pos) const;

		u16 getUShort();

		u16 &getUShort(u32 _pos);

		u16 getUShort(u32 _pos) const;

		s32 getInt();

		s32 &getInt(u32 _pos);

		s32 getInt(u32 _pos) const;

		u32 getUInt();

		u32 &getUInt(u32 _pos);

		u32 getUInt(u32 _pos) const;

		s64 getInt64();

		s64 &getInt64(u32 _pos);

		s64 getInt64(u32 _pos) const;

		u64 getUInt64();

		u64 &getUInt64(u32 _pos);

		u64 getUInt64(u32 _pos) const;

		f32 getFloat();

		f32 &getFloat(u32 _pos);

		f32 getFloat(u32 _pos) const;

		f64 getDouble();

		f64 &getDouble(u32 _pos);

		f64 getDouble(u32 _pos) const;

		bool getBytes(Byte *_out, u32 _count);

		template <class T>
		bool getType(T &_out)
		{
			_out = getType<T>();
		}

		template <class T>
		bool getTypePtr(T *_out)
		{
			*_out = getType<T>();
		}

		template <class T>
		T getType()
		{
			u32 t_oldPos = m_readingpos;
			m_readingpos += sizeof(T);
			return *(T*)&m_content[t_oldPos];
		}

		template <class T>
		T &getType(u32 _pos)
		{
			FDASSERT(_pos + sizeof(T) <= m_readingpos);
			return *(T*)&m_content[_pos];
		}

		template <class T>
		const T &getType(u32 _pos) const
		{
			FDASSERT(_pos + sizeof(T) <= m_readingpos);
			return *(T*)&m_content[_pos];
		}

		CByteArray &operator >> (s8 &_sbyte);

		CByteArray &operator >> (u8 &_ubyte);

		CByteArray &operator >> (s16 &_short);

		CByteArray &operator >> (u16 &_ushort);

		CByteArray &operator >> (s32 &_int);

		CByteArray &operator >> (u32 &_uint);

		CByteArray &operator >> (s64 &_int_64);

		CByteArray &operator >> (u64 &_uint_64);

		CByteArray &operator >> (f32 &_float);

		CByteArray &operator >> (f64 &_double);

		CByteArray &operator >> (stringc &_str);

		template <class T, u32 N>
		CByteArray &operator >> (T (&_array)[N])
		{
			getArray(_array);
			return (*this);
		}

		template <class T, u32 N>
		bool getArray(T (&_array)[N])
		{
			return getBytes(static_cast<Byte*>(_array), sizeof(T) * N);
		}

		sdk::stringc getString();

		sdk::stringc getStringRaw(u32 _strlen);

		bool getString(char *_dest, u32 _destsize);

		bool getStringRaw(char *_dest, u32 _strlen);

		template <class T>
		void getCoordinates(CVec3D<T> &_out)
		{
			_out.X = getType<T>();
			_out.Y = getType<T>();
			_out.Z = getType<T>();
		}

		template <class T>
		CByteArray &operator >> (T &_dest)
		{
			getType(&_dest);
			return *this;
		}

		template <class T>
		void setType(u32 _pos, const T &_value)
		{
			FDASSERT(_pos + sizeof(T) <= size());
			*(T*)&m_content[_pos] = _value;
		}

		void setByte(u32 _pos, Byte _byte);

		void setSByte(u32 _pos, s8 _sbyte);

		void setUByte(u32 _pos, u8 _ubyte);

		void setShort(u32 _pos, s16 _short);

		void setUShort(u32 _pos, u16 _ushort);

		void setInt(u32 _pos, s32 _int);

		void setUInt(u32 _pos, u32 _uint);

		void setInt64(u32 _pos, s64 _int_64);

		void setUInt64(u32 _pos, u64 _uint_64);

		void setFloat(u32 _pos, f32 _float);

		void setDouble(u32 _pos, f64 _double);

		//copies _count bytes from position _pos to _opt_dest
		void copy(u32 _pos, Byte *_dest, u32 _count) const;

		void copy(u32 _pos, CByteArray &_out_dest, u32 _count) const;

		//copies _count bytes from position _pos to _opt_dest and removes them from the bytestream
		void cut(u32 _pos, Byte *_opt_dest, u32 _count);

		//inserts an array of bytes
		void insert(u32 _pos, const Byte *_bytes, u32 _count);

		//add another packet
		void operator += (const CByteArray &_other);

		template <class T, u32 N>
		void operator += (const T (&_arr)[N])
		{
			addBuffer((Byte*)_arr, N * sizeof(T));
		}

		//saves the formatted byte contents to the file
		bool saveFormatted(const char *_filename) const;

		bool fromFile(const char *_filename);

		bool toFile(const char *_filename) const;

		//frees the memory
		void destroy();

		Byte &operator [] (u32 _pos);

		Byte operator [] (u32 _pos) const;

		bool operator == (const CByteArray &_other) const;

		bool operator != (const CByteArray &_other) const;

	private:

		CArray<Byte> m_content;

		u32 m_readingpos;

		enum
		{
			BUF_SIZE = 8192
		};

		static char m_buffer[BUF_SIZE];

	};
}


#endif //CORE_BYTEARRAY_H
