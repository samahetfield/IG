#include "object3d.h"
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>

Object3d::Object3d(vector<_vertex3f> v)
{
    vertex = v;
}

Object3d::Object3d(int num_lados, int radio){
    int pos = 360/num_lados;

    vertex.push_back(_vertex3f(0,0,0));
    vertex.push_back(_vertex3f(1,1,0));
    vertex.push_back(_vertex3f(2,0,0));
    vertex.push_back(_vertex3f(3,1,0));
    vertex.push_back(_vertex3f(4,0,0));


}
void Object3d::draw_points(){

    glColor3f(0,0,1);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (int i=0;i<vertex.size();i++){
        glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);
        }
    glEnd();
}

void Object3d::draw_polygon(){

    glColor3f(0,0,1);

    glBegin(GL_TRIANGLE_STRIP);

        glVertex3f(vertex[0].x, vertex[0].y, vertex[0].z);
        glVertex3f(vertex[1].x, vertex[1].y, vertex[1].z);

    for(int i=2; i<vertex.size(); i++){
        glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);

    }



    glEnd();
}
_vertex3f Object3d::get_vertex(int i){
    return vertex[i];
}

void Object3d::addVertex(_vertex3f v){
    vertex.push_back(v);
}

int Object3d::numVertex(){
    return vertex.size();

}

