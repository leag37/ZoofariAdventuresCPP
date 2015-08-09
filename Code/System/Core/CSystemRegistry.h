// Filename: CSystemRegistry.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

//#include ZOOFARI_INCLUDE(Core/CPtr.h)
#include ZOOFARI_INCLUDE(Core/CUniquePtr.h)
#include ZOOFARI_INCLUDE(Stl/StlMap.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(core)

class ISystem;

/** \addtogroup system
 *	@{
 */

class CSystemRegistry
{
public:
	CSystemRegistry();

	~CSystemRegistry();

	//template <class TSystem>
	//common::core::CPtr<TSystem> GetSystem();

	//template <class TSystem>
	//common::core::CPtr<TSystem> CreateSystem();

private:
    // TODO: change to unordered_map and to u64
	map<unsigned long long, common::core::CUniquePtr<ISystem>> m_Systems;
	
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CSystemRegistry.inl)