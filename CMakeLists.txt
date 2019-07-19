cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)

# Список существующих дейфайнов для проекта:
#   USE_STL_STRING
#   NOT_USE_SFML_COLOR_TYPE

option(BUILD_EXAMPLES "Build example projects" OFF)
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_TMXL_TEST_ONLY "Build TMXL test only" OFF)

#### PROJECT TMXL BUILD ####
project("TMXL")
set(TMXL_VERSION v0.1.0)
if(${CMAKE_VERSION} VERSION_LESS "3.12")
	add_definitions(-DTMXL_VERSION=${TMXL_VERSION})
else()
	add_compile_definitions(TMXL_VERSION="${TMXL_VERSION}")
endif()

set(CMAKE_DEBUG_POSTFIX d)
set(TMXL_LIBRARY_NAME ${PROJECT_NAME})
set(TMXL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/TMXL/include/TMXL")
message("TMXL Version: ${TMXL_VERSION}")
message("TMXL Binary dir: ${CMAKE_CURRENT_BINARY_DIR}")
set(TMXL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/TMXL/include")

file(GLOB_RECURSE TMXL_LIBRARY_HEADERS "${PROJECT_SOURCE_DIR}/TMXL/*.h")
file(GLOB_RECURSE TMXL_LIBRARY_SOURCES "${PROJECT_SOURCE_DIR}/TMXL/*.cpp")
add_library(${TMXL_LIBRARY_NAME} ${TMXL_LIBRARY_HEADERS} ${TMXL_LIBRARY_SOURCES})
message("TMXL OUT DIR: ${CMAKE_CURRENT_BINARY_DIR}")

find_package(SFML REQUIRED window graphics system)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${TMXL_LIBRARY_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/extlibs/pugixml")
target_link_libraries(${TMXL_LIBRARY_NAME} pugixml)
#### PROJECT TMXL BUILD ####

if(BUILD_TESTS OR BUILD_TMXL_TEST_ONLY)
    add_subdirectory(tests)
endif()

#### EXAMPLES BUILD ####
if(BUILD_EXAMPLES)
	add_subdirectory(examples/Base)
endif()
#### EXAMPLES BUILD ####


#### INSTALL SECTION ####
include(GNUInstallDirs)
install(TARGETS ${TMXL_LIBRARY_NAME} 
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/TMXL/include/TMXL" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#### INSTALL SECTION ####