// Filename: CUniquePtr.inl
// Copyright 2015 Gael Huber

#include "CUniquePtr.h"
#include ZOOFARI_INCLUDE(Assert.h)
#include ZOOFARI_INCLUDE_STL(utility)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::CUniquePtr()
	: m_Ptr(nullptr)
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::CUniquePtr(nullptr_t /*inPtr*/)
	: m_Ptr(nullptr)
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::CUniquePtr(CCreate<TPtr, TAllocatorPolicy> && inCreator)
	: m_Ptr(inCreator.Release())
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
template <typename TDerivedPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::CUniquePtr(CCreate<TDerivedPtr, TAllocatorPolicy> && inCreate)
	: m_Ptr(inCreator.Release())
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::CUniquePtr(CUniquePtr && inOther)
	: m_Ptr(std::move(inOther.m_Ptr))
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
template <class TOtherPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::CUniquePtr(CUniquePtr<TOtherPtr> && inOther)
	: m_Ptr(static_cast<TPtr*>(std::move(inOther.m_Ptr)))
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::~CUniquePtr()
{
	Destroy();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr> & CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator=(nullptr_t /*inPtr*/)
{
	Destroy();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr> & CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator=(CCreate<TPtr, TAllocatorPolicy> && inCreator)
{
	Destroy();
	m_Ptr = inCreator.Release();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
template <typename TDerivedPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr> & CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator=(CCreate<TDerivedPtr, TAllocatorPolicy> && inCreate)
{
	Destroy();
	m_Ptr = inCreator.Release();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr> & CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator=(CUniquePtr && inOther)
{
	if (this != &inOther)
	{
		Destroy();

		m_Ptr = std::move(inOther.m_Ptr);
		inOther.m_Ptr = nullptr;
	}
	return *this;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
template <class TDerivedPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr> & CUniquePtr<TPtr, TAllocatorPolicy, bool bAllowWeakPtr>::operator=(CUniquePtr<TDerivedPtr> && inOther)
{
	if (this != &inOther)
	{
		Destroy();
		m_Ptr = std::move(inOther.m_Ptr);
		inOther.m_Ptr = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator==(CUniquePtr const & inOther) const
{
	return m_Ptr == inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
template <class TOtherPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator==(CUniquePtr<TOtherPtr> const & inOther) const
{
	return m_Ptr == inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator==(nullptr_t /*inPtr*/) const
{
	return m_Ptr == nullptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TAllocatorPolicy>::operator!=(CUniquePtr const & inOther) const
{
	return m_Ptr != inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
template <class TOtherPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TAllocatorPolicy>::operator!=(CUniquePtr<TOtherPtr> const & inOther) const
{
	return m_Ptr != inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TAllocatorPolicy>::operator!=(nullptr_t /*inPtr*/) const
{
	return m_Ptr != nullptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE TPtr* CUniquePtr<TPtr, TAllocatorPolicy>::Get() const
{
	return m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE TPtr* CUniquePtr<TPtr, TAllocatorPolicy>::operator->() const
{
	return m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE TPtr & CUniquePtr<TPtr, TAllocatorPolicy>::operator*() const
{
	ZOOFARI_ASSERT(m_Ptr != nullptr);
	return *m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE void CUniquePtr<TPtr, TAllocatorPolicy>::Destroy()
{
	if (m_Ptr != nullptr)
	{
		TAllocatorPolicy allocator;
		allocator.Deallocate(m_Ptr);
		m_Ptr = nullptr;
	}
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()