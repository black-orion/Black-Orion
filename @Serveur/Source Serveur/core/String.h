#ifndef STRING_H
#define STRING_H


#include "CoreBase.h"
#include "Array.h"
#include "Debug.h"
#include "Util.h"

#include <cstdarg>
#include <iostream>


BEGIN_NAMESPACE_CORE
{

	template <class T>
	class CString
	{
	public:

		CString();

		CString(const CString &_str);

		CString(const T *_str);

		~CString();

		CString &operator = (const CString &_str);

		CString &operator = (const T *_str);

		void operator += (const CString &_str);

		void operator += (const T *_str);

		void operator += (T _char);

		CString operator + (const CString &_str) const;

		CString operator + (const T *_str) const;

		bool operator == (const CString &_str) const;

		bool operator == (const T *_str) const;

		bool operator != (const CString &_str) const;

		bool operator != (const T *_str) const;

		T &operator [] (u32 _pos);

		const T &operator [] (u32 _pos) const;

		CString &operator ~ ();

		u32 size() const;

		u32 length() const; //the same as size()

		u32 capacity() const;

		bool empty() const;

		const T *c_str() const;

		T *data();

		T *end();

		const T *end() const;

		T &at(u32 _pos);

		const T &at(u32 _pos) const;

		void resize(u32 _length);

		void reserve(u32 _size);

		void clear();

		void append(const CString &_str);

		void append(const T *_str);

		void append(T _char);

		s32 compare(const CString &_str) const;

		s32 compare(const T *_str) const;

		bool equals(const CString &_str) const;

		bool equals(const T *_str) const;

		CString substr(u32 _pos, u32 _count) const;

		CString substr(u32 _pos) const;

		void trim();

		void trim_front();

		void trim_back();

		void erase(u32 _pos);

		void erase(u32 _pos, u32 _count);

		void erase_all(T _char);

		void erase_first(T _char);

		void push_back(T _char);

		void push_front(T _char);

		void pop_back();

		void pop_front();

		void reverse();

		void shuffle();

		void replace(T _old, T _new);

		void replace(const T *_old, const T *_new); //!

		void insert(u32 _pos, T _char);

		void insert(u32 _pos, const T *_str);

		CArray<T> toArray() const;

		s32 toInt() const;

		u32 toUInt() const;

		f32 toFloat() const;

		f64 toDouble() const;

		void count();

		bool find(u32 &_outPos, u32 _startPos, T _char) const;

		bool fromFile(FILE *_file);

		//CArray<CString<T>> split(T _char) const;

		//void swap(const CString &_str);

		//bool contains(T _char) const;

		//bool contains(const T *_str) const;

		//CArray<CString<T>> split(const T *_str) const;

	private:

		enum
		{
			BUF_SIZE = 16
		};

		enum E_MODE
		{
			MODE_DYNAMIC,
			MODE_STATIC
		};

		T *m_str;

		T m_buf[BUF_SIZE];

		E_MODE m_mode;

		u32 m_size;

		u32 m_used;

		void _require(u32 _size);

		void _copy(const T *_src, u32 _size);

		void _append(const T *_src, u32 _size);

	};


	//typedef CString<char> string;
	typedef CString<char> stringc;
	typedef CString<wchar_t> stringw;


	template <class T>
	CString<T>::CString()
		: m_str(0)
		, m_mode(MODE_STATIC)
		, m_size(BUF_SIZE)
		, m_used(0)
	{
		m_buf[0] = 0;
	}

	template <class T>
	CString<T>::CString(const CString<T> &_str)
		: m_str(0)
		, m_mode(MODE_STATIC)
		, m_size(0)
		, m_used(_str.m_used)
	{
		_require(m_used + 1);

		_copy(_str.c_str(), m_used + 1);
	}

	template <class T>
	CString<T>::CString(const T *_str)
		: m_str(0)
		, m_mode(MODE_STATIC)
		, m_size(0)
		, m_used(xstrlen(_str))
	{
		_require(m_used + 1);

		_copy(_str, m_used + 1);
	}

	template <class T>
	CString<T>::~CString()
	{
		delete[] m_str;
	}

	template <class T>
	CString<T> &CString<T>::operator = (const CString &_str)
	{
		m_used = _str.m_used;

		_require(m_used + 1);

		_copy(_str.c_str(), m_used + 1);

		return *this;
	}

	template <class T>
	CString<T> &CString<T>::operator = (const T *_str)
	{
		if (_str)
		{
			m_used = xstrlen(_str);

			_require(m_used + 1);

			_copy(_str, m_used + 1);
		}

		return *this;
	}

	template <class T>
	void CString<T>::operator += (const CString &_str)
	{
		append(_str);
	}

	template <class T>
	void CString<T>::operator += (const T *_str)
	{
		append(_str);
	}

	template <class T>
	void CString<T>::operator += (T _char)
	{
		append(_char);
	}

	template <class T>
	CString<T> CString<T>::operator + (const CString &_str) const
	{
		CString<T> r_str = *this;
		r_str += _str;
		return r_str;
	}

	template <class T>
	CString<T> CString<T>::operator + (const T *_str) const
	{
		CString<T> r_str = *this;
		r_str += _str;
		return r_str;
	}

	template <class T>
	bool CString<T>::operator == (const CString<T> &_str) const
	{
		return equals(_str);
	}

	template <class T>
	bool CString<T>::operator == (const T *_str) const
	{
		return equals(_str);
	}

	template <class T>
	bool CString<T>::operator != (const CString &_str) const
	{
		return (xstrcmp(c_str(), _str.c_str()) != 0);
	}

	template <class T>
	bool CString<T>::operator != (const T *_str) const
	{
		return (xstrcmp(c_str(), _str) != 0);
	}

	template <class T>
	T &CString<T>::operator [] (u32 _pos)
	{
		FDASSERT(_pos <= m_used);

		if (m_mode == MODE_STATIC)
		{
			return m_buf[_pos];
		}
		else
		{
			return m_str[_pos];
		}
	}

	template <class T>
	const T &CString<T>::operator [] (u32 _pos) const
	{
		FDASSERT(_pos <= m_used);

		return *(c_str() + _pos);
	}

	template <class T>
	CString<T> &CString<T>::operator ~ ()
	{
		T *t_str = data();

		for (u32 i = 0; i < m_used; ++i, ++t_str)
		{
			*t_str = ~*t_str;
		}

		return *this;
	}

	template <class T>
	u32 CString<T>::size() const
	{
		return m_used;
	}

	template <class T>
	u32 CString<T>::length() const
	{
		return m_used;
	}

	template <class T>
	u32 CString<T>::capacity() const
	{
		return (m_mode == MODE_STATIC ? BUF_SIZE : m_size);
	}

	template <class T>
	bool CString<T>::empty() const
	{
		return (m_used == 0);
	}

	template <class T>
	const T *CString<T>::c_str() const
	{
		return (m_mode == MODE_STATIC ? m_buf : m_str);
	}

	template <class T>
	T *CString<T>::data()
	{
		return (m_mode == MODE_STATIC ? m_buf : m_str);
	}

	template <class T>
	T *CString<T>::end()
	{
		return data() + m_used;
	}

	template <class T>
	const T *CString<T>::end() const
	{
		return data() + m_used;
	}

	template <class T>
	T &CString<T>::at(u32 _pos)
	{
		FDASSERT(_pos <= m_used);

		return *(data() + _pos);
	}

	template <class T>
	const T &CString<T>::at(u32 _pos) const
	{
		FDASSERT(_pos <= m_used);

		return *(c_str() + _pos);
	}

	template <class T>
	void CString<T>::resize(u32 _length)
	{
		_require(_length + 1);

		m_used = _length;

		*end() = 0;
	}

	template <class T>
	void CString<T>::reserve(u32 _size)
	{
		_require(_size);
	}

	template <class T>
	void CString<T>::clear()
	{
		m_used = 0;
		*end() = 0;
	}

	template <class T>
	void CString<T>::append(const CString &_str)
	{
		u32 t_newSize = m_used + _str.m_used + 1;

		_require(t_newSize);

		_append(_str.c_str(), _str.m_used + 1);
	}

	template <class T>
	void CString<T>::append(const T *_str)
	{
		u32 t_strSize = xstrlen(_str) + 1;

		u32 t_newSize = m_used + t_strSize;

		_require(t_newSize);

		_append(_str, t_strSize);
	}

	template <class T>
	void CString<T>::append(T _char)
	{
		_require(m_used + 2);

		if (m_mode == MODE_STATIC)
		{
			m_buf[m_used++] = _char;
			m_buf[m_used] = 0;
		}
		else
		{
			m_str[m_used++] = _char;
			m_str[m_used] = 0;
		}
	}

	template <class T>
	s32 CString<T>::compare(const CString<T> &_str) const
	{
		return xstrcmp(c_str(), _str.c_str());
	}

	template <class T>
	s32 CString<T>::compare(const T *_str) const
	{
		return xstrcmp(c_str(), _str);
	}

	template <class T>
	bool CString<T>::equals(const CString<T> &_str) const
	{
		return (xstrcmp(c_str(), _str.c_str()) == 0);
	}

	template <class T>
	bool CString<T>::equals(const T *_str) const
	{
		return (xstrcmp(c_str(), _str) == 0);
	}

	template <class T>
	CString<T> CString<T>::substr(u32 _pos, u32 _count) const
	{
		CString<T> r_str;

		if (_pos + _count <= m_used)
		{
			r_str.resize(_count + 1);
			copy(r_str.data(), c_str() + _pos, _count);
			r_str[_count] = 0;
		}

		return r_str;
	}

	template <class T>
	CString<T> CString<T>::substr(u32 _pos) const
	{
		if (_pos <= m_used)
		{
			return CString<T>(c_str() + _pos);
		}

		return CString<T>();
	}

	template <class T>
	void CString<T>::trim()
	{
		trim_front();
		trim_back();
	}

	template <class T>
	void CString<T>::trim_front()
	{
		T *t_pos = data();

		while (xisspace(*t_pos))
		{
			++t_pos;
		}

		copy(data(), t_pos, m_used + 1);

		m_used -= (t_pos - data()) / sizeof(T);
	}

	template <class T>
	void CString<T>::trim_back()
	{
		T *t_last = data() + m_used - 1;
		T *t_pos = t_last;

		while (t_pos != data() &&
			xisspace(*t_pos))
		{
			--t_pos;
		}

		*(t_pos + 1) = 0;

		m_used -= (t_last - t_pos) / sizeof(T);
	}

	template <class T>
	void CString<T>::erase(u32 _pos)
	{
		erase(_pos, 1);
	}

	template <class T>
	void CString<T>::erase(u32 _pos, u32 _count)
	{
		FASSERT(_pos + _count <= m_used);

        copy(data() + _pos, data() + _pos + _count, m_used - _pos + 1);
        m_used -= _count;
	}

	template <class T>
	void CString<T>::erase_all(T _char)
	{
		for (u32 i = 0; i < m_used;)
		{
			if (*(data() + i) == _char)
			{
				erase(i);
			}
			else
			{
				++i;
			}
		}
	}

	template <class T>
	void CString<T>::erase_first(T _char)
	{
		for (u32 i = 0; i < m_used; ++i)
		{
			if (*(data() + i) == _char)
			{
				erase(i);
				return;
			}
		}
	}

	template <class T>
	void CString<T>::push_back(T _char)
	{
		append(_char);
	}

	template <class T>
	void CString<T>::push_front(T _char)
	{
		_require(m_used + 2);

		copy(data() + 1, data(), ++m_used);
		*data() = _char;
	}

	template <class T>
	void CString<T>::pop_back()
	{
		if (m_used)
		{
			--m_used;
			*(data() + m_used) = 0;
		}
	}

	template <class T>
	void CString<T>::pop_front()
	{
		--m_used;
		copy(data(), data() + 1, m_used);
	}

	template <class T>
	void CString<T>::reverse()
	{
		if (m_used)
		{
			T t_char;
			for (u32 i = 0,
				j = m_used - 1,
				c = m_used / 2; i < c; ++i, --j)
			{
				t_char = at(i);
				at(i) = at(j);
				at(j) = t_char;
			}
		}
	}

	template <class T>
	void CString<T>::shuffle()
	{
		if (m_used)
		{
			T *t_char;
			for (u32 i = 0; i < m_used; ++i)
			{
				t_char = data() + rand() % static_cast<s32>(m_used);

				swap(*(data() + i), *t_char);
			}
		}
	}

	template <class T>
	void CString<T>::replace(T _old, T _new)
	{
		for (u32 i = 0; i < m_used; ++i)
		{
			if (*(data() + i) == _old)
			{
				*(data() + i) = _new;
			}
		}
	}

	template <class T>
	void CString<T>::replace(const T *_old, const T *_new)
	{
		u32 t_oldLen = xstrlen(_old);

		if (t_oldLen >= m_used)
			return;

		u32 t_newLen = xstrlen(_new);

		if (t_newLen > t_oldLen)
		{
			u32 t_diff = t_newLen - t_oldLen;

			for (u32 i = 0, c = (m_used - t_oldLen); i < c; ++i)
			{
				if (xstrncmp(data() + i, _old, t_oldLen) == 0)
				{
					copy(data() + i + t_newLen, data() + i + t_oldLen, m_used + 1 - i - t_oldLen);

					m_used += t_diff;
					c += t_diff;

					copy(data() + i, _new, t_newLen);
				}
			}
		}

		else if (t_oldLen > t_newLen)
		{
			u32 t_diff = t_oldLen - t_newLen;

			for (u32 i = 0, c = (m_used - t_oldLen); i < c; ++i)
			{
				if (xstrncmp(data() + i, _old, t_oldLen) == 0)
				{
					copy(data() + i + t_newLen, data() + i + t_oldLen, m_used + 1 - i - t_oldLen);

					c -= t_diff;
					m_used -= t_diff;

					printf("m_used = %u\n", m_used);
					printf("c = %u\n", c);

					copy(data() + i, _new, t_newLen);
				}
			}
		}

		//t_oldLen == t_newLen
		else
		{
			for (u32 i = 0, c = (m_used - t_oldLen); i < c; ++i)
			{
				if (xstrncmp(data() + i, _old, t_oldLen) == 0)
				{
					_require(c + 1);

					copy(data() + i + t_newLen, data() + i + t_oldLen, m_used + 1 - i - t_oldLen);

					copy(data() + i, _new, t_newLen);
				}
			}
		}
	}

	template <class T>
	void CString<T>::insert(u32 _pos, T _char)
	{
		FDASSERT(_pos <= m_used);

        _require(m_used + 2);

        char *t_data = data() + _pos;

        move(t_data + 1, t_data, m_used + 1 - _pos);

        ++m_used;

        *t_data = _char;
	}

	template <class T>
	void CString<T>::insert(u32 _pos, const T *_str)
	{
		FDASSERT(_pos <= m_used);

        u32 t_strLen = xstrlen(_str);

        _require(m_used + 1 + t_strLen);

        char *t_data = data() + _pos;

        move(t_data + t_strLen, t_data, m_used + 1 - _pos);

        m_used += t_strLen;

        copy(t_data, _str, t_strLen);
	}

	template <class T>
	CArray<T> CString<T>::toArray() const
	{
		CArray<T> r_array(m_used + 1);

		copy(&r_array[0], c_str(), m_used + 1);

		return r_array;
	}

	template <class T>
	s32 CString<T>::toInt() const
	{
		return xtoi(c_str());
	}

	template <class T>
	u32 CString<T>::toUInt() const
	{
		return xtou(c_str());
	}

	template <class T>
	f32 CString<T>::toFloat() const
	{
		return xtof(c_str());
	}

	template <class T>
	f64 CString<T>::toDouble() const
	{
		return xtod(c_str());
	}

	template <class T>
	void CString<T>::count()
	{
		m_used = xstrlen(c_str());
	}

	template <class T>
	bool CString<T>::find(u32 &_outPos, u32 _startPos, T _char) const
	{
		for (u32 &i = _startPos; i < m_used; ++i)
		{
			if (at(i) == _char)
			{
				_outPos = i;
				return true;
			}
		}

		return false;
	}

	template <class T>
	bool CString<T>::fromFile(FILE *_file)
	{
		resize(filesize(_file));
		return freadall(static_cast<Byte*>(data()), size() * sizeof(T), _file);
	}

	template <class T>
	void CString<T>::_require(u32 _size)
	{
		FDASSERT(_size > 0);

		switch (m_mode)
		{
		case MODE_STATIC:
			if (_size > BUF_SIZE)
			{
				m_str = new T[_size];
				m_size = _size;
				m_mode = MODE_DYNAMIC;

				copy(m_str, m_buf, m_used + 1);
			}
			break;

		case MODE_DYNAMIC:
			if (_size > m_size)
			{
				T *m_oldStr = m_str;

				m_str = new T[_size];
				m_size = _size;

				copy(m_str, m_oldStr, m_used + 1);

				delete[] m_oldStr;
			}

			else if (_size <= BUF_SIZE)
			{
				m_mode = MODE_STATIC;

				if (m_used >= _size)
				{
					m_used = _size - 1;
				}

				copy(m_buf, m_str, m_used);
				m_buf[m_used] = 0;

				delete[] m_str;
				m_str = 0;
			}

			break;
		};
	}

	template <class T>
	void CString<T>::_copy(const T *_src, u32 _size)
	{
		FDASSERT(_size <= capacity());

		copy(data(), _src, _size);
	}

	template <class T>
	void CString<T>::_append(const T *_src, u32 _size)
	{
		FDASSERT(m_used + _size <= capacity());

		if (_size)
		{
			copy(data() + m_used, _src, _size);

			m_used += _size - 1;
		}
	}

	template <class T>
	std::ostream &operator << (std::ostream &_os, const CString<T> &_str)
	{
		_os << _str.c_str();
		return _os;
	}

	template <class T>
	CString<T> xescape(const T *_str)
	{
		CString<T> r_str;
		u32 t_reqLen = xstrlen(_str) * 2;
		r_str.resize(t_reqLen);
		xescape(r_str.data(), t_reqLen, _str);
		r_str.count();
		return r_str;
	}

}


#endif //STRING_H
