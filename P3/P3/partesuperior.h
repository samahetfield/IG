#ifndef PARTESUPERIOR_H
#define PARTESUPERIOR_H

#include "o3d.h"
#include "esfera.h"
#include "base.h"
#include "cilindro.h"
#include "brazo.h"

class ParteSuperior
{
public:
    ParteSuperior();
    ParteSuperior(Brazo e, Cilindro c, Base cu);


    void dibujar(float angulo, unsigned int modo,float aumentar);
    void transformar(float x, float y, float z, float xt, float yt, float zt);


private:
    Cilindro c_sujeta_esferas;
    Cilindro union_base;
    Brazo brazo;
    Base pieza_cubo;

};

#endif // PARTESUPERIOR_H
