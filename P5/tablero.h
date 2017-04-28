#ifndef TABLERO_H
#define TABLERO_H

#include"o3d.h"

class Tablero: public O3d
{
public:
    Tablero();
    Tablero(int tama);

    void draw_tex();

    void draw_edges();
    void draw_solid(int r,int g, int b);
    void draw_chess();
    void draw_all();
    void draw_points();
    void draw_solid_illuminated(int material,float alpha, float beta);
    void draw_solid_gouroud(int material,float alpha, float beta);


    void vertex_normals();
    void faces_normals();

private:
    O3d tab;
    int tama;
};

#endif // TABLERO_H
