/**
 * \file level.h
 * \brief Mini-projet CS210
 * \author SCHLOTTERBECK Guillaume - EYMARD Gabrielle
 * \version 1.0
 * \date 16/05/2013
 *
 */


#ifndef LEVEL_H
#define LEVEL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h> /* uint16_t : unsigned short int (entier de 16 bits non signe) */

#define BUFFER_SIZE 64

#define ENCODE_WALL '#'     /* '#' */
#define ENCODE_GROUND ' '   /* ' ' */
#define ENCODE_TARGET '.'   /* '.' */
#define ENCODE_BAG '$'      /* '$' */
#define ENCODE_PLAYER '@'   /* '@' */



/**
 * \enum cell
 * \brief les different trucs possible dans une cellule
 * 
 */
typedef enum {
    lvl_NULL = 0,     /*!< Sentinelle. */
    lvl_PLAYER,
    lvl_TARGET,
    lvl_BAG,
    lvl_WALL,
    lvl_GROUND,    
    lvl_BAG_OK
} lvl_cell;



/**
 * \struct Level
 * \brief contient les infos necessaires au niveau
 * 
 */
typedef struct {
    uint16_t num;   /*!< Contient le numero du niveau. */
    lvl_cell **dat;     /*!< Tableau 2D vers les elements du niveau. */
} lvl_t;



int8_t lvl_openFileLvl( char *file );
void lvl_closeFileLvl();

lvl_t* lvl_readLevel( int16_t num );
void lvl_closeLevel(lvl_t* lvl);


#endif


