// Filename: Assert.h
// Copyright 2015 Gael Huber
#pragma once

#include "Platform.h"
#include ZOOFARI_INCLUDE_STL(cassert)

ZOOFARI_BEGIN_NAMESPACE(zoofari)

#define ZOOFARI_ASSERT(_statement) assert(_statement);

#define ZOOFARI_ERROR(x) assert(false);

ZOOFARI_END_NAMESPACE()