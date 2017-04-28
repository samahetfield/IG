//**************************************************************************
// Práctica 4
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <iostream>
#include <GL/glut.h>
#include <ctype.h>
#include "vertex.h"
#include "file_ply_stl.h"
#include <math.h>
#include "object3d.h"
#include "o3d.h"
#include "esfera.h"
#include "base.h"
#include "cilindro.h"
#include "partesuperior.h"
#include "regulador_watt.h"
#include "brazo.h"
#include "beethoven.h"
#include "tablero.h"
#include <QImage>
#include <GL/glu.h>

// tamaño de los ejes
const int AXIS_SIZE=5000;
const int BUFFER_SIZE=512;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=1000,UI_window_height=1000;

// Creación de los vectores de vertices y aristas del cubo
vector<_vertex3f> vertex_cube= {{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5},{-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,-0.5,0.5},{-0.5,-0.5,0.5}};
vector<_vertex3ui> edges_cube={{0,1,2},{0,2,3},{5,6,2},{2,3,4},{3,0,7},{6,0,1},{7,4,5},{7,5,6},{5,2,4},{4,3,7},{0,6,7},{1,2,6}};

O3d cube(vertex_cube, edges_cube);

// Creación de los vectores de vertices y aristas del tetraedro
vector<_vertex3f> vertex_tetra= {{-0.5,-0.25,-0.5},{0.5,-0.25,-0.5},{0,-0.25,0.25},{0,0.5,0}};
vector<_vertex3ui> edges_tetra={{0,1,2},{3,0,2},{3,0,1},{2,1,3}};

O3d tetrahedro(vertex_tetra, edges_tetra);

_file_ply file;
vector<float> Vertices;
vector<int> faces;

int numero_perfiles = 50;
O3d cilindro, vaso, vaso_inv, cono, tubo, esf,beto;

Esfera esfera;
Cilindro zylinder;
Base base;
Brazo brazo;
ParteSuperior ps;
Regulador_Watt r_w;
Beethoven beethoven;



double angulo=0;
double var = 0.1;
double aumentar = 0;
bool fin=false;


unsigned int modo=-1;
unsigned int objeto=-1;
unsigned int o_ply=-1;


int tama = 5;
Tablero tablero(tama);
QImage Imagen;
QImage Imagen_mundo;
QImage Imagen_estrellas;
unsigned int imagen = 0;
//Variables iluminación

bool illuminated = false;
bool gouroud = false;
bool activate_material=false;
int material = 0;

float alpha = 0;
float beta =0;
float alpha2 = 0;
float beta2 = 0;


int mouse_x, mouse_y;
bool click_central = false;
vector<bool> pintado(9,false);
int proy=0;
float zoom_factor = 1.0;
bool sel_mode;
Beethoven beto1,beto2,beto3,beto4;
int r1=1,g1=0,b1=0,r2=1,g2=0,b2=0,r3=1,g3=0,b3=0,r4=1,g4=0,b4=0,r5=1,g5=0,b5=0, r6=1, g6=0, b6=0, r7=1,g7=0,b7=0, r8=1, g8=0, b8=0, r9=1, g9=0, b9=0;


//**************************************************************************
//
//***************************************************************************

void func_idle(){
    angulo += var;

   glutPostRedisplay();
}


void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
if(proy == 0)
    glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
else
    glOrtho(-Window_width*(zoom_factor),Window_width*(zoom_factor),-Window_height*(zoom_factor),Window_height*(zoom_factor),Front_plane,Back_plane);

}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}




//**************************************************************************
// Funcion que dibuja los objetos con nombres
//**************************************************************************

void draw_objects_with_names() {


    glMatrixMode(GL_MODELVIEW);
    glInitNames();
    glPushMatrix();
    glPushName(0);

    for(float i=0; i<4; i+=1){
        for(float j=0; j<4; j+=1){
            glPushMatrix();
            glLoadName(i+1);
            glTranslatef(-(j/2)*15, 0, (i/2)*20);
            beethoven.draw_all();
            glPopMatrix();
        }

    }
/*
    glLoadName(1);
    beethoven.draw_solid(r1,g1,b1);

  //  glPushMatrix();
    glTranslatef(10,0,0);
    glLoadName(2);
    beto.draw_solid(r2,g2,b2);
  //  glPopMatrix();

    //glPushMatrix();
    glTranslatef(-20,0,0);
    glLoadName(3);
    beto1.draw_solid(r3,g3,b3);
  //  glPopMatrix();

  //  glPushMatrix();
    glTranslatef(30,0,0);
    glLoadName(4);
    beto2.draw_solid(r4,g4,b4);
  //  glPopMatrix();

    //glPushMatrix();
    glTranslatef(-40,0,0);
    glLoadName(5);
    beto3.draw_solid(r5,g5,b5);

    glPopMatrix();
*/
    // Dejo vacia la pila de nombres
    // al terminar.
    glPopName();

    // Restablezco la matriz modelo.
    glPopMatrix();
    // Selecciono la matriz proyeccion
    glMatrixMode(GL_PROJECTION);
    // La restablezco.
    glPopMatrix();
    // Dejo la de matriz modelo.
    glMatrixMode(GL_MODELVIEW);

}

void draw_scene_with_names(void) {
    clear_window();
    change_projection();
    change_observer();
    draw_axis();
    draw_objects_with_names();
    glutSwapBuffers();
}



//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{

    switch (objeto) {
    case 0:
        if(activate_material){
            cube.change_material(material);
        }
        switch (modo) {
        default :
            if(!illuminated && !gouroud)
                cube.draw_points();
            break;
        case 2:
            cube.draw_edges();
            break;
        case 1:
            cube.draw_points();
            break;
        case 3:
            if(!illuminated && !gouroud)
                cube.draw_solid(1,0,0);
            else if(!gouroud && illuminated)
                cube.draw_solid_illuminated(material,alpha,beta,alpha2,beta2);
            else
                cube.draw_solid_gouroud(material,alpha,beta,alpha2,beta2);
            break;
        case 4:
            cube.draw_chess();
            break;
        case 5:
            cube.draw_all();
            break;
        }
        break;
    case 1:
        if(activate_material){
            tetrahedro.change_material(material);
        }
        switch (modo) {
        default :
            tetrahedro.draw_points();
            break;
        case 2:
            tetrahedro.draw_edges();
            break;
        case 1:
            tetrahedro.draw_points();
            break;
        case 3:
            if(!illuminated && !gouroud)
                tetrahedro.draw_solid(1,0,0);
            else if(!gouroud && illuminated)
                tetrahedro.draw_solid_illuminated(material,alpha,beta,alpha2,beta2);
            else
                tetrahedro.draw_solid_gouroud(material, alpha,beta,alpha2,beta2);
            break;
        case 4:
            tetrahedro.draw_chess();
            break;
        case 5:
            tetrahedro.draw_all();
            break;
        }
    case 3:
        switch (o_ply) {
        case 1:
            if(activate_material){
                zylinder.change_material(material);
            }
            switch (modo) {
            default :
                zylinder.draw_points();
                break;
            case 2:
                zylinder.draw_edges();
                break;
            case 1:
                zylinder.draw_points();
                break;
            case 3:
                if(!illuminated && !gouroud)
                    zylinder.draw_solid(1,0,0);
                if(illuminated)
                    zylinder.draw_solid_illuminated(material,alpha,beta,alpha2,beta2);
                if(gouroud)
                    zylinder.draw_solid_gouroud(material,alpha,beta,alpha2,beta2);

                break;
            case 4:
                zylinder.draw_chess();
                break;
            case 5:
                zylinder.draw_all();
                break;

            case 6:
                zylinder.draw_tex(numero_perfiles, alpha, beta);
            }
            break;
        case 2:
            if(activate_material){
                vaso.change_material(material);
            }
            switch (modo) {
            default :
                vaso.draw_points();
                break;
            case 2:
                vaso.draw_edges();
                break;
            case 1:
                vaso.draw_points();
                break;
            case 3:
                if(!illuminated && !gouroud)
                    vaso.draw_solid(1,0,0);
                else if(!gouroud && illuminated)
                    vaso.draw_solid_illuminated(material,alpha,beta,alpha2,beta2);
                else
                    vaso.draw_solid_gouroud(material,alpha,beta,alpha2,beta2);
                break;
            case 4:
                vaso.draw_chess();
                break;
            case 5:
                vaso.draw_all();
                break;
            case 6:
                vaso.draw_tex(numero_perfiles,alpha,beta);
                break;
            }
            break;
        case 3:
            if(activate_material){
                vaso_inv.change_material(material);
            }
            switch (modo) {
            default :
                vaso_inv.draw_points();
                break;
            case 2:
                vaso_inv.draw_edges();
                break;
            case 1:
                vaso_inv.draw_points();
                break;
            case 3:
                if(!illuminated && !gouroud)
                    vaso_inv.draw_solid(1,0,0);
                else if(!gouroud && illuminated)
                    vaso_inv.draw_solid_illuminated(material, alpha,beta,alpha2,beta2);
                else
                    vaso_inv.draw_solid_gouroud(material, alpha,beta,alpha2,beta2);
                break;
            case 4:
                vaso_inv.draw_chess();
                break;
            case 5:
                vaso_inv.draw_all();
                break;
            case 6:
                vaso_inv.draw_tex(numero_perfiles,alpha,beta);
                break;
            }
            break;
        case 4:
            if(activate_material){
                cono.change_material(material);
            }
            switch (modo) {
            default :
                cono.draw_points();
                break;
            case 2:
                cono.draw_edges();
                break;
            case 1:
                cono.draw_points();
                break;
            case 3:
                if(!illuminated && !gouroud)
                    cono.draw_solid(1,0,0);
                else if(!gouroud && illuminated)
                    cono.draw_solid_illuminated(material,alpha,beta,alpha2,beta2);
                else
                    cono.draw_solid_gouroud(material,alpha,beta,alpha2,beta2);
                break;
            case 4:
                cono.draw_chess();
                break;
            case 5:
                cono.draw_all();
                break;
            case 6:
                cono.draw_tex(numero_perfiles,alpha,beta);
                break;
            }
            break;
        case 5:
            if(activate_material){
                tubo.change_material(material);
            }
            switch (modo) {
            default :
                tubo.draw_points();
                break;
            case 2:
                tubo.draw_edges();
                break;
            case 1:
                tubo.draw_points();
                break;
            case 3:if(!illuminated && !gouroud)
                    tubo.draw_solid(1,0,0);
                else if(!gouroud && illuminated)
                    tubo.draw_solid_illuminated(material,alpha,beta,alpha2,beta2);
                else
                    tubo.draw_solid_gouroud(material,alpha,beta,alpha2,beta2);
                break;
            case 4:
                tubo.draw_chess();
                break;
            case 5:
                tubo.draw_all();
                break;
            case 6:
                tubo.draw_tex(numero_perfiles,alpha,beta);
                break;
            }
            break;
        case 6:
            if(activate_material){
                esfera.change_material(material);
            }
            switch (modo) {
            default :
                esfera.draw_points();
                break;
            case 2:
                esfera.draw_edges();
                break;
            case 1:
                esfera.draw_points();
                break;
            case 3:
                if(!illuminated && !gouroud)
                    esfera.draw_solid(1,0,0);
                if(illuminated && !gouroud)
                    esfera.draw_solid_illuminated(material,alpha,beta,alpha2,beta2);
                if(gouroud)
                    esfera.draw_solid_gouroud(material,alpha,beta,alpha2,beta2);
                break;
            case 4:
                esfera.draw_chess();
                break;
            case 5:
                esfera.draw_all();
                break;
            case 6:
                esfera.draw_tex(numero_perfiles, alpha, beta);
            }
            break;

        case 7:
            if(activate_material){
                beethoven.change_material(material);
            }
            switch (modo) {
            default :
                beethoven.draw_points();
                break;
            case 2:
                beethoven.draw_edges();
                break;
            case 1:
                beethoven.draw_points();
                break;
            case 3:
                if(!gouroud && !illuminated)
                    beethoven.draw_solid(1,0,0);
                if(illuminated && !gouroud)
                    beethoven.draw_solid_illuminated(material,alpha, beta);
                else
                    beethoven.draw_solid_gouroud(material,alpha,beta);
                break;
            case 4:
                beethoven.draw_chess();
                break;
            case 5:
                beethoven.draw_all();
                break;
            }
            break;

        }
        break;

        case 5:
            r_w.dibujar(angulo,modo,aumentar);
            break;
    case 4:
        switch (modo) {
        default :
            tablero.draw_points();
            break;
        case 2:
            tablero.draw_edges();
            break;
        case 1:
            tablero.draw_points();
            break;
        case 4:
            tablero.draw_chess();
            break;
        case 5:
            tablero.draw_all();
            break;
        case 6:
            tablero.draw_tex();
            break;
        }
        break;

    case 6:

    draw_scene_with_names();
   }

    glFlush();

}

int pick(unsigned int x, unsigned int y) {
    GLuint Hits, Selection_buffer[BUFFER_SIZE]; // Objetos seleccionados y Buffer de datos
    GLint Viewport[4]; // Volumen de visión

    glSelectBuffer(BUFFER_SIZE,Selection_buffer); // Crear buffer de datos
    glGetIntegerv(GL_VIEWPORT,Viewport); // Redefinir volumen de visión
    glRenderMode(GL_SELECT); // Cambiar al modo selección

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPickMatrix(x,Viewport[3]-y,1.0,1.0,Viewport);

   //glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane); // Fijar proyección

    draw_scene_with_names(); // Dibujar
    //glFlush();
    Hits = glRenderMode(GL_RENDER); // Guardar número de objetos seleccionados

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane); // Fijar proyección

    // Analizar resultados
    int encontrado = -1; // Resultado del elemento más cercano

    if(Hits>0) { // Hay algún objeto
        unsigned int i=0; // Contador del buffer
        float z, Zmin = INFINITY; // Valor minimo actual de z
        float i0,i1,i2,i3;

        for(unsigned int k=0; k<Hits; k++) { // Recorrer objetos seleccionados
            //i0 = Selection_buffer[i+0];
          //  i1 = Selection_buffer[i+1];
           // i2 = Selection_buffer[i+2];
          //  i3 = Selection_buffer[i+3];

            if(Selection_buffer[i]!=0) { // Hay nombres en la pila
                z = Selection_buffer[i+1]; // Valor de z min del objeto
                if(z<=Zmin) { // Si es menor que el valor actual mínimo de z
                    encontrado = Selection_buffer[i+3]; // Índice del elemento (solo un nivel jerárquico de nombres)
                    Zmin = z; // Actualizar Zmin

                }
            }
            i += Selection_buffer[i]+3; // Nos movemos al siguiente (N+Zmin+Zmax=3)+N
        }

        //glMatrixMode(GL_PROJECTION);
       // glLoadIdentity();
    }

    return encontrado;
}

//***************************************************************************
// Funciones llamadas cuando se produce un evento con el ratón
//
// el evento manda a la funcion:
// botón del raton
// estado del raton
// posicion x del raton
// posicion y del raton
//***************************************************************************

void click_raton(int boton, int estado, int x, int y) {
    int encontrado;
    switch(boton) {
        case GLUT_LEFT_BUTTON:
            if(estado == GLUT_DOWN) {
                click_central = false;
                encontrado = pick(x,y);
                switch (encontrado) {
                case 0:
                    break;
                case 1:
                    r5=0;
                    g5=1;
                    b5=0;
                    break;
                case 2:
                    r3=0;
                    g3=1;
                    b3=0;

                    break;
                case 3:
                    r1=0;
                    g1=1;
                    b1=0;

                    break;
                case 4:
                    r2=0;
                    g2=1;
                    b2=0;

                    break;
                case 5:
                    r4=0;
                    g4=1;
                    b4=0;

                    break;
                case 6:
                    r6=0;
                    g6=1;
                    b6=0;

                    break;
                case 7:
                    r7=0;
                    g7=1;
                    b7=0;

                    break;
                case 8:
                    r8=0;
                    g8=1;
                    b8=0;

                    break;
                case 9:
                    r9=0;
                    g9=1;
                    b9=0;

                    break;
                }

                glFlush();
                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if(estado == GLUT_DOWN) {
                click_central = true;
                mouse_x = x;
                mouse_y = y;
                glutPostRedisplay();
            }
            break;
        case 3:
            click_central = false;
            if(proy == 0)
                Observer_distance/=1.1;
            else
                zoom_factor -= 0.3;
            change_projection();
            glutPostRedisplay();
            break;
        case 4:
            click_central = false;
            if(proy == 0)
                Observer_distance*=1.1;
            else
                zoom_factor += 0.3;
            change_projection();
            glutPostRedisplay();
            break;
    }
}

void raton_movido(int x, int y) {
    if(click_central) {
        Observer_angle_x += (y - mouse_y);
        Observer_angle_y += (x - mouse_x);
        mouse_x = x;
        mouse_y = y;
        glutPostRedisplay();
    }
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}


//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{

Window_width = 0.5*Ancho1/1000;
Window_height = 0.5*Alto1/1000;

change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

// Modo 1--> dibuja puntos
// Modo 2--> dibuja aristas
// Modo 3--> dibuja solido
//Modo 4--> dibuja ajedrez
//Modo 5--> dibuja todo

    if(sel_mode)
        exit;
    switch (toupper(Tecla1)) {
    case 'Q':
        exit(0);
        break;
    case 'A':
        modo = 2;
        draw_objects();
        break;
    case 'P':
        modo = 1;
        draw_objects();
        break;
    case 'S':
        modo = 3;
        draw_objects();
        break;
    case 'C':
        modo = 4;
        draw_objects();
        break;
    case 'T':
        modo = 5;
        draw_objects();
       break;
    case '1':
        o_ply=1;
        modo = 0;
        draw_objects();
        break;
    case '2':
        o_ply=2;
        modo = 0;
        draw_objects();
        break;
    case '3':
        o_ply=3;
        modo = 0;
        draw_objects();
        break;
    case '4':
        o_ply=4;
        modo = 0;
        draw_objects();
        break;
    case '5':
        o_ply=5;
        modo = 0;
        draw_objects();
        break;
    case '6':
        o_ply=6;
        modo = 0;
        draw_objects();
        break;
    case '7':
        o_ply=7;
        draw_objects();
        break;
    case 'K':
        if(aumentar<=2){
            var += 0.5;
            aumentar += 0.05;
        }
        break;
    case 'L':
        if(var >= 0.3){
            var -= 0.5;
            aumentar -= 0.05;
        }
        else{
            var = 0;
            aumentar = 0;
        }
        break;

    case 'E':
        alpha += 2;
        break;

    case 'D':
        beta += 2;
        break ;

    case 'R':
        alpha2 += 2;
        break;

    case 'F':
        beta2 += 2;
        break;

    case 'M':
        glTexImage2D(GL_TEXTURE_2D,0,4,Imagen.width(),Imagen.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,Imagen.bits());
        modo = 6;
        draw_objects();
        break;
    case 'I':
        if(!illuminated)
            illuminated = true;
        else
            illuminated = false;
        gouroud = false; draw_objects();  break;
    case 'G':
        if(!gouroud)
            gouroud = true;
        else
            gouroud = false;

        illuminated=false; draw_objects(); break;

    case 'Z':
        material = 1;
        draw_objects();
        break;

    case 'X':
        material = 2;
        draw_objects();
        break;

    case '.':
        proy = 1;
        change_projection();
        break;

    case ',':
        proy = 0;
        change_projection();
        break;
    }

    glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
    case GLUT_KEY_UP:Observer_angle_x--; break;
    case GLUT_KEY_DOWN:Observer_angle_x++; break;
    case GLUT_KEY_PAGE_UP:
        if(proy==0)
            Observer_distance*=1.2;
        else
            zoom_factor+=0.3;
        change_projection(); break;
    case GLUT_KEY_PAGE_DOWN:
        if(proy == 0)
            Observer_distance/=1.2;
        else
            zoom_factor-=0.3;
        change_projection(); break;
    case GLUT_KEY_F1: objeto=0; draw_objects();break;
    case GLUT_KEY_F2: objeto=1; draw_objects();break;
    case GLUT_KEY_F3: objeto=3; draw_objects();break;
    case GLUT_KEY_F6: objeto = 4; draw_objects(); break;
    case GLUT_KEY_F10: objeto = 6; draw_objects(); break;
    case GLUT_KEY_F5:
        objeto = 5; draw_objects(); break;
    case GLUT_KEY_F4: objeto =3;
    switch (o_ply) {
    case 1:
       cilindro.createProfile(numero_perfiles);
        break;
    case 2:
       vaso.createProfile(numero_perfiles);
        break;
    case 3:
       vaso_inv.createProfile(numero_perfiles);
        break;
    case 4:
       cono.createProfile(numero_perfiles);
        break;
    case 5:
       tubo.createProfile(numero_perfiles);
        break;
     case 6:
        esfera.createProfile(numero_perfiles);
        break;
    }
    break;
}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=0.5;
Window_height=0.5;
Front_plane=1.0;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);

    file.open("/home/sergio/UGR/IG/P4-buena/modelos_ply/cilindro.ply");

    file.read(Vertices, faces);

    cilindro.readPLY(Vertices, faces);

    file.close();



    file.open("/home/sergio/UGR/IG/P4-buena/modelos_ply/vaso.ply");

    file.read(Vertices, faces);

    vaso.readPLY(Vertices, faces);

    file.close();


    file.open("/home/sergio/UGR/IG/P4-buena/modelos_ply/vaso_invertido.ply");

    file.read(Vertices, faces);

    vaso_inv.readPLY(Vertices, faces);

    file.close();


    file.open("/home/sergio/UGR/IG/P4-buena/modelos_ply/cono.ply");

    file.read(Vertices, faces);

    cono.readPLY(Vertices, faces);

    file.close();


    file.open("/home/sergio/UGR/IG/P4-buena/modelos_ply/tubo.ply");

    file.read(Vertices, faces);

    tubo.readPLY(Vertices, faces);

    file.close();


    file.open("/home/sergio/UGR/IG/P4-buena/modelos_ply/esfera.ply");

    file.read(Vertices, faces);

    esf.readPLY(Vertices, faces);

    file.close();

    file.open("/home/sergio/UGR/IG/P4-buena/modelos_ply/beethoven.ply");

    file.read(Vertices, faces);

    beto.readPLY(Vertices, faces);

    file.close();

    Beethoven beth(beto);
    beethoven = beth;
    beto1 = beethoven;
    beto2 = beethoven;
    beto3 = beethoven;
    beto4 = beethoven;

    Esfera esf2(esf);
    esfera = esf2;

    esfera.createProfile(numero_perfiles);

    cilindro.createProfile(numero_perfiles);

    Cilindro c(cilindro);
    zylinder = c;

    Base b(cube, zylinder);
    base = b;


    Brazo br(esfera, zylinder, beethoven);
    brazo = br;

    ParteSuperior part_s(brazo, zylinder ,base);
    ps = part_s;

    Regulador_Watt r(ps, base);
    r_w = r;

    // definicion de una imagen
    //QImage Imagen;

    // carga de una imagen
    if (Imagen.load("/home/sergio/UGR/IG/P4-buena/texturas/dia_8192.jpg")==false) cout << "Image not loaded" << endl;
    // reflejo vertical
    Imagen=Imagen.mirrored(false,true);
    //

}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Práctica 5");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
glutIdleFunc(func_idle);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);


glutMouseFunc( click_raton );
glutMotionFunc( raton_movido );
// funcion de inicialización
initialize();
// inicio del bucle de eventos
glutMainLoop();
return 0;
}
