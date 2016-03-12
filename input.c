/*
 * $Id: input.c 92 2006-11-30 13:46:52Z julio $
 */

#include <GL/glut.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "input.h"
#include "model.h"
#include "view.h"

extern model_t model;
static int mouseSelectedPoint;


void keyboard_common(unsigned char key, int x, int y){
    int repaint = 1;    
    
    if ( key == 'z'){        
        model.camz++;
    } 
    else if (key == 'Z'){
        model.camz--;
    }
    else if ( key == 'x'){
        model.camx++;
    } 
    else if (key == 'X'){
        model.camx--;
    }
    else if ( key == 'y'){
        model.camy++;
    } 
    else if (key == 'Y'){
        model.camy--;
    }
    else if (key == 'Y'){
        model.camy--;
    }
    else if (key == 'R'){
        model.gridsize++;
        recalc_bezier();
    }
    else if (key == 'r'){
        if (model.gridsize > 1)
            model.gridsize--;
        recalc_bezier();
    }
    else if (key == '+'){
        model.camaperture++;
        update_camera();
    }
    else if (key == '-'){
        model.camaperture--;
        update_camera();
    }
    else if (key == 'j'){
        model.ejes = !model.ejes;
    }
    else if (toupper(key) == 'W'){
        model.wireframe = !model.wireframe;
    }
    else if (toupper(key) == 'C'){
        model.camx = 0;
        model.camy = 45;
        model.camz = 20;
        update_camera();
    }
    else if (key == '\e'){
        exit(0);
    }
    else {
        repaint = 0;
    }

    if (repaint)
        glutPostRedisplay();
    
}

// callback del teclado cuando se esta editando
void keyboardEdit(unsigned char key, int x, int y){
    int repaint = 1;
    
    if (model.over)
        return;

    if ( toupper(key) == 'R'){
        reset_puntos();
    } 
    else if (toupper(key) == 'Q'){
        set_editar(0);
    }
    else {
        keyboard_common(key, x, y);
        repaint = 0;
    }

    if (repaint)
        glutPostRedisplay();
}

void specialEdit(int key, int x, int y){
    int repaint = 1;

    if (model.over)
        return;

    if (key == GLUT_KEY_UP){
        if (--model.edity < 0)
            model.edity = 10;
    } 
    else if (key == GLUT_KEY_DOWN){
        if (++model.edity > 10)
            model.edity = 0;
    }
    else if (key == GLUT_KEY_RIGHT){
        if (++model.editx > 10)
            model.editx = 0;
    }
    else if (key == GLUT_KEY_LEFT){
        if (--model.editx < 0)
            model.editx = 10;
    }
    else if (key == GLUT_KEY_PAGE_UP){
        mover_punto(model.editx, model.edity, 1);
    }
    else if (key == GLUT_KEY_PAGE_DOWN){
        mover_punto(model.editx, model.edity, -1);
    }
    else {
        repaint = 0;
    }
    
    if (repaint)
        glutPostRedisplay();
}

int seleccionarPunto(int x, int y){
    GLuint buffer[512];
    GLint viewport[4] = {0, 0, model.winw-150, model.winh} ;

    //glGetIntegerv(GL_VIEWPORT, viewport);
    //glViewport(0,0, model.winw-150, model.winh);

    glSelectBuffer(512, buffer);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(~0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix((GLdouble)x,
                  (GLdouble)(model.winh - y),
                  10.0, 10.0, viewport);

    gluPerspective(model.camaperture, (GLfloat)(model.winw-150)/model.winh, 1.0, 10000.0);


    glMatrixMode(GL_MODELVIEW);
    dibujar_puntos();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

    int hits = glRenderMode(GL_RENDER);
    if (hits){
        int loop;
        GLuint choose = buffer[3];
        GLuint depth = buffer[1];
        for (loop = 1; loop < hits; loop++){
            if (buffer[loop*4+1] < (GLuint)(depth)) {
                choose = buffer[loop*4+3];
                depth = buffer[loop*4+1];
            }
        }
        if (choose != 512)
            return choose;
    }
    return -1;
}

void mouseEdit(int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON) {
      if (state == GLUT_DOWN) {
          mouseSelectedPoint = seleccionarPunto(x, y);
          printf("seleccionado %d\n", mouseSelectedPoint);
          if ( mouseSelectedPoint != -1){
              model.edity = mouseSelectedPoint / 11;
              model.editx = mouseSelectedPoint % 11;
              glutPostRedisplay();
          }
      } else {
          mouseSelectedPoint = -1;
      }
  }
}

void mouseMotionEdit(int x, int y){
    // mover un punto
    GLdouble objx, objy, objz;
    GLint viewport[4];
    GLdouble projectionMatrix[16], modelMatrix[16];
    if (mouseSelectedPoint != -1){
        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);


        gluUnProject(x, model.winh - y, 0.95,
                     modelMatrix, projectionMatrix, viewport, 
                     &objx, &objy, &objz);

        model.puntos[model.editx][model.edity][1] = objy*5;

        recalc_bezier();
        //grid[selectedPoint * 3 + 1] = objy;
        glutPostRedisplay();        
    }
}

// callback del teclado cuando se esta sugando
void keyboardPlay(unsigned char key, int x, int y){
    int repaint = 1;

/*     if (model.over){ */
/*         if (key=='\e') */
/*             exit(0); */
/*         return; */
/*     } */

    if ( toupper(key) == 'E' && !model.over) {
        set_editar(1);
    } else if (key == ' ' && model.still && !model.over){
        shoot();
        next_turn();
    } else {
        keyboard_common(key, x, y);
        repaint = 0;
    }

    if (repaint)
        glutPostRedisplay();
}

void specialPlay(int key, int x, int y){
    int repaint = 1;

    if (model.over)        
        return;
    
    if (key == GLUT_KEY_UP && model.still && !model.over){
            model.marble[model.turn].mag += 0.25;        
    }
    else if (key == GLUT_KEY_DOWN && model.still && !model.over){
        model.marble[model.turn].mag -= 0.25;
    } 
    else if (key == GLUT_KEY_LEFT && model.still && !model.over){
        model.marble[model.turn].theta += 0.1 * (1/model.marble[model.turn].mag);
        if (model.marble[model.turn].theta > 2*M_PI)
            model.marble[model.turn].theta = model.marble[model.turn].theta - 2*M_PI;
    } 
    else if (key == GLUT_KEY_RIGHT && model.still && !model.over){
        model.marble[model.turn].theta -= 0.1 * (1/model.marble[model.turn].mag);
        if (model.marble[model.turn].theta < 0)
            model.marble[model.turn].theta =  model.marble[model.turn].theta + 2*M_PI;
    } 
    else {
        repaint = 0;
    }

    if (repaint)
        glutPostRedisplay();
}
