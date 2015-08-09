// Filename: CNoAllocatorPolicy.cpp
// Copyright 2015 Gael Huber
#include "CNoAllocatorPolicy.h"

#include ZOOFARI_INCLUDE(Core/Assert.h)
#include ZOOFARI_INCLUDE(GlobalAllocator/CGlobalAllocator.h)

#include ZOOFARI_INCLUDE_STL(stdlib.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

CNoAllocatorPolicy::CNoAllocatorPolicy()
{}

CNoAllocatorPolicy::~CNoAllocatorPolicy()
{}

CNoAllocatorPolicy::TVoidPtr CNoAllocatorPolicy::Allocate(size_t inSize)
{
	return CGlobalAllocator::Get().Allocate(inSize);
	//return malloc(inSize);
}

void CNoAllocatorPolicy::Deallocate(TVoidPtr inAddr)
{
	ZOOFARI_ASSERT(inAddr != nullptr);
	CGlobalAllocator::Get().Free(inAddr);
	//free(inAddr);
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()