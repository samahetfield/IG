#include "base.h"
#include "o3d.h"
#include "cilindro.h"
#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include <GL/glut.h>
#include <math.h>

Base::Base() : O3d::O3d()
{

}

Base::Base(O3d o, Cilindro c): O3d::O3d(){
    cubo = o;
    cilindro = c;
}

void Base::draw_points(){
    cubo.draw_points();
}

void Base::draw_all(){
    cubo.draw_all();
}
void Base::draw_chess(){
    cubo.draw_chess();
}

void Base::draw_edges(){
    cubo.draw_edges();
}

void Base::draw_solid(int r, int g, int b){
    cubo.draw_solid(r,g,b);
}

void Base::transformar(float x, float y, float z, float xt, float yt, float zt){

    glTranslatef(xt,yt,zt);
    glScalef(x,y,z);
}

void Base::dibujar(float angulo, unsigned int modo){

    switch (modo) {
    default:
        glPushMatrix();
        glScalef(2,0.5,2);
        cubo.draw_chess();
        glPopMatrix();

        glPushMatrix();
        cilindro.transformar(0.1,5,0.1,0,2.75,0);
        cilindro.draw_chess();
        glPopMatrix();
        break;
    case 1:
        glPushMatrix();
        glScalef(2,0.5,2);
        cubo.draw_points();
        glPopMatrix();

        glPushMatrix();
        cilindro.transformar(0.1,5,0.1,0,2.75,0);
        cilindro.draw_points();
        glPopMatrix();
        break;

    case 2:
        glPushMatrix();
        glScalef(2,0.5,2);
        cubo.draw_edges();
        glPopMatrix();

        glPushMatrix();
        cilindro.transformar(0.1,5,0.1,0,2.75,0);
        cilindro.draw_edges();
        glPopMatrix();
        break;
    case 3:
        glPushMatrix();
        glScalef(2,0.5,2);
        cubo.draw_solid(1,0,0);
        glPopMatrix();

        glPushMatrix();
        cilindro.transformar(0.1,5,0.1,0,2.75,0);
        cilindro.draw_solid(1,0,0);
        glPopMatrix();
        break;
    case 4:
        glPushMatrix();
        glScalef(2,0.5,2);
        cubo.draw_chess();
        glPopMatrix();

        glPushMatrix();
        cilindro.transformar(0.1,5,0.1,0,2.75,0);
        cilindro.draw_chess();
        glPopMatrix();
        break;
    case 5:
        glPushMatrix();
        glScalef(2,0.5,2);
        cubo.draw_all();
        glPopMatrix();

        glPushMatrix();
        cilindro.transformar(0.1,5,0.1,0,2.75,0);
        cilindro.draw_all();
        glPopMatrix();
        break;

    }

}
