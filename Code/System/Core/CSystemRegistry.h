// Filename: CSystemRegistry.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(CSingleton.h)
#include ZOOFARI_INCLUDE(Core/CUniquePtr.h)
#include ZOOFARI_INCLUDE(Core/ISystem.h)
#include ZOOFARI_INCLUDE(Reflection/Reflection.h)
#include ZOOFARI_INCLUDE(Stl/StlUnorderedMap.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(core)

/** \addtogroup system
 *	@{
 */

class CSystemRegistry : public CSingleton<CSystemRegistry>
{
public:
	template <class TSystem>
	common::core::CUniquePtr<TSystem> const & GetSystem() const;

	template <class TSystem>
	common::core::CUniquePtr<TSystem> const & CreateSystem();

private:
	CSystemRegistry();

	virtual ~CSystemRegistry();

private:
    // TODO: change to unordered_map and to u64
	unordered_map<u64, common::core::CUniquePtr<system::core::ISystem>> m_Systems;
	
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CSystemRegistry.inl)