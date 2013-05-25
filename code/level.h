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

/**
 * \struct Level
 * \brief contient les infos necessaires au niveau
 * 
 */
typedef struct {
    uint16_t num;   /*!< Contient le numero du niveau. */
    char **dat;     /*!< Tableau 2D vers les elements du niveau. */
} Level;



int8_t openFileLvl( char *file );
void closeFileLvl();

Level* readLevel( int16_t num );
void closeLevel(Level* lvl);


#endif


