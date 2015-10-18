// Filename: CAtomicBase.inl
// Copyright 2015 Gael Huber

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)
ZOOFARI_BEGIN_NAMESPACE(atomic_details)

template <typename T, bool IsIntegral>
ZOOFARI_INLINE CAtomicBase<T, IsIntegral>::CAtomicBase()
{
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE CAtomicBase<T, IsIntegral>::CAtomicBase(T const inDesired)
: m_Value(inDesired)
{
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE CAtomicBase<T, IsIntegral>::CAtomicBase(CAtomicBase && inOther)
: m_Value(inOther.Load())
{
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE CAtomicBase<T, IsIntegral>::~CAtomicBase()
{
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE CAtomicBase<T, IsIntegral> & CAtomicBase<T, IsIntegral>::operator=(CAtomicBase && inOther)
{
    Store(inOther.Load());
    return *this;
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE CAtomicBase<T, IsIntegral> & CAtomicBase<T, IsIntegral>::operator=(T const inDesired)
{
    Store(inDesired);
    return *this;
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE T CAtomicBase<T, IsIntegral>::operator()() const
{
    return Load();
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE T CAtomicBase<T, IsIntegral>::Load(EMemoryOrder const inOrder) const
{
    return m_Value.load(LookupOrder(inOrder));
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE void CAtomicBase<T, IsIntegral>::Store(T const inDesired, EMemoryOrder const inOrder)
{
    m_Value.store(inDesired, LookupOrder(inOrder));
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE bool CAtomicBase<T, IsIntegral>::CompareExchangeWeak(T & outExpected, T const inDesired, EMemoryOrder const inSuccessOrder, EMemoryOrder const inFailOrder)
{
    return m_Value.compare_exchange_weak(outExpected, inDesired, LookupOrder(inSuccessOrder), LookupOrder(inFailOrder));
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE bool CAtomicBase<T, IsIntegral>::CompareExchangeStrong(T & outExpected, T const inDesired, EMemoryOrder const inOrder)
{
    return m_Value.compare_exchange_strong(outExpected, inDesired, LookupOrder(inOrder));
}

template <typename T, bool IsIntegral>
ZOOFARI_INLINE std::memory_order CAtomicBase<T, IsIntegral>::LookupOrder(EMemoryOrder const inOrder) const
{
    switch (inOrder)
    {
        case EMemoryOrder::Relaxed:
            return std::memory_order_relaxed;
        case EMemoryOrder::Consume:
            return std::memory_order_consume;
            
        case EMemoryOrder::Acquire:
            return std::memory_order_acquire;
            
        case EMemoryOrder::Release:
            return std::memory_order_release;
            
        case EMemoryOrder::AcqRel:
            return std::memory_order_acq_rel;
            
        case EMemoryOrder::SeqCst:
            return std::memory_order_seq_cst;
            
        default:
            ZOOFARI_ASSERT(!"Using unknown memory ordering, defaulting to sequentially consistent");
            return std::memory_order_seq_cst;
    }
}

template <typename T>
CAtomicBase<T, true>::CAtomicBase()
: TBase()
{
}

//--------------------------------------------------------------------------------------------------
template <typename T>
CAtomicBase<T, true>::CAtomicBase(T const inValue)
: TBase(inValue)
{
}

//--------------------------------------------------------------------------------------------------
template <typename T>
bool CAtomicBase<T, true>::operator==(T const inValue) const
{
	return Load() == inValue;
}

//--------------------------------------------------------------------------------------------------
template <typename T>
bool CAtomicBase<T, true>::operator!=(T const inValue) const
{
	return Load() != inValue;
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::FetchAdd(T const inValue, EMemoryOrder const inOrder)
{
    return TBase::m_Value.fetch_add(inValue, TBase::LookupOrder(inOrder));
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::FetchSub(T const inValue, EMemoryOrder const inOrder)
{
    return TBase::m_Value.fetch_sub(inValue, TBase::LookupOrder(inOrder));
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::FetchAnd(T const inValue, EMemoryOrder const inOrder)
{
    return TBase::m_Value.fetch_and(inValue, TBase::LookupOrder(inOrder));
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::FetchOr(T const inValue, EMemoryOrder const inOrder)
{
    return TBase::m_Value.fetch_or(inValue, TBase::LookupOrder(inOrder));
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::FetchXor(T const inValue, EMemoryOrder const inOrder)
{
    return TBase::m_Value.fetch_xor(inValue, TBase::LookupOrder(inOrder));
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::FetchMultiply(T const inValue, EMemoryOrder const inOrder)
{
    T expected = T();
    T current = T();
    
    do
    {
        current = TBase::Load(inOrder);
        expected = current * inValue;
        
    } while(!TBase::CompareExchangeStrong(current, expected, inOrder));
                                 
    return expected;
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::FetchDivide(T const inValue, EMemoryOrder const inOrder)
{
    T expected = T();
    T current = T();
    
    do
    {
        current = TBase::Load(inOrder);
        expected = current * inValue;
    } while(!TBase::CompareExchangeStrong(current, expected, inOrder));
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator++()
{
    return FetchAdd(1);
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator++(T const inValue)
{
    return FetchAdd(inValue);
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator+=(T const inValue)
{
    return FetchAdd(inValue);
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator--()
{
    return FetchSub(1);
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator--(T const inValue)
{
    return FetchSub(inValue);
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator-=(T const inValue)
{
    return FetchSub(inValue);
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator&=(T const inValue)
{
    return FetchAnd(inValue);
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator|=(T const inValue)
{
    return FetchOr(inValue);
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator^=(T const inValue)
{
    return FetchXor(inValue);
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator*=(T const inValue)
{
    return FetchMultiply(inValue);
}

//--------------------------------------------------------------------------------------------------
template <typename T>
T CAtomicBase<T, true>::operator/=(T const inValue)
{
    return FetchDivide(inValue);
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()