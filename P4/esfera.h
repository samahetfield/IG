#ifndef ESFERA_H
#define ESFERA_H

#include "o3d.h"

class Esfera: public O3d
{
public:
    Esfera();
    Esfera(O3d o);

    void draw_edges();
    void draw_solid();
    void draw_chess();
    void draw_all();
    void draw_points();
    void draw_solid_gouroud(int material,float alpha, float beta, float alpha2, float beta2);
    void draw_solid_illuminated(int material,float alpha, float beta, float alpha2, float beta2);
    void draw_tex(float num_perfiles, int alpha, int beta);

    void createProfile(int num_perf);
    void addFaces(int tama,int fueraEje, int num_perfiles);

    void vertex_normals();
    void faces_normals();

    void transformar(float x, float y, float z, float xt, float yt, float zt);


private:
    O3d obj_rev;
    int tama_ini;
    int fueraDelEje;
};

#endif // ESFERA_H
