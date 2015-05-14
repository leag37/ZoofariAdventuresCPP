# Makefile for RPicG Project Setup and Configuration
# Copyright 2014 Gael Huber

# Setup Generators:
# Visual Studio 12 2013 Win32
# Visual Studio 12 2013 Win64
# Xcode
PLATFORM ?= Win64
ifeq "$(PLATFORM)" "Win32"
	#GENERATOR = Visual Studio 12 2013
	GENERATOR = Visual Studio 14 2015
	POST_PROCESS := ./Toolchain/Win32PostProcess.sh
endif
ifeq "$(PLATFORM)" "Win64"
	#GENERATOR = Visual Studio 12 Win64
	GENERATOR = Visual Studio 14 2015 Win64
	POST_PROCESS := ./Toolchain/Win64PostProcess.sh
endif

# OS Detection for build_all rule
OS := $(shell uname)
ifneq "" "$(findstring MINGW32_NT,$(OS))"
	BUILD_WIN32=make build PLATFORM=Win32
	BUILD_WIN64=make build PLATFORM=Win64
endif

# Mac
ifneq "" "$(findstring Darwin,$(OS))"
	BUILD_OSX=make build PLATFORM=OSX
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
	$(ECHO) ${RED}build ${ORANGE}\<PLATFORM\>${NC} - Builds the project for the target platform
	$(ECHO) ${RED}build_all${NC} - Builds the project for all available targets
	$(ECHO) ${RED}clean ${ORANGE}\<PLATFORM\>${NC} - Cleans the target platform \(defaults to Win64\)
	$(ECHO) ${RED}clean_all${NC} - Cleans all platforms
	$(ECHO)
	$(ECHO) ${GREEN}Platforms:${NC}
	$(ECHO) ${RED}Win32${NC} - Windows 32-bit
	$(ECHO) ${RED}Win64${NC} - Windows 64-bit
	$(ECHO) ${RED}OSX${NC} - Apple OSX \(OS version not yet specified\)

.PHONY: build
build:
	$(ECHO) ${GREEN}Building for $(PLATFORM) using $(GENERATOR)${NC}
	@mkdir -p Build/$(PLATFORM)
	@cd Build/$(PLATFORM); 									\
	cmake ../../Code -G"$(GENERATOR)" -DPLATFORM=$(PLATFORM) $(ARGS)
	@$(POST_PROCESS)
	$(ECHO) ${GREEN}Done${NC}

.PHONY: build_all
build_all:
	$(ECHO) Building for all platforms
	@$(BUILD_WIN32)
	@$(BUILD_WIN64)
	@$(BUILD_OSX)

.PHONY: clean
clean:
	$(ECHO) Removing build files for $(PLATFORM)
	@rm -rf Build/$(PLATFORM)

.PHONY: clean_all
clean_all:
	$(ECHO) Removing build files for all platforms
	@rm -rf Build
