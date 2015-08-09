// Filename: CPtr.h
// Copyright 2015 Gael huber
#pragma once

#include "Core/ZoofariCore.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

/** \addtogroup common
 *	@{
 */

/**
 * CPtr is a standard reference to a pointer type. It acts as a simple wrapper for a raw pointer type.
 */
template <class PType>
class CPtr
{
public:
	/**
	 * ctor
	 */
    CPtr();

	/**
	 * ctor
	 * @tParam PFromType The source type of the pointer
	 * @param inPtr The source pointer
	 */
	template <class PFromType>
    explicit CPtr(PFromType * inPtr);

private:
	/**
	 * Raw pointer
	 */
	PType* m_Ptr;
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()