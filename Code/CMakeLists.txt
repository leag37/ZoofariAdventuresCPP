# Copyright 2014 Gael Huber

# Project info
cmake_minimum_required (VERSION 3.1.2)
project (ZOOFARI)
set (ZOOFARI_VERSION_MAJOR 0)
set (ZOOFARI_VERSION_MINOR 1)

function(create_source_group DIRECTORY_NAME SRCS_NAME CPPS_NAME)
	message("Adding ${DIRECTORY_NAME} to source")
	file(GLOB_RECURSE SRCS
		${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY_NAME}/*.h 
		${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY_NAME}/*.inl 
		${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY_NAME}/*.cpp)

	file(GLOB_RECURSE CPPS 
			${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY_NAME}/*.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY_NAME}/*.cpp)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY_NAME})

	# Create file groups
	foreach(f ${SRCS})
	    # Get the path of the file relative to ${CMAKE_CURRENT_SOURCE_DIR},
	    # then alter it (not compulsory)
	    file(RELATIVE_PATH SRCGR ${CMAKE_CURRENT_SOURCE_DIR} ${f})
	    set(SRCGR "${SRCGR}")

	    # Extract the folder, ie remove the filename part
	    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

	    # Source_group expects \\ (double antislash), not / (slash)
	    string(REPLACE / \\ SRCGR ${SRCGR})
	    source_group("${SRCGR}" FILES ${f})
	endforeach()

	set(${SRCS_NAME} ${SRCS} PARENT_SCOPE)
	set(${CPPS_NAME} ${CPPS} PARENT_SCOPE)
endfunction()


create_source_group(Common ZOOFARI_COMMON_SRCS ZOOFARI_COMMON_CPPS)
create_source_group(Game ZOOFARI_GAME_SRCS ZOOFARI_GAME_CPPS)
create_source_group(Editor ZOOFARI_EDITOR_SRCS ZOOFARI_EDITOR_CPPS)
create_source_group(System ZOOFARI_SYSTEM_SRCS ZOOFARI_SYSTEM_CPPS)

# Add platform-specific information
if(DEFINED PLATFORM)
	if(${PLATFORM} STREQUAL "Win32" OR ${PLATFORM} STREQUAL "Win64")
		# Windows Platform-Dependent Files
		create_source_group(Platform/Windows/Editor ZOOFARI_PLATFORM_EDITOR_SRCS ZOOFARI_PLATFORM_EDITOR_CPPS)
		create_source_group(Platform/Windows/Game ZOOFARI_PLATFORM_GAME_SRCS ZOOFARI_PLATFORM_GAME_CPPS)

		# Set as a Windows application
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

		# Support Link Time Code Generation for all release build types without debug information
		set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG /INCREMENTAL:NO")
		set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} /LTCG /INCREMENTAL:NO")
		
		# Release modes should use fast floating point model and whole program optimization to use with LTCG
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /fp:fast ")
		set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /fp:fast ")

	elseif(${PLATFORM} STREQUAL "Darwin")
		# Mac Platform-Dependent Files
		create_source_group(Platform/Darwin/Editor ZOOFARI_PLATFORM_EDITOR_SRCS ZOOFARI_PLATFORM_EDITOR_CPPS)
		create_source_group(Platform/Darwin/Game ZOOFARI_PLATFORM_GAME_SRCS ZOOFARI_PLATFORM_GAME_CPPS)

		# Strip all symbols from the final build
		# Support Link Time Optimization for all release build types without debug information
		set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s -flto")
		set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -s -flto")

		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -v")
		
		# Support C++11, multi-processor builds for compilation speed and OpenMP for parallel processing
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

		# Add debug support to debug builds
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g ")
		set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -g ")

		# Optimize program as much as possible
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto")
		set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -O3 -flto")
	else()

	endif()

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../Game")

	if(${PLATFORM} STREQUAL "Win64")
		add_definitions(-DZOOFARI_WIN64 -DZOOFARI_WINDOWS)

		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MACHINE:X64")

	elseif(${PLATFORM} STREQUAL "Darwin")
		add_definitions(-DZOOFARI_DARWIN)

	endif()
endif()

if(DEFINED USE_CUSTOM_ALLOCATOR)
	if(${USE_CUSTOM_ALLOCATOR} STREQUAL "true")
		message("Using custom allocator")
		add_definitions(-DZOOFARI_USE_CUSTOM_ALLOCATOR)
	else()
		message("Using default allocator")
	endif()
endif()

# Coallate all sources
set(ZOOFARI_GAME_SRCS 
	${ZOOFARI_GAME_SRCS} 
	${ZOOFARI_PLATFORM_GAME_SRCS}
	)
set(ZOOFARI_EDITOR_SRCS 
	${ZOOFARI_EDITOR_SRCS} 
	${ZOOFARI_PLATFORM_EDITOR_SRCS}
	)

# Common flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DZOOFARI_DEBUG -DZOOFARI_DEBUG_ENABLED")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DZOOFARI_RELWITHDEBINFO -DZOOFARI_DEBUG_ENABLED")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DZOOFARI_RELEASE")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -DZOOFARI_MINSIZEREL")

add_executable(ZOOFARI_GAME ${ZOOFARI_GAME_SRCS} ${ZOOFARI_PLATFORM_SRCS} ${ZOOFARI_SYSTEM_SRCS} ${ZOOFARI_COMMON_SRCS})
add_executable(ZOOFARI_EDITOR ${ZOOFARI_EDITOR_SRCS} ${ZOOFARI_PLATFORM_SRCS} ${ZOOFARI_SYSTEM_SRCS} ${ZOOFARI_COMMON_SRCS})