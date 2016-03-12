/*
 * $Id: marble.c 89 2006-11-30 12:51:22Z cesar $
 */

#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "marble.h"
#include "model.h"


extern model_t model;


void init_bolas()
{
  SDL_Surface *tex;
  // primera metra
  model.marble[0].vx=0;
  model.marble[0].vz=0;
  model.marble[0].nx=0;
  model.marble[0].nz=0;
  model.marble[0].x=4.0;
  model.marble[0].y=0.0;
  model.marble[0].z=4.0;
  model.marble[0].r=0.3;
  model.marble[0].rotz=0;
  model.marble[0].rotx=0;
  model.marble[0].theta=0;
  model.marble[0].mag=1;
  

  model.marble[0].q = gluNewQuadric();
  gluQuadricNormals(model.marble[0].q, GLU_SMOOTH);
  if ((tex = SDL_LoadBMP("data/marble5.bmp"))){
    printf("cargue la textura\n");
    gluQuadricTexture(model.marble[0].q, GL_TRUE);
    glGenTextures(1, &model.marble[0].texture);
    glBindTexture(GL_TEXTURE_2D,model.marble[0].texture);
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex->w, tex->h, 0, GL_BGR, GL_UNSIGNED_BYTE, tex->pixels );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    SDL_FreeSurface(tex);
  }

  material_t m0 = {
    {0,0,0,0}, //ambient
    {1,0,0,0}, //diffuse
    {0,0,0,0}, //specular
    {0,0,0,0}, //emission
    {50}
  };
  assignMaterial(&m0,&model.marble[0].material);

  if(model.players<2) return;// segunda metra
  model.marble[1].vx=0;
  model.marble[1].vz=0;
  model.marble[1].nx=0;
  model.marble[1].nz=0;
  model.marble[1].x=-4.0;
  model.marble[1].y=0.0;
  model.marble[1].z=4.0;
  model.marble[1].r=0.3;
  model.marble[1].rotz=0;
  model.marble[1].rotx=00;
  model.marble[1].theta=0;
  model.marble[1].mag=1;

  model.marble[1].q = gluNewQuadric();
  gluQuadricNormals(model.marble[1].q, GLU_SMOOTH);
  if ((tex = SDL_LoadBMP("data/marble2.bmp"))){
    printf("cargue la textura\n");
    gluQuadricTexture(model.marble[1].q, GL_TRUE);
    glGenTextures(1, &model.marble[1].texture);
    glBindTexture(GL_TEXTURE_2D,model.marble[1].texture);
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex->w, tex->h, 0, GL_BGR, GL_UNSIGNED_BYTE, tex->pixels );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    SDL_FreeSurface(tex);
  }

  material_t m1 = {
    {0,0,0,0}, //ambient
    {0,1,0,0}, //diffuse
    {0,0,0,0}, //specular
    {0,0,0,0}, //emission
    {50}
  };
  assignMaterial(&m1,&model.marble[1].material);

  if(model.players<3) return;// tercera metra
  model.marble[2].vx=0;
  model.marble[2].vz=0;
  model.marble[2].nx=0;
  model.marble[2].nz=0;
  model.marble[2].x=4.0;
  model.marble[2].y=0.0;
  model.marble[2].z=-4.0;
  model.marble[2].r=0.3;
  model.marble[2].rotz=0;
  model.marble[2].rotx=00;
  model.marble[2].theta=0;
  model.marble[2].mag=1;

  model.marble[2].q = gluNewQuadric();
  gluQuadricNormals(model.marble[2].q, GLU_SMOOTH);
  if ((tex = SDL_LoadBMP("data/marble3.bmp"))){
    printf("cargue la textura\n");
    gluQuadricTexture(model.marble[2].q, GL_TRUE);
    glGenTextures(1, &model.marble[2].texture);
    glBindTexture(GL_TEXTURE_2D,model.marble[2].texture);
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex->w, tex->h, 0, GL_BGR, GL_UNSIGNED_BYTE, tex->pixels );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    SDL_FreeSurface(tex);
  }

  material_t m2 = {
    {0,0,0,0}, //ambient
    {0,0,1,0}, //diffuse
    {0,0,0,0}, //specular
    {0,0,0,0}, //emission
    {50}
  };
  assignMaterial(&m2,&model.marble[2].material);

  if(model.players<4) return;// cuarta metra
  model.marble[3].vx=0;
  model.marble[3].vz=0;
  model.marble[3].nx=0;
  model.marble[3].nz=0;
  model.marble[3].x=-4.0;
  model.marble[3].y=0.0;
  model.marble[3].z=-4.0;
  model.marble[3].r=0.3;
  model.marble[3].rotz=0;
  model.marble[3].rotx=00;
  model.marble[3].theta=0;
  model.marble[3].mag=1;

  model.marble[3].q = gluNewQuadric();
  gluQuadricNormals(model.marble[3].q, GLU_SMOOTH);
  if ((tex = SDL_LoadBMP("data/marble4.bmp"))){
    printf("cargue la textura\n");
    gluQuadricTexture(model.marble[3].q, GL_TRUE);
    glGenTextures(1, &model.marble[3].texture);
    glBindTexture(GL_TEXTURE_2D,model.marble[3].texture);
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex->w, tex->h, 0, GL_BGR, GL_UNSIGNED_BYTE, tex->pixels );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    SDL_FreeSurface(tex);
  }

  material_t m3 = {
    {0,0,0,0}, //ambient
    {1,0,1,0}, //diffuse
    {0,0,0,0}, //specular
    {0,0,0,0}, //emission
    {50}
  };
  assignMaterial(&m3,&model.marble[3].material);
}


/*
 * Calcula la fisica del juego. Devuelve 1 si alguna pelota cambia de posicion
 *
 */
int marble_physics()
{
  int cambio =0;
  int i,j;
  for(i=0;i<model.players;i++){
     
    float x=model.marble[i].x;
    float z=model.marble[i].z;
    //    float y=model.marble[i].y;

    //vamos a ver si choca
    int c=0; //choco?
    float d,xtmp,ztmp;
    for(j=i+1;j<model.players;j++){
      float dx=model.marble[i].x-model.marble[j].x;
      float dz=model.marble[i].z-model.marble[j].z;
      d=sqrt(pow(dx,2)+pow(dz,2));
      if(d<2*MARBLE_RADIO){//choque
        //	printf("choque:i:%d:j:%d\n",i,j);
        xtmp=model.marble[i].vx;
        ztmp=model.marble[i].vz;
        model.marble[i].vx=model.marble[j].vx;
        model.marble[i].vz=model.marble[j].vz;
        model.marble[j].vx=xtmp;
        model.marble[j].vz=ztmp;
        c=1;
        cambio=1;
        //desfollo
        dx=dx*2*MARBLE_RADIO/d;
        dz=dz*2*MARBLE_RADIO/d;
        model.marble[i].x=model.marble[j].x+dx;
        model.marble[i].z=model.marble[j].z+dz;

        break;

      }
    }

    //calculo la normal
    float x1,x2,nx,y1,y2,ny,z1,z2,nz,vx,vz;

    if(!c){//sino choco, calculo la velocidad en funcion de la normal
    
      //velocidad
      vx=model.marble[i].vx*.85+model.marble[i].nx*.85;
      vz=model.marble[i].vz*.85+model.marble[i].nz*.85;

      // frenar completamente si la velocidad es muy poca 
      if (fabs(vx) <= 0.01)
        vx = 0;
      if (fabs(vz) <= 0.01)
        vz = 0;

      model.marble[i].vx=vx;
      model.marble[i].vz=vz;
      cambio = cambio || (vx != 0) || (vz != 0);
      //printf("physics:vx:%f:vz:%f\n",model.marble[i].vx,model.marble[i].vz);
            
    }

    float dx = model.marble[i].vx;
    float dz =  model.marble[i].vz;

    //actualizo la posicion de acuerdo a la velocidad y la normal
    model.marble[i].x+=model.marble[i].vx;
    model.marble[i].z+=model.marble[i].vz;

    //rebote en las paredes
    if(model.marble[i].x<-5 || 5<model.marble[i].x){
      model.marble[i].x-=model.marble[i].vx;
      model.marble[i].vx*=-.5;
      cambio = 1;
    } else if (dx != 0){
      model.marble[i].rotx += dx * model.marble[i].r;
    }
            
    if(model.marble[i].z<-5 || 5<model.marble[i].z){
      model.marble[i].z-=model.marble[i].vz;
      model.marble[i].vz*=-.5;
      cambio = 1;
    } else if (dz != 0){
      model.marble[i].rotz += dz * model.marble[i].r;
    }

    model.marble[i].y=compute(model.marble[i].x,model.marble[i].z);

    //calculo normal
    x1=0;z1=(z>0)?-0.5:0.5;//busco puntos cercanos al centro a ver si lo logra
    y1=compute(model.marble[i].x+x1,model.marble[i].z+z1)-model.marble[i].y;

    x2=(x>0)?-0.5:0.5;z2=0;
    y2=compute(model.marble[i].x+x2,model.marble[i].z+z2)-model.marble[i].y;

    int b=((x*z>0)?1:-1);//el signo depende del cuadrante
    nx=b*y1*z2-b*y2*z1;//+model.marble[i].x;
    ny=-b*x1*z2+b*x2*z1;//+y+1;
    nz=b*x1*y2-b*x2*y1;//+model.marble[i].z;

    model.marble[i].nx=nx;
    model.marble[i].ny=ny;
    model.marble[i].nz=nz;

    //si no me muevo, todo va en cero para cambiar de turno
    if(x==model.marble[i].x && z==model.marble[i].z) cambio=0;

  }

  if (!cambio){
    model.still = 1;
    glutPostRedisplay();
  }

  return cambio;
}
