// Filename: CReflectionDefinition.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(reflection)

template <class TReflectableClass>
class CReflectionDefinition
{
	typedef typename TReflectableClass::CReflectableData TReflectableData;

public:
	CReflectionDefinition();

	CReflectionDefinition(TReflectableData && inData);

	u64 GetClassID() const;

private:
	u64 m_ClassID;
	TReflectableData m_Data;
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CReflectionDefinition.inl)