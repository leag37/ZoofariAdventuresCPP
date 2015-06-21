// Filename: CSpanTree.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core\ZoofariCore.h"

#include ZOOFARI_INCLUDE_HEADER(CMemNode)
#include ZOOFARI_INCLUDE_HEADER(Memory\CMemConst)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

class CSpanTree
{
public:
	CSpanTree() : m_Head(nullptr), m_FreeHead(nullptr), m_AllocatedBytes(0) {}
	CMemNode* Allocate(size_t inPageCount);

	CMemNode* Find(void* inAddress);

	void Release();

private:
	// Allocate
	void* AllocateInternal(size_t const inSize);
	void FreeInternal(void* inMem, size_t const inSize);

	void Insert(CMemNode * inNode);

private:
	// Mem node tree
	CMemNode* m_Head;

	// Free list of mem nodes
	CMemNode* m_FreeHead;

	// The amount allocated
	size_t m_AllocatedBytes;
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()