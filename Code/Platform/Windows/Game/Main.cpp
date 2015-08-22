// Filename: Main_win.cpp
// Copyright 2015 Gael Huber
#include <Windows.h>

#include "Core\CGameRoot.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	zoofari::game::core::CGameRoot root;
	root.Initialize();
	root.Run();
	root.Shutdown();

	return 0;
}