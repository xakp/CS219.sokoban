/**
 * \file testsUnitaires.c
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 04/06/2013
 *
 */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "log.h"



int main (int argc, char* argv[]) 
{
    log_t *log = NULL;
    int* d1 = (int*) malloc( sizeof (int) );
    int* d2 = (int*) malloc( sizeof (int) );
    int* d3 = (int*) malloc( sizeof (int) );
    
    assert( d1 && d2 && d3 );
    
    *d1 = 25;
    *d2 = 26;
    *d3 = 27;
    
    /*Test des fonctions log_create et log_insertAfter*/
    log = log_create( sizeof (int) );
    printf("log created\n");
    
    /*25 est à la fois start, selected et end car seul maillon de la chaine*/
    log_insertAfter( log, ((void*)d1) );
    printf ("start(%d)  end(%d)  select(%d)\n", (int)(*((int*)(log->start)->data)), (int)(*((int*)(log->end)->data)), (int)(*((int*)(log->selected)->data)));

    /*Test de log_insertBefore : cas elt selected est premier */
    log_insertBefore( log, ((void*)d2) );
    printf ("start(%d)  end(%d)  select(%d)\n", (int)(*((int*)(log->start)->data)), (int)(*((int*)(log->end)->data)), (int)(*((int*)(log->selected)->data)));

    /*Test de log_insertBefore : cas elt selected milieu */
    log_insertBefore( log , ((void*)d3) );
    log_previous( log );
    printf ("start(%d)  end(%d)  select(%d)\n", (int)(*((int*)(log->start)->data)), (int)(*((int*)(log->end)->data)), (int)(*((int*)(log->selected)->data)));

    /*Test de la fct de sauvegarde*/
    log_save( log, "save1" );
    printf("log save to save1\n");
    
    /* destroy */
    log_destroy(log);
    printf("log destroyed\n");
    
    /*Test de la fct de chargement*/
    log = log_load( "save1", sizeof(int) );
    printf("%d", *((int*)(log->selected)->data) );
    


    return (0);
}









/*Brouillon test marche pas */
    /*char str[]="abcde"; liste de caractere a placer dans les maillons
    char *p = str;
    void* data;*/ 
    /*for (p = str; (*p) != '\0'; p++)
    {
        data = malloc( sizeof (char) );
        assert(data != NULL);
        log_insertAfter(log, data );
        
        
        *((char*)((log->selected)->data)) = *p;
    }
    
    for ( log_start(log) ; (log->selected)->next != NULL ; log_next(log) )
    {
        printf ("%c\n", *(char*)((log->selected)->data) );
    }
    */