// Filename	: MemNode.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core\ZoofariCore.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

class CMemNode
{
public:


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