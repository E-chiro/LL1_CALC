TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    lexer.cpp \
    parser.cpp \
    numfunc.cpp \
    vartable.cpp

HEADERS += \
    lexer.h \
    parser.h \
    numfunc.h \
    strfunc.h \
    vartable.h \
    fractions.h

