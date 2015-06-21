// Filename: CSpanTree.cpp
// Copyright 2015 Gael Huber
#include "CSpanTree.h"

#include ZOOFARI_INCLUDE_STL(cstdlib)
#include ZOOFARI_INCLUDE_STL(new)
#include ZOOFARI_INCLUDE_STL(algorithm)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

CMemNode* CSpanTree::Allocate(size_t inSizeClass)
{
	// Do we have free mem nodes
	if (m_FreeHead == nullptr)
	{
		void* pFreeNodes(AllocateInternal(CMemConst::PAGE));
		size_t const blocks(CMemConst::PAGE / sizeof(CMemNode));
		for (size_t i(0); i < blocks; ++i)
		{
			CMemNode* node(new (pFreeNodes) CMemNode());
			node->m_Left = m_FreeHead;
			m_FreeHead = node;
			pFreeNodes = node + 1;;
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
		if ((inAddress < result) && (result->m_Left != nullptr))
		{
			result = result->m_Left;
		}
		else if ((inAddress >= result) && (result->m_Right != nullptr))
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
		while (inNode != nullptr)
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

			// Remove the head node and add it to the free list
			m_Head->m_Left = m_FreeHead;
			m_FreeHead = m_Head;
			m_Head = nullptr;
		}
		else
		{
			// Free node
			FreeInternal(m_Head->m_Span, m_Head->m_PageCount * CMemConst::PAGE);

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
		CMemNode** pNode(&m_FreeHead);
		while (*pNode != nullptr)
		{
			// A left child exists, so compare against left
			CMemNode* pCurrNode(*pNode);
			CMemNode* pNextNode((*pNode)->m_Left);
			while (pNextNode != nullptr)
			{
				// If the next node address is less than the current node, swap
				if (pNextNode < *pNode)
				{
					// Swap the values. First, let's tell the "current" node what the next node will be pointer to
					pCurrNode->m_Left = *pNode;

					// Next, store off the left of the source node
					CMemNode* pLeft((*pNode)->m_Left);

					// Then, override the left of the source node with the left of the next node
					(*pNode)->m_Left = pNextNode->m_Left;

					// Then, set the left of the next node to the stored off left of the source node
					pNextNode->m_Left = pLeft;

					// Finally, set the source node to the next node
					*pNode = pNextNode;
				}

				// Advance
				pCurrNode = pCurrNode->m_Left;
				pNextNode = pNextNode->m_Left;
			}

			// Advance pNode
			pNode = &(*pNode)->m_Left;
		}
	}

	// Third, free all items on free list
	size_t const cNodesPerPage(CMemConst::PAGE / sizeof(CMemNode));
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
		FreeInternal(pOldHead, CMemConst::PAGE);
	}

	// At this point, there should be no dynamically allocated bytes
	ZOOFARI_ASSERT(m_AllocatedBytes == 0);
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()