// Filename	: CSingleton.h
// Author	: Gael Huber
// Created	: 2015.09.19
// Copyright 2015
#pragma once

#include "Core/ZoofariCore.h"
#include "Core/CUniquePtr.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(core)

/** \addtogroup system
 *	@{
 */

template <class TSingleton>
class CSingleton
{
	ZOOFARI_COPY_PROTECT(CSingleton);
	ZOOFARI_MOVE_PROTECT(CSingleton);

public:
	typedef CUniquePtr<TSingleton> TPointer;

public:
	static TPointer const & GetInstance();
	static TPointer const & CreateInstance();
	static void DestroyInstance();

protected:
	CSingleton();
	virtual ~CSingleton();

private:
	static TPointer sInstance;
};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()

#include ZOOFARI_INCLUDE(CSingleton.inl)