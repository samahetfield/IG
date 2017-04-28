#ifndef O3D_H
#define O3D_H

#include <vector>
#include "vertex.h"
#include "object3d.h"

class O3d : public Object3d
{
public:
    O3d(vector<_vertex3f> v, vector<_vertex3ui> e);
    O3d(int lados, int radio);

    void draw_edges();
    void draw_solid();
    void draw_chess();
    void draw_all();
    void move_object(float x, float y, float z);

protected:
    vector<_vertex3ui> triangles;
};

#endif // O3D_H
