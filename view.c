/*
 * $Id: view.c 86 2006-11-30 04:46:13Z julio $
 */

#include <GL/glut.h>
#include "model.h"
#include "view.h"
#include "material.h"
#include "marble.h"
#include "texto.h"

#define DEG2RAD(x) (((x)*M_PI)/180.0)
#define MARBLE(i) model.marble[i]

extern model_t model;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0,0, model.winw-150, model.winh);

    //update_camera();

    glLoadIdentity();

    
    
    gluLookAt(0, 0, model.camz, 0, 0, 0, 0, 1, 0);
    glRotatef(model.camy, 1, 0, 0);
    glRotatef(model.camx, 0, 1, 0);
    
    dibujar_tablero();
    dibujar_ejes();
    
    dibujar_bolas();
    dibujar_puntos();
    

    if (model.over) {
        ganador();
    }
    
    dibujar_texto();
    glutSwapBuffers();
}


static GLfloat colorjugador[][3] = {
    {1,0,0}, {0,1,0}, {0, 0, 1}, {1, 0, 1}
};

void ganador(){ 

    glDisable(GL_LIGHTING);
    
    // guardar y cambiar la matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, model.winw-150, model.winh, 0);

    // guardar y cambiar la matriz de modelview
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //dibujar

    float mindist = 1000;
    int ganador = 0;
    int i;
    for (i=0; i<4; i++){
        float f = dist3d(MARBLE(i).x, model.objx, 
                         MARBLE(i).y, model.objy, 
                         MARBLE(i).z, model.objz);

        if (f < mindist){
            mindist = f;
            ganador = i;
        }
    }
    
    glColor3fv(colorjugador[ganador]);
    glPrint24((model.winw/2-150) - 40, 100, "El ganador es el Jugador %d\n", ganador+1);


    // restaurar la matriz de modelview
    glPopMatrix();

    // restaurar la matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_LIGHTING);

}

void dibujar_texto(){ 
    glViewport(model.winw-150,0, 150, model.winh);

    glDisable(GL_LIGHTING);
    
    // guardar y cambiar la matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 150, model.winh, 0);

    // guardar y cambiar la matriz de modelview
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //dibujar

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(0,model.winh);
    glEnd();
    

    int i;
    int ypos =0;
    for (i=0; i<4; i++){
        ypos += 24;
        glColor3fv(colorjugador[i]);
        if ( i == model.turn)
            glPrint24(10, ypos, "* Jugador %d\n", i+1);
        else
            glPrint24(10, ypos, "Jugador %d\n", i+1);
        
        glColor3f(1,1,1);
        
        ypos += 15;
        glColor3f(1,1, 0);
        glPrint10(15, ypos, "Dist: %.4f\n", dist3d(MARBLE(i).x, model.objx, 
                                                 MARBLE(i).y, model.objy, 
                                                 MARBLE(i).z, model.objz));

        glColor3f(1,1, 1);
        ypos += 15;
        glPrint10(15, ypos, "(x,y,z): (%.2f, %.2f, %.2f)\n", MARBLE(i).x, MARBLE(i).y, MARBLE(i).z);

        ypos += 15;
        glPrint10(15, ypos, "(vx,vz): (%.2f, %.2f)\n", MARBLE(i).vx, MARBLE(i).vz);

        ypos += 15;
        glPrint10(15, ypos, "|v|: %.4f\n", hypot(MARBLE(i).vx, MARBLE(i).vz));

        ypos += 15;
        glPrint10(15, ypos, "F: %.4f\n", MARBLE(i).mag);

        ypos += 15;
        glPrint10(15, ypos, "theta: %.4f\n", MARBLE(i).theta);

        ypos += 5;
    }


    // restaurar la matriz de modelview
    glPopMatrix();

    // restaurar la matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_LIGHTING);

}


void dibujar_ejes(){
    if (!model.ejes)
        return;
    
    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(0, -0.1, 0);
    glVertex3f(100, -0.1, 0);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0, -.1, 0);
    glVertex3f(0, 100, 0);

    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(0, -0.1, 0);
    glVertex3f(0, -0.1, 100);
    glEnd();


    glPopAttrib();
}

void dibujar_puntos(){
    if (!model.editando)
        return;

    int i, j;

    glPushAttrib(GL_ENABLE_BIT);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glPointSize(4);
    glColor3f(1,1,0);
    for (i=0; i<11; i++){
        for (j=0; j<11; j++){
            if (i==model.editx && j==model.edity){
                glColor3f(1, 0, 0);
                glBegin(GL_LINES);
                glVertex3f(model.puntos[i][j][0], 
                           1+model.puntos[i][j][1]/5.0,
                           model.puntos[i][j][2]);
                glEvalCoord2f(j/10.0, i/10.0);
                glEnd();
            } else{
                glColor3f(1, 1, 0);
            }

            glLoadName(j*11+i);
            glBegin(GL_POINTS);
            glVertex3f(model.puntos[i][j][0], 
                       1+model.puntos[i][j][1]/5.0,
                       model.puntos[i][j][2]);
            glEnd();
        }
    }
    // redibujar el seleccionado de color amarillo
/*     glColor3f(1,0,0); */
/*     glVertex3f(model.puntos[model.editx][model.edity][0],  */
/*                1+model.puntos[model.editx][model.edity][1]/5.0, */
/*                model.puntos[model.editx][model.edity][2]); */
    
    glPopAttrib();
}

void dibujar_tablero(){
    //glLoadIdentity();
    material_t material_superficie = {
        { 0.0, 0, 0, 0},
        { 1.0f, 168/255.9, 88/255.0f, 0.0f },
        //{ 0, 0, 1.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 47.0f }
    };
    setMaterial(&material_superficie);
    glEvalMesh2(model.wireframe ? GL_LINE : GL_FILL, 0, model.gridsize, 0, model.gridsize);
}


material_t material_negro = {
    { 0.0, 0, 0, 0},
    { 0.0f, 0, 0.0f, 0.0f },
    //{ 0, 0, 1.0f, 0.0f },
    { 1.0f, 1.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 47.0f }
};

void dibujar_bolas()
{
  //TODO: hacer que la bola solo toque la superficie, no siempre la
  //parte de abajo de la bola es la que esta mas cerca
  //  marble_physics();
    int i;
  glEnable(GL_LIGHTING);

  //primero dibujo el objetivo 
  glDisable(GL_TEXTURE_2D);
  glPushMatrix();
  setMaterial(&material_negro);
  glTranslatef(model.objx, model.objy, model.objz);
  glutSolidSphere(0.1,10, 10);
  glPopMatrix();

  for(i=0;i<model.players;i++){
    //trato de no atravesar la superficie
    float mn=sqrt(model.marble[i].nx*model.marble[i].nx+model.marble[i].ny*model.marble[i].ny+model.marble[i].nz*model.marble[i].nz);
    float x=model.marble[i].x+(model.marble[i].nx/mn)*model.marble[i].r;
    float z=model.marble[i].z+(model.marble[i].nz/mn)*model.marble[i].r;
    float y=model.marble[i].y+(model.marble[i].ny/mn)*model.marble[i].r;
    
    glPushMatrix();
    glTranslatef(x,y,z);
    setMaterial(&model.marble[i].material);            

    if (model.wireframe)
        glutWireSphere(model.marble[i].r,50,50);
    else {
        //  rotar la textura para que parezca que la pelota se mueve
        glPushAttrib(GL_TEXTURE_BIT | GL_ENABLE_BIT);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glTranslatef(model.marble[i].rotx, 0, 0);
        glTranslatef(0, model.marble[i].rotz, 0);
        glMatrixMode(GL_MODELVIEW);

        glBindTexture(GL_TEXTURE_2D,model.marble[i].texture);
        gluSphere(model.marble[i].q, model.marble[i].r, 50, 50);
        //glutSolidSphere(model.marble[i].r,50,50);
	
        glPopAttrib();
    }
    
    glPopMatrix();
    
/*     nx=model.marble[i].nx; */
/*     ny=model.marble[i].ny; */
/*     nz=model.marble[i].nz; */

/*     glBegin(GL_LINES); */
/*     glVertex3f(x,y,z); */
/*     glVertex3f(nx+x,ny+y+1,nz+z); */
/*     glEnd(); */

/*     // dibujo una esfera pequenia donde va la normal */
/*     glPushMatrix(); */
/*     glTranslatef(nx+x,ny+y+1,nz+z); */
/*     setMaterial(&model.marble[i].material); */
/*     if (model.wireframe) */
/*         glutWireSphere(0.1,10,10); */
/*     else */
/*         glutSolidSphere(0.1,10,10); */
/*     glPopMatrix(); */

/*     //dibujo vector velocidad */
/*     glBegin(GL_LINES); */
/*     glVertex3f(x,y,z); */
/*     glVertex3f(x+model.marble[i].vx,y,z+model.marble[i].vz); */
/*     glEnd();     */

  // dibujo el vector de fuerza que va aplicarsele a la metra    

    if (!model.editando && i == model.turn && model.still){
        GLfloat theta = model.marble[i].theta;
        GLfloat mag = model.marble[i].mag;

        glPushAttrib(GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT | GL_LINE_BIT );

        // renderizar la lineas con antialias
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHTING);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POINT_SMOOTH);

        glLineWidth(2.0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(x,y + MARBLE_RADIO,z);
        glVertex3f(x + mag*sin(theta) ,y + MARBLE_RADIO,z + mag*cos(theta));
        glEnd();

        /*         glEnable(GL_LIGHTING); */
        /*         glDisable(GL_BLEND); */
        /*         glDisable(GL_LINE_SMOOTH); */
        /*         glDisable(GL_POINT_SMOOTH);     */
        glPopAttrib();
    }


  }
}
