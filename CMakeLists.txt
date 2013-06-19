#
# Top level makefile for Priori
#
# John Farrier
#

#
# Cmake Configuration
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Project Name
PROJECT(priori)

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

#
# Compiler Settings
#

if(MSVC) 
  # Force to always compile with warning level 4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]") 
	string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") 
  else() 
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4") 
  endif() 

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "Compiler Flags for All Builds" FORCE) 
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "Compiler Flags for Debug Builds" FORCE) 
  set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "Compiler Flags for Release Builds" FORCE) 

  add_definitions("/D_CRT_SECURE_NO_WARNINGS /wd4251 /nologo")
endif() 
 
if(BORLAND) 
  set(CMAKE_CXX_FLAGS "" CACHE STRING "Compiler Flags for All Builds" FORCE) 
  set(CMAKE_CXX_FLAGS_DEBUG "" CACHE STRING "Compiler Flags for Debug Builds" FORCE)  
  set(CMAKE_CXX_FLAGS_RELEASE  "" CACHE STRING "Compiler Flags for Release Builds" FORCE) 
endif() 

message (STATUS "SYSTEM: ${CMAKE_SYSTEM_NAME}")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	EXEC_PROGRAM(xcrun ARGS -find clang++ OUTPUT_VARIABLE XCODE_CLANG_PATH)
	set (XCODE_CLANG_PATH "${XCODE_CLANG_PATH}" CACHE STRING "Xcode clang path")
	set (CMAKE_CXX_COMPILER "${XCODE_CLANG_PATH}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++") 
	set (CMAKE_COMPILER_IS_GNUCXX 1)
endif()
 
if(CMAKE_COMPILER_IS_GNUCXX) 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=gnu++11 -Wall" CACHE STRING "Compiler Flags for All Builds" FORCE) 
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pedantic" CACHE STRING "Compiler Flags for Debug Builds" FORCE) 
  set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "Compiler Flags for Release Builds" FORCE) 
endif() 

#
# Build and Install Settings
#

set(CMAKE_DEBUG_POSTFIX          "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX        ""  CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX ""  CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX     ""  CACHE STRING "add a postfix, usually empty on windows")


# --------------------------------------------------------------------------- #
# --------------------------------------------------------------------------- #

#
# Install Locations
#

#
# include path to be used by all projects
#

SET(HEADER_PATH ${priori_SOURCE_DIR}/include)

set(PROJECT_NAME priori)

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
include_directories(${HEADER_PATH})

# --------------------------------------------------------------------------- #
# --------------------------------------------------------------------------- #

#
# Optional
#

if(PRIORI_USE_FOLDERS)
	set_property(TARGET priori PROPERTY FOLDER "Priori")
endif()

# --------------------------------------------------------------------------- #
# GTest Unit Tests
# --------------------------------------------------------------------------- #

option(PRIORI_GTEST "Set to ON to enable Google tests Priori." ON)

if(PRIORI_GTEST)
	set(PROJECT_TEST_NAME prioriTest)
	set(GTEST_LIBRARY gtest)
	set(GTEST_MAIN_LIBRARY gtest_main)

	enable_testing(true)

	add_executable(${PROJECT_TEST_NAME} 
		src/test.cpp
		)

	# VS2012 doesn't support true variadic templates
	if(MSVC) 
		add_definitions( /D _VARIADIC_MAX=10 )
	endif()

	set(GTEST_RELATIVE_PATH "./" CACHE PATH "")
	add_subdirectory(${GTEST_RELATIVE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/gtest)
	set(GTEST_INCLUDE_DIR ${GTEST_RELATIVE_PATH}/include)

	include_directories(${HEADER_PATH})
	include_directories(${GTEST_INCLUDE_DIR})
	
	target_link_libraries(${PROJECT_TEST_NAME} 
		${GTEST_LIBRARY} 
		${GTEST_MAIN_LIBRARY} 
		priori
		)

	add_test(${PROJECT_TEST_NAME} ${PROJECT_TEST_NAME} )
	add_custom_command(TARGET ${PROJECT_TEST_NAME} POST_BUILD COMMAND $<TARGET_FILE:${PROJECT_TEST_NAME}>)
endif()

# --------------------------------------------------------------------------- #
# Celero Benchmarks
# --------------------------------------------------------------------------- #

option(PRIORI_CELERO "Set to ON to enable Celero benchmarks Priori." ON)

if(PRIORI_CELERO)
	set(PROJECT_TEST_NAME prioriBenchmark)
	set(CELERO_LIBRARY celero)

	add_executable(${PROJECT_TEST_NAME} 
		src/benchmark.cpp
		src/priori.cpp
		)

	# VS2012 doesn't support true variadic templates
	if(MSVC) 
		add_definitions( /D _VARIADIC_MAX=10 )
	endif()

	if(CELERO_COMPILE_DYNAMIC_LIBRARIES)
	else()
		add_definitions(-DCELERO_STATIC)
	endif()

	set(CELERO_RELATIVE_PATH "./" CACHE PATH "")
	add_subdirectory(${CELERO_RELATIVE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/celero)
	set(CELERO_INCLUDE_DIR ${CELERO_RELATIVE_PATH}/include)

	include_directories(${HEADER_PATH})
	include_directories(${CELERO_INCLUDE_DIR})
	add_dependencies(${PROJECT_TEST_NAME} celero)
	
	target_link_libraries(${PROJECT_TEST_NAME} 
		${CELERO_LIBRARY} 
		priori
		)
	
	add_test(${PROJECT_TEST_NAME} ${PROJECT_TEST_NAME} )
	add_custom_command(TARGET ${PROJECT_TEST_NAME} POST_BUILD COMMAND $<TARGET_FILE:${PROJECT_TEST_NAME}>)
endif()
