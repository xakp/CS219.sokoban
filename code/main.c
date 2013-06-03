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
 * \date 16/05/2013
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


/**
 * \fn int main()
 * \brief Point d'entree du programme
 * \param [in] int argc : nombre d'argument
 * \param [in] char **argv : arguments
 */
int main( int argc, char **argv )
{
    int i, j;
    int run;
    int posx, posy;
    KEY_CODE key_k;
    lvl_t *lvl = NULL;
    
    assert ( ihm_init(256, 256, 0) == 0 ) ;
    
    
    /* ouvre le fichier de level */
    if (lvl_openFileLvl("../data/levels.lvl") != 0) {
        puts("erreur\n");
        return (-1);
    }
    
    /* lit un level et test l'ouveture */
    lvl = lvl_readLevel(2);
    if (lvl == NULL) {
        puts("lecture impossible\n");
        return (-1);
    }
    
    
    /* l'affiche dans le terminal */
    for (i=0; lvl->dat[i] != NULL ; i++ ) {
        for (j=0; lvl->dat[i][j] != lvl_NULL ; j++ ) 
            putc( " @.$# "[ lvl->dat[i][j] ], stdout );
        printf("\n");
    }
    
    ihm_loadLab(lvl, -1, -1);
    
    
    if ( ihm_loadSpriteSheet("../data/_spritesheet.bmp", 32) != 0 ) {
        puts("erreur chargement spritesheet\n");
        return (-1);
    }
    

    run = 1;
    while ( !windowClosed() && run ) {
        ihm_drawSpriteInLab(0, 0, 0);
        al_flip_display();
        
        if ( newkey(&key_k) ) {
            if ( key_k == ALLEGRO_KEY_ESCAPE )
                run = 0;
        }
        
        if ( mouseClicked(&posx, &posy) ) {
            printf("(%d,%d)\n", posx, posy);
        }
        
    }


    /* libere le level */
    lvl_closeLevel(lvl);
    
    /* non implemente */
    lvl_closeFileLvl();
    
    return (0);
}



 

