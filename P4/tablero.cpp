#include "tablero.h"
#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include <GL/glut.h>
#include <ctype.h>
#include <QImage>
#include <math.h>
#include <iostream>

Tablero::Tablero() : O3d::O3d()
{

}

Tablero::Tablero(int t) : O3d::O3d()
{

    tama = t;
    vector<_vertex3f> tablero;
    vector<_vertex3ui> tab_tri;
    //tablero.resize(4*tama*tama);
    for(int i=0; i<tama; i++){
        for(int j=0; j<tama; j++){
            tablero.push_back(_vertex3f(-(tama/2.0)+j,-(tama/2.0)+i,0));
            tablero.push_back(_vertex3f(1-(tama/2.0)+j,-(tama/2.0)+i,0));
            tablero.push_back(_vertex3f(1-(tama/2.0)+j,1-(tama/2.0)+i,0));
            tablero.push_back(_vertex3f(-(tama/2.0)+j,1-(tama/2.0)+i,0));

        }
    }

    int ite=0;

    for(int i=0; i<tama; i++){
        for(int j=0; j<tama; j++){
            ite = (tama*4)*i;
            tab_tri.push_back(_vertex3ui(ite + (j*4),ite +1+(j*4),ite+3+(j*4)));
            tab_tri.push_back(_vertex3ui(ite+1+(j*4),ite+2+(j*4), ite+3+(j*4)));
        }
    }

    for(int i=0; i<tablero.size(); i++)
        tab.addVertex(tablero[i]);

    for(int i=0; i<tab_tri.size(); i++)
        tab.addTriangle(tab_tri[i]);
    //tab = table;
}

void Tablero::draw_points(){
    tab.draw_points();
}

void Tablero::draw_all(){
    tab.draw_all();
}
void Tablero::draw_chess(){
    tab.draw_chess();
}

void Tablero::draw_edges(){
    tab.draw_edges();
}

void Tablero::draw_solid(){
    tab.draw_solid();
}

void Tablero::draw_solid_illuminated(int material,float alpha, float beta){
    tab.draw_solid_illuminated(material,alpha,beta,0,0);
}

void Tablero::draw_solid_gouroud(int material,float alpha, float beta){
    tab.draw_solid_gouroud(material,alpha,beta,0,0);
}

void Tablero::vertex_normals(){
    tab.vertex_normals();
}

void Tablero::faces_normals(){
    tab.faces_normals();
}

void Tablero::draw_tex(){
    glPushMatrix();

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // parametros de aplicacion de la textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_TEXTURE_2D);

    glPopMatrix();
    glBegin(GL_TRIANGLES);

    int ite = 0;
    double inicio=0;
    double fin = 1.0;
    double inicio_y = 0;
    double fin_y = 1.0;
    double divisiones = 1.0/tama;

    int divi = (fin-inicio)/divisiones;

    float div = 1.0/divi;

    int divi_y = (fin_y-inicio_y)/divisiones;

    float div_y = 1.0/divi_y;



    int j=0;
    int i=0;
    bool avance = false;
    for(int step_y=0; step_y<tama; step_y++){
        j=0;
        for(int step=0; step<tama; step++){
            if(divisiones*step >= inicio && divisiones*step_y >= inicio_y && divisiones*step < fin && divisiones*step_y < fin_y){

                ite = (tama*4)*step_y;
                glTexCoord2f(div*j, div_y*i);
                glVertex3f(tab.get_vertex(ite+(step*4)).x, tab.get_vertex(ite +(step*4)).y, tab.get_vertex(ite + (step*4)).z);
                glTexCoord2f(div*j+div, div_y*i);
                glVertex3f(tab.get_vertex(ite +1+(step*4)).x, tab.get_vertex(ite+1+(step*4)).y, tab.get_vertex(ite+1+(step*4)).z);
                glTexCoord2f(div*j, div_y*i+div_y);
                glVertex3f(tab.get_vertex(ite+3+(step*4)).x, tab.get_vertex(ite+3+(step*4)).y, tab.get_vertex(ite+3+(step*4)).z);
                glTexCoord2f(div*j+div, div_y*i);
                glVertex3f(tab.get_vertex(ite+1+(step*4)).x, tab.get_vertex(ite+1+(step*4)).y, tab.get_vertex(ite+1+(step*4)).z);
                glTexCoord2f(div*j+div, div_y*i+div_y);
                glVertex3f(tab.get_vertex(ite+2+(step*4)).x, tab.get_vertex(ite+2+(step*4)).y, tab.get_vertex(ite+2+(step*4)).z);
                glTexCoord2f(div*j, div_y*i+div_y);
                glVertex3f(tab.get_vertex(ite+3+(step*4)).x, tab.get_vertex(ite+3+(step*4)).y, tab.get_vertex(ite+3+(step*4)).z);

                j++;
                avance =true;
            }
        }

        if(avance){
            i++;
            avance = false;
        }
    }

    this->draw_solid();

    glEnd();
}

