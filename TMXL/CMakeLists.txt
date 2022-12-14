project(TMXL VERSION 2.0.0 LANGUAGES CXX)


set(TMXL_HEADERS
        include/TMXL/Tools.h
        include/TMXL/TypeConvert.h
        include/TMXL/Encodings/Base64Encoder.h
        include/TMXL/Encodings/IEncoder.h
        include/TMXL/Map/NodeObject.h
        include/TMXL/Map/NodeObjectWalker.h
        include/TMXL/Map/TMENodes.h
        include/TMXL/Map/Converters/TMEConverter.h
        include/TMXL/Parsers/IFormater.h
        include/TMXL/Parsers/IParser.h
        include/TMXL/Parsers/LayerDataParser.h
        include/TMXL/Parsers/XMLFormater.h
        include/TMXL/Parsers/XML/PugiParser.h
        include/TMXL/System/AutoSwitchLoader.h
        include/TMXL/System/Color.h
        include/TMXL/System/IDGenerator.h
        include/TMXL/System/Logger.h
        include/TMXL/System/NodeObjectPrinter.h
        include/TMXL/System/StringTools.h)

set(TMXL_SOURCES
        src/Encodings/Base64Encoder.cpp
        src/Map/NodeObject.cpp
        src/Map/NodeObjectWalker.cpp
        src/Map/Converters/TMEConverter.cpp
        src/Parsers/IParser.cpp
        src/Parsers/LayerDataParser.cpp
        src/Parsers/XMLFormater.cpp
        src/Parsers/XML/PugiParser.cpp
        src/System/AutoSwitchLoader.cpp
        src/System/Color.cpp
        src/System/IDGenerator.cpp
        src/System/NodeObjectPrinter.cpp)


if (TMXL_BUILD_SHARED)
    add_library(${PROJECT_NAME} SHARED ${TMXL_HEADERS} ${TMXL_SOURCES})
else()
    add_library(${PROJECT_NAME} STATIC ${TMXL_HEADERS} ${TMXL_SOURCES})
endif()


target_include_directories(${PROJECT_NAME}
        PUBLIC include
        PUBLIC ${CONAN_INCLUDE_DIRS}
) # target_include_directories

target_link_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
) # target_link_directories

target_link_libraries(${PROJECT_NAME}
        PUBLIC ${CONAN_LIBS}
) # target_link_libraries