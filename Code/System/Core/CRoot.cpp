// Filename: CRoot.cpp
// Copyright 2015 Gael Huber
#include "CRoot.h"

#include ZOOFARI_INCLUDE(Memory/GlobalAllocator/CGlobalAllocator.h)
#include ZOOFARI_INCLUDE(Threads/CThreadSystem.h)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(system)
ZOOFARI_BEGIN_NAMESPACE(core)

//*************************************************************************************************
CRoot::CRoot()
{}

//*************************************************************************************************
CRoot::~CRoot()
{}

//*************************************************************************************************
void CRoot::Initialize()
{
	// Initialize Memory
	memory::CGlobalAllocator::Get().Initialize();

	// Initialize base systems (threading, rendering, physics, etc.)
	//---------------------------------------------------------------

	// Initialize thread system
	m_Registry = CCreate<CSystemRegistry>();
	CPtr<threads::CThreadSystem> const pThreadSystem(m_Registry->CreateSystem<threads::CThreadSystem>());
	//pThreadSystem->Initialize();

	// Initialize render system
	//CPtr<CRenderSystem> pRenderSystem(m_Registry.Create<CRenderSystem>());

	
}

//*************************************************************************************************
void CRoot::Shutdown()
{
	// Shutdown Memory
	memory::CGlobalAllocator::Get().Shutdown();

}

//*************************************************************************************************
void CRoot::Run()
{

}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()