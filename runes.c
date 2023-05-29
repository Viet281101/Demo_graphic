
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dh.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4df.h>
#include <SDL2/SDL_image.h>

#include "audioHelper.h"
#include "animations.h"

static void runes_init(void);
static void runes_draw(void);
static void runes_sortie(void);

/*!\brief identifiant du programme GLSL */
static GLuint _pId = 0;
/*!\brief position de la lumière relativement à la sphère éclairée */
/*!\brief tableau des identifiants de texture à charger */
static GLuint _tId[22] = {0};
/*!\brief pour les deux astres : terre et lune */
static GLuint _quad = 0;


void runes(int state) {
  switch(state) {
  case GL4DH_INIT:
    runes_init();
    return;
  case GL4DH_FREE:
    runes_sortie();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default: /* GL4DH_DRAW */
    runes_draw();
    return;
  }
}

void runes_init(void) 
{
  int i;
  SDL_Surface * t;
  int vp[4], w, h;
  static char * files[22] = {
    "./assets/images/runes/fond.png",
    "./assets/images/runes/spirit_runes1.png",
    "./assets/images/runes/spirit_runes2.png",
    "./assets/images/runes/spirit_runes3.png",
    "./assets/images/runes/spirit_runes4.png",
    "./assets/images/runes/spirit_runes5.png",
    "./assets/images/runes/spirit_runes6.png",
    "./assets/images/runes/spirit_runes7.png",
    "./assets/images/runes/spirit_runes8.png",
    "./assets/images/runes/spirit_runes9.png",
    "./assets/images/runes/spirit_runes10.png",
    "./assets/images/runes/spirit_runes11.png",
    "./assets/images/runes/spirit_runes12.png",
    "./assets/images/runes/spirit_runes13.png",
    "./assets/images/runes/spirit_runes14.png",
    "./assets/images/runes/spirit_runes15.png",
    "./assets/images/runes/spirit_runes16.png",
    "./assets/images/runes/spirit_runes17.png",
    "./assets/images/runes/spirit_runes18.png",
    "./assets/images/runes/spirit_runes19.png",
    "./assets/images/runes/spirit_runes20.png",
    "./assets/images/runes/spirit_runes21.png",
  };
  _pId  = gl4duCreateProgram("<vs>shaders/earth.vs", "<fs>shaders/earth.fs", NULL);
  glGetIntegerv(GL_VIEWPORT, vp);
  w = vp[2] - vp[0];
  h = vp[3] - vp[1];
  gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.5, 0.5, -0.5 * h / w, 0.5 * h / w, 1.0, 1000.0);
  gl4duBindMatrix("modelViewMatrix");
  glGenTextures(22, _tId);
  for(i = 0; i < 22; i++) {
    glBindTexture(GL_TEXTURE_2D, _tId[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if( (t = IMG_Load(files[i])) != NULL ) {
#ifdef __APPLE__
      int mode = t->format->BytesPerPixel == 4 ? GL_BGRA : GL_BGR;
#else
      int mode = t->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
#endif       
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->w, t->h, 0, mode, GL_UNSIGNED_BYTE, t->pixels);
      SDL_FreeSurface(t);
    } else {
      fprintf(stderr, "can't open file %s : %s\n", files[i], SDL_GetError());
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
  }
  _quad = gl4dgGenQuadf();
}


void runes_draw(void) {
  static GLuint image = 0;
  static GLfloat a0 = 0.0;
  static Uint32 t0 = 0, t;
  GLfloat dt = 0.0;
  dt = ((t = SDL_GetTicks()) - t0) / 1000.0;
  t0 = t;

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gl4duBindMatrix("modelViewMatrix");
  gl4duLoadIdentityf();
  gl4duTranslatef(0, 0, -14);

  glUseProgram(_pId);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _tId[0]);
  //Fond d'écran
  /* envoi de toutes les matrices stockées par GL4D */
  gl4duPushMatrix(); {
    gl4duScalef(300, 250, 100);
    gl4duRotatef(a0, 0, 0, 0);
    gl4duTranslatef(0, 0, -5);
    gl4duScalef(0.9, 0.8, 1); //taille fond d'écran
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform1i(glGetUniformLocation(_pId, "specular"), 0);
  gl4dgDraw(_quad);

  //Runes
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _tId[((image)%18)+1]);
  gl4duPushMatrix(); {
    gl4duScalef(300, 100, 100);
    gl4duRotatef(a0, 0, 0, 0);
    gl4duTranslatef(0.0, 0.06, -1.8); //taille de runes
    gl4duScalef(0.8, 0.8, 0.8); //taille fond d'écran
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform1i(glGetUniformLocation(_pId, "specular"), 0);
  gl4dgDraw(_quad);

  if(image < 71){
    image ++;
  }

  a0 += 360.0 * dt / (6.0); //vitesse de rotation
}


void runes_sortie(void) {
  if (_tId[0]) {
    glDeleteTextures(22, _tId);
    _tId[0] = 0;
  }
}


