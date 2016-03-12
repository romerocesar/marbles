/*
 * $Id: material.c 79 2006-11-24 01:14:50Z julio $
 */

#include "material.h"

void setMaterial(material_t *m){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, m->shininess);
}

void assignMaterial(const material_t *m,material_t *n)
{
  memcpy(n,m,sizeof(material_t));
}
