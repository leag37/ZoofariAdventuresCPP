// Filename: EMemoryOrder.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

#include <atomic>

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

enum class EMemoryOrder
{
    Relaxed,
    Consume,
    Acquire,
    Release,
    AcqRel,
    SeqCst
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()