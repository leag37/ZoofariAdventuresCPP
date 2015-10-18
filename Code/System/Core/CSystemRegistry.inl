// Filename: CSystemRegistry.inl
// Copyright 2015 Gael Huber
#include "Core/ZoofariCore.h"
#include ZOOFARI_INCLUDE(Core/CCreate.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(core)

template <class TSystem>
ZOOFARI_INLINE common::core::CUniquePtr<TSystem> const & CSystemRegistry::GetSystem() const
{
	reflection::TReflectableClassID const classID(TSystem::GetReflectionDefinition().GetClassID());
	auto const itr(m_Systems.find(classID));
	ZOOFARI_ASSERT(itr != m_Systems.end());
	return itr->second;
}

template <class TSystem>
ZOOFARI_INLINE common::core::CUniquePtr<TSystem> const & CSystemRegistry::CreateSystem()
{
	// Get the class id and create a new system of the given type to place in the map
	reflection::TReflectableClassID const classID(TSystem::GetReflectionDefinition().GetClassID());
	ZOOFARI_ASSERT(m_Systems.find(classID) == m_Systems.end());
	auto const result(m_Systems.emplace(classID, common::core::CCreate<TSystem>()));
	
	// Make sure the insertion was successful and return the resultant system
	ZOOFARI_ASSERT(result.second);
	auto const & itr(result.first);
	return itr->second;
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()