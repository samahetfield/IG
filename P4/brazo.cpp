#include "brazo.h"
#include "base.h"
#include "o3d.h"
#include "cilindro.h"
#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include <GL/glut.h>
#include <math.h>
#include "beethoven.h"

Brazo::Brazo()
{

}

Brazo::Brazo(Esfera e, Cilindro c1, Beethoven be ){
    esfera1 = e;
    esfera2 = e;
    barra_sup = c1;
    barra_inf = c1;
    beethoven = be;
}

void Brazo::dibujar(float angulo, unsigned int modo,float aumentar){

    switch (modo) {
    case 1:
        glPushMatrix();
            glTranslatef(0,5.5,0);
            glRotatef(angulo,0,1,0);
            glRotatef(30+(aumentar*20),0,0,1);

            glPushMatrix();
            barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
            barra_sup.draw_points();
            glPopMatrix();


            glPushMatrix();
            esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
            esfera2.draw_points();
            glPopMatrix();

            glPushMatrix();
            beethoven.transformar(0.05,0.05,0.05,0.3,-1.5,0);
            glRotatef(180,1,0,0);
            glRotatef(270,0,0,1);
            beethoven.draw_points();
            glPopMatrix();

       glPopMatrix();

       glPushMatrix();
           glTranslatef(0,5.5,0);
           glRotatef(angulo,0,1,0);
           glRotatef(330-(aumentar*20),0,0,1);

           glPushMatrix();
           barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
           barra_sup.draw_points();
           glPopMatrix();


           glPushMatrix();
           esfera2 = esfera1;
           esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
           esfera2.draw_points();
           glPopMatrix();

           glPushMatrix();
           beethoven.transformar(0.05,0.05,0.05,-0.3,-1.5,0);
           glRotatef(90,0,0,1);
           beethoven.draw_points();
           glPopMatrix();

      glPopMatrix();

      glPushMatrix();
          glTranslatef(0,5.5,0);
          glRotatef(angulo,0,1,0);
          glRotatef(30+(aumentar*20),1,0,0);

          glPushMatrix();
          barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
          barra_sup.draw_points();
          glPopMatrix();


          glPushMatrix();
          esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
          esfera2.draw_points();
          glPopMatrix();

          glPushMatrix();
          beethoven.transformar(0.05,0.05,0.05,0,-1.5,-0.3);
          glRotatef(90,0,0,1);
          glRotatef(270,1,0,0);
          beethoven.draw_points();
          glPopMatrix();

     glPopMatrix();

     glPushMatrix();
         glTranslatef(0,5.5,0);
         glRotatef(angulo,0,1,0);
         glRotatef(330-(aumentar*20),1,0,0);

         glPushMatrix();
         barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
         barra_sup.draw_points();
         glPopMatrix();


         glPushMatrix();
         esfera2 = esfera1;
         esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
         esfera2.draw_points();
         glPopMatrix();

         glPushMatrix();
         beethoven.transformar(0.05,0.05,0.05,0,-1.5,0.3);
         glRotatef(90,0,0,1);
         glRotatef(90,1,0,0);
         beethoven.draw_points();
         glPopMatrix();

    glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_points();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_points();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),1,0,0);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_points();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),1,0,0);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_points();
            glPopMatrix();
        break;
    case 2:
        glPushMatrix();
            glTranslatef(0,5.5,0);
            glRotatef(angulo,0,1,0);
            glRotatef(30+(aumentar*20),0,0,1);

            glPushMatrix();
            barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
            barra_sup.draw_edges();
            glPopMatrix();


            glPushMatrix();
            esfera2 = esfera1;
            esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
            esfera2.draw_edges();
            glPopMatrix();

            glPushMatrix();
            beethoven.transformar(0.05,0.05,0.05,0.3,-1.5,0);
            glRotatef(180,1,0,0);
            glRotatef(270,0,0,1);
            beethoven.draw_edges();
            glPopMatrix();

       glPopMatrix();

       glPushMatrix();
           glTranslatef(0,5.5,0);
           glRotatef(angulo,0,1,0);
           glRotatef(330-(aumentar*20),0,0,1);

           glPushMatrix();
           barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
           barra_sup.draw_edges();
           glPopMatrix();


           glPushMatrix();
           esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
           esfera2.draw_edges();
           glPopMatrix();

           glPushMatrix();
           beethoven.transformar(0.05,0.05,0.05,-0.3,-1.5,0);
           glRotatef(90,0,0,1);
           beethoven.draw_edges();
           glPopMatrix();

      glPopMatrix();

      glPushMatrix();
          glTranslatef(0,5.5,0);
          glRotatef(angulo,0,1,0);
          glRotatef(30+(aumentar*20),1,0,0);

          glPushMatrix();
          barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
          barra_sup.draw_edges();
          glPopMatrix();


          glPushMatrix();
          esfera2 = esfera1;
          esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
          esfera2.draw_edges();
          glPopMatrix();

          glPushMatrix();
          beethoven.transformar(0.05,0.05,0.05,0,-1.5,-0.3);
          glRotatef(90,0,0,1);
          glRotatef(270,1,0,0);
          beethoven.draw_edges();
          glPopMatrix();

     glPopMatrix();

     glPushMatrix();
         glTranslatef(0,5.5,0);
         glRotatef(angulo,0,1,0);
         glRotatef(330-(aumentar*20),1,0,0);

         glPushMatrix();
         barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
         barra_sup.draw_edges();
         glPopMatrix();


         glPushMatrix();
         esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
         esfera2.draw_edges();
         glPopMatrix();

         glPushMatrix();
         beethoven.transformar(0.05,0.05,0.05,0,-1.5,0.3);
         glRotatef(90,0,0,1);
         glRotatef(90,1,0,0);
         beethoven.draw_edges();
         glPopMatrix();

    glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_edges();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_edges();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),1,0,0);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_edges();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),1,0,0);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_edges();
            glPopMatrix();

        break;
    case 3:
        glPushMatrix();
            glTranslatef(0,5.5,0);
            glRotatef(angulo,0,1,0);
            glRotatef(30+(aumentar*20),0,0,1);

            glPushMatrix();
            barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
            barra_sup.draw_solid();
            glPopMatrix();


            glPushMatrix();
            esfera2 = esfera1;
            esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
            esfera2.draw_solid();
            glPopMatrix();

            glPushMatrix();
            beethoven.transformar(0.05,0.05,0.05,0.3,-1.5,0);
            glRotatef(180,1,0,0);
            glRotatef(270,0,0,1);
            beethoven.draw_solid();
            glPopMatrix();

       glPopMatrix();

       glPushMatrix();
           glTranslatef(0,5.5,0);
           glRotatef(angulo,0,1,0);
           glRotatef(330-(aumentar*20),0,0,1);

           glPushMatrix();
           barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
           barra_sup.draw_solid();
           glPopMatrix();


           glPushMatrix();
           esfera2 = esfera1;
           esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
           esfera2.draw_solid();
           glPopMatrix();

           glPushMatrix();
           beethoven.transformar(0.05,0.05,0.05,-0.3,-1.5,0);
           glRotatef(90,0,0,1);
           beethoven.draw_solid();
           glPopMatrix();

      glPopMatrix();

      glPushMatrix();
          glTranslatef(0,5.5,0);
          glRotatef(angulo,0,1,0);
          glRotatef(30+(aumentar*20),1,0,0);

          glPushMatrix();
          barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
          barra_sup.draw_solid();
          glPopMatrix();


          glPushMatrix();
          esfera2 = esfera1;
          esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
          esfera2.draw_solid();
          glPopMatrix();

          glPushMatrix();
          beethoven.transformar(0.05,0.05,0.05,0,-1.5,-0.3);
          glRotatef(90,0,0,1);
          glRotatef(270,1,0,0);
          beethoven.draw_solid();
          glPopMatrix();

     glPopMatrix();

     glPushMatrix();
         glTranslatef(0,5.5,0);
         glRotatef(angulo,0,1,0);
         glRotatef(330-(aumentar*20),1,0,0);

         glPushMatrix();
         barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
         barra_sup.draw_solid();
         glPopMatrix();


         glPushMatrix();
         esfera2 = esfera1;
         esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
         esfera2.draw_solid();
         glPopMatrix();

         glPushMatrix();
         beethoven.transformar(0.05,0.05,0.05,0,-1.5,0.3);
         glRotatef(90,0,0,1);
         glRotatef(90,1,0,0);
         beethoven.draw_solid();
         glPopMatrix();

    glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_solid();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_solid();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_solid();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_solid();
            glPopMatrix();
        break;
    case 4:
        glPushMatrix();
            glTranslatef(0,5.5,0);
            glRotatef(angulo,0,1,0);
            glRotatef(30+(aumentar*20),0,0,1);

            glPushMatrix();
            barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
            barra_sup.draw_chess();
            glPopMatrix();


            glPushMatrix();
            esfera2 = esfera1;
            esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
            esfera2.draw_chess();
            glPopMatrix();

            glPushMatrix();
            beethoven.transformar(0.05,0.05,0.05,0.3,-1.5,0);
            glRotatef(180,1,0,0);
            glRotatef(270,0,0,1);
            beethoven.draw_chess();
            glPopMatrix();

       glPopMatrix();

       glPushMatrix();
           glTranslatef(0,5.5,0);
           glRotatef(angulo,0,1,0);
           glRotatef(330-(aumentar*20),0,0,1);

           glPushMatrix();
           barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
           barra_sup.draw_chess();
           glPopMatrix();


           glPushMatrix();
           esfera2 = esfera1;
           esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
           esfera2.draw_chess();
           glPopMatrix();

           glPushMatrix();
           beethoven.transformar(0.05,0.05,0.05,-0.3,-1.5,0);
           glRotatef(90,0,0,1);
           beethoven.draw_chess();
           glPopMatrix();

      glPopMatrix();

      glPushMatrix();
          glTranslatef(0,5.5,0);
          glRotatef(angulo,0,1,0);
          glRotatef(30+(aumentar*20),1,0,0);

          glPushMatrix();
          barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
          barra_sup.draw_chess();
          glPopMatrix();


          glPushMatrix();
          esfera2 = esfera1;
          esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
          esfera2.draw_chess();
          glPopMatrix();

          glPushMatrix();
          beethoven.transformar(0.05,0.05,0.05,0,-1.5,-0.3);
          glRotatef(90,0,0,1);
          glRotatef(270,1,0,0);
          beethoven.draw_chess();
          glPopMatrix();

     glPopMatrix();

     glPushMatrix();
         glTranslatef(0,5.5,0);
         glRotatef(angulo,0,1,0);
         glRotatef(330-(aumentar*20),1,0,0);

         glPushMatrix();
         barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
         barra_sup.draw_chess();
         glPopMatrix();


         glPushMatrix();
         esfera2 = esfera1;
         esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
         esfera2.draw_chess();
         glPopMatrix();

         glPushMatrix();
         beethoven.transformar(0.05,0.05,0.05,0,-1.5,0.3);
         glRotatef(90,0,0,1);
         glRotatef(90,1,0,0);
         beethoven.draw_chess();
         glPopMatrix();

    glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_chess();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_chess();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),1,0,0);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_chess();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),1,0,0);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_chess();
            glPopMatrix();
        break;
    case 5:
        glPushMatrix();
            glTranslatef(0,5.5,0);
            glRotatef(angulo,0,1,0);
            glRotatef(30+(aumentar*20),0,0,1);

            glPushMatrix();
            barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
            barra_sup.draw_all();
            glPopMatrix();


            glPushMatrix();
            esfera2 = esfera1;
            esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
            esfera2.draw_all();
            glPopMatrix();

            glPushMatrix();
            beethoven.transformar(0.05,0.05,0.05,0.3,-1.5,0);
            glRotatef(180,1,0,0);
            glRotatef(270,0,0,1);
            beethoven.draw_all();
            glPopMatrix();

       glPopMatrix();

       glPushMatrix();
           glTranslatef(0,5.5,0);
           glRotatef(angulo,0,1,0);
           glRotatef(330-(aumentar*20),0,0,1);

           glPushMatrix();
           barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
           barra_sup.draw_all();
           glPopMatrix();


           glPushMatrix();
           esfera2 = esfera1;
           esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
           esfera2.draw_all();
           glPopMatrix();

           glPushMatrix();
           beethoven.transformar(0.05,0.05,0.05,-0.3,-1.5,0);
           glRotatef(90,0,0,1);
           beethoven.draw_all();
           glPopMatrix();

      glPopMatrix();

      glPushMatrix();
          glTranslatef(0,5.5,0);
          glRotatef(angulo,0,1,0);
          glRotatef(30+(aumentar*20),1,0,0);

          glPushMatrix();
          barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
          barra_sup.draw_all();
          glPopMatrix();


          glPushMatrix();
          esfera2 = esfera1;
          esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
          esfera2.draw_all();
          glPopMatrix();

          glPushMatrix();
          beethoven.transformar(0.05,0.05,0.05,0,-1.5,-0.3);
          glRotatef(90,0,0,1);
          glRotatef(270,1,0,0);
          beethoven.draw_all();
          glPopMatrix();

     glPopMatrix();

     glPushMatrix();
         glTranslatef(0,5.5,0);
         glRotatef(angulo,0,1,0);
         glRotatef(330-(aumentar*20),1,0,0);

         glPushMatrix();
         barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
         barra_sup.draw_all();
         glPopMatrix();


         glPushMatrix();
         esfera2 = esfera1;
         esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
         esfera2.draw_all();
         glPopMatrix();

         glPushMatrix();
         beethoven.transformar(0.05,0.05,0.05,0,-1.5,0.3);
         glRotatef(90,0,0,1);
         glRotatef(90,1,0,0);
         beethoven.draw_all();
         glPopMatrix();

    glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_all();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_all();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),1,0,0);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_all();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),1,0,0);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_all();
            glPopMatrix();
        break;
    default:
        glPushMatrix();
            glTranslatef(0,5.5,0);
            glRotatef(angulo,0,1,0);
            glRotatef(30+(aumentar*20),0,0,1);

            glPushMatrix();
            barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
            barra_sup.draw_chess();
            glPopMatrix();


            glPushMatrix();
            esfera2 = esfera1;
            esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
            esfera2.draw_chess();
            glPopMatrix();

            glPushMatrix();
            beethoven.transformar(0.05,0.05,0.05,0.3,-1.5,0);
            glRotatef(180,1,0,0);
            glRotatef(270,0,0,1);
            beethoven.draw_chess();
            glPopMatrix();

       glPopMatrix();

       glPushMatrix();
           glTranslatef(0,5.5,0);
           glRotatef(angulo,0,1,0);
           glRotatef(330-(aumentar*20),0,0,1);

           glPushMatrix();
           barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
           barra_sup.draw_chess();
           glPopMatrix();


           glPushMatrix();
           esfera2 = esfera1;
           esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
           esfera2.draw_chess();
           glPopMatrix();

           glPushMatrix();
           beethoven.transformar(0.05,0.05,0.05,-0.3,-1.5,0);
           glRotatef(90,0,0,1);
           beethoven.draw_chess();
           glPopMatrix();

      glPopMatrix();

      glPushMatrix();
          glTranslatef(0,5.5,0);
          glRotatef(angulo,0,1,0);
          glRotatef(30+(aumentar*20),1,0,0);

          glPushMatrix();
          barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
          barra_sup.draw_chess();
          glPopMatrix();


          glPushMatrix();
          esfera2 = esfera1;
          esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
          esfera2.draw_chess();
          glPopMatrix();

          glPushMatrix();
          beethoven.transformar(0.05,0.05,0.05,0,-1.5,-0.3);
          glRotatef(90,0,0,1);
          glRotatef(270,1,0,0);
          beethoven.draw_chess();
          glPopMatrix();

     glPopMatrix();

     glPushMatrix();
         glTranslatef(0,5.5,0);
         glRotatef(angulo,0,1,0);
         glRotatef(330-(aumentar*20),1,0,0);

         glPushMatrix();
         barra_sup.transformar(0.1, 3,0.1,0,-1.5,0);
         barra_sup.draw_chess();
         glPopMatrix();


         glPushMatrix();
         esfera2 = esfera1;
         esfera2.transformar(0.6,0.6,0.6,0,-3.5,0);
         esfera2.draw_chess();
         glPopMatrix();

         glPushMatrix();
         beethoven.transformar(0.05,0.05,0.05,0,-1.5,0.3);
         glRotatef(90,0,0,1);
         glRotatef(90,1,0,0);
         beethoven.draw_chess();
         glPopMatrix();

    glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_chess();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),0,0,1);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_chess();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(145-(aumentar*20),1,0,0);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_chess();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0,2.5+aumentar,0);
            glRotatef(angulo,0,1,0);
            glRotatef(215+(aumentar*20),1,0,0);
            barra_inf.transformar(0.1,1.6,0.1,0,-0.85,0);
            barra_inf.draw_chess();
            glPopMatrix();
        break;
    }

}
