
set(TMXL_TEST_NAME tmxl_basic_test)
set(GOOGLE_TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/googletest")

link_directories(${CMAKE_BINARY_DIR})
message("Google test source dir: ${GOOGLE_TEST_SOURCE_DIR}")
message("Check TMXL dir for tests: ${CMAKE_BINARY_DIR}")
include_directories(${GOOGLE_TEST_SOURCE_DIR}/include ${GOOGLE_TEST_SOURCE_DIR} ${TMXL_INCLUDE_DIR})

add_executable(${TMXL_TEST_NAME} tools_check.cpp sfml_sugar_check.cpp xmlparser_check.cpp type_convert_check.cpp string_tools_check.cpp)

target_link_libraries(${TMXL_TEST_NAME} gtest gtest_main)
target_link_libraries(${TMXL_TEST_NAME} ${TMXL_LIBRARY_NAME})