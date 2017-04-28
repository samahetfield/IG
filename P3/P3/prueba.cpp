#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>

double rotacion = 0.5, x = 0, velocidad = 180;
float rojo, verde, azul;
double delta;
int tiempoActual, tiempoAnterior;

void reshape(int width, int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(double)width/(double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

/* Restamos el tiempo actual del tiempo pasado para
 * para saber cuanto tiempo transcurrió entre un frame y otro */

void calculaTiempo(){
    tiempoActual = glutGet(GLUT_ELAPSED_TIME);
    delta = (double)(tiempoActual - tiempoAnterior)/1000;
    tiempoAnterior = tiempoActual;
}

/* Se actualizan los valores de los atributos que
 * serán animados */
void animacionTiempo(double delta) {
    float deltaRojo = delta/3,
          deltaAzul = delta/2,
          deltaVerde = delta/4;

    azul = azul < 1.0f ? azul+deltaAzul:0.0f;
    rojo = rojo < 1.0f ? rojo+deltaRojo:0.0f;
    verde = rojo < 1.0f ? verde+deltaVerde:0.0f;


    rotacion += velocidad * delta;

    if(x > 5){
        x = -5;
    }
    else {
        x += 5 * delta;
    }
}



void animacionFrames(){
    azul =  azul < 1.0f  ? azul  + 0.05: 0.0f;
    rojo =  rojo < 1.0f  ? rojo  + 0.02: 0.0f;
    verde = verde < 1.0f ? verde + 0.01: 0.0f;

    rotacion += 0.5;
    if(x > 5){
        x = -5;
    }
    else {
        x += 0.02;
    }
}

void animar(){
    calculaTiempo();
    animacionTiempo(delta);
    //animacionFrames();
    glutPostRedisplay();

}

void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(rojo, azul, 0.0f, 1.0f);
    glColor3f(1.0f,0.0f,1.0f);
    /* Se guarda la matriz de transformación para no afectar
     * las siguientes primitivas dibujadas */
    glPushMatrix();
    glTranslatef(x, 0.0f,0.0f);
    glRotatef(rotacion, 0.0f,1.0f,0.0f);
    glutSolidTeapot(1.0f);
    /* Regresamos la matriz de transformación a su estado
     * anterior para volver a dibujar desde el origen */
    glPopMatrix();
    /* Se cambia al buffer con el nuevo contenido */
    glutSwapBuffers();
}

void teclas(unsigned char key, int x, int y){
    printf("%d\n", key);
    switch(key){
        /* Salir del programa */
        case 27:
            exit(0);
            break;
        /* Aumentar o disminuir velocidad de rotación */
        case 43:
            velocidad+=5;
            break;
        case 45:
            velocidad-=5;
            break;
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - Animacion test");

    glutReshapeFunc(reshape);
    glutIdleFunc(animar);
    glutKeyboardFunc(teclas);
    glutDisplayFunc(dibuja);

    glClearColor(0.3,0.3,0.3, 1.0);
    /* Luces y DEPTH_TEST para poder ver bien el modelo */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
      /* posición y orientación */
    gluLookAt(  0.0, 0.0, 10.0, /* eye point */
                0.0, 0.0, 0.0,  /* punto de referencia */
                0.0, 1.0, 0.0); /* vector que indica arriba, en este caso Y */
    tiempoActual = tiempoAnterior = 0;
    glutMainLoop();
    return 0;
}
