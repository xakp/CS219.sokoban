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


/**
 * \fn int main()
 * \brief Point d'entree du programme
 * \param [in] int argc : nombre d'argument
 * \param [in] char **argv : arguments
 */
int main( int argc, char **argv )
{
    int i;  
    int j;  
    lvl_t *lvl = NULL;
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_BITMAP* background = NULL;
    
    
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
        for (j=0; lvl->dat[i][j] != NULL ; j++ ) 
            putc( " @.$# "[ lvl->dat[i][j] ] );
        printf("\n");
    }

    
    /* libere le level */
    lvl_closeLevel(lvl);
    
    /* non implemente */
    lvl_closeFileLvl();
    
    return (0);
}



 

