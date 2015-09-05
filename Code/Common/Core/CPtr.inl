// Filename: CPtr.inl
// Copyright 2015 Gael huber
#include "CPtr.h"

#include ZOOFARI_INCLUDE(Stl/StlUtility.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

template <class TPtr>
CPtr<TPtr>::CPtr()
	: m_Ptr(nullptr)
{
}

template <class TPtr>
CPtr<TPtr>::CPtr(CUniquePtr<TPtr> const & inPtr)
	: m_Ptr(inPtr)
{
}

template <class TPtr>
template <class TAllocatorPolicy>
CPtr<TPtr>::CPtr(CUniquePtr<TPtr, TAllocatorPolicy> const & inPtr)
	: m_Ptr(inPtr.Get())
{
}

template <class TPtr>
template <class TFromPtr>
CPtr<TPtr>::CPtr(CUniquePtr<TFromPtr> const & inPtr)
	: m_Ptr(static_cast<TPtr*>(inPtr.Get()))
{
}

template <class TPtr>
template <class TFromPtr, class TAllocatorPolicy>
CPtr<TPtr>::CPtr(CUniquePtr<TPtr, TAllocatorPolicy> const & inPtr)
	: m_Ptr(inPtr.Get())
{
}

template <class TPtr>
CPtr<TPtr>::CPtr(CPtr const & inPtr)
	: m_Ptr(inPtr.m_Ptr)
{
}

template <class TPtr>
template <class TFromPtr>
CPtr<TPtr>::CPtr(CPtr<TFromPtr> const & inPtr)
	: m_Ptr(static_cast<TPtr*>(inPtr.m_Ptr))
{
}

template <class TPtr>
CPtr<TPtr>::CPtr(CPtr && inPtr)
	: m_Ptr(move(inPtr.m_Ptr))
{
}

template <class TPtr>
template <class TFromPtr>
CPtr<TPtr>::CPtr(CPtr<TFromPtr> && inPtr)
	: m_Ptr(move(static_cast<TPtr*>(inPtr.m_Ptr)))
{
}

template <class TPtr>
CPtr<TPtr>::~CPtr()
{
}

template <class TPtr>
CPtr<TPtr> & CPtr<TPtr>::operator=(CUniquePtr<TPtr> const & inPtr)
{
	m_Ptr = inPtr.Get();
	return *this;
}

template <class TPtr>
template <class TAllocatorPolicy>
CPtr<TPtr> & CPtr<TPtr>::operator=(CUniquePtr<TPtr, TAllocatorPolicy> const & inPtr)
{
	m_Ptr = inPtr.Get();
	return *this;
}

template <class TPtr>
CPtr<TPtr> & CPtr<TPtr>::operator=(CPtr const & inPtr)
{
	if (this != &inPtr)
	{
		m_Ptr = inPtr.m_Ptr;
	}
	return *this;
}

template <class TPtr>
template <class TFromPtr>
CPtr<TPtr> & CPtr<TPtr>::operator=(CPtr<TFromPtr> const & inPtr)
{
	m_Ptr = static_cast<TPtr*>(inPtr.m_Ptr);
}

template <class TPtr>
CPtr<TPtr> & CPtr<TPtr>::operator=(CPtr && inPtr)
{
	if (this != &inPtr)
	{
		m_Ptr = move(inPtr.m_Ptr);
	}
	return *this;
}

template <class TPtr>
template <class TFromPtr>
CPtr<TPtr> & CPtr<TPtr>::operator=(CPtr<TFromPtr> && inPtr)
{
	m_Ptr = static_cast<TPtr*>(inPtr.m_Ptr);
}

template <class TPtr>
bool CPtr<TPtr>::operator==(CPtr const & inPtr) const
{
	return m_Ptr == inPtr.m_Ptr;
}

template <class TPtr>
template <class TFromPtr>
bool CPtr<TPtr>::operator==(CPtr<TFromPtr> const & inPtr) const
{
	return m_Ptr == inPtr.m_Ptr;
}

template <class TPtr>
bool CPtr<TPtr>::operator==(CUniquePtr<TPtr> const & inPtr) const
{
	return m_Ptr == inPtr.m_Ptr;
}

template <class TPtr>
template <class TFromPtr>
bool CPtr<TPtr>::operator==(CUniquePtr<TFromPtr> const & inPtr) const
{
	return m_Ptr == inPtr.m_Ptr;
}

template <class TPtr>
bool CPtr<TPtr>::operator!=(CPtr const & inPtr) const
{
	return m_Ptr != inPtr.m_Ptr;
}

template <class TPtr>
template <class TFromPtr>
bool CPtr<TPtr>::operator!=(CPtr<TFromPtr> const & inPtr) const
{
	return m_Ptr != inPtr.m_Ptr;
}

template <class TPtr>
bool CPtr<TPtr>::operator!=(CUniquePtr<TPtr> const & inPtr) const
{
	return m_Ptr != inPtr.m_Ptr;
}

template <class TPtr>
template <class TFromPtr>
bool CPtr<TPtr>::operator!=(CUniquePtr<TFromPtr> const & inPtr) const
{
	return m_Ptr != inPtr.m_Ptr
}

template <class TPtr>
TPtr * CPtr<TPtr>::Get() const
{
	return m_Ptr;
}

template <class TPtr>
TPtr * CPtr<TPtr>::operator->() const
{
	return m_Ptr;
}

template <class TPtr>
TPtr & CPtr<TPtr>::operator*() const
{
	ZOOFARI_ASSERT(m_Ptr != nullptr);
	return *m_Ptr;
}

template <class TPtr>
CPtr<TPtr>::CPtr(TPtr * inPtr)
	: m_Ptr(inPtr)
{
}

template <class TPtr>
template <class TFromPtr>
CPtr<TPtr>::CPtr(TFromPtr * inPtr)
	: m_Ptr(static_cast<TPtr*>(inPtr))
{
}

template <class TPtr>
CPtr<TPtr> CPtr<TPtr>::MakeFromRaw(TPtr * inPtr)
{
	return C_Ptr<TPtr>(inPtr);
}

template <class TPtr>
template <class TFromPtr>
CPtr<TPtr> CPtr<TPtr>::MakeFromRaw(TFromPtr * inPtr)
{
	return C_Ptr<TPtr>(inPtr);
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()