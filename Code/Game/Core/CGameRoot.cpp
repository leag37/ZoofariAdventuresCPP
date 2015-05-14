// Filename: CGameRoot.cpp
// Copyright 2015 Gael Huber
#include "CGameRoot.h"

#include ZOOFARI_INCLUDE_HEADER(Stl\StlVector)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(game)
ZOOFARI_BEGIN_NAMESPACE(core)

//*************************************************************************************************
CGameRoot::CGameRoot()
{}

//*************************************************************************************************
CGameRoot::~CGameRoot()
{}

//*************************************************************************************************
void CGameRoot::Initialize()
{
	// Setup FSM
	//CSharedPtr<CSystemFsmStartState> pStartState(CMake<CStartState>());
	//CSharedPtr<CSystemFsmInitState> pInitState(CMake<CSystemFsmInitState>());
	//
	//pStartState->AddTransition(pInitState, EFsmTransition::OK);
	//pStartState->AddTransition(pDoneState, EFsmTransition::FAIL);
	//m_Fsm.SetStartState(pStartState);
}

//*************************************************************************************************
void CGameRoot::Shutdown()
{}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()