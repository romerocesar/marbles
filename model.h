/*
 * $Id: model.h 85 2006-11-30 04:33:13Z julio $
 */

#ifndef __MODEL_H
#define __MODEL_H

#define XMAX 5
#define XMIN -5
#define ZMAX XMAX
#define ZMIN XMIN

#define UPDATE_MS 10

#include <GL/glut.h>
#include <math.h>
#include "marble.h"

typedef struct {
    
    int editando;
    int editx;
    int edity;

    int gridsize;

    // puntos de control
    GLfloat puntos[11][11][3];


    // angulo de la camara en x, y
    GLfloat camx, camy; 
    // distancia de la camara al centro
    GLfloat camz;
    GLfloat camaperture;

    int winw;
    int winh;

    int wireframe;

    float objx, objy, objz;
    int ronda;
    int over;

  int ejes;
  
  //maximo 4 jugadorese
  int players;
  int turn;
  marble_t marble[4];

    int still; // no hay metras moviendose
    int wait_still; // estamos esperando que las metras se detengan para empezar el proximo turno


} model_t;


void next_turn();

void recalc_bezier();
void init_model();

void mover_punto(int x, int y, int n);
int altura_punto(int x, int y);
void reset_puntos();

void update_camera();

void set_editar(int b);

float compute(float u, float v);

void shoot();

float dist3d(float x1, float x2, float y1, float y2, float z1, float z2);
float rand_float(float min, float max);

#endif
