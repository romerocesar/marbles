/*
 * $Id: model.c 89 2006-11-30 12:51:22Z cesar $
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "model.h"
#include "input.h"

extern model_t model;

void recalc_bezier(){
    model.still = 0;

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 11, 0, 1, 33, 11, &model.puntos[0][0][0]);
    glMapGrid2f(model.gridsize, 0.0, 1.0, model.gridsize, 0.0, 1.0);

    model.objy = compute(model.objx, model.objz) + 0.1;

}

float dist3d(float x1, float x2, float y1, float y2, float z1, float z2){
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1));
}

void init_model(){
    model.over = 0;
    model.editando = 1;
    model.editx = 0;
    model.edity = 0;

    model.camx = 0;
    model.camy = 45;
    model.camz = 20;
    model.camaperture = 45;
    
    model.gridsize = 40;

    model.wireframe =0;
    model.ejes = 0;
    reset_puntos();

    model.turn = 0;

    model.players=4;


    model.objx = rand_float(-5, 5);
    model.objz = rand_float(-5, 5);
    model.objy = compute(model.objx, model.objz);


    model.ronda = 0;
    
    init_bolas();
}

float rand_float(float min, float max){
    return min + (max-min)* ((float)random()/RAND_MAX);
}


void next_turn(){
    model.turn = (model.turn + 1) % 4;
    model.wait_still = 1;
    if (model.turn == 0)
        model.ronda++;

    if (model.ronda >= 2)
        model.over = 1;
}

void update_camera(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(model.camaperture, (GLfloat)(model.winw-150)/model.winh, 1.0, 10000.0);

    glMatrixMode(GL_MODELVIEW);
}

void reset_puntos(){
    int z,x;
    for (z=0; z<11; z++){
        for (x=0; x<11; x++){
            model.puntos[x][z][0] = x-5;
            model.puntos[x][z][1] = 0;
            model.puntos[x][z][2] = z-5;
        }
    }
    recalc_bezier();
}

void mover_punto(int x, int y, int n){
    model.puntos[x][y][1] += n;
    recalc_bezier();
}

int altura_punto(int x, int y){
    return model.puntos[x][y][1];
}

void set_editar(int b){
    model.editando = b;
    if (model.editando){
        printf("editando\n");
        glutKeyboardFunc(keyboardEdit);
        glutSpecialFunc(specialEdit);
        glutMouseFunc(mouseEdit);
        glutMotionFunc(mouseMotionEdit);       
        recalc_bezier();
    } else {
        printf("jugando\n");
        glutKeyboardFunc(keyboardPlay);
        glutSpecialFunc(specialPlay);
        glutMouseFunc(0);
        glutMotionFunc(0);
        recalc_bezier();
    }
    
}


/* Polinomio de bernstein de grado 11 */
/* i - punto de control [0-10] */
/* u - coordenada del punto */
float B(int i, float u)
{
  // comb11[i] combinacion de 11 en i
  //int comb11[]={1,11,55,165,330,462,462,330,165,55,11,1};
  int comb10[]={1,10,45,120,210,252,210,120,45,10,1};
  return comb10[i]*pow(u,i)*pow(1-u,10-i);
}

/* Computa el valor del spline de bezier  */
/* x - coordenada x */
/* z - coordenada z */
/* Devuelve el valor del spline en el sistema de coordenadas del
   mundo */
float compute(float x,float z)
{
  //TODO:que no use todos los puntos de control sino lo minimo
  //necesario
  int a,b,n,m,ix,iz;
  ix=(int)x;iz=(int)z;
  a=ix-2;n=ix+2;
  b=iz-2;m=iz+2;
  float u=(x-XMIN)/(XMAX-XMIN);
  float v=(z-ZMIN)/(ZMAX-ZMIN);
  int i,j;
  float ans=0;
  for(i=0;i<11;i++)
    for(j=0;j<11;j++)
      ans+=B(i,u)*B(j,v)*model.puntos[i][j][1];

  return ans;
}

void shoot()
{
  model.marble[model.turn].vz=model.marble[model.turn].mag*cos(model.marble[model.turn].theta)*.5;
  model.marble[model.turn].vx=model.marble[model.turn].mag*sin(model.marble[model.turn].theta)*.5;
  model.still = 0;
}

