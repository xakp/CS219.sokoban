/**
 * \file engine.h
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/06/2013
 *
 */


#ifndef ENGINE_H
#define ENGINE_H


#include "level.h"
#include <stdint.h>


/* les differentes directions */
typedef enum {
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3,
    UP = 4,
    START = 5,
    END = 6
} Move;


#define PUSHED 0x80

typedef unsigned int movePlayed_t;

/* joue le coup et renvoi la donnee a allouee */
movePlayed_t* playMove( lvl_t* , Move );

/* test la validite du coup */
int testMove( lvl_t*, Move );

/* annule le coup passe en param */
void revertMove( lvl_t*, movePlayed_t*  );

/* retablie un move */
void replayMove( lvl_t*, movePlayed_t*  );





#endif


