// Filename: TypeTraits.h
// Copyright 2015 Gael huber
#pragma once

#include "Core/ZoofariCore.h"
ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(traits)

template <typename T>
struct allow_weakptr
{
	static const bool value = false;
};

template <typename T>
struct is_smart_ptr
{
	static const bool value = false;
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()