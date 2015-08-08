// Filename: IAllocatorPolicy.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

/** \addtogroup memory
*	@{
*/

class IAllocatorPolicy
{
public:
	typedef void* TVoidPtr;

public:
	IAllocatorPolicy() {}

	virtual ~IAllocatorPolicy() {}

	virtual TVoidPtr Allocate(size_t inSize) = 0;

	virtual void Deallocate(TVoidPtr inAddr) = 0;
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()