cmake_minimum_required(VERSION 3.0)
project(LPugiXMLExample)

include_directories(${TMXL})
link_directories(${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${TMXL_LIBRARY_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${PROJECT_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../")