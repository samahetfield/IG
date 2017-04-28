HEADERS = \ 
    file_ply_stl.h \
    o3d.h \
    object3d.h \
    esfera.h \
    base.h \
    cilindro.h \
    partesuperior.h \
    regulador_watt.h \
    brazo.h \
    beethoven.h \
    tablero.h

SOURCES = \
    practica4.cc \
    file_ply_stl.cc \
    o3d.cpp \
    object3d.cpp \
    esfera.cpp \
    base.cpp \
    cilindro.cpp \
    partesuperior.cpp \
    regulador_watt.cpp \
    brazo.cpp \
    beethoven.cpp \
    tablero.cpp

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut

CONFIG += console
QT += opengl

