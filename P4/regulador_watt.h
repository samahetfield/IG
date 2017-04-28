#ifndef REGULADOR_WATT_H
#define REGULADOR_WATT_H

#include "partesuperior.h"
#include "base.h"

class Regulador_Watt
{
public:
    Regulador_Watt();
    Regulador_Watt(ParteSuperior par_s, Base b);

    void dibujar(float angulo, unsigned int modo,float aumentar);
    void transformar(float x, float y, float z, float xt, float yt, float zt);


private:
   ParteSuperior ps;
   Base base;
};

#endif // REGULADOR_WATT_H
