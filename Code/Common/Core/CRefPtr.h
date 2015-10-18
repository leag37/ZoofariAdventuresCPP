// Filename: CRefPtr.h
// Copyright 2015 Gael Huber
#pragma once

#include "ZoofariCore.h"
#include ZOOFARI_INCLUDE(CRefCounter.h)
#include ZOOFARI_INCLUDE_STL(memory)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

template <class TPtr, class TDeleter = std::default_delete<TPtr>>
class CRefPtr
{
	template <class TPtr>
	friend class CWeakPtr;

	template <class TFromPtr>
	friend class CWeakPtr;
public:
	typedef TPtr ValueType;
	typedef TPtr * PtrType;
	typedef TPtr & RefType;
	typedef TPtr const * ConstPtrType;
	typedef TPtr const & ConstRefType;
	typedef CRefCounter * RefCounterPtrType;

public:
	CRefPtr();
	
	CRefPtr(CCreate<TPtr> && inCreator);

	template <class TFromPtr>
	CRefPtr(CCreate<TFromPtr> && inCreator);
	
	CRefPtr(nullptr_t inPtr);
	
	CRefPtr(CRefPtr && inOther);
	
	template <class TFromPtr>
	CRefPtr(CRefPtr<TFromPtr> && inOther);

	CRefPtr(CRefPtr const & inOther);

	template <class TFromPtr>
	CRefPtr(CRefPtr<TFromPtr> const & inOther);

	//template<class TFromPtr>
	//CRefPtr(CWeakPtr<TFromPtr> const & inWeak);
	//template<class TFromPtr>
	//CRefPtr(CWeakPtr<TFromPtr> && inWeakPtr);
	//CRefPtr(CWeakPtr<TPtr> const & inWeak);
	//CRefPtr(CWeakPtr<TPtr> && inWeakPtr);
	
	~CRefPtr();

	CRefPtr & operator=(CRefPtr && inOther);

	template <class TFromPtr>
	CRefPtr & operator=(CRefPtr<TFromPtr> && inOther);

	CRefPtr & operator=(CRefPtr const & inOther);

	template <class TFromPtr>
	CRefPtr & operator=(CRefPtr<TFromPtr> const & inOther);

	PtrType operator->() const;
	ConstRefType operator*() const;
	RefType operator*();
	PtrType Get() const;

private:
	void Set(ConstPtrType inPtr, CounterPtrType inCounter);
	
private:
	PtrType m_Ptr;
	RefCounterPtrType m_Counter;
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CRefPtr.inl)	