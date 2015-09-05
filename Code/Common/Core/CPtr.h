// Filename: CPtr.h
// Copyright 2015 Gael huber
#pragma once

#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(CUniquePtr.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

/** \addtogroup common
 *	@{
 */

/**
 * CPtr is a standard reference to a pointer type. It acts as a simple wrapper for a raw pointer type.
 */
template <class TPtr>
class CPtr
{
public:
	/**
	 * ctor
	 */
    CPtr();

	explicit CPtr(CUniquePtr<TPtr> const & inPtr);

	template <class TAllocatorPolicy>
	explicit CPtr(CUniquePtr<TPtr, TAllocatorPolicy> const & inPtr);

	template <class TFromPtr>
	explicit CPtr(CUniquePtr<TFromPtr> const & inPtr);

	template <class TFromPtr, class TAllocatorPolicy>
	explicit CPtr(CUniquePtr<TPtr, TAllocatorPolicy> const & inPtr);

	explicit CPtr(CPtr const & inPtr);

	template <class TFromPtr>
	explicit CPtr(CPtr<TFromPtr> const & inPtr);

	explicit CPtr(CPtr && inPtr);

	template <class TFromPtr>
	explicit CPtr(CPtr<TFromPtr> && inPtr);

	~CPtr();

	CPtr & operator=(CUniquePtr<TPtr> const & inPtr);
	
	template <class TAllocatorPolicy>
	CPtr & operator=(CUniquePtr<TPtr, TAllocatorPolicy> const & inPtr);

	CPtr & operator=(CPtr const & inPtr);

	template <class TFromPtr>
	CPtr & operator=(CPtr<TFromPtr> const & inPtr);

	CPtr & operator=(CPtr && inPtr);

	template <class TFromPtr>
	CPtr & operator=(CPtr<TFromPtr> && inPtr);

	bool operator==(CPtr const & inPtr) const;

	template <class TFromPtr>
	bool operator==(CPtr<TFromPtr> const & inPtr) const;

	bool operator==(CUniquePtr<TPtr> const & inPtr) const;

	template <class TFromPtr>
	bool operator==(CUniquePtr<TFromPtr> const & inPtr) const;

	bool operator!=(CPtr const & inPtr) const;

	template <class TFromPtr>
	bool operator!=(CPtr<TFromPtr> const & inPtr) const;

	bool operator!=(CUniquePtr<TPtr> const & inPtr) const;

	template <class TFromPtr>
	bool operator!=(CUniquePtr<TFromPtr> const & inPtr) const;

	TPtr * Get() const;

	TPtr * operator->() const;

	TPtr & operator*() const;

private:
	explicit CPtr(TPtr * inPtr);

	/**
	* ctor
	* @tParam PFromType The source type of the pointer
	* @param inPtr The source pointer
	*/
	template <class TFromPtr>
	explicit CPtr(TFromPtr * inPtr);

public:
	static CPtr MakeFromRaw(TPtr * inPtr);

	template <class TFromPtr>
	static CPtr MakeFromRaw(TFromPtr * inPtr);

private:
	/**
	 * Raw pointer
	 */
	TPtr * m_Ptr;
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CPtr.inl)