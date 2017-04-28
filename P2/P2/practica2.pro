HEADERS = \ 
    file_ply_stl.h \
    o3d.h \
    object3d.h

SOURCES = \
    practica2.cc \
    file_ply_stl.cc \
    o3d.cpp \
    object3d.cpp

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut

CONFIG += console
QT += opengl

