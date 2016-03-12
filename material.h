/*
 * $Id: material.h 79 2006-11-24 01:14:50Z julio $
 */

#ifndef __MATERIAL_H
#define __MATERIAL_H

#include <string.h>
#include <GL/glut.h>

typedef struct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat emission[4];
  GLfloat shininess[1];
} material_t;

void setMaterial(material_t *m);
void assignMaterial(const material_t *m,material_t *n);
#endif
