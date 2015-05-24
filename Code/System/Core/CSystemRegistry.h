// Filename: CSystemRegistry.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core\Platform.h"

#include ZOOFARI_INCLUDE_HEADER(Core\CPtr)
#include ZOOFARI_INCLUDE_HEADER(Core\CUniquePtr)
#include ZOOFARI_INCLUDE_HEADER(Stl\StlMap)

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

	template <class TSystem>
	common::core::CPtr<TSystem> GetSystem();

	template <class TSystem>
	common::core::CPtr<TSystem> CreateSystem();

private:
	map<unsigned long long, common::core::CUniquePtr<ISystem>> m_Systems;
	
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE_INLINE(CSystemRegistry)