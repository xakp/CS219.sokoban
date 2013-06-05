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
    LEFT = 0,
    DOWN = 1,
    RIGHT = 2,
    UP = 3
} Move;


typedef uint8_t movePlayed;

/* joue le coup et renvoi la donnee a allouee */
movePlayed* playMove( lvl_t* , Move );

/* test la validite du coup */
int testMove( lvl_t*, Move );

/* annule le coup passe en param */
void revertMove( lvl_t*, movePlayed*  );

/* retablie un move */
void replayMove( lvl_t*, movePlayed*  );





#endif


