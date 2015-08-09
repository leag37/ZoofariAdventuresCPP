// Filename: Main.cpp
// Copyright 2015 Gael Huber

#include "Core/ZoofariCore.h"
#include ZOOFARI_INCLUDE(Core/CGameRoot.h)

#include ZOOFARI_INCLUDE_STL(iostream)
#include ZOOFARI_INCLUDE_STL(chrono)

int main(int argc, char** argv)
{
    auto start = std::chrono::high_resolution_clock::now();
    
	zoofari::game::core::CGameRoot root;
	root.Initialize();
	root.Run();
	root.Shutdown();
    
    // record end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << "Execution time: " << diff.count() << " s\n";


	return 0;
}