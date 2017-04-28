#ifndef BEETHOVEN_H
#define BEETHOVEN_H

#include "o3d.h"

class Beethoven: public O3d
{
public:
    Beethoven();
    Beethoven(O3d o);

    void draw_edges();
    void draw_solid(int r,int g, int b);
    void draw_chess();
    void draw_all();
    void draw_points();
    void draw_solid_gouroud(int material, float alplha, float beta);
    void draw_solid_illuminated(int material, float alpha, float beta);

    void vertex_normals();
    void faces_normals();

    void transformar(float x, float y, float z, float xt, float yt, float zt);

private:
    O3d beethoven;

};

#endif // BEETHOVEN_H
