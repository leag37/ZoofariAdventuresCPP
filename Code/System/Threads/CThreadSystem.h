// Filename: CThreadSystem.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"
#include ZOOFARI_INCLUDE(Core/ISystem.h)
#include ZOOFARI_INCLUDE(Reflection/Reflection.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(threads)

class CThreadSystem : public core::ISystem
{
	ZOOFARI_DECLARE_REFLECTION(CThreadSystem);

public:
	CThreadSystem();
	virtual ~CThreadSystem();

private:

};

ZOOFARI_BEGIN_REFLECTION_DESCRIPTION(CThreadSystem)
ZOOFARI_END_REFLECTION_DESCRIPTION()

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()