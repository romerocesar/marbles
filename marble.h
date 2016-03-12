/*
 * $Id: marble.h 79 2006-11-24 01:14:50Z julio $
 */

#ifndef _marble_h
#define _marble_h

#include <GL/glut.h>
#include "material.h"

#define MARBLE_RADIO 0.2
#define EPSILON 0.0001

typedef struct{
  float x;
  float y;
  float z;
  float r;

  float vx;
  float vz;

  float nx;
  float ny;
  float nz;

  material_t material;

  GLUquadricObj *q;
  GLuint texture;

  GLfloat rotx;
  GLfloat rotz;

  GLfloat theta; // angulo con el que el usuario quiere disparar (en radianes)
  GLfloat mag; // magnitud del vector de fuerza resultante

} marble_t;


void init_bolas();
int marble_physics();

#endif
