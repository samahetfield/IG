#include "o3d.h"
#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include <GL/glut.h>
#include <math.h>

O3d::O3d(vector<_vertex3f> v, vector<_vertex3ui> e): Object3d::Object3d(v)
{
    triangles= e;

    tapa_inf=false;
    tapa_sup=false;
    faces_normals();
    vertex_normals();
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

    faces_normals();
    vertex_normals();
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
            tapa_sup=true;
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
            tapa_inf = true;
        }
    }


    //Si dicho vértice eiste, sabemos que hay que crear la tapa inferior
    if(hayProyeccion){
        for(int i=1; i<numeroCaras; i++){
            if(baseCogida){
                //Los vértices sabemos que son, el anterior al que cogimos como primero que sale del eje Y
                //El cogido y llamado como ult
                //Y el siguiente que se calcula como el ult+los vértices que hay fuera del eje Y
                this->addTriangle(_vertex3ui(base,ult+fueraEje,ult));
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

if(indice%2 == 0)
this->addTriangle(_vertex3ui(v1,v3,v2));
else
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
    tama_ini = tama;


    //Con el siguiente bucle contamos cuantos puntos tiene el perfil fuera del eje Y
    for(int i=0; i<tama; i++){
        if(vertex[i].x != 0)
            fueraEje++;
    }

    fueraDelEje = fueraEje;

    //Dentro del while iremos creando los nuevos perfiles
    while(step < num_perf){
        for(int i=0; i<tama;i++){
            int num = this->numVertex();
            v1 = vertex[i].x;
            v2 = vertex[i].y;
            v3 = vertex[i].z;

            //Sólo crearemos aquellos vertices que no estén en el eje Y, para no tener puntos repetidos
            if(v1 != 0){
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

    faces_normals();
    vertex_normals();

}


void O3d::draw_edges(){

    glColor3f(0,0,1);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (int i=0;i<vertex.size();i++){
        glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);
    }

    for(int i=0; i<normal_vertex.size(); i++){
        glVertex3f(normal_vertex[i].x, normal_vertex[i].y, normal_vertex[i].z);

    }
    glEnd();
    /*
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
    */
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


//Funciones para dibujar con iluminación

void O3d::draw_solid_illuminated(int material, float alpha,float beta,float alpha2, float beta2){
    unsigned int v1,v2,v3;
    glPointSize(4);

    GLfloat Luz0[4]={10,10,10,1};
    GLfloat Luz1[4]={0,0,1,0};

    GLfloat specularD[] = { 0, 1, 0, 1.0 };
    GLfloat ambientD[] = { 0, 1, 0, 1 };



    this->change_material(material);

    glPushMatrix();
    glRotatef(alpha, 0,1,0);
    glRotatef(beta, 1,0,0);
    glLightfv(GL_LIGHT0,GL_POSITION,Luz0);
    glPopMatrix();



    glPushMatrix();
    glRotatef(alpha2, 0,1,0);
    glRotatef(beta2, 1,0,0);
    glLightfv(GL_LIGHT1,GL_POSITION,Luz1);

    glPopMatrix();

    glShadeModel(GL_FLAT);


    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT1, GL_DIFFUSE, ambientD);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularD);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);


    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    for(int i=0; i<triangles.size(); i++){
        v1 = triangles[i].x;
        v2 = triangles[i].y;
        v3 = triangles[i].z;

        // Dibujamos las aristas obteniendo los vértices de la superclase
        //llamando a la función para obtener el vértice de la posición dada
        glNormal3f(normal_faces[i].x, normal_faces[i].y, normal_faces[i].z);
        glVertex3f((this->get_vertex(v1)).x, this->get_vertex(v1).y, this->get_vertex(v1).z);
        glVertex3f((this->get_vertex(v2)).x, this->get_vertex(v2).y, this->get_vertex(v2).z);
        glVertex3f((this->get_vertex(v3)).x, this->get_vertex(v3).y, this->get_vertex(v3).z);

    }

    glEnd();

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);


}

void O3d::draw_solid_gouroud(int material, float alpha, float beta,float alpha2, float beta2){
    unsigned int v1,v2,v3;
    glPointSize(4);
    GLfloat Luz0[4]={0,0,10,1};
    GLfloat Luz1[4]={0,0,1,0};
    GLfloat specularD[] = { 0, 1, 0, 0.1 };
    GLfloat ambientD[] = { 0, 1, 0, 1 };
    GLfloat specularP[] = { 1, 1, 0, 1.0 };
    GLfloat ambientP[] = { 1, 1, 0, 1 };


    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glPushMatrix();
    glRotatef(alpha, 0,1,0);
    glRotatef(beta,1,0,0);
    glLightfv(GL_LIGHT0,GL_POSITION,Luz0);
    glPopMatrix();

    glPushMatrix();
    glRotatef(alpha2, 0,1,0);
    glRotatef(beta2,1,0,0);
    glLightfv(GL_LIGHT1,GL_POSITION,Luz1);
    glPopMatrix();


    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, ambientD);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularD);
    glEnable(GL_LIGHT1);

    this->change_material(material);


    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    for(int i=0; i<triangles.size(); i++){
        v1 = triangles[i].x;
        v2 = triangles[i].y;
        v3 = triangles[i].z;

        // Dibujamos las aristas obteniendo los vértices de la superclase
        //llamando a la función para obtener el vértice de la posición dada
        glNormal3fv((GLfloat *) &normal_vertex[triangles[i].x]);
        glVertex3f((this->get_vertex(v1)).x, this->get_vertex(v1).y, this->get_vertex(v1).z);
        glNormal3fv((GLfloat *) &normal_vertex[triangles[i].y]);
        glVertex3f((this->get_vertex(v2)).x, this->get_vertex(v2).y, this->get_vertex(v2).z);
        glNormal3fv((GLfloat *) &normal_vertex[triangles[i].z]);
        glVertex3f((this->get_vertex(v3)).x, this->get_vertex(v3).y, this->get_vertex(v3).z);

    }

    glEnd();
   // glDisable(GL_LIGHTING);
   // glDisable(GL_LIGHT0);
   // glDisable(GL_LIGHT1);
}

//Funciones para calcular las normales de los vértices y de las caras

void O3d::faces_normals(){
    vector<_vertex3f> vertices1, vertices2;

    if(!faces_normals_computed){
        vertices1.resize(triangles.size());
        vertices2.resize(triangles.size());

        normal_faces.resize(triangles.size());

        //Calculo de las normales de las caras

        for(int i=0; i<triangles.size(); i++){

            vertices1[i].x = vertex[triangles[i].y].x - vertex[triangles[i].x].x;
            vertices1[i].y = vertex[triangles[i].y].y - vertex[triangles[i].x].y;
            vertices1[i].z = vertex[triangles[i].y].z - vertex[triangles[i].x].z;

            vertices2[i].x = vertex[triangles[i].x].x - vertex[triangles[i].z].x;
            vertices2[i].y = vertex[triangles[i].x].y - vertex[triangles[i].z].y;
            vertices2[i].z = vertex[triangles[i].x].z - vertex[triangles[i].z].z;

        }

        //Calculo la normal del plano
        for(int i=0; i<vertices1.size(); i++){
            normal_faces[i] = vertices2[i].cross_product(vertices1[i]);
            normal_faces[i].normalize();

            faces_normals_computed = true;
        }

    }


}

void O3d::vertex_normals(){
    vector<int> contador;

    normal_vertex.resize(triangles.size());
    contador.resize(triangles.size());

    if(!vertices_normals_computed){
        faces_normals();

        for(int i=0; i<vertex.size(); i++){
            contador[i] = 0;
        }

        for(int i=0; i<triangles.size(); i++){
            normal_vertex[i].x = 0;
            normal_vertex[i].y = 0;
            normal_vertex[i].z = 0;
        }

        //Calculo de caras adyacentes
        for(int i=0; i<normal_faces.size(); i++){
            normal_vertex[triangles[i].x].x += normal_faces[i].x;
            normal_vertex[triangles[i].x].y += normal_faces[i].y;
            normal_vertex[triangles[i].x].z += normal_faces[i].z;
            normal_vertex[triangles[i].y].x += normal_faces[i].x;
            normal_vertex[triangles[i].y].y += normal_faces[i].y;
            normal_vertex[triangles[i].y].z += normal_faces[i].z;
            normal_vertex[triangles[i].z].x += normal_faces[i].x;
            normal_vertex[triangles[i].z].y += normal_faces[i].y;
            normal_vertex[triangles[i].z].z += normal_faces[i].z;

            contador[triangles[i].x]++;
            contador[triangles[i].y]++;
            contador[triangles[i].z]++;

        }

        //Promedio de caras adyacentes

        for(int i=0; i<normal_vertex.size(); i++){
            normal_vertex[i] /= contador[i];
            normal_vertex[i].normalize();

            vertices_normals_computed = true;
        }

    }

}

void O3d::change_material(int material){

    GLfloat ambient1[4] = { 0.19125f, 0.0735f, 0.0225f, 1.0f};
    GLfloat ambient2[4] = {0.329412f, 0.223529f, 0.027451f,1.0f};
    GLfloat specular1[4] = {0.256777f, 0.137622f, 0.086014f, 1.0f};
    GLfloat specular2[4] = {0.992157f, 0.941176f, 0.807843f, 1.0f};

    GLfloat material1[4] = {0.7038f, 0.27048f, 0.0828f, 1.0f };
    GLfloat material2[4] = {0.780392f, 0.568627f, 0.113725f, 1.0f};

    if(material == 1){
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material1);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
        glMaterialf(GL_FRONT, GL_SHININESS,  12.8f);
    }
    else if(material == 2){

        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialf(GL_FRONT, GL_SHININESS, 27.8974f);

    }

}

void O3d::draw_tex(float num_perfiles,int alpha,int beta){
    glPushMatrix();

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // parametros de aplicacion de la textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_TEXTURE_2D);

    glPopMatrix();

    glBegin(GL_TRIANGLES);

    float divisiones = 1.0/num_perfiles;
    int ite = 0;
    float inicio=0;
    int primero = 0;
    int resta = 0;
    int avance = tama_ini - fueraDelEje;
    bool prim = false;
        int tama = this->numVertex();
        int paso = 0;
        int step=0;


        //this->draw_solid_gouroud(1,0,0);
        if(fueraDelEje == 1){
            for(int j=0; step<(num_perfiles-1); j++){
                if(vertex[j].x != 0){
                    if(!prim){
                        primero =j;
                        resta = tama_ini-fueraDelEje;
                    }
                    prim = true;

                    glTexCoord2f(1-(divisiones*(j-2)),0.5);
                    glVertex3f(this->get_vertex(ite+2+((j-2)*fueraDelEje)).x, this->get_vertex(ite +2+((j-2)*fueraDelEje)).y, this->get_vertex(ite +2+ ((j-2)*fueraDelEje)).z);
                    glTexCoord2f(1-(divisiones*(j-2)+divisiones),0.5);
                    glVertex3f(this->get_vertex(ite +3+((j-2)*fueraDelEje)).x, this->get_vertex(ite+3+((j-2)*fueraDelEje)).y, this->get_vertex(ite+3+((j-2)*fueraDelEje)).z);
                    glTexCoord2f(1-(divisiones*(j-2)), 0);
                    glVertex3f(this->get_vertex(1).x, this->get_vertex(1).y, this->get_vertex(1).z);

                    step++;

                }
            }

            glTexCoord2f(divisiones,0.5);
            glVertex3f(this->get_vertex(tama-1).x, this->get_vertex(tama-1).y, this->get_vertex(tama-1).z);
            glTexCoord2f(0,0.5);
            glVertex3f(this->get_vertex(2).x, this->get_vertex(2).y, this->get_vertex(2).z);
            glTexCoord2f(divisiones, 0);
            glVertex3f(this->get_vertex(1).x, this->get_vertex(1).y, this->get_vertex(1).z);


            step = 0;
            for(int j=0; step<(num_perfiles-1); j++){
                if(vertex[j].x != 0){
                    if(!prim){
                        primero =j;
                        resta = tama_ini-fueraDelEje;
                    }
                    prim = true;

                    glTexCoord2f(1-(divisiones*(j-2)),0.5);
                    glVertex3f(this->get_vertex(ite+2+((j-2)*fueraDelEje)).x, this->get_vertex(ite +2+((j-2)*fueraDelEje)).y, this->get_vertex(ite +2+ ((j-2)*fueraDelEje)).z);
                    glTexCoord2f(1-(divisiones*(j-2)+divisiones),0.5);
                    glVertex3f(this->get_vertex(ite +3+((j-2)*fueraDelEje)).x, this->get_vertex(ite+3+((j-2)*fueraDelEje)).y, this->get_vertex(ite+3+((j-2)*fueraDelEje)).z);
                    glTexCoord2f(1-(divisiones*(j-2)), 1);
                    glVertex3f(this->get_vertex(0).x, this->get_vertex(0).y, this->get_vertex(0).z);

                    step++;

                }
            }

            glTexCoord2f(divisiones,0.5);
            glVertex3f(this->get_vertex(tama-1).x, this->get_vertex(tama-1).y, this->get_vertex(tama-1).z);
            glTexCoord2f(0,0.5);
            glVertex3f(this->get_vertex(2).x, this->get_vertex(2).y, this->get_vertex(2).z);
            glTexCoord2f(divisiones, 1);
            glVertex3f(this->get_vertex(0).x, this->get_vertex(0).y, this->get_vertex(0).z);
        }
        else{
            float partes_ini;
            float partes_fin;
            if(tapa_sup && tapa_inf){
                partes_ini = 1.0/3;
                partes_fin = partes_ini + partes_ini;
            }
            else if(tapa_sup){
                partes_ini = 0 ;
                partes_fin = 0.5;

            }
            else if(tapa_inf){
                partes_ini = 0.5;
                partes_fin = 1;
            }
            else{
                partes_ini = 0;
                partes_fin = 1;
            }

            if(tapa_sup){
                step = 0;
                for(int j=0; step<(num_perfiles-1); j++){
                    if(vertex[j].x != 0){
                        if(!prim){
                            primero =j+1;
                            resta = tama_ini-fueraDelEje;
                        }
                        prim = true;

                        glTexCoord2f(1-(divisiones*(j-2)),partes_fin);
                        glVertex3f(this->get_vertex(ite+primero+((j-2)*fueraDelEje)).x, this->get_vertex(ite +primero+((j-2)*fueraDelEje)).y, this->get_vertex(ite +primero+ ((j-2)*fueraDelEje)).z);
                        glTexCoord2f(1-(divisiones*(j-2)+divisiones),partes_fin);
                        glVertex3f(this->get_vertex(ite +primero+fueraDelEje+((j-2)*fueraDelEje)).x, this->get_vertex(ite+primero+fueraDelEje+((j-2)*fueraDelEje)).y, this->get_vertex(ite+primero+fueraDelEje+((j-2)*fueraDelEje)).z);
                        glTexCoord2f(1-(divisiones*(j-2)), 1);
                        glVertex3f(this->get_vertex(0).x, this->get_vertex(0).y, this->get_vertex(0).z);

                        step++;

                    }
                }

                glTexCoord2f(divisiones,partes_fin);
                glVertex3f(this->get_vertex(tama-1).x, this->get_vertex(tama-1).y, this->get_vertex(tama-1).z);
                glTexCoord2f(0,partes_fin);
                glVertex3f(this->get_vertex(primero).x, this->get_vertex(primero).y, this->get_vertex(primero).z);
                glTexCoord2f(divisiones, 1);
                glVertex3f(this->get_vertex(0).x, this->get_vertex(0).y, this->get_vertex(0).z);
            }
            if(tapa_inf){
                step = 0;
                prim = false;
                for(int j=0; step<(num_perfiles-1); j++){
                    if(vertex[j].x != 0){
                        if(!prim){
                            primero =j;
                            resta = tama_ini-fueraDelEje;
                        }
                        prim = true;

                        glTexCoord2f(1-(divisiones*(j-resta)),partes_ini);
                        glVertex3f(this->get_vertex(ite+primero+((j-resta)*fueraDelEje)).x, this->get_vertex(ite +primero+((j-resta)*fueraDelEje)).y, this->get_vertex(ite +primero+ ((j-resta)*fueraDelEje)).z);
                        glTexCoord2f(1-(divisiones*(j-resta)+divisiones),partes_ini);
                        glVertex3f(this->get_vertex(ite +primero+fueraDelEje+((j-resta)*fueraDelEje)).x, this->get_vertex(ite+primero+fueraDelEje+((j-resta)*fueraDelEje)).y, this->get_vertex(ite+primero+fueraDelEje+((j-resta)*fueraDelEje)).z);
                        glTexCoord2f(1-(divisiones*(j-resta)), 0);
                        glVertex3f(this->get_vertex(primero-1).x, this->get_vertex(primero-1).y, this->get_vertex(primero-1).z);

                        step++;

                    }
                }

                glTexCoord2f(divisiones,partes_ini);
                glVertex3f(this->get_vertex(tama-2).x, this->get_vertex(tama-2).y, this->get_vertex(tama-2).z);
                glTexCoord2f(0,partes_ini);
                glVertex3f(this->get_vertex(primero).x, this->get_vertex(primero).y, this->get_vertex(primero).z);
                glTexCoord2f(divisiones, 0);
                glVertex3f(this->get_vertex(primero-1).x, this->get_vertex(primero-1).y, this->get_vertex(primero-1).z);
            }


            // Parte central
            step = 0;
            prim = false;
            for(int j=0; step<(num_perfiles-1); j++){
                if(vertex[j].x != 0){
                    if(!prim){
                        primero =j;
                        resta = tama_ini-fueraDelEje;
                    }
                    prim = true;

                    if(divisiones*j >= inicio){
                        if(primero%2 != 0){
                            ite = 2*paso;
                            glTexCoord2f(1-divisiones*(j-1),partes_ini);
                            glVertex3f(this->get_vertex(ite+1+((j-1)*2)).x, this->get_vertex(ite +1+((j-1)*2)).y, this->get_vertex(ite +1+ ((j-1)*2)).z);
                            glTexCoord2f(1-(divisiones*j+divisiones),partes_ini);
                            glVertex3f(this->get_vertex(ite +3+((j-1)*2)).x, this->get_vertex(ite+3+((j-1)*2)).y, this->get_vertex(ite+3+((j-1)*2)).z);
                            glTexCoord2f(1-(divisiones*j), partes_fin);
                            glVertex3f(this->get_vertex(ite+2+((j-1)*2)).x, this->get_vertex(ite+2+((j-1)*2)).y, this->get_vertex(ite+2+((j-1)*2)).z);
                            glTexCoord2f(1-(divisiones*j+divisiones), partes_ini);
                            glVertex3f(this->get_vertex(ite+3+((j-1)*2)).x, this->get_vertex(ite+3+((j-1)*2)).y, this->get_vertex(ite+3+((j-1)*2)).z);
                            glTexCoord2f(1-(divisiones*j+divisiones),partes_fin);
                            glVertex3f(this->get_vertex(ite+4+((j-1)*2)).x, this->get_vertex(ite+4+((j-1)*2)).y, this->get_vertex(ite+4+((j-1)*2)).z);
                            glTexCoord2f(1-(divisiones*j),partes_fin);
                            glVertex3f(this->get_vertex(ite+2+((j-1)*2)).x, this->get_vertex(ite+2+((j-1)*2)).y, this->get_vertex(ite+2+((j-1)*2)).z);
                        }
                        else{
                            ite = 2*paso;
                            glTexCoord2f(1-(divisiones*(j-resta)), partes_ini);
                            glVertex3f(this->get_vertex(ite+resta+((j-resta)*(fueraDelEje))).x,this->get_vertex(ite+resta+((j-resta)*(fueraDelEje))).y, this->get_vertex(ite+resta+((j-resta)*(fueraDelEje))).z);
                            glTexCoord2f(1-(divisiones*(j-resta)+divisiones),partes_ini);
                            glVertex3f(this->get_vertex(ite +resta+((j-resta+1)*fueraDelEje)).x, this->get_vertex(ite +resta+((j-resta+1)*fueraDelEje)).y, this->get_vertex(ite +resta+((j-resta+1)*fueraDelEje)).z);
                            glTexCoord2f(1-(divisiones*(j-resta)), partes_fin);
                            glVertex3f(this->get_vertex(ite+resta+1+((j-resta)*fueraDelEje)).x, this->get_vertex(ite+resta+1+((j-resta)*fueraDelEje)).y, this->get_vertex(ite+resta+1+((j-resta)*fueraDelEje)).z);
                            glTexCoord2f(1-(divisiones*(j-resta)+divisiones), partes_ini);
                            glVertex3f(this->get_vertex(ite+resta+((j-resta+1)*fueraDelEje)).x, this->get_vertex(ite+resta+((j-resta+1)*fueraDelEje)).y, this->get_vertex(ite+resta+((j-resta+1)*fueraDelEje)).z);
                            glTexCoord2f(1-(divisiones*(j-resta)+divisiones),partes_fin);
                            glVertex3f(this->get_vertex(ite+resta+1+((j-resta+1)*fueraDelEje)).x, this->get_vertex(ite+resta+1+((j-resta+1)*fueraDelEje)).y, this->get_vertex(ite+resta+1+((j-resta+1)*fueraDelEje)).z);
                            glTexCoord2f(1-(divisiones*(j-resta)), partes_fin);
                            glVertex3f(this->get_vertex(ite+resta+1+((j-resta)*fueraDelEje)).x, this->get_vertex(ite+resta+1+((j-resta)*fueraDelEje)).y,this->get_vertex(ite+resta+1+((j-resta)*fueraDelEje)).z);
                        }

                    }
                    step++;
                }
            }


            if(primero%2 != 0){
                glTexCoord2f(divisiones,partes_ini);
                glVertex3f(this->get_vertex(tama-2).x, this->get_vertex(tama-2).y, this->get_vertex(tama-2).z);
                glTexCoord2f(0,partes_ini);
                glVertex3f(this->get_vertex(1).x, this->get_vertex(1).y, this->get_vertex(1).z);
                glTexCoord2f(divisiones, partes_fin);
                glVertex3f(this->get_vertex(tama-1).x, this->get_vertex(tama-1).y, this->get_vertex(tama-1).z);
                glTexCoord2f(0, partes_ini);
                glVertex3f(this->get_vertex(1).x, this->get_vertex(1).y, this->get_vertex(1).z);
                glTexCoord2f(0,partes_fin);
                glVertex3f(this->get_vertex(2).x, this->get_vertex(2).y, this->get_vertex(2).z);
                glTexCoord2f(divisiones,partes_fin);
                glVertex3f(this->get_vertex(tama-1).x, this->get_vertex(tama-1).y, this->get_vertex(tama-1).z);
            }
            else{

                glTexCoord2f(divisiones,partes_ini);
                glVertex3f(this->get_vertex(tama-2).x, this->get_vertex(tama-2).y, this->get_vertex(tama-2).z);
                glTexCoord2f(0,partes_ini);
                glVertex3f(this->get_vertex(resta).x, this->get_vertex(resta).y, this->get_vertex(resta).z);
                glTexCoord2f(divisiones, partes_fin);
                glVertex3f(this->get_vertex(tama-1).x, this->get_vertex(tama-1).y, this->get_vertex(tama-1).z);
                glTexCoord2f(0, partes_ini);
                glVertex3f(this->get_vertex(resta).x, this->get_vertex(resta).y, this->get_vertex(resta).z);
                glTexCoord2f(0,partes_fin);
                glVertex3f(this->get_vertex(resta+1).x, this->get_vertex(resta+1).y, this->get_vertex(resta+1).z);
                glTexCoord2f(divisiones,partes_fin);
                glVertex3f(this->get_vertex(tama-1).x, this->get_vertex(tama-1).y, this->get_vertex(tama-1).z);
            }
        }

    glEnd();

    glPushMatrix();
    GLfloat ambient1[4] = {1,1,1,1};
    GLfloat specular1[4] = {1,1,1,1};

    GLfloat material1[4] = {1,1,1,1};
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material1);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
        glMaterialf(GL_FRONT, GL_SHININESS, 4);
    this->draw_solid_gouroud(0,alpha,beta,0,0);
    glPopMatrix();
}


void O3d::transformar(float x, float y, float z, float xt, float yt, float zt){
    glTranslatef(x,y,z);
    glScalef(xt,yt,zt);
}
