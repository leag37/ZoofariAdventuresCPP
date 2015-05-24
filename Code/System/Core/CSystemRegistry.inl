// Filename: CSystemRegistry.inl
// Copyright 2015 Gael Huber
#include ZOOFARI_INCLUDE_HEADER(Core\Assert)
#include ZOOFARI_INCLUDE_HEADER(Core\CPtr)
#include ZOOFARI_INCLUDE_HEADER(Core\CUniquePtr)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(core)

template <class TSystem>
common::core::CPtr<TSystem> CSystemRegistry::GetSystem()
{
	//ZOOFARI_ASSERT
}

template <class TSystem>
common::core::CPtr<TSystem> CreateSystem()
{}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()