cmake_minimum_required(VERSION 3.12)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)

# Список существующих дейфайнов для проекта:
#   USE_STL_STRING
#   NOT_USE_SFML_COLOR_TYPE

option(BUILD_EXAMPLES "Build example projects" ON)
option(TMXL_BUILD_TESTS "Build TMXL tests" ON)
option(USE_STL_STRING "Use string from std by default" OFF)

string(TOLOWER ${CMAKE_BUILD_TYPE} TMXL_BUILD_TYPE)
if(TMXL_BUILD_TYPE STREQUAL debug)
    add_compile_definitions(_COUT_DEBUG_OUTPUT)
endif()

#### PROJECT TMXL BUILD ####
project(TMXL)
set(TMXL_VERSION v0.1.0)
add_compile_definitions(TMXL_VERSION="${TMXL_VERSION}")

set(CMAKE_DEBUG_POSTFIX d)
set(TMXL_LIBRARY_NAME ${PROJECT_NAME})
set(TMXL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/TMXL")
message("TMXL Version: ${TMXL_VERSION}")
message("TMXL Binary dir: ${CMAKE_CURRENT_BINARY_DIR}")
set(TMXL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

include_directories("${CMAKE_SOURCE_DIR}/TMXL/include")

file(GLOB_RECURSE TMXL_LIBRARY_HEADERS "${PROJECT_SOURCE_DIR}/TMXL/*.h")
file(GLOB_RECURSE TMXL_LIBRARY_SOURCES "${PROJECT_SOURCE_DIR}/TMXL/*.cpp")
add_library(${TMXL_LIBRARY_NAME} ${TMXL_LIBRARY_HEADERS} ${TMXL_LIBRARY_SOURCES})
message("TMXL OUT DIR: ${CMAKE_CURRENT_BINARY_DIR}")

find_package(SFML REQUIRED window graphics system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${TMXL_LIBRARY_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/extlibs/pugixml")
target_link_libraries(${TMXL_LIBRARY_NAME} pugixml)
#### PROJECT TMXL BUILD ####

if(TMXL_BUILD_TESTS)
    add_subdirectory(tests)
endif()

#### EXAMPLES BUILD ####
if(BUILD_EXAMPLES)
    add_subdirectory(examples/Base)
endif()
#### EXAMPLES BUILD ####

install(TARGETS ${PROJECT_NAME} DESTINATION bin)