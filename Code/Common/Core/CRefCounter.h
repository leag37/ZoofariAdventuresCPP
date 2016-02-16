// Filename: CRefCounter.h
// Copyright 2015 Gael Huber
#pragma once

#include "ZoofariCore.h"
#include ZOOFARI_INCLUDE(CAtomic.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(ptrdetails)

class CRefCounter
{
public:
	CRefCounter();
	CRefCounter(s32 const inInitRef);
	~CRefCounter();

	template <bool bStrong, bool bWeak>
	void IncrementRef();

	template <bool bStrong, bool bWeak>
	void DecrementRef();

	// @return Returns true if there is a valid strong reference to this counter
	bool HasStrongRef() const;

	bool HasWeakRef() const;

private:
	common::core::CAtomic<s32> m_StrongRef;
	common::core::CAtomic<s32> m_WeakRef;
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CRefCounter.inl)