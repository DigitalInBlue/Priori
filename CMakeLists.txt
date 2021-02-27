#
# Top level makefile for Priori
#
# John Farrier
#

#
# Cmake Configuration
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

include(CheckFunctionExists)
include(CheckCXXSourceCompiles)
include(CheckIncludeFile)

#
# User Options
#

option(PRIORI_COMPILE_DYNAMIC_LIBRARIES "Set to ON to build Priori for dynamic linking.  Use OFF for static." ON)
option(PRIORI_USE_FOLDERS "Enable to put Priori in its own solution folder under Visual Studio" OFF)
option(PRIORI_THREAD_SAFE "Enable to compile Priori for thread safety.  Disable for very slight speed advantage." ON)

if(PRIORI_COMPILE_DYNAMIC_LIBRARIES)
	SET(PRIORI_USER_DEFINED_SHARED_OR_STATIC "SHARED")
else()
	SET(PRIORI_USER_DEFINED_SHARED_OR_STATIC "STATIC")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

macro(PrioriSetDefaultCompilerOptions)
	set_target_properties(${PROJECT_NAME} PROPERTIES
		POSITION_INDEPENDENT_CODE "${PRIORI_COMPILE_PIC}"
	)
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		target_compile_options(${PROJECT_NAME} PRIVATE /D_VARIADIC_MAX=10 )
		target_compile_options(${PROJECT_NAME} PRIVATE /D_CRT_SECURE_NO_WARNINGS)
		target_compile_options(${PROJECT_NAME} PRIVATE /wd4251)
		target_compile_options(${PROJECT_NAME} PRIVATE /MP)
		target_compile_options(${PROJECT_NAME} PRIVATE /D_SCL_SECURE_NO_WARNINGS)
		target_compile_options(${PROJECT_NAME} PRIVATE /permissive-)

        if(PRIORI_TREAT_WARNINGS_AS_ERRORS)
            target_compile_options(${PROJECT_NAME} PRIVATE /WX)
		endif()

		set_target_properties(${PROJECT_NAME} PROPERTIES
			ARCHIVE_OUTPUT_NAME "${PROJECT_NAME}.dll")

	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
		target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
		if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
			target_compile_options(${PROJECT_NAME} PRIVATE -Xclang)
			target_compile_options(${PROJECT_NAME} PRIVATE -Wno-c++98-compat)
			target_compile_options(${PROJECT_NAME} PRIVATE -Wno-c++98-compat-pedantic)
			target_compile_options(${PROJECT_NAME} PRIVATE -Wno-reserved-id-macro)
			if(PRIORI_TREAT_WARNINGS_AS_ERRORS)
				target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
			endif()
		else()
			target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
			if(PRIORI_TREAT_WARNINGS_AS_ERRORS)
				target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
			endif()
		endif()

	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
		target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

		if(PRIORI_TREAT_WARNINGS_AS_ERRORS)
			target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
		endif()
	endif()
endmacro()

#
# Compiler Settings
#


# Project Name
set(PROJECT_NAME priori)
PROJECT(${PROJECT_NAME})

include(CheckFunctionExists)
include(CheckCXXSourceCompiles)
include(CheckIncludeFile)

#
# Build and Install Settings
#

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_DEBUG_POSTFIX          "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX        ""  CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX ""  CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX     ""  CACHE STRING "add a postfix, usually empty on windows")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


# --------------------------------------------------------------------------- #
# --------------------------------------------------------------------------- #

#
# Install Locations
#

#
# include path to be used by all projects
#

SET(HEADER_PATH ${priori_SOURCE_DIR}/include)

if(PRIORI_COMPILE_DYNAMIC_LIBRARIES)
	add_definitions(-DPRIORI_EXPORTS)
else()
	add_definitions(-DPRIORI_STATIC)
endif()

if(PRIORI_THREAD_SAFE)
	add_definitions(-DPRIORI_THREAD_SAFE)
endif()

#
# Define header and sources
#

set(TARGET_H
	include/priori/export.h
	include/priori/priori.h
)

set(TARGET_SRC
	src/priori.cpp
)

set(TARGET_LIBRARIES ${SYSLIBS})
add_library(${PROJECT_NAME} ${PRIORI_USER_DEFINED_SHARED_OR_STATIC} ${TARGET_SRC} ${TARGET_H})
PrioriSetDefaultCompilerOptions()

include_directories(${HEADER_PATH})

# ---------------------------------------------------------------------------
# Install and exports
# ---------------------------------------------------------------------------

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-target
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX})

# export to be used from install location
install(EXPORT ${PROJECT_NAME}-target
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share
)

# export to be used from build directory
export(EXPORT ${PROJECT_NAME}-target
  FILE ${PROJECT_NAME}-target.cmake
)

# --------------------------------------------------------------------------- #
# --------------------------------------------------------------------------- #

# --------------------------------------------------------------------------- #
# GTest Unit Tests
# --------------------------------------------------------------------------- #

option(PRIORI_GTEST "Set to ON to enable Google tests Priori." ON)

if(PRIORI_GTEST)
	add_subdirectory(test)
endif()

# --------------------------------------------------------------------------- #
# Priori Celero Benchmarks
# --------------------------------------------------------------------------- #

option(PRIORI_PRIORI "Set to ON to enable Priori benchmarks Priori." ON)

if(PRIORI_PRIORI)
	add_subdirectory(benchmark)
endif()

#
# Optional
#

if(PRIORI_USE_FOLDERS)
	set_property(TARGET priori PROPERTY FOLDER "Priori")
endif()