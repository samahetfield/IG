#ifndef CILINDRO_H
#define CILINDRO_H

#include "o3d.h"

class Cilindro: public O3d
{
public:
    Cilindro();
    Cilindro(O3d o);

    void createProfile(int num_perf);

    void draw_edges();
    void draw_solid(int r, int g,int b);
    void draw_chess();
    void draw_all();
    void draw_points();
    void draw_solid_gouroud(int material,float alpha, float beta, float alpha2, float beta2);
    void draw_solid_illuminated(int material,float alpha, float beta,float alpha2, float beta2);
    void draw_tex(float num_perfiles, int alpha, int beta);

    void transformar(float x, float y, float z, float xt, float yt, float zt);


    void vertex_normals();
    void faces_normals();

private:
    O3d cilindro;

};

#endif // CILINDRO_H
