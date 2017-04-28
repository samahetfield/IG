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

    void createProfile(int num_perf);
    void addFaces(int tama,int fueraEje, int num_perfiles);

    void transformar(float x, float y, float z, float xt, float yt, float zt);


private:
    O3d obj_rev;
};

#endif // ESFERA_H
