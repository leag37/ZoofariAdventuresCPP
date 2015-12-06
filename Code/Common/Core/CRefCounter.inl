// Filename: CRefCounter.cpp
// Copyright 2015 Gael Huber
#include "ZoofariCore.h"
#include ZOOFARI_INCLUDE(CRefCounter.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

template <bool bStrong, bool bWeak>
void CRefCounter::IncrementRef()
{
	if (bStrong)
	{
		m_StrongRef.FetchAdd(1, EMemoryOrder::Relaxed);
	}

	if (bWeak)
	{
		m_WeakRef.FetchAdd(1, EMemoryOrder::Relaxed);
	}
}

template <bool bStrong, bool bWeak>
void CRefCounter::DecrementRef()
{
	if (bStrong)
	{
		m_StrongRef.FetchSub(1, EMemoryOrder::Relaxed);
	}

	if (bWeak)
	{
		m_WeakRef.FetchSub(1, EMemoryOrder::Relaxed);
	}
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()