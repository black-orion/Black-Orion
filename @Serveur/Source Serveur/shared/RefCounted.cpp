#include "RefCounted.h"


IRefCounted::IRefCounted()
	: m_countOfReferences(SINGLE_REFERENCE_COUNT - 1)
{
}

IRefCounted::~IRefCounted()
{
	FDASSERT(m_countOfReferences == 0);
}

u32 IRefCounted::getCountOfReferences() const
{
	return m_countOfReferences;
}

bool IRefCounted::isUnique() const
{
	return (m_countOfReferences == SINGLE_REFERENCE_COUNT);
}

void boost::intrusive_ptr_add_ref(IRefCounted *_ref)
{
	++(_ref->m_countOfReferences);
}

void boost::intrusive_ptr_release(IRefCounted *_ref)
{
	FDASSERT(m_countOfReferences > 0);

	--(_ref->m_countOfReferences);

	if (_ref->m_countOfReferences == 0)
	{
		delete _ref;
	}
}
