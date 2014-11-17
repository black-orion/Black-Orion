#ifndef CORE_ARRAY_H
#define CORE_ARRAY_H


#include "CoreBase.h"
#include "Debug.h"
#include "Util.h"


BEGIN_NAMESPACE_CORE
{

	template <class T>
	class CArray
	{
	public:

		class iterator
		{
		public:

			iterator()
				: m_element(0)
			{
			}

			iterator(T *_element)
				: m_element(_element)
			{
			}

			T &operator -> ()
			{
				return m_element;
			}

			T &operator * ()
			{
				return *m_element;
			}

			iterator &operator ++ ()
			{
				++m_element;
				return *this;
			}

			iterator operator ++ (const s32)
			{
				iterator r = *this;
				++m_element;
				return r;
			}

			iterator operator + (u32 _size)
			{
				return iterator(m_element + _size);
			}

			iterator operator - (u32 _size)
			{
				return iterator(m_element - _size);
			}

			void operator += (u32 _size)
			{
				m_element += _size;
			}

			void operator -= (u32 _size)
			{
				m_element -= _size;
			}

			bool operator == (const iterator &_iter)
			{
				return m_element == _iter.m_element;
			}

			bool operator != (const iterator &_iter)
			{
				return m_element != _iter.m_element;
			}

			bool operator < (const iterator &_iter)
			{
				return m_element < _iter.m_element;
			}

		private:

			T *m_element;

		};

		CArray();

		CArray(u32 _size);

		CArray(const CArray<T> &_other);

		~CArray();

		u32 size() const;

		bool empty() const;

		void clear();

		void destroy();

		void resize(u32 _size);

		void erase(u32 _pos, u32 _count = 1);

		//swaps the last element with the _pos element and pops the new last element
		//! use erase(..) if the element order must not be changed !
		void erase_fast(u32 _pos);

		//erases the first occurance of this value
		void erase_value(const T &_element);

		void erase_vfast(const T &_element);

		//erases all values that are equal to _element
		void erase_all(const T &_element);

		void erase_afast(const T &_element);

		void push_back(const T &_element);

		void push_front(const T &_element);

		void pop_back();

		void pop_front();

		void insert(u32 _pos, const T &_element);

		void insert(u32 _pos, const CArray<T> &_other);

		void fill(const T &_element);

		void fill(const T &_element, u32 _pos, u32 _count);

		void add(const CArray<T> &_other);

		void reverse();

		void sortAsc();

		void sortDesc();

		void swap(u32 _pos1, u32 _pos2);

		T &first();

		const T &first() const;

		T &last();

		const T &last() const;

		T &at(u32 _pos);

		const T &at(u32 _pos) const;

		T *content();

		const T *content() const;

		T &operator [] (u32 _pos);

		const T &operator [] (u32 _pos) const;

		bool contains(const T &_element) const;

		bool find(u32 &_out_resultindex, const T &_element, u32 _begin = 0) const;

		u32 getAppearances(const T &_element) const;

		u32 getReservedElementCount() const;

		void freeUnusedMemory();

		CArray<T> &operator << (const T &_element);

		void operator += (const CArray<T> &_other);

		CArray<T> &operator = (const CArray<T> &_other);

	private:

		T *m_content;

		u32 m_used;

		u32 m_size;

		enum {BASE_SIZE = 8, GROW_FACTOR = 2};

		inline void _realloc(u32 _size, u32 _offset = 0);

		inline bool _require(u32 _size, u32 _offset = 0);

	};


	template <class T>
	CArray<T>::CArray()
		: m_used(0)
		, m_size(BASE_SIZE)
	{
		m_content = new T[m_size];
	}

	template <class T>
	CArray<T>::CArray(u32 _size)
		: m_used(0)
		, m_size(_size ? _size : BASE_SIZE)
	{
		m_content = new T[m_size];
		m_used = m_size;
	}

	template <class T>
	CArray<T>::CArray(const CArray<T> &_other)
		: m_used(_other.m_used)
		, m_size(_other.m_size ? _other.m_size : BASE_SIZE)
	{

		m_content = new T[m_size];

		for (u32 i = 0; i < m_used; ++i)
		{
			m_content[i] = _other.m_content[i];
		}
	}

	template <class T>
	CArray<T>::~CArray()
	{
		delete[] m_content;
	}

	template <class T>
	u32 CArray<T>::size() const
	{
		return m_used;
	}

	template <class T>
	bool CArray<T>::empty() const
	{
		return (m_used == 0);
	}

	template <class T>
	void CArray<T>::clear()
	{
		m_used = 0;
	}

	template <class T>
	void CArray<T>::destroy()
	{
		m_used = 0;
		m_size = 0;
		delete[] m_content;
		m_content = 0;
	}

	template <class T>
	void CArray<T>::resize(u32 _size)
	{
		_require(_size);

		m_used = _size;
	}

	template <class T>
	void CArray<T>::erase(u32 _pos, u32 _count)
	{
		FDASSERT(_pos < m_used);

		if (_count >= m_used)
		{
			m_used = 0;
		}
		else
		{
			m_used -= _count;
		}

		for (; (_pos < m_used); ++_pos)
		{
			m_content[_pos] = m_content[_pos + _count];
		}
	}

	template <class T>
	void CArray<T>::erase_fast(u32 _pos)
	{
		FDASSERT(_pos < m_used);

		m_content[_pos] = m_content[m_used - 1];

		--m_used;
	}

	template <class T>
	void CArray<T>::erase_value(const T &_element)
	{
		for (u32 i = 0; i < m_used; ++i)
		{
			if (m_content[i] == _element)
			{
				erase(i);
				return;
			}
		}
	}

	template <class T>
	void CArray<T>::erase_vfast(const T &_element)
	{
		for (u32 i = 0; i < m_used; ++i)
		{
			if (m_content[i] == _element)
			{
				erase_fast(i);
				return;
			}
		}
	}

	template <class T>
	void CArray<T>::erase_all(const T &_element)
	{
		for (u32 i = 0; i < m_used; ++i)
		{
			if (m_content[i] == _element)
			{
				erase(i);
			}
		}
	}

	template <class T>
	void CArray<T>::erase_afast(const T &_element)
	{
		for (u32 i = 0; i < m_used; ++i)
		{
			if (m_content[i] == _element)
			{
				erase_fast(i);
			}
		}
	}

	template <class T>
	void CArray<T>::push_back(const T &_element)
	{
		FASSERT(m_size != 0);

		_require(m_used + 1);

		m_content[m_used++] = _element;
	}

	template <class T>
	void CArray<T>::push_front(const T &_element)
	{
		insert(0, _element);
	}

	template <class T>
	void CArray<T>::pop_back()
	{
		if (m_used)
		{
			m_used--;
		}
	}

	template <class T>
	void CArray<T>::pop_front()
	{
		erase(0);
	}

	template <class T>
	void CArray<T>::insert(u32 _pos, const T &_element)
	{
		_require(m_used + 1);

		if (_pos >= m_used)
		{
			_pos = m_used;
		}

		if (m_used)
		{
			for (u32 i = m_used; i > _pos; i--)
			{
				m_content[i] = m_content[i - 1];
			}
		}

		m_content[_pos] = _element;
		++m_used;
	}

	template <class T>
	void CArray<T>::insert(u32 _pos, const CArray<T> &_other)
	{
		if (_other.m_used == 0)
			return;

		if (_pos >= m_used)
		{
			_pos = m_used;
		}

		u32 t_newused = m_used + _other.m_used;

		_require(t_newused);

		u32 i;

		if (m_used)
		{
			for (i = t_newused; i >= _pos + _other.m_used; --i)
			{
				m_content[i] = m_content[i - _other.m_used];
			}
		}

		m_used = t_newused;

		for (i = 0; i < _other.m_used; ++i, ++_pos)
		{
			m_content[_pos] = _other.m_content[i];
		}
	}

	template <class T>
	void CArray<T>::fill(const T &_element)
	{
		for (u32 i = 0; i < m_used; ++i)
			m_content[i] = _element;
	}

	template <class T>
	void CArray<T>::fill(const T &_element, u32 _pos, u32 _count)
	{
		if (_pos + _count <= m_used)
		{
			_count = m_used + _count;
			for (u32 i = _pos; i < _count; ++i)
				m_content[i] = _element;
		}
	}

	template <class T>
	void CArray<T>::add(const CArray<T> &_other)
	{
		if (this != &_other &&
			_other.m_used)
		{
			u32 t_newusedsize = m_used + _other.m_used;
			_require(t_newusedsize);

			memcpy(&m_content[m_used], _other.m_content, _other.m_used);
			m_used = t_newusedsize;
		}
	}

	template <class T>
	void CArray<T>::reverse()
	{
		for (u32 i = 0, c = m_used >> 1; i < c; ++i)
		{
			sdk_swap(m_content[i], m_content[m_used - i - 1]);
		}
	}

	template <class T>
	void CArray<T>::sortAsc()
	{
		if (m_used > 1)
		{
			u32 t_pos = 0;
			u32 t_smallest = 0;
			bool t_found;
			u32 i;

			while (t_pos < m_used)
			{
				//find smallest
				t_found = false;
				t_smallest = t_pos;
				for (i = t_pos; i < m_used; ++i)
				{
					if (m_content[i] < m_content[t_smallest])
					{
						t_smallest = i;
						t_found = true;
					}
				}

				//swap
				if (t_found)
					sdk_swap(m_content[t_pos], m_content[t_smallest]);

				++t_pos;
			}
		}
	}

	template <class T>
	void CArray<T>::sortDesc()
	{
		sortAsc();
		reverse();
	}

	template <class T>
	void CArray<T>::swap(u32 _pos1, u32 _pos2)
	{
		FASSERT(_pos1 < m_used && "_pos1 is out of range!");
		FASSERT(_pos2 < m_used && "_pos2 is out of range!");

		sdk_swap(m_content[_pos1], m_content[_pos2]);
	}

	template <class T>
	T &CArray<T>::first()
	{
		FASSERT(m_used != 0);

		return m_content[0];
	}

	template <class T>
	const T &CArray<T>::first() const
	{
		FASSERT(m_used != 0);

		return m_content[0];
	}

	template <class T>
	T &CArray<T>::last()
	{
		FASSERT(m_used != 0);

		return m_content[m_used - 1];
	}

	template <class T>
	const T &CArray<T>::last() const
	{
		FASSERT(m_used != 0);

		return m_content[m_used - 1];
	}

	template <class T>
	T &CArray<T>::at(u32 _pos)
	{
		FASSERT(_pos >= m_used);

		return m_content[_pos];
	}

	template <class T>
	const T &CArray<T>::at(u32 _pos) const
	{
		FASSERT(_pos >= m_used);

		return m_content[_pos];
	}

	template <class T>
	T *CArray<T>::content()
	{
		return m_content;
	}

	template <class T>
	const T *CArray<T>::content() const
	{
		return m_content;
	}

	template <class T>
	T &CArray<T>::operator [] (u32 _pos)
	{
		return m_content[_pos];
	}

	template <class T>
	const T &CArray<T>::operator [] (u32 _pos) const
	{
		return m_content[_pos];
	}

	template <class T>
	bool CArray<T>::contains(const T &_element) const
	{
		for (u32 i = 0; i < m_used; ++i)
		{
			if (m_content[i] == _element)
				return true;
		}

		return false;
	}

	template <class T>
	bool CArray<T>::find(u32 &_out_resultindex, const T &_element, u32 _begin) const
	{
		for (u32 i = _begin; i < m_used; ++i)
		{
			if (m_content[i] == _element)
			{
				_out_resultindex = i;
				return true;
			}
		}

		return false;
	}

	template <class T>
	u32 CArray<T>::getAppearances(const T &_element) const
	{
		u32 r_app = 0;

		for (u32 i = 0; i < m_used; ++i)
		{
			if (m_content[i] == _element)
				++r_app;
		}

		return r_app;
	}

	template <class T>
	u32 CArray<T>::getReservedElementCount() const
	{
		return m_size;
	}

	template <class T>
	void CArray<T>::freeUnusedMemory()
	{
		_realloc(m_used);
	}

	template <class T>
	CArray<T> &CArray<T>::operator << (const T &_element)
	{
		push_back(_element);

		return (*this);
	}

	template <class T>
	void CArray<T>::operator += (const CArray<T> &_other)
	{
		add(_other);
	}

	template <class T>
	CArray<T> &CArray<T>::operator = (const CArray<T> &_other)
	{
		if (this != &_other)
		{
			delete[] m_content;
			m_size = _other.m_size;
			m_content = new T[m_size];
			m_used = _other.m_used;

			for (u32 i = 0; i < m_used; ++i)
				m_content[i] = _other.m_content[i];
		}

		return (*this);
	}

	template <class T>
	inline void CArray<T>::_realloc(u32 _size, u32 _offset)
	{
		if (_size == 0)
		{
			_size = BASE_SIZE;
		}

		m_size = _size;

		if (m_used > m_size)
		{
			m_used = m_size;
		}

		T *t_newcontent = new T[m_size];

		for (u32 i = 0, c = ((_offset > m_used) ? (0) : (m_used - _offset)); i < c; ++i)
		{
			t_newcontent[i + _offset] = m_content[i];
		}

		delete[] m_content;

		m_content = t_newcontent;
	}

	template <class T>
	inline bool CArray<T>::_require(u32 _size, u32 _offset)
	{
		if (m_size < _size)
		{
			u32 t_newSize = m_size * GROW_FACTOR;

			while (t_newSize < _size)
			{
				t_newSize *= GROW_FACTOR;
			}

			_realloc(t_newSize, _offset);

			return true;
		}

		return false;
	}
}


#endif //CORE_ARRAY_H
