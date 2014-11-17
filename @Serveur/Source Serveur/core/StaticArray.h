#ifndef CORE_STATICARRAY_H
#define CORE_STATICARRAY_H


#include "CoreBase.h"
#include "Util.h"


BEGIN_NAMESPACE_CORE
{

	template <class T, u32 N>
	class CStaticArray
	{
	public:

		CStaticArray()
		{
		}

		template <u32 P>
		CStaticArray(const CStaticArray<T, P> &_other)
		{
			u32 t_size = Min(N, P);

			for (u32 i = 0; i < t_size; ++i)
			{
				m_content[i] = _other[i];
			}
		}

		template <class U>
		CStaticArray(const CStaticArray<U, N> &_other)
		{
			for (u32 i = 0; i < N; ++i)
			{
				m_content[i] = static_cast<T>(_other[i]);
			}
		}

		u32 size() const
		{
			return N;
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

		T &first()
		{
			return m_content[0];
		}

		const T &first() const
		{
			return m_content[0];
		}

		T &last()
		{
			return m_content[size() - 1];
		}

		const T &last() const
		{
			return m_content[size() - 1];
		}

		void assign(const T &_value)
		{
			for (u32 i = 0; i < N; ++i)
			{
				m_content[i] = _value;
			}
		}

		T *content()
		{
			return m_content;
		}

		const T *content() const
		{
			return m_content;
		}

	private:

		T m_content[N];

	};

};


#endif //CORE_STATICARRAY_H
