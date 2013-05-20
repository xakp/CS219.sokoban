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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


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
    
    if (openFileLvl("../data/levels.lvl") != 0) {
        puts("erreur\n");
    }
    
    Level *lvl = (Level*)readLevel(2);
    if (lvl == NULL) {
        puts("lecture impossible\n");
        return -1;
    }
    

    for (i=0; lvl->dat[i] != NULL ; i++ ) {
        printf("-%s-\n", lvl->dat[i]);
    }
    
    
    

    
    closeFileLvl();
    
    return (0);
}

