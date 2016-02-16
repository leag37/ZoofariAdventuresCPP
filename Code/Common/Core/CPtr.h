// Filename: CPtr.h
// Copyright 2015 Gael huber
#pragma once

#include "Core/ZoofariCore.h"
#include "TypeTraits.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)

/** \addtogroup common
 *	@{
 */

/**
 * CPtr is a standard reference to a pointer type. It acts as a simple wrapper for a raw pointer type.
 */
template <class PType>
class CPtr
{
	template <class TDerivedPtr>
	friend class CPtr;

public:
	/**
	 * ctor
	 */
	CPtr() 
		: m_Ptr(nullptr)
	{}

	CPtr(PType * inPtr)
		: m_Ptr(inPtr)
	{}

	template <class TDerivedPtr>
	CPtr(CPtr<TDerivedPtr> const & inOther)
		: m_Ptr(static_cast<TDerivedPtr*>(inOther.m_Ptr))
	{
	}

	/**
	 * ctor
	 * @tParam PFromType The source type of the pointer
	 * @param inPtr The source pointer
	 */
	template <class PFromType>
    explicit CPtr(PFromType * inPtr)
		: m_Ptr(static_cast<PType*>(inPtr))
	{}

	template <class PtrWrapper>
	CPtr(PtrWrapper const & inPtrWrapper)
		: m_Ptr(static_cast<PType*>(inPtrWrapper.Get()))
	{
		static_assert(traits::is_smart_ptr<PtrWrapper>::value, "[CPtr] Type is not a smart pointer");
	}

	PType* Get() const { return m_Ptr; }

private:
	/**
	 * Raw pointer
	 */
	PType* m_Ptr;
};

template <class TPtr>
struct traits::is_smart_ptr<CPtr<TPtr>>
{
	static const bool value = true;
};

/** @} */

ZOOFARI_END_NAMESPACE()