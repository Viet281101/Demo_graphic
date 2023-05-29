/*!\file animations.h
 *
 * \brief Votre espace de liberté : c'est ici que vous pouvez ajouter
 * vos fonctions de transition et d'animation avant de les faire
 * référencées dans le tableau _animations du fichier \ref window.c
 *
 * Des squelettes d'animations et de transitions sont fournis pour
 * comprendre le fonctionnement de la bibliothèque. En bonus des
 * exemples dont un fondu en GLSL.
 *
 * \author Farès BELHADJ, amsi@up8.edu
 * \date April 12, 2023
 */

#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H


#include <GL4D/gl4du.h>
#include <GL4D/gl4dp.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C" {
#endif

  /* animations */
  extern void animation_vide(int state);
  extern void exemple_d_animation_00(int state);
  extern void fond_ecran(int state);
  extern void fond_skull(int state);
  extern void fond_blood(int state);

  extern void rouge(int state);
  extern void vert(int state);
  extern void bleu(int state);
  extern void ciel(int state);

  extern void animationsInit(void);

  /* transition */
  extern void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void fondui(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void exemple_de_transition_00(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);

  /* dans texte_intro.c */
  extern void texte_intro(int state);

  /* dans credit.c */
  extern void credit_fin(int state);

  /* dans pentagram.c */
  extern void pentagram(int state);

  /* dans explosion.c */
  extern void explosion(int state);

  /* dans spectre.c */
  extern void spectre(int state);

  /* dans mob.c */
  extern void mob(int state);
  extern void multi_mob(int state);

  /* dans runes.c */
  extern void runes(int state);

#ifdef __cplusplus
}
#endif

#endif



