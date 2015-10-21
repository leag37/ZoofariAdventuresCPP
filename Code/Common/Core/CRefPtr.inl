// Filename	: CRefPtr.inl
// Copyright 2015 Gael Huber

#include "ZoofariCore.h"
#include ZOOFARI_INCLUDE(CRefPtr.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

//-------------------------------------------------------------------------------------------------
template <typename TPtr, class TDeleter>
ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr()
	: m_Ptr(nullptr)
	, m_Counter(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
template <typename TPtr, class TDeleter>
ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(CCreate<TPtr> && inCreator)
	: m_Ptr(inCreator.Release())
	, m_Counter(new CRefCounter(1))
{
}

//template <typename TPtr, class TDeleter>
//template <class TFromPtr>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(CCreate<TFromPtr, TDeleter> && inCreator);

//-------------------------------------------------------------------------------------------------
template <typename TPtr, class TDeleter>
ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(nullptr_t inPtr)
	: m_Ptr(nullptr)
	, m_Counter(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
template <typename TPtr, class TDeleter>
ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(CRefPtr && inOther)
	: m_Ptr(std::move(inOther.m_Ptr))
	, m_Counter(std::move(inOther.m_Counter))
{
	inOther.m_Ptr = nullptr;
	inOther.m_Counter = nullptr;
}

//template <typename TPtr, class TDeleter>
//template <class TFromPtr>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(CRefPtr<TFromPtr, TDeleter> && inOther);

//-------------------------------------------------------------------------------------------------
template <typename TPtr, class TDeleter>
ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(CRefPtr const & inOther)
	: m_Ptr(inOther.m_Ptr)
	, m_Counter(inOther.m_Counter)
{
	if (m_Counter != nullptr)
	{
		m_Counter->IncrementRef<true, true>();
	}
}

//template <typename TPtr, class TDeleter>
//template <class TFromPtr>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(CRefPtr<TFromPtr, TDeleter> const & inOther);
//
//template <typename TPtr, class TDeleter>
////template<class TFromPtr>
////ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(CWeakPtr<TFromPtr, TDeleter> const & inWeak);
//
//template <typename TPtr, class TDeleter>
////template<class TFromPtr>
////ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(CWeakPtr<TFromPtr, TDeleter> && inWeakPtr);
//
//template <typename TPtr, class TDeleter>
////ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(CWeakPtr<TPtr, TDeleter> const & inWeak);
//
//template <typename TPtr, class TDeleter>
////ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::CRefPtr(CWeakPtr<TPtr, TDeleter> && inWeakPtr);

template <typename TPtr, class TDeleter>
ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::~CRefPtr()
{
	Set(nullptr, nullptr);
}
//
//template <typename TPtr, class TDeleter>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter> & CRefPtr<TPtr, TDeleter>::operator=(CRefPtr && inOther);
//
//template <typename TPtr, class TDeleter>
//template <class TFromPtr>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter> & CRefPtr<TPtr, TDeleter>::operator=(CRefPtr<TFromPtr, TDeleter> && inOther);
//
//template <typename TPtr, class TDeleter>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter> & CRefPtr<TPtr, TDeleter>::operator=(CRefPtr const & inOther);
//
//template <typename TPtr, class TDeleter>
//template <class TFromPtr>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter> & CRefPtr<TPtr, TDeleter>::operator=(CRefPtr<TFromPtr, TDeleter> const & inOther);
//
//template <typename TPtr, class TDeleter>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::PtrType CRefPtr<TPtr, TDeleter>::operator->() const;
//
//template <typename TPtr, class TDeleter>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::ConstRefType CRefPtr<TPtr, TDeleter>::operator*() const;
//
//template <typename TPtr, class TDeleter>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::RefType CRefPtr<TPtr, TDeleter>::operator*();
//
//template <typename TPtr, class TDeleter>
//ZOOFARI_INLINE CRefPtr<TPtr, TDeleter>::PtrType CRefPtr<TPtr, TDeleter>::Get() const;

template <typename TPtr, class TDeleter>
ZOOFARI_INLINE void CRefPtr<TPtr, TDeleter>::Set(ConstPtrType inPtr, CounterPtrType inCounter)
{
	// Current pointer is valid, decrement reference and reset
	if (m_Ptr != nullptr && m_Ptr != inPtr))
	{
		// Decrement the ref counter
		m_Counter->DecrementRef<true, true>();
		
		// Delete the pointer if there are no more valid strong references
		if (!m_Counter->HasStrongRef())
		{
			TDeleter deleter;
			deleter(m_Ptr);
		}

		// Delete the counter if there are no more valid weak references (this will occur when all RefPtr 
		// and WeakPtrs have been destructed)
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