#ifndef O3D_H
#define O3D_H

#include <vector>
#include "vertex.h"
#include "object3d.h"

class O3d : public Object3d
{
public:
    O3d(vector<_vertex3f> v, vector<_vertex3ui> e);
    O3d();
    O3d(vector<float> v, vector<int> e);
    O3d(int lados, int radio);

    void clear();

    void addTriangle(_vertex3ui);
    int numFaces();
    _vertex3ui getFace(int i);
    void draw_edges();
    void draw_solid();
    void draw_chess();
    void draw_all();
   // void move_object(float x, float y, float z);

    void readPLY(vector<float> v, vector<int> f);
    void createProfile(int num_perf);
    void addTop(int tama, int fueraEje, int numeroCaras);
    void addSub(int tama, int fueraEje, int numeroCaras);
    void addFaces(int tama,int fueraEje, int num_perfiles);

protected:
    vector<_vertex3ui> triangles;
};

#endif // O3D_H
