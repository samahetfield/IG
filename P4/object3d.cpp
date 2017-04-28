#include "object3d.h"
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>

Object3d::Object3d(vector<_vertex3f> v)
{
    vertex = v;
}

Object3d::Object3d(){
    vector<_vertex3f> v;
    vertex = v;
}

Object3d::Object3d(vector<float> v){
    int a=0;
    for(int i=0; i<v.size(); i+=3){
        vertex[a].x = v[i];
        vertex[a].y = v[i+1];
        vertex[a].z = v[i+2];
        a++;
    }
}

Object3d::Object3d(int num_lados, int radio){
    int pos = 360/num_lados;

    vertex.push_back(_vertex3f(0,0,0));

    for(int i=0; i<num_lados; i++){
        vertex.push_back(_vertex3f(radio*(cos(pos*i)), radio*(sin(pos*i)), 0));
    }
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

    glBegin(GL_TRIANGLE_FAN);

    for(int i=0; i<vertex.size()-1; i++){
        glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);
    }
        glVertex3f(vertex[1].x, vertex[1].y, vertex[1].z);


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

