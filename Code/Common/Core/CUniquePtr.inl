// Filename: CUniquePtr.inl
// Copyright 2015 Gael Huber

#include ZOOFARI_INCLUDE_HEADER(Assert)
#include ZOOFARI_INCLUDE_STL(utility)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
CUniquePtr<TPtr, TAllocatorPolicy>::CUniquePtr()
	: m_Ptr(nullptr)
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
CUniquePtr<TPtr, TAllocatorPolicy>::CUniquePtr(nullptr_t /*inPtr*/);

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
CUniquePtr<TPtr, TAllocatorPolicy>::CUniquePtr(CCreate<TPtr, TAllocatorPolicy> && inCreator)
	: m_Ptr(inCreator.Release())
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
CUniquePtr<TPtr, TAllocatorPolicy>::CUniquePtr(CUniquePtr && inOther)
	: m_Ptr(std::move(inOther.m_Ptr))
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
template <class TOtherPtr>
CUniquePtr<TPtr, TAllocatorPolicy>::CUniquePtr(CUniquePtr<TOtherPtr> && inOther)
	: m_Ptr(static_cast<TPtr*>(std::move(inOther.m_Ptr)))
{}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
CUniquePtr<TPtr, TAllocatorPolicy>::~CUniquePtr()
{
	Destroy();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
CUniquePtr<TPtr, TAllocatorPolicy> & CUniquePtr<TPtr, TAllocatorPolicy>::operator=(nullptr_t /*inPtr*/)
{
	Destroy();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
CUniquePtr<TPtr, TAllocatorPolicy> & CUniquePtr<TPtr, TAllocatorPolicy>::operator=(CCreate<TPtr, TAllocatorPolicy> && inCreator)
{
	Destroy();

	inCreator = inCreator.Release();
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
CUniquePtr<TPtr, TAllocatorPolicy> & CUniquePtr<TPtr, TAllocatorPolicy>::operator=(CUniquePtr && inOther)
{
	if (this != &inOther)
	{
		Destroy();

		m_Ptr = std::move(inOther.m_Ptr);
		inOther.m_Ptr = nullptr;
	}
	return *this;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
bool CUniquePtr<TPtr, TAllocatorPolicy>::operator==(CUniquePtr const & inOther) const
{
	return m_Ptr == inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
template <class TOtherPtr>
bool CUniquePtr<TPtr, TAllocatorPolicy>::operator==(CUniquePtr<TOtherPtr> const & inOther) const
{
	return m_Ptr == inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
bool CUniquePtr<TPtr, TAllocatorPolicy>::operator!=(CUniquePtr const & inOther) const
{
	return m_Ptr != inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
template <class TOtherPtr>
bool CUniquePtr<TPtr, TAllocatorPolicy>::operator!=(CUniquePtr<TOtherPtr> const & inOther) const
{
	return m_Ptr != inOther.m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
TPtr* CUniquePtr<TPtr, TAllocatorPolicy>::Get() const
{
	return m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
TPtr* CUniquePtr<TPtr, TAllocatorPolicy>::operator->() const
{
	return m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
TPtr & CUniquePtr<TPtr, TAllocatorPolicy>::operator*() const
{
	ZOOFARI_ASSERT(m_Ptr != nullptr);
	return *m_Ptr;
}

//-------------------------------------------------------------------------------------------------
template <class TPtr, class TAllocatorPolicy>
void CUniquePtr<TPtr, TAllocatorPolicy>::Destroy()
{
	if (m_Ptr != nullptr)
	{
		TAllocatorPolicy allocator;
		allocator.Deallocate(m_Ptr);
		m_Ptr = nullptr;
	}
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()