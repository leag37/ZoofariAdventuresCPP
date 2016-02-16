// Filename: CSystemRegistry.inl
// Copyright 2015 Gael Huber
#include "Core/ZoofariCore.h"
#include ZOOFARI_INCLUDE(Core/CCreate.h)

#include <unordered_map>
#include <utility>

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(core)

//template <class TSystem>
//ZOOFARI_INLINE CPtr<TSystem> const CSystemRegistry::GetSystem() const
//{
//	reflection::TReflectableClassID const classID(TSystem::GetReflectionDefinition().GetClassID());
//	auto const itr(m_Systems.find(classID));
//	ZOOFARI_ASSERT(itr != m_Systems.end());
//	//return itr->second;
//	return CPtr<TSystem>();
//}
//
template <class TSystem>
ZOOFARI_INLINE CPtr<TSystem> const CSystemRegistry::CreateSystem()
{
	// Get the class id and create a new system of the given type to place in the map
	system::reflection::TReflectableClassID const classID(TSystem::GetReflectionDefinition().GetClassID());
	ZOOFARI_ASSERT(m_Systems.find(classID) == m_Systems.end());
	//CUniquePtr<TSystem> pSystem(CCreate<TSystem>{});
	//CUniquePtr<ISystem> pISystem(std::move(pSystem));
	//CUniquePtr<ISystem> pISystem(CCreate<TSystem>());
	//CCreate<TSystem> create = (CCreate<TSystem>());
	//CUniquePtr<TSystem> pSystem (std::move(create));
	//pSystem = std::move(pSystem);
	//CCreate<TSystem> meow;
	//meow.Release();
	//CUniquePtr<ISystem> pISystem(CCreate<ISystem>());
	//CUniquePtr<ISystem> pISystem2;
	//if (pISystem == nullptr)
	//{
	//	return CPtr<TSystem>();
	//}
	auto result(m_Systems.emplace(classID, CCreate<TSystem>()));
	
	// Make sure the insertion was successful and return the resultant system
	ZOOFARI_ASSERT(result.second);
	auto const & itr(result.first);

	bool sp = traits::is_smart_ptr<CUniquePtr<TSystem>>::value;

	//return itr->second;
	CUniquePtr<ISystem> const & pISystem(itr->second);
	CPtr<ISystem> ppISystem(pISystem);
	//return CPtr<TSystem>(ppISystem);
	return CPtr<TSystem>(ppISystem.Get());
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()