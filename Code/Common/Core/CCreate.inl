// Filename: CCreate.inl
// Copyright 2015 Gael Huber
#include ZOOFARI_INCLUDE(Assert.h)
#include ZOOFARI_INCLUDE_STL(utility)

ZOOFARI_BEGIN_NAMESPACE(zoofari)

template <class TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE CCreate<TPtr, TAllocatorPolicy>::CCreate()
	: m_Ptr()
{
	TAllocatorPolicy allocator;
	void* ptr(allocator.Allocate(sizeof(TPtr)));
	::new (ptr) TPtr();
	m_Ptr = static_cast<TPtr*>(ptr);
}

template <class TPtr, class TAllocatorPolicy>
template <typename... TArgs>
inline CCreate<TPtr, TAllocatorPolicy>::CCreate(TArgs &&... inArgs)
	: m_Ptr(nullptr)
{
	TAllocatorPolicy allocator;
	void* ptr(allocator.Allocate(sizeof(TPtr)));
	::new (ptr) TPtr(std::forward<TArgs>(inArgs)...);
	m_Ptr = static_cast<TPtr*>(ptr);
}

template <class TPtr, class TAllocatorPolicy>
ZOOFARI_INLINE CCreate<TPtr, TAllocatorPolicy>::CCreate(CCreate && inOther)
	: m_Ptr(std::move(inOther.m_Ptr))
{
	inOther.m_Ptr = nullptr;
}

template <class TPtr, class TAllocatorPolicy>
inline CCreate<TPtr, TAllocatorPolicy>::~CCreate()
{
	ZOOFARI_ASSERT(m_Ptr == nullptr);
}

template <class TPtr, class TAllocatorPolicy>
CCreate<TPtr, TAllocatorPolicy> & CCreate<TPtr, TAllocatorPolicy>::operator=(CCreate && inOther)
{
	if (this != &inOther)
	{
		m_Ptr = std::move(inOther.m_Ptr);
		inOther.m_Ptr = nullptr;
	}
	return *this;
}

template <class TPtr, class TAllocatorPolicy>
inline TPtr* CCreate<TPtr, TAllocatorPolicy>::Release()
{
	TPtr* outResult(m_Ptr);
	m_Ptr = nullptr;
	return outResult;
}

ZOOFARI_END_NAMESPACE()