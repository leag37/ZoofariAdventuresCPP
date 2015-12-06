// Filename: CRefCounter.cpp
// Copyright 2015 Gael Huber
#include "ZoofariCore.h"
#include ZOOFARI_INCLUDE(CRefCounter.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

//-------------------------------------------------------------------------------------------------
CRefCounter::CRefCounter()
	: m_StrongRef(0)
	, m_WeakRef(0)
{
}

//-------------------------------------------------------------------------------------------------
CRefCounter::CRefCounter(s32 const inInitRef)
	: m_StrongRef(inInitRef)
	, m_WeakRef(inInitRef)
{
}

//-------------------------------------------------------------------------------------------------
CRefCounter::~CRefCounter()
{
	ZOOFARI_ASSERT(m_StrongRef == 0);
	ZOOFARI_ASSERT(m_WeakRef == 0);
}

//-------------------------------------------------------------------------------------------------
bool CRefCounter::HasStrongRef() const
{
	return m_StrongRef.Load() != 0;
}

//-------------------------------------------------------------------------------------------------
bool CRefCounter::HasWeakRef() const
{
	return m_WeakRef.Load() != 0;
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()