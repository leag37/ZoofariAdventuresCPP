// Filename: GlobalMemory.h
// Copyright 2015 Gael Huber
#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(GlobalAllocator/CGlobalAllocator.h)

/** \addtogroup memory
 *	@{
 */

#if defined(ZOOFARI_USE_CUSTOM_ALLOCATOR)
ZOOFARI_GLOBAL void * operator new(size_t inSize)
 {
	using namespace zoofari::system::memory;
	return CGlobalAllocator::Get().Allocate(inSize);
 }
 
 ZOOFARI_GLOBAL void * operator new[](size_t inSize)
 {
	using namespace zoofari::system::memory;
	return CGlobalAllocator::Get().Allocate(inSize);
 }
 
 ZOOFARI_GLOBAL void operator delete(void * inPtr) noexcept
 {
	using namespace zoofari::system::memory;
	CGlobalAllocator::Get().Free(inPtr);
 }
 
 ZOOFARI_GLOBAL void operator delete[](void * inPtr) noexcept
 {
	using namespace zoofari::system::memory;
	CGlobalAllocator::Get().Free(inPtr);
 }
#endif

/** @} */