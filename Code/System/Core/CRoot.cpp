// Filename: CRoot.cpp
// Copyright 2015 Gael Huber
#include "CRoot.h"

#include ZOOFARI_INCLUDE(Memory/GlobalAllocator/CGlobalAllocator.h)

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
	
	// Initialize render system
	//CPtr<CRenderSystem> pRenderSystem(m_Registry.Create<CRenderSystem>());

	// Initialize thread system
	//CPtr<CThreadSystem> pThreadSystem(m_Registry.Create<CThreadSystem>());
	//CMake<CThreadSystem>());
	//pThreadSystem->ReserveRenderThread();
	//pThreadSystem->RegisterMainThread();
	//pThreadSystem->Initialize();
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