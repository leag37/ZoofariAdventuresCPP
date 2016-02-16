// Filename: CUniquePtr.inl
// Copyright 2015 Gael Huber

#include "CUniquePtr.h"
#include ZOOFARI_INCLUDE(Assert.h)
#include ZOOFARI_INCLUDE_STL(utility)

ZOOFARI_BEGIN_NAMESPACE(zoofari)

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
template <class TDerivedPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::CUniquePtr(CCreate<TDerivedPtr, TAllocatorPolicy> && inCreator)
	: m_Ptr(static_cast<TPtr*>(inCreator.Release()))
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::CUniquePtr(CUniquePtr && inOther)
	: m_Ptr(std::move(inOther.m_Ptr))
{
	inOther.m_Ptr = nullptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
template <class TDerivedPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::CUniquePtr(CUniquePtr<TDerivedPtr> && inOther)
	: m_Ptr(static_cast<TPtr*>(std::move(inOther.m_Ptr)))
{
	inOther.m_Ptr = nullptr;
}

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
	return *this;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
template <typename TDerivedPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr> & CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator=(CCreate<TDerivedPtr, TAllocatorPolicy> && inCreate)
{
	Destroy();
	m_Ptr = inCreator.Release();
	return *this;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr> & CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator=(CUniquePtr && inOther)
{
	if (this != &inOther)
	{
		Destroy();

		m_Ptr = inOther.m_Ptr;
		inOther.m_Ptr = nullptr;
	}
	return *this;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
template <class TDerivedPtr>
ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr> & CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator=(CUniquePtr<TDerivedPtr> && inOther)
{
	if (this != &inOther)
	{
		Destroy();
		m_Ptr = inOther.m_Ptr;
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
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator!=(CUniquePtr const & inOther) const
{
	return m_Ptr != inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
template <class TOtherPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator!=(CUniquePtr<TOtherPtr> const & inOther) const
{
	return m_Ptr != inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE bool CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator!=(nullptr_t /*inPtr*/) const
{
	return m_Ptr != nullptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE TPtr* CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::Get() const
{
	return m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE TPtr* CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator->() const
{
	return m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE TPtr & CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::operator*() const
{
	ZOOFARI_ASSERT(m_Ptr != nullptr);
	return *m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy, bool bAllowWeakPtr>
ZOOFARI_INLINE void CUniquePtr<TPtr, TAllocatorPolicy, bAllowWeakPtr>::Destroy()
{
	if (m_Ptr != nullptr)
	{
		TAllocatorPolicy allocator;
		allocator.Deallocate(m_Ptr);
		m_Ptr = nullptr;
	}
}

////-------------------------------------------------------------------------------------------------
//template <class TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, true>::CUniquePtr()
//	: TBase()
//	, m_Counter(nullptr)
//{
//}
//
////-------------------------------------------------------------------------------------------------
//template <class TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, true>::CUniquePtr(nullptr_t inPtr)
//	: TBase(inPtr)
//	, m_Counter(nullptr)
//{
//}
//
////-------------------------------------------------------------------------------------------------
//template <class TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, true>::CUniquePtr(CCreate<TPtr, TAllocatorPolicy> && inCreate)
//	: TBase(std::forward<CCreate<TPtr, TAllocatorPolicy>>(inCreate))
//	, m_Counter(TAllocatorPolicy::Create<ptrdetails::CRefCounter>(1)new TAllocatorPolicy(1))
//{
//}
//
////-------------------------------------------------------------------------------------------------
//template <class TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, true>::CUniquePtr(CUniquePtr && inOther)
//	: TBase(std::forward<CUniquePtr>(inOther))
//	, m_Counter(std::move(inOther.m_Counter))
//{
//	inOther.m_Counter = nullptr;
//}
//
////-------------------------------------------------------------------------------------------------
//template <class TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, true>::~CUniquePtr()
//{
//	Destroy();
//}
//
////-------------------------------------------------------------------------------------------------
//template <class TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, true> & CUniquePtr<TPtr, TAllocatorPolicy, true>::operator=(CCreate<TPtr, TAllocatorPolicy> && inCreate)
//{
//	Destroy();
//	TAllocatorPolicy policy;
//	m_Counter = ::new(policy.Allocate(sizeof(TPtr))) ptrdetails::CRefCounter(1);
//	return TBase::operator=(std::forward<CCreate<TPtr, TAllocatorPolicy>>(inCreate));
//}
//
////-------------------------------------------------------------------------------------------------
//template <class TPtr, class TAllocatorPolicy>
//template <class TDerivedPtr>
//ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, true> & CUniquePtr<TPtr, TAllocatorPolicy, true>::operator=(CCreate<TDerivedPtr, TAllocatorPolicy> && inCreate)
//{
//	Destroy();
//	TAllocatorPolicy policy;
//	m_Counter = ::new(policy.Allocate(sizeof(TPtr))) ptrdetails::CRefCounter(1);
//	return TBase::operator=(std::forward<CCreate<TDerivedPtr, TAllocatorPolicy>>(inCreate));
//}
//
////-------------------------------------------------------------------------------------------------
//template <class TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CUniquePtr<TPtr, TAllocatorPolicy, true> & CUniquePtr<TPtr, TAllocatorPolicy, true>::operator=(CUniquePtr && inOther)
//{
//	if (this != &inOther)
//	{
//		Destroy();
//
//		m_Counter = inOther.m_Counter;
//		inOther.m_Counter = nullptr;
//		return TBase::operator=(std::forward<CUniquePtr>(inOther));
//	}
//	return *this;
//}
//
////-------------------------------------------------------------------------------------------------
//template <class TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE void CUniquePtr<TPtr, TAllocatorPolicy, true>::Destroy()
//{
//	TBase::Destroy();
//
//	if (m_Counter != nullptr)
//	{
//		m_Counter->DecrementRef<true, true>();
//		
//		if (!m_Counter->HasWeakRef())
//		{
//			TAllocatorPolicy deleter;
//			deleter(m_Counter);
//			m_Counter = nullptr;
//		}
//	}
//}

ZOOFARI_END_NAMESPACE()