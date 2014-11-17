#ifndef CORE_PAIR_H
#define CORE_PAIR_H


#include "CoreBase.h"


BEGIN_NAMESPACE_CORE
{

	template <class A, class B>
	class CPair
	{
	public:

		A first;
		B second;

		CPair()
		{
		}

		CPair(const A &_first)
			: first(_first)
		{
		}

		CPair(const A &_first, const B &_second)
			: first(_first)
			, second(_second)
		{
		}

		CPair<B, A> flip() const
		{
			return CPair<B, A>(second, first);
		}

		bool operator == (const CPair &_pair) const
		{
			return first == _pair.first &&
				second == _pair.second;
		}

		bool operator != (const CPair &_pair) const
		{
			return !(*this == _pair);
		}

	};

	template <class A, class B>
	CPair<A, B> make_pair(const A &_a, const B &_b)
	{
		return CPair<A, B>(_a, _b);
	}

};


#endif //CORE_PAIR_H
