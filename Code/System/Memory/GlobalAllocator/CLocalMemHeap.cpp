// Filename: CLocalMemHeap.cpp
// Copyright 2015 Gael Huber
#include "CLocalMemHeap.h"

#include ZOOFARI_INCLUDE_HEADER(CMemNode)
#include ZOOFARI_INCLUDE_HEADER(Memory\CMemConst)

#include ZOOFARI_INCLUDE_STL(new)
#include ZOOFARI_INCLUDE_STL(algorithm)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

CLocalMemHeap::CLocalMemHeap() 
{
	// Initialize caches
	for (u32 i(0U); i < 256; ++i)
	{
		m_Length[i] = 0;
		m_MaxLength[i] = 0;
	}
}

CLocalMemHeap::~CLocalMemHeap() 
{}

CLocalMemHeap::TVoidPtr CLocalMemHeap::GetMem(TCSizeType inSize, TCSizeType inClassIndex)
{
	// If the index is 255, get large mem
	TVoidPtr mem(nullptr);
	if (inClassIndex == 255)
	{
		ZOOFARI_ERROR("TODO: Not implemented");
	}
	else
	{
		CMemBlock* block(m_Blocks[inClassIndex]);
		if (block != nullptr)
		{
			// Get the memory if there is a free block
			mem = block;
			m_Blocks[inClassIndex] = block->m_Next;
			
			// Decrement the length
			--m_Length[inClassIndex];

			ZOOFARI_ASSERT(m_Length[inClassIndex] != (0U - 1U));
		}
	}
	return mem; 
}

CMemBlock* CLocalMemHeap::FreeMem(TVoidPtr inAddr, TCSizeType inClassIndex, TCSizeType inSizeClass)
{
	CMemBlock* bReleasedBlocks(nullptr);

	// Lookup the block at the appropriate index
	if (inClassIndex != 255)
	{
		CMemBlock* block = new(inAddr)CMemBlock();

		CMemBlock** head = &m_Blocks[inClassIndex];

		// Update the head by pushing the new block onto the start of the queue.
		block->m_Next = (*head);
		*head = block;
		
		// Increase the size of the list. If the size now exeeds the maximum length, donate to the central list
		++m_Length[inClassIndex];

		if (m_Length[inClassIndex] > m_MaxLength[inClassIndex])
		{
			// Decrease size of total cache by calculating class size and decrementing
			m_CacheSize -= (m_MaxLength[inClassIndex] * inSizeClass);

			// Increase max length accordingly if it exceeds capacity. This helps a slow-start buildup of this block of memory
			m_MaxLength[inClassIndex] = m_Length[inClassIndex];

			// Flush the cache
			m_Length[inClassIndex] = 0;
			bReleasedBlocks = m_Blocks[inClassIndex];
			m_Blocks[inClassIndex] = nullptr;
		}
		else
		{
			// Decrease size of total cache by calculating class size and decrementing
			m_CacheSize += inSizeClass;

		}
	}
	else
	{
		ZOOFARI_ERROR("TODO: Not implemented");
	}

	// Return true if the cache is full for the requested size class
	return bReleasedBlocks;
}

CLocalMemHeap::TVoid CLocalMemHeap::DonateNode(CMemNode* inNode, TCSizeType inSizeClass, TCSizeType inClassIndex)
{
	ZOOFARI_ASSERT(m_Blocks[inClassIndex] == nullptr);

	// If the size of the class is less than or equal to a page, mark the size class
	if (inNode->m_PageCount <= 1)
	{
		// Mark the size class
		inNode->m_SizeClass = static_cast<u32>(inSizeClass);

		// Determine the number of chunks to break the node into
		TSizeType blockCount(inNode->m_PageCount * CMemConst::PAGE / inSizeClass);

		// Increase the cache size for the local size class
		m_MaxLength[inClassIndex] += blockCount;

		// Break into blocks
		CMemBlock* block(nullptr);
		void* place(inNode->m_Span);
		for (TSizeType i(0); i < blockCount; ++i)
		{
			block = new(place) CMemBlock();
			block->m_Next = block + 1;
			place = block->m_Next;
		}
		block->m_Next = nullptr;

		// Store head block
		m_Blocks[inClassIndex] = static_cast<CMemBlock*>(inNode->m_Span);
	}
	else
	{
		// Increase the cache size for the local size class
		m_MaxLength[inClassIndex]++;

		m_Blocks[inClassIndex] = new(inNode->m_Span) CMemBlock();
	}
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()