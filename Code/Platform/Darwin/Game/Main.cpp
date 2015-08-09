// Filename: Main.cpp
// Copyright 2015 Gael Huber

#include "Core/ZoofariCore.h"
#include ZOOFARI_INCLUDE(Core/CGameRoot.h)

#include ZOOFARI_INCLUDE_STL(iostream)
#include ZOOFARI_INCLUDE_STL(chrono)
#include ZOOFARI_INCLUDE_STL(unistd.h)

using namespace zoofari;

int main(int argc, char** argv)
{
    auto start = std::chrono::high_resolution_clock::now();
    
    // Set the current working directory
    char * exePath(argv[0]);
    
    size_t len(strlen(exePath));
    size_t lastIndex(0);
    for(size_t i(0); i < len; ++i)
    {
        if(exePath[i] == '/')
        {
            lastIndex = i;
        }
    }
    exePath[lastIndex] = '\0';
    s32 result(chdir(exePath));
    
    if(result == 0)
    {
        // Initialize the game
        game::core::CGameRoot root;
        root.Initialize();
        root.Run();
        root.Shutdown();
    }
    
    // record end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << "Execution time: " << diff.count() << " s\n";

	return 0;
}