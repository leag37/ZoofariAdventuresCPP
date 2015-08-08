// Filename: CMemConst.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(memory)

class CMemConst
{
public:
    static size_t const KILOBYTE;/* = 1024;*/
    static size_t const PAGE;/* = 4U * KILOBYTE;*/
};

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()