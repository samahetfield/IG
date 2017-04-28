#include "beethoven.h"
#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include <GL/glut.h>
#include <math.h>


Beethoven::Beethoven()
{

}

Beethoven::Beethoven(O3d o) : O3d::O3d(){
    beethoven = o;
}

void Beethoven::draw_points(){
    beethoven.draw_points();
}

void Beethoven::draw_all(){
    beethoven.draw_all();
}
void Beethoven::draw_chess(){
    beethoven.draw_chess();
}

void Beethoven::draw_edges(){
    beethoven.draw_edges();
}

void Beethoven::draw_solid(){
    beethoven.draw_solid();
}

void Beethoven::transformar(float x, float y, float z, float xt, float yt, float zt){

    glTranslatef(xt,yt,zt);
    glScalef(x,y,z);
}
