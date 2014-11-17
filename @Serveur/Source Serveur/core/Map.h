#ifndef CORE_MAP_H
#define CORE_MAP_H


#include "CoreBase.h"
#include "Pair.h"
#include "Array.h"


BEGIN_NAMESPACE_CORE
{

	template <class K, class V>
	class CMap
	{
	public:

		typedef CPair<K, V> Entry;

		CMap()
		{
		}

		CMap(u32 _size)
			: m_entries(_size)
		{
		}

		u32 size() const
		{
			return m_entries.size();
		}

		bool empty() const
		{
			return m_entries.empty();
		}

		void clear()
		{
			m_entries.clear();
		}

		V &at(K _key)
		{
			for (u32 i = 0; i < size(); ++i)
			{
				if (get(i).first == _key)
				{
					return get(i).second;
				}
			}

			return insert(_key);
		}

		const V &at(K _key) const
		{
			for (u32 i = 0; i < size(); ++i)
			{
				if (get(i).first == _key)
				{
					return get(i).second;
				}
			}

			return get(0);
		}

		V &operator [] (K _key)
		{
			return at(_key);
		}

		const V &operator [] (K _key) const
		{
			return at(_key);
		}

		Entry &get(u32 _pos)
		{
			return m_entries[_pos];
		}

		const Entry &get(u32 _pos) const
		{
			return m_entries[_pos];
		}

		void assign(const V &_value)
		{
		}

		V &insert(const K &_key, const V &_val)
		{
			m_entries.push_back(Entry(_key, _val));
			return m_entries.last().second;
		}

		V &insert(const K &_key)
		{
			m_entries.push_back(Entry(_key));
			return m_entries.last().second;
		}

		void erase(u32 _pos)
		{
			m_entries.erase_fast(_pos);
		}

		void erase_by_key(const K &_key)
		{
			FOR_EACH (m_entries, i)
			{
				if (m_entries[i].first == _key)
				{
					erase(i);
					return;
				}
			}
		}

		void erase_by_value(const V &_value)
		{
			FOR_EACH (m_entries, i)
			{
				if (m_entries[i].second == _value)
				{
					erase(i);
					if (i)
					{
						--i;
					}
				}
			}
		}

		bool find_key(const K &_key) const
		{
			FOR_EACH (m_entries, i)
			{
				if (m_entries[i].first == _key)
				{
					return true;
				}
			}

			return false;
		}

		bool find_value(const V &_value) const
		{
			FOR_EACH (m_entries, i)
			{
				if (m_entries[i].second == _value)
				{
					return true;
				}
			}

			return false;
		}

	protected:

		CArray<Entry> m_entries;

	};

};


#endif //CORE_MAP_H
