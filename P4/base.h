#ifndef BASE_H
#define BASE_H

#include "o3d.h"
#include "cilindro.h"

class Base : public O3d
{
public:
    Base();
    Base(O3d o, Cilindro c);

    void draw_edges();
    void draw_solid();
    void draw_chess();
    void draw_all();
    void draw_points();

    void transformar(float x, float y, float z, float xt, float yt, float zt);
    void dibujar(float angulo, unsigned int modo);


private:
    O3d cubo;
    Cilindro cilindro;
};

#endif // BASE_H
