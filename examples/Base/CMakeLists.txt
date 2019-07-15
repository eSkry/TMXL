cmake_minimum_required(VERSION 3.0)
project(BaseExample)

include_directories(${TMXL_INCLUDE_DIR})
link_directories(${TMXL_BINARY_DIR} ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${TMXL_LIBRARY_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})