// Filename: CCreate.inl
// Copyright 2015 Gael Huber
#include ZOOFARI_INCLUDE(Assert.h)
#include ZOOFARI_INCLUDE_STL(utility)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

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
inline CCreate<TPtr, TAllocatorPolicy>::~CCreate()
{
	ZOOFARI_ASSERT(m_Ptr == nullptr);
}

template <class TPtr, class TAllocatorPolicy>
inline TPtr* CCreate<TPtr, TAllocatorPolicy>::Release()
{
	TPtr* outResult(m_Ptr);
	m_Ptr = nullptr;
	return outResult;
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()