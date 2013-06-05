/*! \mainpage Mini-projet CS210
 * \section intro_sec Introduction
 * 
 *
 * \subsection step1 Step 1: Opening the box
 */
/**
 * \file main.c
 * \brief Mini-projet CS210
 * \author SCHLOTTERBECK Guillaume - EYMARD Gabrielle
 * \version 1.0
 * \date 05/06/2013
 *
 */


 /* les includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include <allegro5/allegro5.h>


#include "level.h"
#include "IHM.h"
#include "log.h"
#include "engine.h"


/**
 * \fn int main()
 * \brief Point d'entree du programme
 * \param [in] int argc : nombre d'argument
 * \param [in] char **argv : arguments
 */
int main( int argc, char **argv )
{
    KEY_CODE key_k;
    lvl_t* lvl;
    visu_t visu[3];
    int run;
    int num = 7;
    
    assert( ihm_init(256, 256, 0) == 0 ) ;
    
    
    /* ouvre le fichier de level */
    if (lvl_openFileLvl("../data/levels.lvl") != 0) 
    {
        puts("erreur\n");
        return (-1);
    }
    
    
    lvl = lvl_readLevel( num );
    if (lvl == NULL) {
        puts("lecture impossible\n");
        return (-1);
    }
    
    if ( ihm_loadSpriteSheet("../data/spritesheet.png", 32) != 0 ) {
        puts("erreur chargement spritesheet\n");
        return (-1);
    }
    
    ihm_loadLab( lvl, 1, 1, 5 );
    
    run = 1;
    while ( !windowClosed() && run ) {
    
        if ( newkey(&key_k) ) switch ( key_k ) {
        
        /*Autres evenements*/  
        /*Charger un niveau (ecrase la partie sauvegardee sur ce niveau si elle existe*/

        /*On quitte le programme*/  
        case ALLEGRO_KEY_ESCAPE :
            run = 0;
            break;
            
        /*Recommencer niveau*/
        case ALLEGRO_KEY_R :
            lvl_closeLevel( lvl );
            lvl = lvl_readLevel( num );
            if (lvl == NULL) {
                puts("lecture impossible\n");
                return (-1);
            }
            ihm_loadLab( lvl, 1, 1, 7 );
            break;
            
            
            
        /*Deplacements*/
        /*on deplace vers le haut*/
        case ALLEGRO_KEY_Z :
            if ( testMove(lvl, UP) != 0 ) 
            {
                playMove(lvl,UP);/*
                log_insertAfter(log, playMove(lvl,UP));
                log_next(log);*/
            }
            break ;
            
        /*on deplace vers le bas*/
        case ALLEGRO_KEY_S :
            if ( testMove(lvl, DOWN) != 0 ) 
            {
                playMove(lvl,DOWN);/*
                log_insertAfter(log, playMove(lvl,DOWN));
                log_next(log);*/
            }
        
            break ;
            
        /*on deplace vers le gauche*/
        case ALLEGRO_KEY_Q :
            if ( testMove(lvl, LEFT) != 0 ) 
            {
                playMove(lvl,LEFT);/*
                log_insertAfter(log, playMove(lvl,LEFT));
                log_next(log);*/
            }
        
            break ;
            
        /*on deplace vers le droite*/
        case ALLEGRO_KEY_D :
            if ( testMove(lvl, RIGHT) != 0 ) 
            {
                playMove(lvl,RIGHT);/*
                log_insertAfter(log, playMove(lvl,RIGHT));
                log_next(log);*/
            }
            
            break;
            
        /*Ne rien faire*/
        default : break ;
        
        }/* !switch */
        
        /* on affiche */
        ihm_drawBackground();
        ihm_drawInterface(visu, 0);
        ihm_drawMovable();
        
        al_flip_display();
    
    } /* ! while */
    
    lvl_closeLevel(lvl);
    lvl_closeFileLvl();
    ihm_close();
    
    return (0);
}






 