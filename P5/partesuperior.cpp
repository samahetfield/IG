#include "partesuperior.h"
#include "o3d.h"
#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include <GL/glut.h>
#include <math.h>
#include "esfera.h"
#include "cilindro.h"
#include "base.h"

ParteSuperior::ParteSuperior()
{

}

ParteSuperior::ParteSuperior(Brazo e, Cilindro c, Base cu){
    brazo = e;
    c_sujeta_esferas = c;
    union_base = c;
    pieza_cubo = cu;
}

void ParteSuperior::dibujar(float angulo,unsigned int modo,float aumentar){

    brazo.dibujar(angulo,modo,aumentar);

    switch (modo) {
    case 1:
        glPushMatrix();
        glRotatef(angulo,0,1,0);
        union_base.transformar(0.3,0.5,0.3,0,5.35,0);
        union_base.draw_points();
        glPopMatrix();


        glPushMatrix();
        glRotatef(angulo,0,1,0);
        c_sujeta_esferas.transformar(0.3,0.5,0.3,0, 2.6+aumentar,0);
        c_sujeta_esferas.draw_points();
        glPopMatrix();

        glPushMatrix();
        glRotatef(angulo,0,1,0);
        pieza_cubo.transformar(0.05,1.5,0.05,-0.2, 2+aumentar,0);
        pieza_cubo.draw_points();
        glPopMatrix();
        break;
    case 2:
        glPushMatrix();
        glRotatef(angulo,0,1,0);
        union_base.transformar(0.3,0.5,0.3,0,5.35,0);
        union_base.draw_edges();
        glPopMatrix();


        glPushMatrix();
        glRotatef(angulo,0,1,0);
        c_sujeta_esferas.transformar(0.3,0.5,0.3,0, 2.6+aumentar,0);
        c_sujeta_esferas.draw_edges();
        glPopMatrix();

        glPushMatrix();
        glRotatef(angulo,0,1,0);
        pieza_cubo.transformar(0.1,1.5,0.1,-0.2, 2+aumentar,0);
        pieza_cubo.draw_edges();
        glPopMatrix();
        break;
    case 3:
        glPushMatrix();
        glRotatef(angulo,0,1,0);
        union_base.transformar(0.3,0.5,0.3,0,5.35,0);
        union_base.draw_solid(1,0,0);
        glPopMatrix();


        glPushMatrix();
        glRotatef(angulo,0,1,0);
        c_sujeta_esferas.transformar(0.3,0.5,0.3,0, 2.6+aumentar,0);
        c_sujeta_esferas.draw_solid(1,0,0);
        glPopMatrix();

        glPushMatrix();
        glRotatef(angulo,0,1,0);
        pieza_cubo.transformar(0.1,1.5,0.1,-0.2, 2+aumentar,0);
        pieza_cubo.draw_solid(1,0,0);
        glPopMatrix();
        break;
    case 4:
        glPushMatrix();
        glRotatef(angulo,0,1,0);
        union_base.transformar(0.3,0.5,0.3,0,5.35,0);
        union_base.draw_chess();
        glPopMatrix();


        glPushMatrix();
        glRotatef(angulo,0,1,0);
        c_sujeta_esferas.transformar(0.3,0.5,0.3,0, 2.6+aumentar,0);
        c_sujeta_esferas.draw_chess();
        glPopMatrix();

        glPushMatrix();
        glRotatef(angulo,0,1,0);
        pieza_cubo.transformar(0.1,1.5,0.1,-0.2, 2+aumentar,0);
        pieza_cubo.draw_chess();
        glPopMatrix();
        break;

    case 5:
        glPushMatrix();
        glRotatef(angulo,0,1,0);
        union_base.transformar(0.3,0.5,0.3,0,5.35,0);
        union_base.draw_all();
        glPopMatrix();


        glPushMatrix();
        glRotatef(angulo,0,1,0);
        c_sujeta_esferas.transformar(0.3,0.5,0.3,0, 2.6+aumentar,0);
        c_sujeta_esferas.draw_all();
        glPopMatrix();

        glPushMatrix();
        glRotatef(angulo,0,1,0);
        pieza_cubo.transformar(0.1,1.5,0.1,-0.2, 2+aumentar,0);
        pieza_cubo.draw_all();
        glPopMatrix();
        break;
    default:
        glPushMatrix();
        glRotatef(angulo,0,1,0);
        union_base.transformar(0.3,0.5,0.3,0,5.35,0);
        union_base.draw_chess();
        glPopMatrix();


        glPushMatrix();
        glRotatef(angulo,0,1,0);
        c_sujeta_esferas.transformar(0.3,0.5,0.3,0, 2.6+aumentar,0);
        c_sujeta_esferas.draw_chess();
        glPopMatrix();

        glPushMatrix();
        glRotatef(angulo,0,1,0);
        pieza_cubo.transformar(0.1,1.5,0.1,-0.2, 2+aumentar,0);
        pieza_cubo.draw_chess();
        glPopMatrix();
        break;
    }

}


