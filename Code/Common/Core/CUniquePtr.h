// Filename: CPtr.h
// Copyright 2015 Gael huber
#pragma once

#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(CCreate.h)
#include ZOOFARI_INCLUDE(CRefCounter.h)
#include ZOOFARI_INCLUDE(TypeTraits.h)
#include ZOOFARI_INCLUDE_STL(memory)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

/** \addtogroup common
 *	@{
 */

/**
 * CPtr is a standard reference to a pointer type. It acts as a simple wrapper for a raw pointer type.
 * @tparam TPtr The type stored in the unique pointer
 * @tparam TAllocatorPolicy The allocator type being used to allocate and free the object
 */
template <class TPtr, class TDeleter = std::default_delete<TPtr>, bool bAllowWeakPtr = traits::allow_weakptr<TPtr>::value>
class CUniquePtr
{
	ZOOFARI_COPY_PROTECT(CUniquePtr);

public:
	/**
	 * ctor
	 */
	CUniquePtr();

	/**
	 * ctor
	 * @param inPtr The null pointer to assign to this unique pointer
	 */
	CUniquePtr(nullptr_t inPtr);

	/**
	 * ctor
	 * @param inCreate The creation source for this pointer
	 */
	template <class TAllocatorPolicy>
	CUniquePtr(CCreate<TPtr, TAllocatorPolicy> && inCreate);

	/**
	 * ctor
	 * @tparam TDerivedPtr The derived pointer being constructed. This type will be stored into the base class.
	 * @param inCreate The creator for this pointer
	 */
	template <class TDerivedPtr, class TAllocatorPolicy>
	CUniquePtr(CCreate<TDerivedPtr, TAllocatorPolicy> && inCreate);

	/**
	 * move ctor
	 * @param inOther The unique pointer to move
	 */
	CUniquePtr(CUniquePtr && inOther);

	/**
	 * move ctor
	 * @tparam TDerivedPtr The derived pointer type
	 * @param inOther The unique pointer to move
	 */
	template <class TDerivedPtr>
	CUniquePtr(CUniquePtr<TDerivedPtr> && inOther);

	/**
	 * dtor
	 */
	virtual ~CUniquePtr();

	/**
	 * Assignment operator
	 * @param inPtr The null pointer
	 * @return Returns the assigned pointer
	 */
	CUniquePtr & operator=(nullptr_t inPtr);

	/**
	 * Assignment operator
	 * @param inCreate The creator of hte pointer to assign
	 * @return Returns the assigned pointer
	 */
	template <class TAllocatorPolicy>
	CUniquePtr & operator=(CCreate<TPtr, TAllocatorPolicy> && inCreate);

	/**
	 * Assignment operator
	 * @tparam TDerivedPtr The derived pointer type
	 * @param inCreate The creator of hte pointer to assign
	 * @return Returns the assigned pointer
	 */
	template <class TDerivedPtr, class TAllocatorPolicy>
	CUniquePtr & operator=(CCreate<TDerivedPtr, TAllocatorPolicy> && inCreate);

	/**
	 * Assignment operator
	 * @param inOther The pointer to assign
	 * @return Returns the assigned pointer
	 */
	CUniquePtr & operator=(CUniquePtr && inOther);

	/**
	 * Assignment operator
	 * @tparam TDerivedPtr The derived pointer type
	 * @param inOther The pointer to move
	 * @return Returns the assigned pointer
	 */
	template <class TDerivedPtr>
	CUniquePtr & operator=(CUniquePtr<TDerivedPtr> && inOther);

	/**
	 * Equality operator
	 * @param inOther The pointer against which to compare
	 * @return Returns true if the pointers are the same
	 */
	bool operator==(CUniquePtr const & inOther) const;

	/**
	 * Equality operator
	 * @tparam TDerivedPtr The derived pointer type
	 * @param inOther The pointer against which to compare
	 * @return Returns true if the pointers are the same
	 */
	template <class TDerivedPtr>
	bool operator==(CUniquePtr<TDerivedPtr> const & inOther) const;
	
	/**
	 * Equality operator
	 * @param inPtr The nullptr against which to compare
	 * @return Returns true if the stored pointer is null
	 */
	bool operator==(nullptr_t inPtr) const;

	/**
 	 * Inequality operator
	 * @param inOther The pointer against which to compare
	 * @return Returns true if the pointers are the same
	 */
	bool operator!=(CUniquePtr const & inOther) const;
	
	/**
	 * Inequality operator
	 * @tparam TDerivedPtr The derived pointer type
	 * @param inOther The pointer against which to compare
	 * @return Returns true if the pointers are the same
	 */
	template <class TDerivedPtr>
	bool operator!=(CUniquePtr<TDerivedPtr> const & inOther) const;

	/**
	 * Inquality operator
	 * @param inPtr The nullptr against which to compare
	 * @return Returns true if the stored pointer is null
	 */
	bool operator!=(nullptr_t inPtr) const;

	/**
	 * @return Returns a pointer to the object
	 */
	TPtr * Get() const;

	/**
	 * @return Returns the stored pointer
	 */
	TPtr * operator->() const;

	/**
	 * @return Returns the dereferenced stored pointer or asserts if invalid
	 */
	TPtr & operator*() const;

private:
	/**
	 * Destroy the underlying point if it exists
	 */
	void Destroy();

private:
	/**
	* Raw pointer
	*/
	TPtr* m_Ptr;
};

template <class TPtr, class TDeleter>
class CUniquePtr<TPtr, TDeleter, true> : public CUniquePtr<TPtr, TDeleter, false>
{
	typedef CUniquePtr<TPtr, TDeleter, false> TBase;

	ZOOFARI_COPY_PROTECT(CUniquePtr);

public:
	CUniquePtr();
	
	/**
	 * ctor
	 * @param inPtr The null pointer to assign to this unique pointer
	 */
	CUniquePtr(nullptr_t inPtr);

	/**
	 * ctor
	 * @param inCreate The creation source for this pointer
	 */
	template <class TAllocatorPolicy>
	CUniquePtr(CCreate<TPtr, TAllocatorPolicy> && inCreate);

	CUniquePtr(CUniquePtr && inOther);
	virtual ~CUniquePtr();

private:
	void Destroy();

private:
	CRefCounter * m_Counter;
};


/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CUniquePtr.inl)