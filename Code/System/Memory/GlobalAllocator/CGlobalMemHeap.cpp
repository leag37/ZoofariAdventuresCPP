// Filename: CGlobalMemHeap.cpp
// Copyright 2015 Gael Huber
#include "CGlobalMemHeap.h"

#include ZOOFARI_INCLUDE_HEADER(Memory\CMemConst)
#include ZOOFARI_INCLUDE_STL(new)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

CGlobalMemHeap::TVoid CGlobalMemHeap::InsertNode(CMemNode* inNode, TCSizeType inSizeClass, TCSizeType inClassIndex)
{
	ZOOFARI_ASSERT(m_Blocks[inClassIndex] == nullptr);

	// If the size of the class is less than or equal to a page, mark the size class
	if (inNode->m_PageCount <= 1)
	{
		// Determine the number of chunks to break the node into
		TCSizeType blockCount(inNode->m_PageCount * CMemConst::PAGE / inSizeClass);

		// Calculate increment interval (number of times a void pointer goes into the size class of choice)
		TCSizeType increment(inSizeClass / sizeof(TVoidPtr));

		// Break into blocks
		CMemBlock* block(nullptr);
		void* place(inNode->m_Span);
		for (TSizeType i(0); i < blockCount; ++i)
		{
			block = new(place) CMemBlock();
			block->m_Next = block + increment;
			place = block->m_Next;
		}
		block->m_Next = nullptr;

		// Store head block
		m_Blocks[inClassIndex] = static_cast<CMemBlock*>(inNode->m_Span);
	}
	else
	{
		m_Blocks[inClassIndex] = new(inNode->m_Span) CMemBlock();
	}
}

CGlobalMemHeap::TVoid CGlobalMemHeap::InsertBlocks(CMemBlock* inBlock, TCSizeType inClassIndex)
{
	// Find the last node in the blocks being inserted
	CMemBlock* pLastBlock(inBlock);
	while (pLastBlock->m_Next != nullptr)
	{
		pLastBlock = pLastBlock->m_Next;
	}

	// Set the next in the last block to next
	do
	{
		CMemBlock* pHead(m_Blocks[inClassIndex]);
		pLastBlock->m_Next = pHead;

		// Use compare exchange here to set m_Blocks[] to inBlock when pHead==m_Blocks[]
		m_Blocks[inClassIndex] = inBlock;
	} while (false); // TODO
}

CGlobalMemHeap::TVoidPtr CGlobalMemHeap::GetBlock(TCSizeType inClassIndex)
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
		}
	}
	return mem;
}

void CGlobalMemHeap::Clean()
{
	for (u32 i(0U); i < 256; ++i)
	{
		// Remove all mem blocks
		m_Blocks[i] = nullptr;
	}
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
