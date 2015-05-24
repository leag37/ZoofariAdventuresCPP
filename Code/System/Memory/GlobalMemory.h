// Filename: GlobalMemory.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core\Platform.h"

#include ZOOFARI_INCLUDE_STL(cstdlib)

ZOOFARI_BEGIN_NAMESPACE(zoofari)

/** \addtogroup memory
 *	@{
 */

inline void * operator new(size_t inSize)
{
	return malloc(inSize);
}

inline void * operator new(size_t /*inSize*/, void * inPtr)
{
	return inPtr;
}

inline void * operator new[](size_t inSize)
{
	return malloc(inSize);
}

inline void * operator new[](size_t /*inSize*/, void * inPtr)
{
	return inPtr;
}

inline void operator delete(void * inPtr)
{
	free(inPtr);
}

inline void operator delete[](void * inPtr)
{
	free(inPtr);
}

/** @} */

ZOOFARI_END_NAMESPACE()