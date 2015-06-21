// Filename: CGlobalMemHeap.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core\ZoofariCore.h"

#include ZOOFARI_INCLUDE_HEADER(CMemBlock)
#include ZOOFARI_INCLUDE_HEADER(CMemNode)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

// Multi threaded mem heap. Has atomics in place to coordinate.
class CGlobalMemHeap
{
	ZOOFARI_COPY_PROTECT(CGlobalMemHeap);
	ZOOFARI_MOVE_PROTECT(CGlobalMemHeap);

public:
	typedef void* TVoidPtr;
	typedef void TVoid;
	typedef size_t TSizeType;
	typedef size_t const TCSizeType;

public:
	CGlobalMemHeap() {}
	~CGlobalMemHeap() {}

	TVoid InsertNode(CMemNode* inNode, TCSizeType inSizeClass, TCSizeType inClassIndex);
	TVoid InsertBlocks(CMemBlock* inBlock, TCSizeType inClassIndex);
	TVoidPtr GetBlock(TCSizeType inClassIndex);

	void Clean();

private:
	// Mem blocks
	CMemBlock* m_Blocks[256];

};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
