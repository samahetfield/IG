#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include "vertex.h"

class Object3d
{
public:
    Object3d(vector<_vertex3f> v);
    Object3d();
    Object3d(vector<float> v);
    Object3d(int num_lados, int radio);

    void draw_points();
    void draw_polygon();
    _vertex3f get_vertex(int i);
    void setVertex(_vertex3f v);
    void addVertex(_vertex3f v);
    int numVertex();

protected:
    vector<_vertex3f> vertex;

};

#endif // OBJECT3D_H
