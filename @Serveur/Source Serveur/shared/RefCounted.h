#ifndef REFCOUNTED_H
#define REFCOUNTED_H


#include "Base.h"


class IRefCounted;


namespace boost
{
    void intrusive_ptr_add_ref(IRefCounted *_ref);
    void intrusive_ptr_release(IRefCounted *_ref);
};


class IRefCounted
{
public:

	enum
	{
		SINGLE_REFERENCE_COUNT = 1
	};

	IRefCounted();
	virtual ~IRefCounted();

	u32 getCountOfReferences() const;
	bool isUnique() const;

	friend void ::boost::intrusive_ptr_add_ref(IRefCounted *_ref);
	friend void ::boost::intrusive_ptr_release(IRefCounted *_ref);

private:

	u32 m_countOfReferences;
};


#endif //REFCOUNTED_H
