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


    //Nuevas funciones para iluminación
    void draw_solid_illuminated(int material, float alpha, float beta,float alpha2, float beta2);

    void draw_solid_gouroud(int material,float alpha, float beta, float alpha2, float beta2);

    void readPLY(vector<float> v, vector<int> f);
    void createProfile(int num_perf);
    void addTop(int tama, int fueraEje, int numeroCaras);
    void addSub(int tama, int fueraEje, int numeroCaras);
    void addFaces(int tama,int fueraEje, int num_perfiles);

    void transformar(float x, float y, float z, float xt, float yt, float zt);

    void vertex_normals();
    void faces_normals();

    void change_material(int material);

    void draw_tex(float num_perfiles, int alpha, int beta);


protected:
    vector<_vertex3ui> triangles;
    bool faces_normals_computed;
    bool vertices_normals_computed;
    bool vertices_tex_coords_computed;
    vector<_vertex3f> normal_faces;
    vector<_vertex3f> normal_vertex;
    int tama_ini;
    int fueraDelEje;

    bool tapa_sup;
    bool tapa_inf;
};

#endif // O3D_H
