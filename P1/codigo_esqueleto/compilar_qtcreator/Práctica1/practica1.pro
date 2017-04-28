HEADERS = \ 
    object3d.h \
    o3d.h

SOURCES = \
    practica1.cc \
    object3d.cpp \
    o3d.cpp

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut

CONFIG += console
QT += opengl

