// Filename: CSpanTree.cpp
// Copyright 2015 Gael Huber
#include "CSpanTree.h"

#include ZOOFARI_INCLUDE_STL(cstdlib)
#include ZOOFARI_INCLUDE_STL(new)
#include ZOOFARI_INCLUDE_STL(algorithm)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

CSpanTree::CSpanTree()
	: m_Head(nullptr)
	, m_FreeHead(nullptr)
	, m_AllocatedBytes(0) 
	, m_NodeBytesToAlloc(0)
{
	// Find the least common multiple between CMemConst::PAGE and sizeof(CMemNode)
	size_t gcd(2);
	size_t const cMemNodeSize(sizeof(CMemNode));
	for (size_t gcdCandidate(gcd); gcdCandidate < cMemNodeSize; ++gcdCandidate)
	{
		if (((cMemNodeSize % gcdCandidate) == 0) && ((CMemConst::PAGE % gcdCandidate) == 0))
		{
			gcd = gcdCandidate;
		}
	}

	m_NodeBytesToAlloc = (cMemNodeSize * CMemConst::PAGE) / gcd;
}

CMemNode* CSpanTree::Allocate(size_t inSizeClass)
{
	// Do we have free mem nodes
	if (m_FreeHead == nullptr)
	{
		void* pFreeNodes(AllocateInternal(m_NodeBytesToAlloc));
		size_t const cMemNodeSize(sizeof(CMemNode));
		size_t const blocks(m_NodeBytesToAlloc / cMemNodeSize);
		for (size_t i(0); i < blocks; ++i)
		{
			CMemNode* node(new (pFreeNodes) CMemNode());
			node->m_Left = m_FreeHead;
			m_FreeHead = node;
			pFreeNodes = node + 1;
		}
	}

	// Pull a node off the free list
	CMemNode* choiceNode(m_FreeHead);
	m_FreeHead = m_FreeHead->m_Left;

	// Create the span 
	choiceNode->m_Span = AllocateInternal(std::max(CMemConst::PAGE, inSizeClass));
	choiceNode->m_PageCount = std::max(1U, static_cast<u32>(inSizeClass / CMemConst::PAGE));
	choiceNode->m_Left = nullptr;
	choiceNode->m_Right = nullptr;
	choiceNode->m_SizeClass = inSizeClass;
		
	// Insert into the span tree
	Insert(choiceNode);
		
	return choiceNode;
}

CMemNode* CSpanTree::Find(void* inAddress)
{
	ZOOFARI_ASSERT(inAddress != nullptr);
	ZOOFARI_ASSERT(m_Head != nullptr);

	CMemNode* result(m_Head);

	// Find the position in the tree.
	bool bFoundNode(false);
	do
	{
		// Compare the memory address to the span. If the address is within the span, return 0. If the 
		// address is less than the span range, return -1. If the address is greater than the span range, 
		// return 1.
		s32 const iCmpSpan(result->InSpan(inAddress));
		if ((iCmpSpan == -1) && (result->m_Left != nullptr))
		{
			result = result->m_Left;
		}
		else if ((iCmpSpan == 1) && (result->m_Right != nullptr))
		{
			result = result->m_Right;
		}
		else
		{
			bFoundNode = true;
		}
	} while (bFoundNode == false);

	return result;
}

void* CSpanTree::AllocateInternal(size_t const inSize)
{
	ZOOFARI_ASSERT(inSize > 0);

	// Track allocation
	m_AllocatedBytes += inSize;

	// Perform allocation
	return malloc(inSize);
}

void CSpanTree::FreeInternal(void* inMem, size_t const inSize)
{
	// Free the memory
	ZOOFARI_ASSERT(inMem != nullptr);
	free(inMem);

	// Track deallocation
	ZOOFARI_ASSERT(m_AllocatedBytes >= inSize);
	m_AllocatedBytes -= inSize;
}

void CSpanTree::Insert(CMemNode * inNode)
{
	if (m_Head == nullptr)
	{
		m_Head = inNode;
	}
	else
	{
		// Insert the node into the tree
		CMemNode* curr(m_Head);
		while (curr != nullptr)
		{
			// If the memory address is lower, go left
			if (inNode->m_Span < curr->m_Span)
			{
				// If the left child does not exist, proceed. Otherwise, set it.
				if (curr->m_Left != nullptr)
				{
					curr = inNode->m_Left;
				}
				else
				{
					curr->m_Left = inNode;
					inNode = nullptr;
					curr = nullptr;
				}
			}
			// If the address is higher, go right
			else
			{
				// If the right child does not exist, proceed. Otherwise, set it.
				if (curr->m_Right != nullptr)
				{
					curr = inNode->m_Right;
				}
				else
				{
					curr->m_Right = inNode;
					inNode = nullptr;
					curr = nullptr;
				}
			}
		}
	}
}

void CSpanTree::Release()
{
	// First, free all in-use spans
	while (m_Head != nullptr)
	{
		// Find the left-most child
		CMemNode* pNode(m_Head);
		bool bHasChild(true);
		do
		{
			if (pNode->m_Left != nullptr)
			{
				pNode = pNode->m_Left;
			}
			else if (pNode->m_Right != nullptr)
			{
				pNode = pNode->m_Right;
			}
			else
			{
				bHasChild = false;
			}
		} while (bHasChild);

		if (pNode == m_Head)
		{
			// Free node
			FreeInternal(m_Head->m_Span, m_Head->m_PageCount * CMemConst::PAGE);

			// Reset head internals
			m_Head->m_Span = nullptr;
			m_Head->m_PageCount = 0;
			m_Head->m_SizeClass = 0;

			// Remove the head node and add it to the free list
			m_Head->m_Left = m_FreeHead;
			m_FreeHead = m_Head;
			m_Head = nullptr;
		}
		else
		{
			// Free node
			FreeInternal(m_Head->m_Span, m_Head->m_PageCount * CMemConst::PAGE);

			// Reset head internals
			m_Head->m_Span = nullptr;
			m_Head->m_PageCount = 0;
			m_Head->m_SizeClass = 0;

			// Replace the current head with the leaf node
			pNode->m_Left = m_Head->m_Left == pNode ? nullptr : m_Head->m_Left;
			pNode->m_Right = m_Head->m_Right == pNode ? nullptr : m_Head->m_Right;

			m_Head->m_Left = m_FreeHead;
			m_FreeHead = m_Head;

			m_Head = pNode;
		}
	}

	// Second, sort free-list by address
	{
		CMemNode** pCurrNode(&m_FreeHead);
		// Iterate through list
		while (*pCurrNode != nullptr)
		{
			CMemNode* pSmallest = *pCurrNode;
			CMemNode* pSmallPrev = *pCurrNode;

			{
				// Find the smallest address node
				CMemNode* pNode(*pCurrNode);
				CMemNode* pNextNode((*pCurrNode)->m_Left);
				while (pNextNode != nullptr)
				{
					if (pNextNode < pSmallest)
					{
						pSmallest = pNextNode;
						pSmallPrev = pNode;
					}
					pNextNode = pNextNode->m_Left;
					pNode = pNode->m_Left;
				}
			}

			// Swap with smallest address node
			if (pSmallest != *pCurrNode)
			{
				// Store the current node and next nodes
				CMemNode* pNextNode = (*pCurrNode)->m_Left;
				CMemNode* pSmallNext = pSmallest->m_Left;

				// Swap lefts. If this is swapping direct neighbors, set smallest->left to the current node
				if (pNextNode == pSmallest)
				{
					pSmallest->m_Left = *pCurrNode;
					(*pCurrNode)->m_Left = pSmallNext;
				}
				else
				{
					pSmallest->m_Left = pNextNode;
					(*pCurrNode)->m_Left = pSmallNext;

					// Connect the larger node to the slot where the old smallest was
					pSmallPrev->m_Left = *pCurrNode;
				}
				

				// Now move the smallest into the current "head"
				*pCurrNode = pSmallest;
			}

			pCurrNode = &(*pCurrNode)->m_Left;
		}
	}

	// Third, free all items on free list
	size_t const cMemNodeSize(sizeof(CMemNode));
	size_t const cNodesPerPage(m_NodeBytesToAlloc / cMemNodeSize);
	while (m_FreeHead != nullptr)
	{
		// Store off head
		CMemNode* pOldHead(m_FreeHead);

		// Advance to the next allocated page
		for (size_t i(0); i < cNodesPerPage; ++i)
		{
			m_FreeHead = m_FreeHead->m_Left;
		}

		// Free the current page
		FreeInternal(pOldHead, m_NodeBytesToAlloc);
	}

	// At this point, there should be no dynamically allocated bytes
	ZOOFARI_ASSERT(m_AllocatedBytes == 0);
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()