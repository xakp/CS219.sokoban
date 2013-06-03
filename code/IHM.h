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

#include <allegro5/allegro5.h>




#include "level.h"

typedef struct {
    ALLEGRO_BITMAP* background;
    int offsetx;
    int offsety;
    
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


int loadSpriteSheet(char* path, int dimsprite);

ihm_lab* ihm_loadLab(lvl_t* lvl);
int ihm_drawSpriteInLab(ihm_lab* lab, int posx, int posy, Sprites sp);





#endif



