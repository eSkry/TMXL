project(TMXL VERSION 2.0.0 LANGUAGES CXX)

set(TMXL_HEADERS
        include/TMXL/Tools.h
        include/TMXL/TypeConvert.h
        include/TMXL/Map/TMENodes.h
        include/TMXL/Parsers/IParser.h
        include/TMXL/Parsers/LayerDataParser.h
        include/TMXL/System/Color.h
        include/TMXL/System/IDGenerator.h
        include/TMXL/System/StringTools.h
        include/TMXL/Parsers/XML/XMLParser.h)

set(TMXL_SOURCES
        src/Parsers/LayerDataParser.cpp
        src/System/Color.cpp
        src/System/IDGenerator.cpp
        src/Parsers/XML/XMLParser.cpp)

add_library(${PROJECT_NAME} SHARED ${TMXL_HEADERS} ${TMXL_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION}
        OUTPUT_NAME ${PROJECT_NAME}
) # set_target_properties

target_include_directories(${PROJECT_NAME}
        PUBLIC include
        PUBLIC ${CONAN_INCLUDE_DIRS}
) # target_include_directories

target_link_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        PUBLIC ${CONAN_LIB_DIRS}
) # target_link_directories

target_link_libraries(${PROJECT_NAME}
        PUBLIC ${CONAN_LIBS}
) # target_link_libraries