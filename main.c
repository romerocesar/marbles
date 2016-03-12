/*
 * $Id: main.c 86 2006-11-30 04:46:13Z julio $
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "model.h"
#include "view.h"
#include "marble.h"
#include "texto.h"

model_t model;

void reshape(int ww, int hh)
{
    //    glViewport(0,0, ww, hh);
    model.winw = ww;
    model.winh = hh;
    update_camera();

}


void luces(){
    static GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    static GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    static GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0  };
    static GLfloat position[] = { 10.0, 5.0, 2.0, 1.0 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}


void init(){
    initTexto();
    init_model();

/*     mover_punto(5,5, 20); */
/*     mover_punto(6,6, 20); */
/*     mover_punto(7,7, 20); */
/*     mover_punto(8,8, 20); */
/*     mover_punto(5,10, -20); */
/*     mover_punto(5,71, -20); */


    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    luces();
}

void actualizar()
{
    if (marble_physics()){
        glutPostRedisplay();
    }
    if (!model.over)
        glutTimerFunc(5,actualizar,5);
}


int main(int argc, char **argv){

    srand(time(NULL));


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(50, 50);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Marbles");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    set_editar(0);

    glutTimerFunc(UPDATE_MS,actualizar,10);

    glutMainLoop();

    return 0;
}
