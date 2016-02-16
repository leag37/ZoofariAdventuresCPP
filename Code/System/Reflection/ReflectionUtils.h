// Filename: ReflectionUtils.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"
#include ZOOFARI_INCLUDE_STL(string)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(reflection)

typedef u64 TReflectableClassID;

extern TReflectableClassID GetUniqueClassID(std::string const & inClassName);

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()