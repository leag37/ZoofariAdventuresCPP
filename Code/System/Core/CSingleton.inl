// Filename	: CSingleton.h
// Author	: Gael Huber
// Created	: 2015.09.19
// Copyright 2015

#include "CSingleton.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(core)

//-------------------------------------------------------------------------------------------------
template <class TSingleton>
CUniquePtr<TSingleton> CSingleton<TSingleton>::sInstance = nullptr;

//-------------------------------------------------------------------------------------------------
template <class TSingleton>
ZOOFARI_INLINE CUniquePtr<TSingleton> const & CSingleton<TSingleton>::GetInstance() const
{
	ZOOFARI_ASSERT(sInstance != nullptr);
	return sInstance;
}

//-------------------------------------------------------------------------------------------------
template <class TSingleton>
ZOOFARI_INLINE CUniquePtr<TSingleton> const & CSingleton<TSingleton>::CreateInstance()
{
	ZOOFARI_ASSERT(sInstance == nullptr);
	sInstance = CCreate<TSingleton>();
	return sInstance;
}

//-------------------------------------------------------------------------------------------------
template <class TSingleton>
void CSingleton<TSingleton>::DestroyInstance()
{
	ZOOFARI_ASSERT(sInstance != nullptr);
	sInstance = nullptr;
}

//-------------------------------------------------------------------------------------------------
template <class TSingleton>
ZOOFARI_INLINE CSingleton<TSingleton>::CSingleton()
{
}

//-------------------------------------------------------------------------------------------------
template <class TSingleton>
ZOOFARI_INLINE CSingleton<TSingleton>::~CSingleton()
{
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()