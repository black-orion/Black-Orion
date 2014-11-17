#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H


#include "CoreBase.h"
#include "Util.h"
#include "Debug.h"


BEGIN_NAMESPACE_CORE
{

	template <class T>
	class CVector
	{
	public:

		CVector()
			: m_content(0)
			, m_size(0)
		{
		}

		CVector(const CVector &_vector)
			: m_size(_vector.m_size)
		{
			m_content = new T[m_size];
			sdk::copy(m_content, _vector.m_content, m_size);
		}

		CVector(u32 _size)
		{
			if (_size > 0)
			{
				m_size = _size;

				m_content = new T[m_size];
			}
			else
			{
				m_size = 0;
				m_content = 0;
			}
		}

		~CVector()
		{
			delete[] m_content;
		}

		u32 size() const
		{
			return m_size;
		}

		bool empty() const
		{
			return m_size == 0;
		}

		u32 used() const
		{
			return m_size;
		}

		void clear()
		{
			delete[] m_content;
			m_content = 0;
			m_size = 0;
		}

		void resize(u32 _size)
		{
			_realloc(_size);
		}

		T &at(u32 _pos)
		{
			FASSERT(_pos < size());

			return get(_pos);
		}

		const T &at(u32 _pos) const
		{
			FASSERT(_pos < size());

			return get(_pos);
		}

		T &get(u32 _pos)
		{
			return m_content[_pos];
		}

		const T &get(u32 _pos) const
		{
			return m_content[_pos];
		}

		T &operator [] (u32 _pos)
		{
			return get(_pos);
		}

		const T &operator [] (u32 _pos) const
		{
			return get(_pos);
		}

		T &last()
		{
			return m_content[m_size - 1];
		}

		const T &last() const
		{
			return m_content[m_size - 1];
		}

		T &first()
		{
			return m_content[0];
		}

		const T &first() const
		{
			return m_content[0];
		}

		T *data()
		{
			return m_content;
		}

		const T *data() const
		{
			return m_content;
		}

		void assign(const T &_value)
		{
			for (u32 i = 0; i < size(); ++i)
			{
				m_content[i] = _value;
			}
		}

		bool contains(const T &_value) const
		{
			for (u32 i = 0; i < size(); ++i)
			{
				if (m_content[i] == _value)
				{
					return true;
				}
			}

			return false;
		}

		T *content()
		{
			return m_content;
		}

		const T *content() const
		{
			return m_content;
		}

		void push_back(const T &_value)
		{
			_realloc(m_size + 1);

			last() = _value;
		}

		void push_front(const T &_value)
		{
			_realloc(m_size + 1, 1);

			first() = _value;
		}

		void pop_back()
		{
			FDASSERT(!empty());

			_realloc(m_size - 1);
		}

		void pop_front()
		{
			erase(0);
		}

		void erase(u32 _pos, u32 _count = 1)
		{
			m_size -= _count;
			T *t_new = new T[m_size];

			if (_pos)
			{
				sdk::copy(t_new, m_content, _pos);
				sdk::copy(t_new + _pos, m_content + _pos + _count, size() - _pos);
			}
			else
			{
				sdk::copy(t_new, m_content + _count, size());
			}

			delete[] m_content;
			m_content = t_new;
		}

		bool erase_value(const T &_val)
		{
			for (u32 i = 0; i < size(); ++i)
			{
				if (get(i) == _val)
				{
					erase(i);
					return true;
				}
			}

			return false;
		}

		void erase_fast(u32 _pos)
		{
			get(_pos) = last();
			resize(size() - 1);
		}

		bool erase_vfast(const T &_val)
		{
			for (u32 i = 0; i < size(); ++i)
			{
				if (get(i) == _val)
				{
					erase_fast(i);
					return true;
				}
			}

			return false;
		}

	protected:

		T *m_content;

		u32 m_size;

		void _realloc(u32 _size)
		{
			T *t_new = new T[_size];
			sdk::copy(t_new, m_content, (_size < m_size ? _size : m_size));
			delete[] m_content;
			m_content = t_new;
			m_size = _size;
		}

		void _realloc(u32 _size, u32 _offset)
		{
			T *t_new = new T[_size];
			sdk::copy(t_new + _offset, m_content, (_size < m_size ? _size : m_size) - _offset);
			delete[] m_content;
			m_content = t_new;
			m_size = _size;
		}

	};

};


#endif //CORE_VECTOR_H
