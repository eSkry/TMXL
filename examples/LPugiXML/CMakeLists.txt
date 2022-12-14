project(LPugiXMLExample)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        ${TMXL}
        ${CONAN_LIBS}
) # target_link_libraries

target_link_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        PUBLIC ${CONAN_LIB_DIRS}
) # target_link_directories

target_include_directories(${PROJECT_NAME}
        PUBLIC "${CMAKE_SOURCE_DIR}/TMXL/include"
        PUBLIC ${CONAN_INCLUDE_DIRS}
) # target_include_directories

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${PROJECT_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../")