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

O3d::O3d(): Object3d::Object3d(){
    vector<_vertex3ui> t;
    triangles = t;
}

O3d::O3d(vector<float> v, vector<int> e): Object3d::Object3d(v){
    int a=0;
    for(int i=0; i<e.size(); i++){
        triangles[a].x = e[i];
        triangles[a].y = e[i+1];
        triangles[a].z = e[i+2];
        a++;
     }
}

void O3d::clear(){
    vertex.clear();
    triangles.clear();
}

void O3d::addTriangle(_vertex3ui v){
    triangles.push_back(v);
}

int O3d::numFaces(){
    return triangles.size();
}

_vertex3ui O3d::getFace(int i){
    return triangles[i];
}

//Función para crear la tapa superior
void O3d::addTop(int tama, int fueraEje, int numeroCaras){
    bool hayProyeccion = false;
    int ult=tama-1;

    //Comprobamos que hay algún vértice en el eje Y con la misma altura que el último vertice del perfil
    for(int i=0; i<tama; i++){
        if(vertex[i].y == vertex[ult].y && (vertex[i].x != vertex[ult].x)){
            hayProyeccion = true;
        }
    }

    //En el caso de que exista dicho vértice, sabemos que hay que crear la tapa superior
    if(hayProyeccion){
        for(int i=1; i<numeroCaras; i++){
            //Habrá que ir añadiendo el primer vértice, el último del perfil,
            //y el siguiente que dependerá de los vertices que haya fuera del eje
            this->addTriangle(_vertex3ui(0,ult,ult+fueraEje));
            ult = ult+fueraEje;
        }

        this->addTriangle(_vertex3ui(0,ult,(ult+tama)%vertex.size()));
    }

}

//Función para crear la tapa inferior
void O3d::addSub(int tama, int fueraEje, int numeroCaras){
    int ult, base = 0;
    bool baseCogida = false;
    bool hayProyeccion = false;

    //Comprobamos cuál es el primer vértice que está fuera del eje Y
    for(int i=0; i<tama && !baseCogida; i++){
        if(vertex[i].x!=0){
            base = i-1;
            ult = base+1;
            baseCogida = true;
        }
    }

    //Así como que exista un vértice dentro del eje Y con la misma altura que el encontrado anteriormente
    for(int i=0; i<tama; i++){
        if(vertex[i].y == vertex[ult].y && (vertex[i].x != vertex[ult].x)){
            hayProyeccion = true;
        }
    }


    //Si dicho vértice eiste, sabemos que hay que crear la tapa inferior
    if(hayProyeccion){
        for(int i=1; i<numeroCaras; i++){
            if(baseCogida){
                //Los vértices sabemos que son, el anterior al que cogimos como primero que sale del eje Y
                //El cogido y llamado como ult
                //Y el siguiente que se calcula como el ult+los vértices que hay fuera del eje Y
                this->addTriangle(_vertex3ui(base,ult,ult+fueraEje));
                ult+=fueraEje;
            }
         }

        this->addTriangle(_vertex3ui(ult, base, (ult+tama)%(vertex.size())));
    }
}

//Función para añadir las caras exteriores al objeto creado por revolución
void O3d::addFaces(int tama, int fueraEje, int num_perfiles){
int v1,v2,v3;
int indice = vertex.size()-1;

//Comprobamos cuantos vértices hay fuera del eje
//Con esto conoceremos cuantos posiciones retroceder desde el último vertice añadido para crear la nueva cara
for(int i=0; i<fueraEje; i++){
    indice --;
}

v1 = (indice)%(vertex.size());
v2= (indice+1) % (vertex.size());
v3 = (indice +2) % (vertex.size());

this->addTriangle(_vertex3ui(v1,v2,v3));

}

//Función para leer desde el archivo ply los vertices y las caras del perfil
void O3d::readPLY(vector<float>v, vector<int> f){
    this->clear();
    for(int i=0; i<v.size(); i+=3){
        this->addVertex(_vertex3f(v[i], v[i+1], v[i+2]));
    }

    for(int i=0; i<f.size(); i+=3){
       this->addTriangle(_vertex3ui(f[i], f[i+1], f[i+2]));
    }
}


//Esta función nos creará tantos perfiles como le sean indicados
void O3d::createProfile(int num_perf){
    /*
        Como aclaración, se le describe que los vértices siempre están introducidos en los ficheros
        siguiendo el mismo orden.

        Dicho orden será como el descrito en la imagen siguiente
        EL sentido será el contrario a las agujas del reloj
        Y el primer elemento siempre el marcado con asterisco

        *p-----p        * p
         |     |          | \
         |     |          |    \
         p-----p          p------p


         Como se puede ver, siempre cogemos como primer elemento el situado en el eje Y,
         o en su defecto el más cercano, y en el caso de que haya varios, el que esté situado
         con un valor mayor en el eje Y
    */

    //Declaración de variables necesarias
    float v1,v2,v3;
    int step = 1;
    float angulo = 2*M_PI/num_perf;
    float perfiles_hechos = angulo;
    int fueraEje = 0;

    int tama = this->numVertex();
    int caras = this->numFaces();

    //Dentro del while iremos creando los nuevos perfiles
    while(step < num_perf){
        for(int i=0; i<tama;i++){
            int num = this->numVertex();
            v1 = vertex[i].x;
            v2 = vertex[i].y;

            //Sólo crearemos aquellos vertices que no estén en el eje Y, para no tener puntos repetidos
            if(v1 != 0){

	       fueraEje++; //Con el siguiente bucle contamos cuantos puntos tiene el perfil fuera del eje Y

               v1 = cos(perfiles_hechos)*v1;
               v3 = sin(perfiles_hechos)*vertex[i].x;

               //Añadimos el vértice y la cara correspondiente
               this->addVertex(_vertex3f(v1,v2,v3));
               this->addFaces(tama,fueraEje, num_perf);

            }

        }

        perfiles_hechos += angulo;
        step++;
    }


    //Añadimos la última cara para cerrar el objeto creado por revolución
    int last_added = vertex.size()-fueraEje;  //El primer punto que cogeremos para cerrar el objeto creado dependerá
                                              //del número de vertices que haya fuera del eje Y
    for(int i=0; i<fueraEje; i++){
        if((i==0))
            this->addTriangle(_vertex3ui((last_added) % (vertex.size()), (last_added+1)%(vertex.size()) ,tama-fueraEje));
        else{
            this->addTriangle(_vertex3ui((last_added) % (vertex.size()), tama-fueraEje ,(tama-fueraEje)+1));
        }
        last_added++;
    }

    //Crearemos las tapas superior e inferior, siempre y cuando exista algún punto en el eje
    //lo que nos dirá que habrá una cara entre este punto y los que haya fuera de este eje

    if(tama-fueraEje != 0){
       this->addTop(tama,fueraEje, num_perf);
       this->addSub(tama, fueraEje, num_perf);
    }

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
        glVertex3f((this->get_vertex(v3)).x, this->get_vertex(v3).y, this->get_vertex(v3).z);
        glVertex3f((this->get_vertex(v1)).x, this->get_vertex(v1).y, this->get_vertex(v1).z);

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

//Función que nos permite dibujar todos los estilos a la vez
void O3d::draw_all(){
    draw_points();
    draw_edges();
    draw_solid();
}
