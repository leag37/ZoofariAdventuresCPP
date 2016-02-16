// Filename: Root.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core/ZoofariCore.h"

#include ZOOFARI_INCLUDE(CSystemRegistry.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(core)

/**	\addtogroup system
 *	@{
 */

class CRoot
{
public:
	/**
	 * ctor
	 */
	CRoot();

	/**
	 * dtor
	 */
	virtual ~CRoot();

	/**
	 * Initialize the root
	 */
	virtual void Initialize();

	/**
	 * Shutdown the root
	 */
	virtual void Shutdown();

	/**
	 * Run the root
	 */
	virtual void Run();

protected:
	/**
	 * The system registry containing all primary subsystems
	 */
	CUniquePtr<CSystemRegistry> m_Registry;

	/**
	 * The system-level FSM
	 */
	//SystemFsm m_Fsm;

};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()