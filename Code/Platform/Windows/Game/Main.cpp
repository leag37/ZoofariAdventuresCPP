// Filename: Main_win.cpp
// Copyright 2015 Gael Huber
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <tchar.h>

#include "Core\CGameRoot.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Set the current working directory
	TCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	size_t len(strlen(buffer));
	size_t lastIndex(0);
	for (auto i(0); i < len; ++i)
	{
		if (buffer[i] == '\\')
		{
			lastIndex = i;
		}
	}
	buffer[lastIndex + 1] = '\0';
	SetCurrentDirectory(buffer);

	// Initialize the game
	zoofari::game::core::CGameRoot root;
	root.Initialize();
	root.Run();
	root.Shutdown();

	return 0;
}