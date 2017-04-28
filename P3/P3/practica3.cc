//**************************************************************************
// Práctica 1
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

// tamaño de los ejes
const int AXIS_SIZE=5000;

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
vector<_vertex3ui> edges_cube={{0,1,2},{2,0,3},{2,3,0},{5,6,2},{2,4,3},{3,7,0},{0,6,1},{7,4,5},{5,7,6},{5,2,4},{3,4,7},{0,6,7},{1,2,6}};

O3d cube(vertex_cube, edges_cube);

// Creación de los vectores de vertices y aristas del tetraedro
vector<_vertex3f> vertex_tetra= {{-0.5,-0.25,-0.5},{0.5,-0.25,-0.5},{0,-0.25,0.25},{0,0.5,0}};
vector<_vertex3ui> edges_tetra={{1,0,2},{0,3,2},{0,3,1},{2,1,3}};

O3d tetrahedro(vertex_tetra, edges_tetra);

_file_ply file;
vector<float> Vertices;
vector<int> faces;

int numero_perfiles = 20;
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
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
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
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{

    switch (objeto) {
    case 0:
        switch (modo) {

        default :
            cube.draw_points();
            break;
        case 2:
            cube.draw_edges();
            break;
        case 1:
            cube.draw_points();
            break;
        case 3:
            cube.draw_solid();
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
            tetrahedro.draw_solid();
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
            switch (modo) {
            default :
                cilindro.draw_points();
                break;
            case 2:
                cilindro.draw_edges();
                break;
            case 1:
                cilindro.draw_points();
                break;
            case 3:
                cilindro.draw_solid();
                break;
            case 4:
                cilindro.draw_chess();
                break;
            case 5:
                cilindro.draw_all();
                break;
            }
            break;
        case 2:
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
                vaso.draw_solid();
                break;
            case 4:
                vaso.draw_chess();
                break;
            case 5:
                vaso.draw_all();
                break;
            }
            break;
        case 3:
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
                vaso_inv.draw_solid();
                break;
            case 4:
                vaso_inv.draw_chess();
                break;
            case 5:
                vaso_inv.draw_all();
                break;
            }
            break;
        case 4:
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
                cono.draw_solid();
                break;
            case 4:
                cono.draw_chess();
                break;
            case 5:
                cono.draw_all();
                break;
            }
            break;
        case 5:
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
            case 3:
                tubo.draw_solid();
                break;
            case 4:
                tubo.draw_chess();
                break;
            case 5:
                tubo.draw_all();
                break;
            }
            break;
        case 6:
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
                esfera.draw_solid();
                break;
            case 4:
                esfera.draw_chess();
                break;
            case 5:
                esfera.draw_all();
                break;
            }
            break;
        }
        break;

        case 5:
                r_w.dibujar(angulo,modo,aumentar);
                break;
    }

    glFlush();

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
        draw_objects();
        break;
    case '2':
        o_ply=2;
        draw_objects();
        break;
    case '3':
        o_ply=3;
        draw_objects();
        break;
    case '4':
        o_ply=4;
        draw_objects();
        break;
    case '5':
        o_ply=5;
        draw_objects();
        break;
    case '6':
        o_ply=6;
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
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
    case GLUT_KEY_F1: objeto=0; draw_objects();break;
    case GLUT_KEY_F2: objeto=1; draw_objects();break;
    case GLUT_KEY_F3: objeto=3; draw_objects();break;
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

    file.open("../modelos_ply/cilindro.ply");

    file.read(Vertices, faces);

    cilindro.readPLY(Vertices, faces);

    file.close();



    file.open("../modelos_ply/vaso.ply");

    file.read(Vertices, faces);

    vaso.readPLY(Vertices, faces);

    file.close();


    file.open("../modelos_ply/vaso_invertido.ply");

    file.read(Vertices, faces);

    vaso_inv.readPLY(Vertices, faces);

    file.close();


    file.open("../modelos_ply/cono.ply");

    file.read(Vertices, faces);

    cono.readPLY(Vertices, faces);

    file.close();


    file.open("../modelos_ply/tubo.ply");

    file.read(Vertices, faces);

    tubo.readPLY(Vertices, faces);

    file.close();


    file.open("../modelos_ply/esfera.ply");

    file.read(Vertices, faces);

    esf.readPLY(Vertices, faces);

    file.close();

    file.open("../modelos_ply/beethoven.ply");

    file.read(Vertices, faces);

    beto.readPLY(Vertices, faces);

    file.close();

    Beethoven beth(beto);
    beethoven = beth;

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
glutCreateWindow("Práctica 3");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
glutIdleFunc(func_idle);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();
// inicio del bucle de eventos
glutMainLoop();
return 0;
}
