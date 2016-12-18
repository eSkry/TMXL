TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

CONFIG(release, debug|release): LIBS += -lpugixml
CONFIG(debug, debug|release): LIBS += -lpugixml

CONFIG(release, debug|release): LIBS += -lBox2D
CONFIG(debug, debug|release): LIBS += -lBox2D

SOURCES += main.cpp \
    Loader/level.cpp \
    Loader/objects.cpp \
    Loader/datatilepropertys.cpp

HEADERS += \
    Loader/level.h \
    Loader/objects.h \
    Loader/datatilepropertys.h
