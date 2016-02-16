// Filename: CSystemRegistry.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(CSingleton.h)
#include ZOOFARI_INCLUDE(Core/CPtr.h)
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
	CSystemRegistry();

	virtual ~CSystemRegistry();

	//template <class TSystem>
	//CPtr<TSystem> const GetSystem() const;

	template <class TSystem>
	CPtr<TSystem> const CreateSystem();

private:
	unordered_map<u64, CUniquePtr<ISystem>> m_Systems;
	
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CSystemRegistry.inl)