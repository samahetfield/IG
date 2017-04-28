#ifndef BEETHOVEN_H
#define BEETHOVEN_H

#include "o3d.h"

class Beethoven: public O3d
{
public:
    Beethoven();
    Beethoven(O3d o);

    void draw_edges();
    void draw_solid();
    void draw_chess();
    void draw_all();
    void draw_points();

    void transformar(float x, float y, float z, float xt, float yt, float zt);

private:
    O3d beethoven;

};

#endif // BEETHOVEN_H
