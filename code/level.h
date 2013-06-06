/**
 * \file level.h
 * \brief Fichier d'en-tete : Gestion des fichier *.lvl
 * \author SCHLOTTERBECK Guillaume - EYMARD Gabrielle
 * \version 1.0
 * \date 16/05/2013
 *
 */

#ifndef LEVEL_H
#define LEVEL_H


/**
  * @addtogroup Level
  * @{
  */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/* to uint16_t : unsigned short int (entier de 16 bits non signe) */
#include <stdint.h> 


/** 
 * \def BUFFER_SIZE
 * \brief Tampon pour lire les lignes de level.lvl
 *
 */
#define BUFFER_SIZE 64


/** 
 * \def ENCODE_WALL
 * \brief Caractere qui encode le mur dans level.lvl
 *
 */
#define ENCODE_WALL '#'

/** 
 * \def ENCODE_GROUND
 * \brief Caractere qui encode le sol dans level.lvl
 *
 */
#define ENCODE_GROUND ' '

/** 
 * \def ENCODE_TARGET
 * \brief Caractere qui encode la cible dans level.lvl
 *
 */
#define ENCODE_TARGET '.'

/** 
 * \def ENCODE_BAG
 * \brief Caractere qui encode le sac dans level.lvl
 *
 */
#define ENCODE_BAG '$'

/** 
 * \def ENCODE_BAG_TARGETED
 * \brief Caractere qui encode le sac stocke dans level.lvl
 *
 */
#define ENCODE_BAG_TARGETED '*'

/** 
 * \def ENCODE_PLAYER
 * \brief Caractere qui encode le joueur dans level.lvl
 *
 */
#define ENCODE_PLAYER '@'



/**
 * \enum lvl_cell
 * \brief les differentes entites dans une cellule
 * 
 */
typedef enum {
    lvl_NULL    = 0,     /*!< Sentinelle */
    
    lvl_WALL    = 0x10,  /*!< Mur : 5eme bit */
    lvl_PLAYER  = 0x08,  /*!< Joureur : 4eme bit */
    lvl_BAG     = 0x04,  /*!< Sac : 3eme bit. */
    lvl_GROUND  = 0x02,  /*!< Sol : 2eme bit. */
    lvl_TARGET  = 0x01   /*!< Cible : 1er bit. */
} lvl_cell;


/**
 * \def lvl_access (~(lvl_TARGET|lvl_GROUND))
 * \brief Informe si une lvl_cell est libre
 * Exemple : ((cell & lvl_access) == 0) => cell est accessible
 *
 */
#define lvl_access (~(lvl_TARGET|lvl_GROUND))


/**
 * \def lvl_movable (lvl_PLAYER|lvl_BAG)
 * \brief Informe si une lvl_cell est deplacable
 * Exemple : ((cell & lvl_movable) == 0) => cell est deplacable
 *
 */
#define lvl_movable (lvl_PLAYER|lvl_BAG)


/**
 * \def lvl_bagStocked (lvl_TARGET|lvl_BAG)
 * \brief Informe si un sac se trouve sur une cible
 * Exemple : ((cell & lvl_bagStocked) == 0) => cell est deplacable
 *
 */
#define lvl_bagStocked (lvl_TARGET|lvl_BAG)




/**
 * \struct lvl_t
 * \brief Contient les informations necessaires a l'utilisation d'un niveau
 * 
 */
typedef struct {
    uint32_t num;       /*!< Contient le numero du niveau */
    uint16_t nbrTarget; /*!< Contient le nombre de cible dans le niveau */
    lvl_cell **dat;     /*!< Tableau 2D vers les cellules du niveau. */
} lvl_t;



int getNbrLvl();
int8_t lvl_openFileLvl( char *file );
void lvl_closeFileLvl();
lvl_t* lvl_readLevel( int16_t num );
void lvl_closeLevel(lvl_t* lvl);



/** @} */

#endif


