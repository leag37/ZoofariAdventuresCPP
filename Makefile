# Makefile for RPicG Project Setup and Configuration
# Copyright 2014 Gael Huber

# Setup Generators:
# Visual Studio 12 2013 Win32
# Visual Studio 12 2013 Win64
# Xcode
UNAME := $(shell uname -s)
ifeq "$(UNAME)" "Darwin"
	# OSX
	PLATFORM = Darwin
	GENERATOR = Xcode
else
	# Windows for now
	PLATFORM = Windows
	GENERATOR = Visual Studio 14 2015 Win64
	POST_PROCESS := ./Toolchain/Win64PostProcess.sh
endif

USE_CUSTOM_ALLOCATOR ?= true

# Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
ORANGE="\033[0;33m"
NC="\033[0m"

# Echo command for Darwin
ifneq "" "$(findstring Darwin,$(UNAME))"
	ECHO:=@echo
else
	ECHO:=@echo -e
endif

.PHONY: help
help:
	$(ECHO)
	$(ECHO) ${GREEN}Commands:${NC}
	$(ECHO) ${RED}build ${ORANGE}[\<PLATFORM\>=\<platform\>] [\<USE_CUSTOM_ALLOCATOR\>=true\|false]${NC} - Builds the project for the target platform
	$(ECHO) ${RED}clean${NC} - Cleans the target platform

.PHONY: build
build:
	$(ECHO) ${GREEN}Building for $(PLATFORM) using $(GENERATOR)${NC}
	@mkdir -p Build/$(PLATFORM)
	@cd Build/$(PLATFORM); 									\
	cmake ../../Code -G"$(GENERATOR)" -DPLATFORM=$(PLATFORM) -DUSE_CUSTOM_ALLOCATOR=$(USE_CUSTOM_ALLOCATOR) $(ARGS)
	$(ECHO) ${GREEN}Done${NC}

.PHONY: clean
clean:
	$(ECHO) Removing build files
	@rm -rf Build