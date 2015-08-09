// Filename: CPtr.h
// Copyright 2015 Gael huber
#pragma once

#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(Core/CCreate.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

/** \addtogroup common
*	@{
*/

/**
* CPtr is a standard reference to a pointer type. It acts as a simple wrapper for a raw pointer type.
*/
template <class TPtr, class TAllocatorPolicy = system::memory::CNoAllocatorPolicy>
class CUniquePtr
{
	ZOOFARI_COPY_PROTECT(CUniquePtr);

public:
	/**
	 * ctor
	 */
	CUniquePtr();

	CUniquePtr(nullptr_t inPtr);

	/**
	 * ctor
	 * @param inCreate The creation source for this pointer
	 */
	CUniquePtr(CCreate<TPtr, TAllocatorPolicy> && inCreate);

	CUniquePtr(CUniquePtr && inOther);

	template <class TOtherPtr>
	CUniquePtr(CUniquePtr<TOtherPtr> && inOther);

	~CUniquePtr();

	CUniquePtr & operator=(nullptr_t inPtr);

	CUniquePtr & operator=(CCreate<TPtr, TAllocatorPolicy> && inOther);

	CUniquePtr & operator=(CUniquePtr && inOther);

	bool operator==(CUniquePtr const & inOther) const;

	template <class TOtherPtr>
	bool operator==(CUniquePtr<TOtherPtr> const & inOther) const;

	bool operator!=(CUniquePtr const & inOther) const;

	template <class TOtherPtr>
	bool operator!=(CUniquePtr<TOtherPtr> const & inOther) const;

	TPtr* Get() const;

	TPtr* operator->() const;

	TPtr & operator*() const;

private:
	void Destroy();

private:
	/**
	* Raw pointer
	*/
	TPtr* m_Ptr;
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CUniquePtr.inl)