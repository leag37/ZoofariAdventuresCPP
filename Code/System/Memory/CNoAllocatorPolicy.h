// Filename: CNoAllocatorPolicy.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core\Platform.h"
#include ZOOFARI_INCLUDE_HEADER(IAllocatorPolicy)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

/** \addtogroup memory
 *	@{
 */

class CNoAllocatorPolicy : public IAllocatorPolicy
{
public:
	CNoAllocatorPolicy();

	~CNoAllocatorPolicy();

	TVoidPtr Allocate(size_t inSize) override;

	void Deallocate(TVoidPtr inAddr) override;
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()