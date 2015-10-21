// Filename: CUniquePtr.inl
// Copyright 2015 Gael Huber

#include "CUniquePtr.h"
#include ZOOFARI_INCLUDE(Assert.h)
#include ZOOFARI_INCLUDE_STL(utility)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::CUniquePtr()
	: m_Ptr(nullptr)
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::CUniquePtr(nullptr_t /*inPtr*/)
	: m_Ptr(nullptr)
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
template <class TAllocatorPolicy>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::CUniquePtr(CCreate<TPtr, TAllocatorPolicy> && inCreator)
	: m_Ptr(inCreator.Release())
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
template <class TDerivedPtr, class TAllocatorPolicy>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::CUniquePtr(CCreate<TDerivedPtr, TAllocatorPolicy> && inCreate)
	: m_Ptr(inCreator.Release())
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::CUniquePtr(CUniquePtr && inOther)
	: m_Ptr(std::move(inOther.m_Ptr))
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
template <class TOtherPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::CUniquePtr(CUniquePtr<TOtherPtr> && inOther)
	: m_Ptr(static_cast<TPtr*>(std::move(inOther.m_Ptr)))
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::~CUniquePtr()
{
	Destroy();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr> & CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator=(nullptr_t /*inPtr*/)
{
	Destroy();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
template <class TAllocator>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr> & CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator=(CCreate<TPtr, TAllocator> && inCreator)
{
	Destroy();
	m_Ptr = inCreator.Release();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
template <typename TDerivedPtr, class TAllocator>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr> & CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator=(CCreate<TDerivedPtr, TAllocator> && inCreate)
{
	Destroy();
	m_Ptr = inCreator.Release();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr> & CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator=(CUniquePtr && inOther)
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
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
template <class TDerivedPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, bAllowWeakPtr> & CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator=(CUniquePtr<TDerivedPtr> && inOther)
{
	if (this != &inOther)
	{
		Destroy();
		m_Ptr = std::move(inOther.m_Ptr);
		inOther.m_Ptr = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator==(CUniquePtr const & inOther) const
{
	return m_Ptr == inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
template <class TOtherPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator==(CUniquePtr<TOtherPtr> const & inOther) const
{
	return m_Ptr == inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator==(nullptr_t /*inPtr*/) const
{
	return m_Ptr == nullptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator!=(CUniquePtr const & inOther) const
{
	return m_Ptr != inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
template <class TOtherPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator!=(CUniquePtr<TOtherPtr> const & inOther) const
{
	return m_Ptr != inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator!=(nullptr_t /*inPtr*/) const
{
	return m_Ptr != nullptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE TPtr* CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::Get() const
{
	return m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE TPtr* CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator->() const
{
	return m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE TPtr & CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::operator*() const
{
	ZOOFARI_ASSERT(m_Ptr != nullptr);
	return *m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter, bool bAllowWeakPtr>
ZOOFARI_INLINE void CUniquePtr<TPtr, TDeleter, bAllowWeakPtr>::Destroy()
{
	if (m_Ptr != nullptr)
	{
		TDeleter deleter;
		deleter(m_Ptr);
	}
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, true>::CUniquePtr()
	: TBase()
	, m_Counter(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, true>::CUniquePtr(nullptr_t inPtr)
	: TBase(inPtr)
	, m_Counter(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter>
template <class TAllocatorPolicy>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, true>::CUniquePtr(CCreate<TPtr, TAllocatorPolicy> && inCreate)
	: TBase(std::forward<CCreate<TPtr, TAllocatorPolicy>>(inCreate))
	, m_Counter(new CRefCounter(1))
{
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, true>::CUniquePtr(CUniquePtr && inOther)
	: TBase(std::forward<CUniquePtr>(inOther))
	, m_Counter(std::move(inOther.m_Counter))
{
	inOther.m_Counter = nullptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter>
ZOOFARI_INLINE CUniquePtr<TPtr, TDeleter, true>::~CUniquePtr()
{
	Destroy();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TDeleter>
ZOOFARI_INLINE void CUniquePtr<TPtr, TDeleter, true>::Destroy()
{
	TBase::Destroy();

	if (m_Counter != nullptr)
	{
		m_Counter->DecrementRef<true, true>();
		
		if (!m_Counter->HasWeakRef())
		{
			TDeleter deleter;
			deleter(m_Counter);
		}
	}
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()