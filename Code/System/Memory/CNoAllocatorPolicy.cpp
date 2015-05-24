// Filename: CNoAllocatorPolicy.cpp
// Copyright 2015 Gael Huber
#include "CNoAllocatorPolicy.h"

#include ZOOFARI_INCLUDE_HEADER(core\Assert)
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
	return malloc(inSize);
}

void CNoAllocatorPolicy::Deallocate(TVoidPtr inAddr)
{
	ZOOFARI_ASSERT(inAddr != nullptr);
	free(inAddr);
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()