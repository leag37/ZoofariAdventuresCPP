// Filename: GlobalAllocator.cpp
// Copyright 2015 Gael Huber
#include "CGlobalAllocator.h"

#include ZOOFARI_INCLUDE(CMemNode.h)

#include ZOOFARI_INCLUDE(Stl/StlUtility.h)
#include ZOOFARI_INCLUDE_STL(algorithm)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

CGlobalAllocator CGlobalAllocator::sGlobalAllocator = zoofari::move(CGlobalAllocator());

// Thread-local heap
THREADLOCAL CLocalMemHeap* CGlobalAllocator::m_LocalHeap = nullptr;

CGlobalAllocator & CGlobalAllocator::Get()
{
	return sGlobalAllocator;
}

bool CGlobalAllocator::Initialize()
{
#if defined(ZOOFARI_USE_CUSTOM_ALLOCATOR)
	m_InUse = 0;
    
    m_LocalHeap = &m_LocalHeaps;
#endif
	return true;
}

void CGlobalAllocator::Shutdown()
{
#if defined(ZOOFARI_USE_CUSTOM_ALLOCATOR)
	// Shutdown the global allocator by freeing all memory in global heap. By this point, all memory should be returned
	// to global heap.
	m_CentralHeap.Clean();
	m_SpanTree.Release();

	// There should be no dynamic memory in use at this stage
	ZOOFARI_ASSERT(m_InUse == 0);
#endif
}

void* CGlobalAllocator::Allocate(size_t const inSize)
{
	ZOOFARI_ASSERT(inSize > 0);

	// Default to nullptr
	void* addr(nullptr);

	// Get size class and round allocation
	size_t sizeClass(std::max(inSize, static_cast<size_t>(8)));
	size_t classIndex = 1;

	if (inSize <= CMemConst::PAGE)
	{
		// This is a small allocation. Round to the nearest power of 2 with a minimum of 8 bytes
		--sizeClass;
		sizeClass |= sizeClass >> 1;
		sizeClass |= sizeClass >> 2;
		sizeClass |= sizeClass >> 4;
		sizeClass |= sizeClass >> 8;
		sizeClass |= sizeClass >> 16;
		sizeClass |= sizeClass >> 32;
		++sizeClass;

		// Calculate index of size class
		classIndex = CalcClassIndexSmall(sizeClass);
	}
	else
	{
		// This is a large allocation. Round to the closest page size.
		size_t remainder = sizeClass % CMemConst::PAGE;
		if (remainder != 0)
		{
			sizeClass = sizeClass + CMemConst::PAGE - remainder;
		}

		// Large allocations are encoded into sections upper array indices (10 -> 254, as 255 is reserved
		// for huge allocs). The smallest size class possible for a large allocation is 2 pages. 2 pages
		// must map to index 10, so the calculated class index must be incremented by 8 to have the proper
		// offset. 
		classIndex = (sizeClass / CMemConst::PAGE) + 8;
		classIndex = std::min(classIndex, static_cast<size_t>(255));
	}

	// First, get memory from the local heap
    size_t allocatedSizeClass;
	addr = m_LocalHeap->GetMem(sizeClass, classIndex, allocatedSizeClass);
	
	// If the local heap does not return a valid address, perform a lookup on the global heap
	if (addr == nullptr)
	{
		// Get a memory block from the central heap. The central heap donates a best fit node from the available nodes.
		addr = m_CentralHeap.GetBlock(sizeClass, classIndex, allocatedSizeClass);// m_CentralHeap.GetNode(sizeClass);

		// If no nodes are available, the allocate a new run of pages and give it to the local heap to chunk up and process.
		// A single span will always be owned by a single local heap.
		//if (node == nullptr)
		if(addr == nullptr)
		{
			// Allocate the span and register it with the span tree
			CMemNode* node = m_SpanTree.Allocate(sizeClass);
			m_CentralHeap.InsertNode(node, sizeClass, classIndex);
			addr = m_CentralHeap.GetBlock(sizeClass, classIndex, allocatedSizeClass);
		}
	}

	m_InUse += allocatedSizeClass;

	ZOOFARI_ASSERT(addr != nullptr);
	return addr;
}

void CGlobalAllocator::Free(void* inMem)
{
	// Ensure the address exists
	ZOOFARI_ASSERT(inMem != nullptr);

	// Lookup the memnode in the span tree
	CMemNode* pSource(m_SpanTree.Find(inMem));
	ZOOFARI_ASSERT(pSource != nullptr);

	// Free as a large alloc or a small alloc depending
	size_t classIndex(0);
	if (pSource->m_PageCount > 1)
	{
		classIndex = std::min(pSource->m_PageCount + 8, static_cast<size_t>(255));
	}
	else
	{
		classIndex = CalcClassIndexSmall(pSource->m_SizeClass);
	}

	// Return the memory to the local heap. If the local heap is filled, flush the cache to the global heap.
	CMemBlock* pReleasedBlocks = m_LocalHeap->FreeMem(inMem, classIndex, pSource->m_SizeClass);
	if (pReleasedBlocks != nullptr)
	{
		// Give the blocks back to the global heap
		m_CentralHeap.InsertBlocks(pReleasedBlocks, classIndex);
	}

    ZOOFARI_ASSERT(pSource->m_SizeClass <= m_InUse);
	m_InUse -= pSource->m_SizeClass;
}

CGlobalAllocator::CGlobalAllocator()
{
}

CGlobalAllocator::CGlobalAllocator(CGlobalAllocator &&)
{
}

CGlobalAllocator::~CGlobalAllocator()
{}

size_t CGlobalAllocator::CalcClassIndexSmall(size_t inSizeClass)
{
	size_t classIndex(1);
	if ((inSizeClass & 0xFFFF) == 0)
	{
		//inSizeClass >>= 16;
		//classIndex += 16;
	}
	if ((inSizeClass & 0xFF) == 0)
	{
		inSizeClass >>= 8;
		classIndex += 8;
	}
	if ((inSizeClass & 0xF) == 0)
	{
		inSizeClass >>= 4;
		classIndex += 4;
	}
	if ((inSizeClass & 0x3) == 0)
	{
		inSizeClass >>= 2;
		classIndex += 2;
	}
	classIndex -= (inSizeClass & 0x1);

	// 8 is the smallest possible index, which means at least 3 trailing zeros must exist
	classIndex -= 3;

	ZOOFARI_ASSERT(classIndex < 10);
	return classIndex;
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()