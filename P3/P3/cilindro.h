#ifndef CILINDRO_H
#define CILINDRO_H

#include "o3d.h"

class Cilindro: public O3d
{
public:
    Cilindro();
    Cilindro(O3d o);

    void draw_edges();
    void draw_solid();
    void draw_chess();
    void draw_all();
    void draw_points();

    void transformar(float x, float y, float z, float xt, float yt, float zt);

private:
    O3d cilindro;

};

#endif // CILINDRO_H
