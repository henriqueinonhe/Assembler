TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        code.cpp \
        command.cpp \
        main.cpp \
        parser.cpp \
        symboltable.cpp \
        tests.cpp

HEADERS += \
    catch.hpp \
    code.h \
    command.h \
    parser.h \
    symboltable.h
