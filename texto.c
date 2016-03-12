#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <GL/glut.h>

// TODO: el glPrint de nehe es mas avanzado
static GLuint base10;
static GLuint base24;


void initTexto(){
  int i;
  base10 = glGenLists(256);
  base24 = glGenLists(256);
  for (i = 0; i< 256; ++i){
    glNewList(base10 + i, GL_COMPILE);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, i);
    glEndList();

    glNewList(base24 + i, GL_COMPILE);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);
    glEndList();
  }
}


void glPrint10(int x, int y, const char *fmt, ...){
  char text[256];
  va_list ap;

  if (fmt == NULL)
    return;

  va_start(ap, fmt);
  vsprintf(text, fmt, ap);
  va_end(ap);
  
  glListBase(base10);
  glRasterPos2i(x,y);
  glCallLists(strlen(text), GL_BYTE, text);
}

void glPrint24(int x, int y, const char *fmt, ...){
  char text[256];
  va_list ap;

  if (fmt == NULL)
    return;

  va_start(ap, fmt);
  vsprintf(text, fmt, ap);
  va_end(ap);
  
  glListBase(base24);
  glRasterPos2i(x,y);
  glCallLists(strlen(text), GL_BYTE, text);
}
