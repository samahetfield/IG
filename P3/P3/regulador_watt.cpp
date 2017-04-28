#include "regulador_watt.h"
#include "o3d.h"
#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include <GL/glut.h>
#include <math.h>

Regulador_Watt::Regulador_Watt()
{

}

Regulador_Watt::Regulador_Watt(ParteSuperior par_s, Base b){
    ps = par_s;
    base = b;
}


void Regulador_Watt::dibujar(float angulo, unsigned int modo,float aumentar){
    ps.dibujar(angulo,modo,aumentar);

    //base.dibujar(angulo,modo);

}

void Regulador_Watt::transformar(float x, float y, float z, float xt, float yt, float zt){
}
