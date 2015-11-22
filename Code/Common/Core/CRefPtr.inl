// Filename	: CRefPtr.inl
// Copyright 2015 Gael Huber

#include "ZoofariCore.h"
#include ZOOFARI_INCLUDE(CRefPtr.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

//-------------------------------------------------------------------------------------------------
template <typename TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr()
	: m_Ptr(nullptr)
	, m_Counter(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
template <typename TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(CCreate<TPtr> && inCreator)
	: m_Ptr(inCreator.Release())
	, m_Counter(nullptr)
{
	TAllocatorPolicy allocator;
	void* ptr(allocator.Allocate(sizeof(TPtr)));
	m_Ptr = ::new (ptr) CRefCounter(1);
}

//template <typename TPtr, class TAllocatorPolicy>
//template <class TFromPtr>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(CCreate<TFromPtr> && inCreator);

//-------------------------------------------------------------------------------------------------
template <typename TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(nullptr_t inPtr)
	: m_Ptr(nullptr)
	, m_Counter(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
template <typename TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(CRefPtr && inOther)
	: m_Ptr(std::move(inOther.m_Ptr))
	, m_Counter(std::move(inOther.m_Counter))
{
	inOther.m_Ptr = nullptr;
	inOther.m_Counter = nullptr;
}

//template <typename TPtr, class TAllocatorPolicy>
//template <class TFromPtr>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(CRefPtr<TFromPtr, TAllocatorPolicy> && inOther);

//-------------------------------------------------------------------------------------------------
template <typename TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(CRefPtr const & inOther)
	: m_Ptr(inOther.m_Ptr)
	, m_Counter(inOther.m_Counter)
{
	if (m_Counter != nullptr)
	{
		m_Counter->IncrementRef<true, true>();
	}
}

//template <typename TPtr, class TAllocatorPolicy>
//template <class TFromPtr>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(CRefPtr<TFromPtr, TAllocatorPolicy> const & inOther);
//
//template <typename TPtr, class TAllocatorPolicy>
////template<class TFromPtr>
////ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(CWeakPtr<TFromPtr, TAllocatorPolicy> const & inWeak);
//
//template <typename TPtr, class TAllocatorPolicy>
////template<class TFromPtr>
////ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(CWeakPtr<TFromPtr, TAllocatorPolicy> && inWeakPtr);
//
//template <typename TPtr, class TAllocatorPolicy>
////ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(CWeakPtr<TPtr, TAllocatorPolicy> const & inWeak);
//
//template <typename TPtr, class TAllocatorPolicy>
////ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::CRefPtr(CWeakPtr<TPtr, TAllocatorPolicy> && inWeakPtr);

template <typename TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::~CRefPtr()
{
	Set(nullptr, nullptr);
}
//
//template <typename TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy> & CRefPtr<TPtr, TAllocatorPolicy>::operator=(CRefPtr && inOther);
//
//template <typename TPtr, class TAllocatorPolicy>
//template <class TFromPtr>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy> & CRefPtr<TPtr, TAllocatorPolicy>::operator=(CRefPtr<TFromPtr, TAllocatorPolicy> && inOther);
//
//template <typename TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy> & CRefPtr<TPtr, TAllocatorPolicy>::operator=(CRefPtr const & inOther);
//
//template <typename TPtr, class TAllocatorPolicy>
//template <class TFromPtr>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy> & CRefPtr<TPtr, TAllocatorPolicy>::operator=(CRefPtr<TFromPtr, TAllocatorPolicy> const & inOther);
//
//template <typename TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::PtrType CRefPtr<TPtr, TAllocatorPolicy>::operator->() const;
//
//template <typename TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::ConstRefType CRefPtr<TPtr, TAllocatorPolicy>::operator*() const;
//
//template <typename TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::RefType CRefPtr<TPtr, TAllocatorPolicy>::operator*();
//
//template <typename TPtr, class TAllocatorPolicy>
//ZOOFARI_INLINE CRefPtr<TPtr, TAllocatorPolicy>::PtrType CRefPtr<TPtr, TAllocatorPolicy>::Get() const;

template <typename TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE void CRefPtr<TPtr, TAllocatorPolicy>::Set(ConstPtrType inPtr, CounterPtrType inCounter)
{
	// Current pointer is valid, decrement reference and reset
	if (m_Ptr != nullptr && m_Ptr != inPtr))
	{
		// Decrement the ref counter
		m_Counter->DecrementRef<true, true>();
		
		// Delete the pointer if there are no more valid strong references
		if (!m_Counter->HasStrongRef())
		{
			TAllocatorPolicy policy;
			policy.Free(m_Ptr);
		}

		// Delete the counter if there are no more valid weak references (this will occur when all RefPtr 
		// and WeakPtrs have been destructed)
		if (!m_Counter->HasWeakRef())
		{
			TAllocatorPolicy policy;
			policy.Free(m_Counter);
		}
	}
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()