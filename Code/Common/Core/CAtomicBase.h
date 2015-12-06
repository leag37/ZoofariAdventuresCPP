// Filename: CAtomicBase.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(EMemoryOrder.h)
#include ZOOFARI_INCLUDE_STL(atomic)
#include ZOOFARI_INCLUDE_STL(type_traits)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)
ZOOFARI_BEGIN_NAMESPACE(atomic_details)

/** \addtogroup core
 *  @{
 */

template <typename T, bool = std::is_integral<T>::value || std::is_floating_point<T>::value>
class CAtomicBase
{
    ZOOFARI_COPY_PROTECT(CAtomicBase);
    
public:
    CAtomicBase();
    CAtomicBase(T const inDesired);
    CAtomicBase(CAtomicBase && inOther);
    virtual ~CAtomicBase();
    CAtomicBase & operator=(CAtomicBase && inOther);
    CAtomicBase & operator=(T const inDesired);
    
    T operator()() const;
    T Load(EMemoryOrder const inOrder = EMemoryOrder::SeqCst) const;
    void Store(T const inDesired, EMemoryOrder const inOrder = EMemoryOrder::SeqCst);
    bool CompareExchangeWeak(T & outExpected, T const inDesired, EMemoryOrder const inSuccessOrder, EMemoryOrder const inFailOrder);
    bool CompareExchangeStrong(T & outExpected, T const inDesired, EMemoryOrder const inOrder = EMemoryOrder::SeqCst);
    
protected:
    std::memory_order LookupOrder(EMemoryOrder const inOrder) const;
    
protected:
    // Underlying atomic value
    std::atomic<T> m_Value;
};

template <typename T>
class CAtomicBase<T, true> : public CAtomicBase<T, false>
{
    typedef CAtomicBase<T, false> TBase;
    
public:
    CAtomicBase();
    CAtomicBase(T const inValue);
    CAtomicBase & operator=(T const inValue);

	bool operator==(T const inValue) const;
	bool operator!=(T const inValue) const;
    
    T FetchAdd(T const inValue, EMemoryOrder const inOrder = EMemoryOrder::SeqCst);
    T FetchSub(T const inValue, EMemoryOrder const inOrder = EMemoryOrder::SeqCst);
    T FetchAnd(T const inValue, EMemoryOrder const inOrder = EMemoryOrder::SeqCst);
    T FetchOr(T const inValue, EMemoryOrder const inOrder = EMemoryOrder::SeqCst);
    T FetchXor(T const inValue, EMemoryOrder const inOrder = EMemoryOrder::SeqCst);
    T FetchMultiply(T const inValue, EMemoryOrder const inOrder = EMemoryOrder::SeqCst);
    T FetchDivide(T const inValue, EMemoryOrder const inOrder = EMemoryOrder::SeqCst);
    
    T operator++();
    T operator++(T const inValue);
    T operator+=(T const inValue);
    
    T operator--();
    T operator--(T const inValue);
    T operator-=(T const inValue);
    
    T operator&=(T const inValue);
    
    T operator|=(T const inValue);
    
    T operator^=(T const inValue);
    
    T operator*=(T const inValue);
    
    T operator/=(T const inValue);
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CAtomicBase.inl)
