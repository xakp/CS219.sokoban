/**
 * \file IHM.h
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/06/2013
 *
 */


#ifndef IHM_H
#define IHM_H

#include <stdlib.h>
#include <assert.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>


typedef int KEY_CODE;


#include "level.h"

typedef struct {
    lvl_t* lvl;
    ALLEGRO_BITMAP* background;
    int margex; /*!< en nombre de cellules de GROUND. */
    int margey; /*!< en nombre de cellules de GROUND. */
    
} ihm_lab;


typedef enum {
    ihm_PLAYER_LEFT = 0,
    ihm_PLAYER_RIGHT = 1,
    ihm_PLAYER_UP = 2,
    ihm_PLAYER_DOWN = 3,
    ihm_PLAYER_LEFT_PUSH = 4,
    ihm_PLAYER_RIGHT_PUSH = 5,
    ihm_PLAYER_UP_PUSH = 6,
    ihm_PLAYER_DOWN_PUSH = 7,
    ihm_TARGET = 8,
    ihm_BAG = 9,
    ihm_WALL = 10,
    ihm_GROUND = 11
} Sprites;


/* initialise allegro ET le module clavier d'allegro, creer une pile en globale static ET lespiles d'events de display... */
ALLEGRO_DISPLAY* ihm_init(int w, int h, int flags);
void ihm_close();

/* Fonctions relatives a l'affichage. */
int         ihm_loadSpriteSheet(char* path, int dimsprite);
ihm_lab*    ihm_loadLab(lvl_t* lvl, int margex, int margey);
void        ihm_closelab( ihm_lab* );
int         ihm_drawSpriteInLab(ihm_lab* lab, int posx, int posy, Sprites sp);


/* Fonctions relatives aux evenements */
int     newkey( KEY_CODE* );
int     windowClosed();
int     mouseClicked(ihm_lab* , int*, int*);




#endif



