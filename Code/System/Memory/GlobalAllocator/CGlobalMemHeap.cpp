// Filename: CGlobalMemHeap.cpp
// Copyright 2015 Gael Huber
#include "CGlobalMemHeap.h"



#include ZOOFARI_INCLUDE(Memory/CMemConst.h)
#include ZOOFARI_INCLUDE_STL(new)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

CGlobalMemHeap::TVoid CGlobalMemHeap::InsertNode(CMemNode* inNode, TCSizeType inSizeClass, TCSizeType inClassIndex)
{
	// If the size of the class is less than or equal to a page, mark the size class
	if (inNode->m_PageCount == 1)
	{
		ZOOFARI_ASSERT(m_Blocks[inClassIndex] == nullptr);

		// Determine the number of chunks to break the node into
		TCSizeType blockCount(inNode->m_PageCount * CMemConst::PAGE / inSizeClass);

		// Calculate increment interval (number of times a void pointer goes into the size class of choice)
		TCSizeType increment(inSizeClass / sizeof(CMemBlock));

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
	else if (inNode->m_PageCount < 255)
	{
		ZOOFARI_ASSERT(m_Blocks[inClassIndex] == nullptr);
		CMemBlock* block(new(inNode->m_Span) CMemBlock());
		block->m_Next = m_Blocks[inClassIndex];
		m_Blocks[inClassIndex] = block;
		
	}
	else
	{
		// Insert a huge block, there may already be large blocks here
		CMemBlockHuge* block(new(inNode->m_Span) CMemBlockHuge());
		block->m_Next = m_Blocks[inClassIndex];
		block->m_PageCount = inNode->m_PageCount;
		m_Blocks[inClassIndex] = block;
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
		m_Blocks[inClassIndex] = inBlock/*pLastBlock*/;
	} while (false); // TODO
}

CGlobalMemHeap::TVoidPtr CGlobalMemHeap::GetBlock(TCSizeType inSize, TCSizeType inClassIndex, TSizeType & outAllocatedSizeClass)
{ 
	// If the index is 255, get large mem
	TVoidPtr mem(nullptr);
	if (inClassIndex == 255)
	{
		// Calculate number of pages
		size_t const uNumPages(inSize / CMemConst::PAGE);

		// Cast the block to a large block (which has some extra data attached such as number of pages, etc.
		CMemBlockHuge* pHugeBlock(static_cast<CMemBlockHuge*>(m_Blocks[inClassIndex]));
		CMemBlockHuge* pPreviousBlock(nullptr);
		while ((pHugeBlock != nullptr) && (pHugeBlock->m_PageCount < uNumPages))
		{
			pPreviousBlock = pHugeBlock;
			pHugeBlock = static_cast<CMemBlockHuge*>(pHugeBlock->m_Next);
		}

		// If a valid huge block is found, pull it from the list
		if (pHugeBlock != nullptr)
		{
			mem = pHugeBlock;
            outAllocatedSizeClass = pHugeBlock->m_PageCount * CMemConst::PAGE;

			// If the previous block does not exist, the selected block was the list start, so just destroy the list
			if (pPreviousBlock == nullptr)
			{
				m_Blocks[inClassIndex] = nullptr;
			}
			else
			{
				// In this case, the selected block is somewhere in the middle of the list, so just remove it
				pPreviousBlock->m_Next = pHugeBlock->m_Next;
			}
		}
	}
	else
	{
		CMemBlock* block(m_Blocks[inClassIndex]);
		if (block != nullptr)
		{
			// Get the memory if there is a free block
			mem = block;
            outAllocatedSizeClass = inSize;
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
