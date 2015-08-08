// Filename: CCreate.h
// Copyright 2015 Gael Huber
#pragma once

#include "ZoofariCore.h"

#include ZOOFARI_INCLUDE(Memory/CNoAllocatorPolicy.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

/** \addtogroup common
 *	@{
 */

template <class TPtr, class TAllocatorPolicy = system::memory::CNoAllocatorPolicy>
class CCreate
{
	ZOOFARI_COPY_PROTECT(CCreate);
public:
	template <typename... TArgs>
	explicit CCreate(TArgs &&... inArg);

	~CCreate();

	TPtr* Release();

private:
	TPtr* m_Ptr;
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CCreate.inl)