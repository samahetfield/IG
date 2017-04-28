#include "esfera.h"
#include "o3d.h"
#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include <GL/glut.h>
#include <math.h>


Esfera::Esfera() : O3d::O3d()
{

}

Esfera::Esfera(O3d o) : O3d::O3d(){
    obj_rev = o;
}

void Esfera::createProfile(int num_perf){
    float v1,v2,v3;
    int step = 1;
    float angulo = 2*M_PI/num_perf;
    float perfiles_hechos = angulo;
    int fueraEje = 0;

    int tama = obj_rev.numVertex();
    int caras = obj_rev.numFaces();

    //Con el siguiente bucle contamos cuantos puntos tiene el perfil fuera del eje Y
    for(int i=0; i<tama; i++){
        if(obj_rev.get_vertex(i).x != 0)
            fueraEje++;
    }

    //Dentro del while iremos creando los nuevos perfiles
    while(step < num_perf){
        bool primero = false;
        for(int i=0; i<tama;i++){
            int num = obj_rev.numVertex();
            v1 = obj_rev.get_vertex(i).x;
            v2 = obj_rev.get_vertex(i).y;
            v3 = obj_rev.get_vertex(i).z;

            //Sólo crearemos aquellos vertices que no estén en el eje Y, para no tener puntos repetidos
            if(v1 != 0){
               v1 = cos(perfiles_hechos)*v1;
               v3 = sin(perfiles_hechos)*obj_rev.get_vertex(i).x;

               //Añadimos el vértice y la cara correspondiente
               obj_rev.addVertex(_vertex3f(v1,v2,v3));

               if(primero){
                this->addFaces(tama,fueraEje, num_perf);
               }
               primero = true;
            }

        }

        perfiles_hechos += angulo;
        step++;
    }


    //Añadimos la última cara para cerrar el objeto creado por revolución
    int last_added = obj_rev.numVertex()-fueraEje;  //El primer punto que cogeremos para cerrar el objeto creado dependerá
    int indice = tama-fueraEje;                                      //del número de vertices que haya fuera del eje Y
    for(int i=0; i<fueraEje; i++){
        obj_rev.addTriangle(_vertex3ui((last_added), (last_added+1) ,indice));
        obj_rev.addTriangle(_vertex3ui((last_added+1) ,indice,indice+1));

        indice++;
        last_added++;
    }

    //Crearemos las tapas superior e inferior, siempre y cuando exista algún punto en el eje
    //lo que nos dirá que habrá una cara entre este punto y los que haya fuera de este eje

    for(int i=tama-fueraEje; i<obj_rev.numVertex(); i+= fueraEje){
        int num = (i+fueraEje) % (obj_rev.numVertex() - (tama-fueraEje));
        obj_rev.addTriangle(_vertex3ui(i,  (tama-fueraEje)-1 , (i+fueraEje) % (obj_rev.numVertex() - (tama-fueraEje))));
    }
    int ult =0;
    for(int i=tama-1; i<obj_rev.numVertex()-fueraEje; i+= fueraEje){
        obj_rev.addTriangle(_vertex3ui(i, 0,i+fueraEje));
        ult = i;
    }
        obj_rev.addTriangle(_vertex3ui(ult, 0,tama-1));

}
void Esfera::addFaces(int tama, int fueraEje, int num_perfiles){
    int v1,v2,v3;
    int indice = obj_rev.numVertex()-2;

    //Comprobamos cuantos vértices hay fuera del eje
    //Con esto conoceremos cuantos posiciones retroceder desde el último vertice añadido para crear la nueva cara
    for(int i=0; i<fueraEje; i++){
        indice --;
    }

    v1 = (indice)%(obj_rev.numVertex());
    v2= (indice+1) % (obj_rev.numVertex());
    v3 = (indice + fueraEje) % (obj_rev.numVertex());

    obj_rev.addTriangle(_vertex3ui(v1,v2,v3));

    v1 = (indice+1)%(obj_rev.numVertex());
    v2= (indice + fueraEje) % (obj_rev.numVertex());
    v3 = (obj_rev.numVertex() -1) % (obj_rev.numVertex());

    obj_rev.addTriangle(_vertex3ui(v1,v2,v3));
}


void Esfera::draw_points(){
    obj_rev.draw_points();
}

void Esfera::draw_all(){
    obj_rev.draw_all();
}
void Esfera::draw_chess(){
    obj_rev.draw_chess();
}

void Esfera::draw_edges(){
    obj_rev.draw_edges();
}

void Esfera::draw_solid(){
    obj_rev.draw_solid();
}

void Esfera::transformar(float x, float y, float z, float xt, float yt, float zt){
    glTranslatef(xt,yt,zt);
    glScalef(x,y,z);

}
