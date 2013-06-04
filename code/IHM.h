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


/**
 * \enum Sprites
 * \brief les differents sprites a afficher
 * 
 */
typedef enum {  
    ihm_PLAYER_RIGHT = 0,        /*!<  */
    ihm_PLAYER_LEFT = 1,       /*!<  */
    ihm_PLAYER_UP = 2,          /*!<  */
    ihm_PLAYER_DOWN = 3,        /*!<  */
    ihm_PLAYER_RIGHT_PUSH = 4,   /*!<  */
    ihm_PLAYER_LEFT_PUSH = 5,  /*!<  */
    ihm_PLAYER_UP_PUSH = 6,     /*!<  */
    ihm_PLAYER_DOWN_PUSH = 7,   /*!<  */
    ihm_TARGET = 8,             /*!<  */
    ihm_BAG = 9,                /*!<  */
    ihm_WALL = 10,              /*!<  */
    ihm_GROUND = 11             /*!<  */
} Sprites;
#define NBR_SPRITES 12



/* initialise allegro ET le module clavier d'allegro, creer une pile en globale static ET lespiles d'events de display... */
int     ihm_init(int w, int h, int flags);
void    ihm_close();

/* Fonctions relatives a l'affichage. */
int     ihm_loadSpriteSheet(char* path, int dimsprite);
void    ihm_loadLab(lvl_t* lvl, int margex, int margey, int dimText);
int     ihm_drawSpriteInLab(int posx, int posy, Sprites sp);
void    ihm_drawBackgournd();


/* Fonctions relatives aux evenements */
int     newkey( KEY_CODE* );
int     windowClosed();
int     mouseClicked(int*, int*);




#endif



