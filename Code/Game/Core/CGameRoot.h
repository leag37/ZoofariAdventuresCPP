// Filename: CGameRoot.h
// Copyright 2015 Gael Huber
#pragma once

#include "Core\CRoot.h"

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(game)
ZOOFARI_BEGIN_NAMESPACE(core)

/** \addtogroup game
 *	@{
 */

class CGameRoot : public system::core::CRoot
{
public:
	/**
	 * ctor
	 */
	CGameRoot();

	/**
	 * dtor
	 */
	~CGameRoot();

	/**
	 * @copydoc CRoot::Initialize()
	 */
	virtual void Initialize() override;

	/**
	 * @copydoc CRoot::Shutdown()
	 */
	virtual void Shutdown() override;

	/**
	 * @copydoc CRoot::Run()
	 */
	//virtual void Run() override;


};

/** @} */

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()