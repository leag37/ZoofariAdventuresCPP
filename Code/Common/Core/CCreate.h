// Filename: CCreate.h
// Copyright 2015 Gael Huber
#pragma once

#include "ZoofariCore.h"

#include ZOOFARI_INCLUDE(Memory/CNoAllocatorPolicy.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)

/** \addtogroup common
 *	@{
 */

template <class TPtr, class TAllocatorPolicy = system::memory::CNoAllocatorPolicy>
class CCreate
{
	ZOOFARI_COPY_PROTECT(CCreate);
public:
	explicit CCreate();

	template <typename... TArgs>
	explicit CCreate(TArgs &&... inArg);

	CCreate(CCreate && inOther);

	~CCreate();

	CCreate & operator=(CCreate && inOther);

	TPtr* Release();

private:
	TPtr* m_Ptr;
};

/** @} */

ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CCreate.inl)