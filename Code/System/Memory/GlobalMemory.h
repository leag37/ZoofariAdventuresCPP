// Filename: GlobalMemory.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core\Platform.h"

#include "GlobalAllocator\CGlobalAllocator.h"
//#include ZOOFARI_INCLUDE_STL(cstdlib)

//ZOOFARI_BEGIN_NAMESPACE(zoofari)

/** \addtogroup memory
 *	@{
 */

inline void * operator new(size_t inSize)
{
	using namespace zoofari::system::memory;
	return CGlobalAllocator::Get().Allocate(inSize);//malloc(inSize);
}

inline void * operator new[](size_t inSize)
{
	using namespace zoofari::system::memory;
	return CGlobalAllocator::Get().Allocate(inSize);//malloc(inSize);
}

inline void operator delete(void * inPtr)
{
	using namespace zoofari::system::memory;
	CGlobalAllocator::Get().Free(inPtr);// free(inPtr);
}

inline void operator delete[](void * inPtr)
{
	using namespace zoofari::system::memory;
	CGlobalAllocator::Get().Free(inPtr);// free(inPtr);
}

/** @} */

//ZOOFARI_END_NAMESPACE()