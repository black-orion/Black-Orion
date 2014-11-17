#include "core/Factory.h"
#include "core/Rtti.h"

namespace mada
{
        class RefCounted
        {
                __mada_declare_class(RefCounted);
        public:
                RefCounted();
                int getRefCount() const;
                void addRef();
                void release();

                String getClassName() const;
                bool isInstanceOf(const String&) const;
                bool isA(const String&) const;

        protected:
                virtual ~RefCounted();

        private:
                int m_refCount;
        };

        inline void RefCounted::addRef()
        {
                ++m_refCount;
        }

        inline void RefCounted::release()
        {
                if (0 == --m_refCount)
                {
                        mada_delete(this);
                }
        }

}
