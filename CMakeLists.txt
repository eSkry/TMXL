cmake_minimum_required(VERSION 3.10)
project(TMXLoader LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

option(BUILD_EXAMPLES "Build example projects" ON)
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_TMXL_TEST_ONLY "Build TMXL test only" OFF)
option(BUILD_SHARED_LIBS "Build library as shared" ON)


if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	conan_basic_setup()
else()
	message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

if(MSVC)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
	set(BUILD_SHARED_LIBS TRUE)
endif()


if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release")
	message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
endif()


if (BUILD_SHARED_LIBS)
	set(TMXL_BUILD_SHARED TRUE)
else()
	set(TMXL_BUILD_SHARED FALSE)
endif()
add_subdirectory(TMXL)

#### BUILD TESTS #####
if(BUILD_TESTS OR BUILD_TMXL_TEST_ONLY)
    add_subdirectory(tests)
endif()
#### BUILD TESTS #####


#### EXAMPLES BUILD ####
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
#### EXAMPLES BUILD ####

