// Filename: CLocalMemHeap.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(CMemBlock.h)
#include ZOOFARI_INCLUDE(CMemNode.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)


// Single threaded mem heap. Has no atomics.
class CLocalMemHeap
{
	ZOOFARI_COPY_PROTECT(CLocalMemHeap);

public:
	typedef void* TVoidPtr;
	typedef void TVoid;
	typedef size_t TSizeType;
	typedef size_t const TCSizeType;

public:
	CLocalMemHeap();
	~CLocalMemHeap();

	TVoidPtr GetMem(TCSizeType inSize, TCSizeType inClassIndex, TSizeType & outAllocatedSizeClass);
	CMemBlock* FreeMem(TVoidPtr inAddr, TCSizeType inClassIndex, TCSizeType inSizeClass);

	TVoid DonateNode(CMemNode* inNode, TCSizeType inSizeClass, TCSizeType inClassIndex);

	//CMemBlock* ReleaseNodes()

private:
	// Mem blocks
	CMemBlock* m_Blocks[256];

	size_t m_Length[256];
	size_t m_MaxLength[256];

	// Total size of the cache
	size_t m_CacheSize;

	// In use size of the cache
	//size_t m_InUseBytes;
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()