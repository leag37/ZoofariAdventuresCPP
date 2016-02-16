// Filename: CReflectionDefinition.inl
// Copyright 2015 Gael Huber
#include "CReflectionDefinition.h"
#include ZOOFARI_INCLUDE(ReflectionUtils.h)
#include ZOOFARI_INCLUDE(Stl/StlUtility.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(reflection)

template <class TReflectableClass>
ZOOFARI_INLINE CReflectionDefinition<TReflectableClass>::CReflectionDefinition()
{
}

template <class TReflectableClass>
ZOOFARI_INLINE CReflectionDefinition<TReflectableClass>::CReflectionDefinition(TReflectableData && inData)
	: m_ClassID(GetUniqueClassID(inData.GetClassName()))
	, m_Data(forward<TReflectableData>(inData))
{
	
}

template <class TReflectableClass>
ZOOFARI_INLINE TReflectableClassID CReflectionDefinition<TReflectableClass>::GetClassID() const
{
	return m_ClassID;
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()