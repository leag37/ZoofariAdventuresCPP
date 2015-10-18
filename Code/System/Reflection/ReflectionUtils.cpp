// Filename: ReflectionUtils.cpp
// Copyright 2015 Gael Huber
#include "ReflectionUtils.h"

#include ZOOFARI_INCLUDE_STL(functional)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(reflection)

u64 GetUniqueClassID(std::string const & inClassName)
{
	std::hash<std::string> const classHash;
	return static_cast<u64>(classHash(inClassName));
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()