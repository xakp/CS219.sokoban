/**
 * \file IHM.h
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/06/2013
 * Gestion du temps, du clavier, et du dessin.
 *
 */


#ifndef IHM_H
#define IHM_H

#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>


typedef int KEY_CODE;


#include "level.h"


/**
 * \enum Sprites
 * \brief Les differents sprites a afficher
 * 
 */
typedef enum {  
    ihm_PLAYER_RIGHT = 0,     
    ihm_PLAYER_LEFT = 1,      
    ihm_PLAYER_UP = 2,        
    ihm_PLAYER_DOWN = 3,      
    ihm_PLAYER_RIGHT_PUSH = 4,
    ihm_PLAYER_LEFT_PUSH = 5, 
    ihm_PLAYER_UP_PUSH = 6,   
    ihm_PLAYER_DOWN_PUSH = 7, 
    ihm_BAG = 8,              
    ihm_TARGET = 9,           
    ihm_WALL = 10,            
    ihm_GROUND = 11,          
    ihm_BAG_OK = 12           
} Sprites;
#define NBR_SPRITES 13


typedef enum {
    BIG, SMALL
} ihm_size;


/**
 * \struct visu_t
 * \brief Decrit un element texte a afficher
 * 
 */
typedef struct {
    ALLEGRO_COLOR color; /*!< La couleur */
    ihm_size size;       /*!< Le choix entre 2 tailles */
    char* txt;           /*!< Un pointeur vers la chaine a afficher */
} visu_t;


/* initialise allegro ET les modules clavier, souris, texte graphique d'allegro, cree les files en globale static */
int     ihm_init(int w, int h, int flags);
void    ihm_close();

/* Fonctions relatives a l'affichage. */
int     ihm_loadSpriteSheet(char* path, int dimsprite);
void    ihm_loadLab(lvl_t* lvl, int margex, int margey, int dimText);
void    ihm_drawBackground();
void    ihm_drawInterface( visu_t *, const int n );
int     ihm_drawMovable();
void    ihm_drawIntro();


/* Fonctions relatives aux evenements */
int     newkey( KEY_CODE* );
int     windowClosed();

/* Fonction relative au temps */
int64_t get_time();
void    restartTime();
void    stopTime();


#endif



