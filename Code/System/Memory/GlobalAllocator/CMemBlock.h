// Filename: CMemBlock.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core\ZoofariCore.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

class CMemBlock
{
public:
	CMemBlock() {}

	CMemBlock* m_Next;
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()