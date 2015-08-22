// Filename: CAtomic.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(CAtomicBase.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

/** \addtogroup core
 *  @{
 */

template <typename T>
class CAtomic : public atomic_details::CAtomicBase<T>
{
    typedef atomic_details::CAtomicBase<T> TBase;
public:
    CAtomic();
    CAtomic(T const inValue);
    CAtomic & operator=(T const inValue);
};

template <typename T>
class CAtomic<T*> : public atomic_details::CAtomicBase<T>
{
    typedef atomic_details::CAtomicBase<T> TBase;
    
public:
    CAtomic();
    CAtomic(T* const inValue);
    CAtomic & operator=(T* const inValue);
    
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CAtomic.inl)