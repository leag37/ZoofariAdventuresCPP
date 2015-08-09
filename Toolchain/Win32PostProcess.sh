#!/bin/sh
echo -e "\033[0;32m"Running Post Process"\033[0m"

echo Copying User Settings

# Move VS user settings file
pwd
cp Toolchain/Templates/ZOOFARI_GAME.vcxproj.user Build/Win32/
cp Toolchain/Templates/ZOOFARI_EDITOR.vcxproj.user Build/Win32/

echo -e "\033[0;32m"Post Process Finished"\033[0m"
