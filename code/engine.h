/**
 * \file engine.h
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/06/2013
 * C'est le moteur du jeu, c'est lui qui teste, qui joue, qui annule et qui retablie les coups.
 *
 */


#ifndef ENGINE_H
#define ENGINE_H


#include <stdint.h>
#include "level.h"



/**
 * \def PUSHED
 * \brief C'est le bit qui indique si un sac a ete pousse dans les movePlayed_t
 */
#define PUSHED 0x80


/* les differentes directions et les balises de fin et de debut de chaine */
typedef enum {
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3,
    UP = 4,
    START = 5,
    END = 6
} Move;



typedef unsigned int movePlayed_t;

/* test la validite du mouvement */
int testMove( lvl_t*, Move );

/* joue le mouvement et renvoie la donnee a sauvegarder */
movePlayed_t* playMove( lvl_t* , Move );

/* annule le coup passe en parametre */
void revertMove( lvl_t*, movePlayed_t*  );

/* retabli un mouvement */
void replayMove( lvl_t*, movePlayed_t*  );





#endif


