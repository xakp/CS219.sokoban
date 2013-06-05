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


/**
 * \fn int main()
 * \brief Point d'entree du programme
 * \param [in] int argc : nombre d'argument
 * \param [in] char **argv : arguments
 */
int main( int argc, char **argv )
{
    KEY_CODE key_k;
    int i, j;
    lvl_t* lvl;
    visu_t* visu[3];
    assert( ihm_init(256, 256, 0) == 0 ) ;
    int run;
    
    
    /* ouvre le fichier de level */
    if (lvl_openFileLvl("../data/levels.lvl") != 0) 
    {
        puts("erreur\n");
        return (-1);
    }
    
    
    run = 1;
    while ( !windowClosed() && run ) {   
    switch (key_k) {
    
    /*Autres evenements*/  
    /*Charger un niveau (ecrase la partie sauvegardee sur ce niveau si elle existe*/
    case ALLEGRO_KEY_ENTER :
        lvl = lvl_readLevel( num );
        if (lvl == NULL) {
            puts("lecture impossible\n");
            return (-1);
        }
        
        ihm_loadLab( lvl, 1, 1, 7 );
        ihm_drawBackground();
        ihm_drawInterface
        break;
        
    /*On quitte le programme*/  
    case ALLEGRO_KEY_ESCAPE :
        lvl_closeLevel(lvl);
        lvl_closeFileLvl();
        break;
        
    /*Recommencer niveau*/
    case ALLEGRO_KEY_R :
        lvl_closeLevel( lvl );
        lvl_readLevel( num );
        break;
        
    /*Charger partie deja exisante*/
    case ALLEGRO_KEY_L :
        lvl_readLevel( num );
        log_load( nameLog, sizeLog );
        break;
        
    /*Sauvegarder partie en cours*/
    case ALLEGRO_KEY_C :
        log_save( log, logSaved );
        break;
    

        
    /*Deplacements*/
    /*on deplace vers le haut*/
    case ALLEGRO_KEY_Z :
        if ( testMove(lvl, UP) != 0 ) 
        {
            log_insertAfter(log, playMove(lvl,UP));
            log_next(log);
        }
        break ;
        
    /*on deplace vers le bas*/
    case ALLEGRO_KEY_S :
            if ( testMove(lvl, DOWN) != 0 ) 
        {
            log_insertAfter(log, playMove(lvl,DOWN));
            log_next(log);
        }
    
        break ;
        
    /*on deplace vers le gauche*/
    case ALLEGRO_KEY_Q :
            if ( testMove(lvl, LEFT) != 0 ) 
        {
            log_insertAfter(log, playMove(lvl,LEFT));
            log_next(log);
        }
    
        break ;
        
    /*on deplace vers le droite*/
    case ALLEGRO_KEY_D :
            if ( testMove(lvl, RIGHT) != 0 ) 
        {
            log_insertAfter(log, playMove(lvl,RIGHT));
            log_next(log);
        }
        
        break;
        
    /*Ne rien faire*/
    default :
        
        break;
    }
    
    return (0);
}






 