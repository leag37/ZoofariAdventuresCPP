# Makefile for RPicG Project Setup and Configuration
# Copyright 2014 Gael Huber

# Setup Generators:
# Visual Studio 12 2013 Win32
# Visual Studio 12 2013 Win64
# Xcode
OS := $(shell uname)
ifeq "$(OS)" "Darwin"
	# OSX
	GENERATOR = Xcode
else
	# Windows for now
	GENERATOR = Visual Studio 14 2015 Win64
	POST_PROCESS := ./Toolchain/Win64PostProcess.sh
endif

# Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
ORANGE="\033[0;33m"
NC="\033[0m"

# Echo command for Darwin
ifneq "" "$(findstring Darwin,$(OS))"
	ECHO:=@echo
else
	ECHO:=@echo -e
endif

.PHONY: help
help:
	$(ECHO)
	$(ECHO) ${GREEN}Commands:${NC}
	$(ECHO) ${RED}build ${ORANGE}[\<PLATFORM\>]${NC} - Builds the project for the target platform
	$(ECHO) ${RED}clean${NC} - Cleans the target platform

.PHONY: build
build:
	$(ECHO) ${GREEN}Building for $(OS) using $(GENERATOR)${NC}
	@mkdir -p Build/$(OS)
	@cd Build/$(OS); 									\
	cmake ../../Code -G"$(GENERATOR)" -DPLATFORM=$(OS) $(ARGS)
	@$(POST_PROCESS)
	$(ECHO) ${GREEN}Done${NC}

.PHONY: clean
clean:
	$(ECHO) Removing build files for $(PLATFORM)
	@rm -rf Build

.PHONY: clean_all
clean_all:
	$(ECHO) Removing build files for all platforms
	@rm -rf Build
