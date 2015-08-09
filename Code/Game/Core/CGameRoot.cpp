// Filename: CGameRoot.cpp
// Copyright 2015 Gael Huber
#include "CGameRoot.h"

#include ZOOFARI_INCLUDE(Stl/StlUtility.h)

#include ZOOFARI_INCLUDE(Core/CCreate.h)
#include ZOOFARI_INCLUDE(Memory/CNoAllocatorPolicy.h)

#include ZOOFARI_INCLUDE_STL(vector)

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(game)
ZOOFARI_BEGIN_NAMESPACE(core)

/*class Hello
{
public:
	Hello() {}
	Hello(int inA) : a(inA) {}
private:
	int a;
};*/

//*************************************************************************************************
CGameRoot::CGameRoot()
{}

//*************************************************************************************************
CGameRoot::~CGameRoot()
{}

//*************************************************************************************************
void CGameRoot::Initialize()
{
	CRoot::Initialize();

	//common::core::CUniquePtr<Hello> pHello = common::core::CCreate<Hello>();	
	//common::core::CUniquePtr<Hello> pHello2 = common::core::CCreate<Hello>(1);
	//
	//pHello = move(pHello2);

    for(s32 itr(0); itr < 10; ++itr)
    {
        std::vector<s32> vInt;

        for (s32 i(0); i < 40000000; ++i)
        {
            vInt.emplace_back(i);
        }
    }

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
{
	CRoot::Shutdown();
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()