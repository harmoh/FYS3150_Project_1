TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib

SOURCES += main.cpp \
    row_reduction.cpp
LIBS += -larmadillo -llapack -lblas

HEADERS += \
    row_reduction.h
