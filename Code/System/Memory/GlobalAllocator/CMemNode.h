// Filename	: MemNode.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(Memory/CMemConst.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

class CMemNode
{
public:
	s32 InSpan(void const * inAddress) const
	{
		// Start of span address
		size_t const * pSpanStart(static_cast<size_t const *>(m_Span));

		// Calculate the number of pointers in a page to determine the end address of the span
		size_t const uPointersPerPage(CMemConst::PAGE / sizeof(size_t const *));
		size_t const * pSpanEnd(pSpanStart + (m_PageCount * uPointersPerPage));

		// Convert the parameter to a size_t pointer
		size_t const * pInAddress(static_cast<size_t const *>(inAddress));
		
		// Check if the address is within the span
		s32 result(0);
		if (pInAddress < pSpanStart)
		{
			result = -1;
		}
		else if (pInAddress >= pSpanEnd) // note that pSpanEnd is potentially the start of the next block of memory
		{
			result = 1;
		}

		return result;
	}

public:
	// A pointer to the span of pages this memory node owns
	void* m_Span;

	// A pointer to the next mem node
	CMemNode* m_Left;

	CMemNode* m_Right;

	// The number of pages allocated into the node owned by this span
	size_t m_PageCount;

	// The size class of the span in this node (this will either be a small value (<1 page) or a multiple of 4K
	size_t m_SizeClass;
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()