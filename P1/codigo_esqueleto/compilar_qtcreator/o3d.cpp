#include "o3d.h"
#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include <GL/glut.h>
#include <math.h>

O3d::O3d(vector<_vertex3f> v, vector<_vertex3ui> e): Object3d::Object3d(v)
{
    triangles= e;
}

void O3d::draw_edges(){
    unsigned int v1,v2,v3;
    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_LINES);

    for(int i=0; i<triangles.size(); i++){
        v1 = triangles[i].x;
        v2 = triangles[i].y;
        v3 = triangles[i].z;
        // Dibujamos las aristas obteniendo los vértices de la superclase
        //llamando a la función para obtener el vértice de la posición dada
        glVertex3f((this->get_vertex(v1)).x, this->get_vertex(v1).y, this->get_vertex(v1).z);
        glVertex3f((this->get_vertex(v2)).x, this->get_vertex(v2).y, this->get_vertex(v2).z);
        glVertex3f((this->get_vertex(v2)).x, this->get_vertex(v2).y, this->get_vertex(v2).z);
        glVertex3f((this->get_vertex(v3)).x, this->get_vertex(v3).y, this->get_vertex(v3).z);

    }

    glEnd();
}

void O3d::draw_solid(){
    unsigned int v1,v2,v3;
    glPointSize(4);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    for(int i=0; i<triangles.size(); i++){
        v1 = triangles[i].x;
        v2 = triangles[i].y;
        v3 = triangles[i].z;

        // Dibujamos las aristas obteniendo los vértices de la superclase
        //llamando a la función para obtener el vértice de la posición dada
        glVertex3f((this->get_vertex(v1)).x, this->get_vertex(v1).y, this->get_vertex(v1).z);
        glVertex3f((this->get_vertex(v2)).x, this->get_vertex(v2).y, this->get_vertex(v2).z);
        glVertex3f((this->get_vertex(v3)).x, this->get_vertex(v3).y, this->get_vertex(v3).z);

    }

    glEnd();
}

void O3d::draw_chess(){
    unsigned int v1,v2,v3;
    glPointSize(4);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    // Controlando el valor de i, vamos intercambiando el color con el que queremos colorear la cara
    for(int i=0; i<triangles.size(); i++){
        if((i%2)==0){
            glColor3f(0,0,0);
        }
        else{
            glColor3f(0,1,1);
        }

        v1 = triangles[i].x;
        v2 = triangles[i].y;
        v3 = triangles[i].z;

        // Dibujamos las aristas obteniendo los vértices de la superclase
        //llamando a la función para obtener el vértice de la posición dada
        glVertex3f((this->get_vertex(v1)).x, this->get_vertex(v1).y, this->get_vertex(v1).z);
        glVertex3f((this->get_vertex(v2)).x, this->get_vertex(v2).y, this->get_vertex(v2).z);
        glVertex3f((this->get_vertex(v3)).x, this->get_vertex(v3).y, this->get_vertex(v3).z);
    }

    glEnd();

}

void O3d::draw_all(){
    draw_points();
    draw_edges();
    draw_solid();
}

void O3d::move_object(float x, float y, float z){
    for(int i=0; i<this->numVertex(); i++ ){
        vertex[i].x = vertex[i].x + x;
        vertex[i].y = vertex[i].y + y;
        vertex[i].z = vertex[i].z + z;
    }
}
