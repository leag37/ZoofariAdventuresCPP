// Filename: GlobalAllocator.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core\ZoofariCore.h"

#include ZOOFARI_INCLUDE_HEADER(CLocalMemHeap)
#include ZOOFARI_INCLUDE_HEADER(CGlobalMemHeap)
#include ZOOFARI_INCLUDE_HEADER(CSpanTree)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

/** \addtogroup memory
 *	@{
 */

/**
 * Global memory allocator is the source for all memory allocations across the application.
 * Small allocations are as follows:
 * 8
 * 16
 * 32
 * 64
 * 128
 * 256
 * 512
 * 1024
 * 2048
 * 4096
 * Large allocations are as follows:
 * 8192
 * 12288
 * 16384
 * 20480
 * etc. Increasing by one page until 255 pages+
 */
class CGlobalAllocator
{
	ZOOFARI_COPY_PROTECT(CGlobalAllocator);

public:
	static CGlobalAllocator & Get();

	bool Initialize();
	void Shutdown();

	void* Allocate(size_t const inSize);
	void Free(void* inMem);

private:
	CGlobalAllocator();

	CGlobalAllocator(CGlobalAllocator &&);

	~CGlobalAllocator();

	size_t CalcClassIndexSmall(size_t inSizeClass);

private:
	// Global instance
	static CGlobalAllocator sGlobalAllocator;

	// Thread-local heap
	static thread_local CLocalMemHeap m_LocalHeap;

	// Central heap
	CGlobalMemHeap m_CentralHeap;

	// List of all spans
	CSpanTree m_SpanTree;

	size_t m_InUse;
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()