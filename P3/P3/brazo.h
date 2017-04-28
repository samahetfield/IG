#ifndef BRAZO_H
#define BRAZO_H

#include "esfera.h"
#include "base.h"
#include "beethoven.h"

class Brazo
{
public:
    Brazo();
    Brazo(Esfera e, Cilindro c1, Beethoven b);

    void draw_edges();
    void draw_solid();
    void draw_chess();
    void draw_all();
    void draw_points();

    void transformar(float x, float y, float z, float xt, float yt, float zt);
    void dibujar(float angulo, unsigned int modo,float aumentar);

private:
    Esfera esfera1;
    Esfera esfera2;
    Cilindro barra_sup;
    Cilindro barra_inf;
    Beethoven beethoven;
};

#endif // BRAZO_H
