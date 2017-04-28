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

void Cilindro::createProfile(int num_perf){
    cilindro.createProfile(num_perf);

    cilindro.faces_normals();
    cilindro.vertex_normals();

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

void Cilindro::draw_solid(int r, int g, int b){
    cilindro.draw_solid(r,g,b);
}

void Cilindro::draw_solid_gouroud(int material,float alpha, float beta, float alpha2, float beta2){
    cilindro.draw_solid_gouroud(material, alpha, beta,alpha,beta);
}

void Cilindro::draw_solid_illuminated(int material,float alpha, float beta, float alpha2, float beta2){
    cilindro.draw_solid_illuminated(material,alpha,beta,alpha2,beta2);
}

void Cilindro::draw_tex(float num_perfiles,int alpha,int beta){
    cilindro.draw_tex(num_perfiles,alpha,beta);
}

void Cilindro::vertex_normals(){
    cilindro.vertex_normals();
}

void Cilindro::faces_normals(){
    cilindro.faces_normals();
}


void Cilindro::transformar(float x, float y, float z, float xt, float yt, float zt){

    glTranslatef(xt,yt,zt);
    glScalef(x,y,z);
}
