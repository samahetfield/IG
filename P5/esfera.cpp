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

    tama_ini = tama;

    //Con el siguiente bucle contamos cuantos puntos tiene el perfil fuera del eje Y
    for(int i=0; i<tama; i++){
        if(obj_rev.get_vertex(i).x != 0)
            fueraEje++;
    }

    fueraDelEje = fueraEje;

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
        obj_rev.addTriangle(_vertex3ui((last_added+1) ,indice+1,indice));

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

    faces_normals();
    vertex_normals();

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

    obj_rev.addTriangle(_vertex3ui(v1,v3,v2));
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

void Esfera::draw_solid(int r, int g, int b){
    obj_rev.draw_solid(r,g,b);
}

void Esfera::draw_solid_gouroud(int material,float alpha, float beta, float alpha2, float beta2){
    obj_rev.draw_solid_gouroud(material,alpha, beta,alpha2, beta2);
}

void Esfera::draw_solid_illuminated(int material,float alpha, float beta, float alpha2, float beta2){
    obj_rev.draw_solid_illuminated(material, alpha,beta,alpha2, beta2);
}

void Esfera::vertex_normals(){
    obj_rev.vertex_normals();
}

void Esfera::faces_normals(){
    obj_rev.faces_normals();
}

void Esfera::draw_tex(float num_perfiles, int alpha, int beta){
    glPushMatrix();


    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // parametros de aplicacion de la textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_TEXTURE_2D);

    glPopMatrix();

    glBegin(GL_TRIANGLES);

    float divisiones = 1.0/num_perfiles;
    int ite = 0;
    float inicio=0;
    int primero = 0;
    int resta = 0;
    bool prim = false;
        int tama = obj_rev.numVertex();
        int paso = 0;
        int step=0;


            float partes_ini = 1.0/tama_ini;
            float partes_fin = 1 - partes_ini;

            //Tapa superior


                step = 0;

                for(int j=0; step<(num_perfiles-1); j++){
                    if(obj_rev.get_vertex(j).x != 0){
                        if(!prim){
                            primero = tama_ini-1;
                            resta = tama_ini-fueraDelEje;
                        }
                        prim = true;

                        glTexCoord2f(1-(divisiones*(j-2)),partes_fin);
                        glVertex3f(obj_rev.get_vertex(ite+primero+((j-2)*fueraDelEje)).x, obj_rev.get_vertex(ite +primero+((j-2)*fueraDelEje)).y, obj_rev.get_vertex(ite +primero+ ((j-2)*fueraDelEje)).z);
                        glTexCoord2f(1-(divisiones*(j-2)+divisiones),partes_fin);
                        glVertex3f(obj_rev.get_vertex(ite +primero+fueraDelEje+((j-2)*fueraDelEje)).x, obj_rev.get_vertex(ite+primero+fueraDelEje+((j-2)*fueraDelEje)).y, obj_rev.get_vertex(ite+primero+fueraDelEje+((j-2)*fueraDelEje)).z);
                        glTexCoord2f(1-(divisiones*(j-2)), 1);
                        glVertex3f(obj_rev.get_vertex(0).x, obj_rev.get_vertex(0).y, obj_rev.get_vertex(0).z);

                        step++;

                    }
                }

                glTexCoord2f(divisiones,partes_fin);
                glVertex3f(obj_rev.get_vertex(tama-1).x, obj_rev.get_vertex(tama-1).y, obj_rev.get_vertex(tama-1).z);
                glTexCoord2f(0,partes_fin);
                glVertex3f(obj_rev.get_vertex(primero).x, obj_rev.get_vertex(primero).y, obj_rev.get_vertex(primero).z);
                glTexCoord2f(divisiones, 1);
                glVertex3f(obj_rev.get_vertex(0).x, obj_rev.get_vertex(0).y, obj_rev.get_vertex(0).z);


                //Tapa inferior
                step = 0;
                prim = false;
                for(int j=0; step<(num_perfiles-1); j++){
                    if(obj_rev.get_vertex(j).x != 0){
                        if(!prim){
                            primero =j;
                            resta = tama_ini-fueraDelEje;
                        }
                        prim = true;

                        glTexCoord2f(1-(divisiones*(j-resta)),partes_ini);
                        glVertex3f(obj_rev.get_vertex(ite+primero+((j-resta)*fueraDelEje)).x, obj_rev.get_vertex(ite +primero+((j-resta)*fueraDelEje)).y, obj_rev.get_vertex(ite +primero+ ((j-resta)*fueraDelEje)).z);
                        glTexCoord2f(1-(divisiones*(j-resta)+divisiones),partes_ini);
                        glVertex3f(obj_rev.get_vertex(ite +primero+fueraDelEje+((j-resta)*fueraDelEje)).x, obj_rev.get_vertex(ite+primero+fueraDelEje+((j-resta)*fueraDelEje)).y, obj_rev.get_vertex(ite+primero+fueraDelEje+((j-resta)*fueraDelEje)).z);
                        glTexCoord2f(1-(divisiones*(j-resta)), 0);
                        glVertex3f(obj_rev.get_vertex(primero-1).x, obj_rev.get_vertex(primero-1).y, obj_rev.get_vertex(primero-1).z);

                        step++;

                    }
                }

                glTexCoord2f(divisiones,partes_ini);
                glVertex3f(obj_rev.get_vertex(tama-fueraDelEje).x, obj_rev.get_vertex(tama-fueraDelEje).y, obj_rev.get_vertex(tama-fueraDelEje).z);
                glTexCoord2f(0,partes_ini);
                glVertex3f(obj_rev.get_vertex(primero).x, obj_rev.get_vertex(primero).y, obj_rev.get_vertex(primero).z);
                glTexCoord2f(divisiones, 0);
                glVertex3f(obj_rev.get_vertex(primero-1).x, obj_rev.get_vertex(primero-1).y, obj_rev.get_vertex(primero-1).z);




                // Parte central

          float div = (partes_fin-partes_ini)/47;
          partes_fin = partes_ini + div;
          float ini = partes_ini;
          int avance = 0;
          while(avance <= tama_ini-3){
            step = 0;
            prim = false;
            for(int j=0; step<(num_perfiles-1); j++){
                if(obj_rev.get_vertex(j).x != 0){
                    if(!prim){
                        primero =j + avance;
                        resta = tama_ini-fueraDelEje + avance;
                    }

                    prim = true;

                    if(divisiones*j >= inicio){
                            ite = 2*paso;
                            glTexCoord2f(1-(divisiones*(j+avance-resta)), partes_ini);
                            glVertex3f(obj_rev.get_vertex(ite+resta+((j+avance-resta)*(fueraDelEje))).x,obj_rev.get_vertex(ite+resta+((j+avance-resta)*(fueraDelEje))).y, obj_rev.get_vertex(ite+resta+((j+avance-resta)*(fueraDelEje))).z);
                            glTexCoord2f(1-(divisiones*(j+avance-resta)+divisiones),partes_ini);
                            glVertex3f(obj_rev.get_vertex(ite +resta+((j+avance-resta+1)*fueraDelEje)).x, obj_rev.get_vertex(ite +resta+((j+avance-resta+1)*fueraDelEje)).y, obj_rev.get_vertex(ite +resta+((j+avance-resta+1)*fueraDelEje)).z);
                            glTexCoord2f(1-(divisiones*(j+avance-resta)), partes_fin);
                            glVertex3f(obj_rev.get_vertex(ite+resta+1+((j+avance-resta)*fueraDelEje)).x, obj_rev.get_vertex(ite+resta+1+((j+avance-resta)*fueraDelEje)).y, obj_rev.get_vertex(ite+resta+1+((j+avance-resta)*fueraDelEje)).z);
                            glTexCoord2f(1-(divisiones*(j+avance-resta)+divisiones), partes_ini);
                            glVertex3f(obj_rev.get_vertex(ite+resta+((j+avance-resta+1)*fueraDelEje)).x, obj_rev.get_vertex(ite+resta+((j+avance-resta+1)*fueraDelEje)).y, obj_rev.get_vertex(ite+resta+((j+avance-resta+1)*fueraDelEje)).z);
                            glTexCoord2f(1-(divisiones*(j+avance-resta)+divisiones),partes_fin);
                            glVertex3f(obj_rev.get_vertex(ite+resta+1+((j+avance-resta+1)*fueraDelEje)).x, obj_rev.get_vertex(ite+resta+1+((j+avance-resta+1)*fueraDelEje)).y, obj_rev.get_vertex(ite+resta+1+((j+avance-resta+1)*fueraDelEje)).z);
                            glTexCoord2f(1-(divisiones*(j+avance-resta)), partes_fin);
                            glVertex3f(obj_rev.get_vertex(ite+resta+1+((j+avance-resta)*fueraDelEje)).x, obj_rev.get_vertex(ite+resta+1+((j+avance-resta)*fueraDelEje)).y,obj_rev.get_vertex(ite+resta+1+((j+avance-resta)*fueraDelEje)).z);


                    }
                    step++;
                }
             }

            //Ultima parte
                glTexCoord2f(divisiones,partes_ini);
                glVertex3f(obj_rev.get_vertex(tama-fueraDelEje+avance).x, obj_rev.get_vertex(tama-fueraDelEje+avance).y, obj_rev.get_vertex(tama-fueraDelEje+avance).z);
                glTexCoord2f(0,partes_ini);
                glVertex3f(obj_rev.get_vertex(resta).x, obj_rev.get_vertex(resta).y, obj_rev.get_vertex(resta).z);
                glTexCoord2f(divisiones, partes_fin);
                glVertex3f(obj_rev.get_vertex(tama-fueraDelEje+1+avance).x, obj_rev.get_vertex(tama-fueraDelEje+1+avance).y, obj_rev.get_vertex(tama-fueraDelEje+1+avance).z);
                glTexCoord2f(0, partes_ini);
                glVertex3f(obj_rev.get_vertex(resta).x, obj_rev.get_vertex(resta).y, obj_rev.get_vertex(resta).z);
                glTexCoord2f(0,partes_fin);
                glVertex3f(obj_rev.get_vertex(resta+1).x, obj_rev.get_vertex(resta+1).y, obj_rev.get_vertex(resta+1).z);
                glTexCoord2f(divisiones,partes_fin);
                glVertex3f(obj_rev.get_vertex(tama-fueraDelEje+1+avance).x, obj_rev.get_vertex(tama-fueraDelEje+1+avance).y, obj_rev.get_vertex(tama-fueraDelEje+1+avance).z);

                partes_fin += div;
                partes_ini += div;
                avance++;
        }


    glEnd();
/*
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
*/
}



void Esfera::transformar(float x, float y, float z, float xt, float yt, float zt){
    glTranslatef(xt,yt,zt);
    glScalef(x,y,z);

}
