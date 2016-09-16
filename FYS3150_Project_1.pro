TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib

SOURCES += main.cpp \
    lu_decomposition.cpp \
    tridiagonal.cpp
LIBS += -larmadillo -llapack -lblas

HEADERS += \
    lu_decomposition.h \
    tridiagonal.h
