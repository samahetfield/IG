#include "cilindro.h"
#include "o3d.h"
#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include <GL/glut.h>
#include <math.h>

Cilindro::Cilindro() : O3d::O3d()
{

}

Cilindro::Cilindro(O3d o) : O3d::O3d(){
    cilindro = o;
}

void Cilindro::draw_points(){
    cilindro.draw_points();
}

void Cilindro::draw_all(){
    cilindro.draw_all();
}
void Cilindro::draw_chess(){
    cilindro.draw_chess();
}

void Cilindro::draw_edges(){
    cilindro.draw_edges();
}

void Cilindro::draw_solid(){
    cilindro.draw_solid();
}

void Cilindro::transformar(float x, float y, float z, float xt, float yt, float zt){

    glTranslatef(xt,yt,zt);
    glScalef(x,y,z);
}
