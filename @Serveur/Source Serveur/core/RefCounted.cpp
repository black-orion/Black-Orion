#include "stdmadainc.h"
#include "core/RefCounted.h"

namespace mada
{
        __mada_implement_root_class(RefCounted);

        RefCounted::RefCounted() : m_refCount(0)
        {
        }

        RefCounted::~RefCounted()
        {
                mada_assert(0 == m_refCount);
        }

        int RefCounted::getRefCount() const
        {
                return m_refCount;
        }

        ///\todo implement
        String RefCounted::getClassName() const
        {
                return "TODO";
        }

        ///\todo implement
        bool RefCounted::isInstanceOf(const String&) const
        {
                return false;
        }

        ///\todo implement
        bool RefCounted::isA(const String&) const
        {
                return false;
        }
}
