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


void _log_view(log_t*);


int main (int argc, char* argv[]) 
{
    log_t *log = NULL;
    int* d1 = (int*) malloc( sizeof (int) );
    int* d2 = (int*) malloc( sizeof (int) );
    int* d3 = (int*) malloc( sizeof (int) );
    
    assert( d1 && d2 && d3 );
    
    *d1 = 1;
    *d2 = 10;
    *d3 = 100;
    
    /*Test des fonctions log_create et log_insertAfter*/
    log = log_create( sizeof (int) );
    if (log != NULL) printf("log created\n");
    else return -1;
    
    /*25 est à la fois start, selected et end car seul maillon de la chaine*/
    log_insertAfter( log, ((void*)d1) );
    printf("a "); _log_view(log);


    /*Test de log_insertBefore : cas elt selected est premier */
    log_insertAfter( log, ((void*)d2) );
    printf("b "); _log_view(log);
    
    log_next(log);
    log_freeSelected(log);
    printf("B "); _log_view(log);
    
    /*Test de log_insertBefore : cas elt selected milieu */
    log_insertBefore( log , ((void*)d3) );
    log_previous( log );
    printf("c "); _log_view(log);
    
    /*Test de log_insertBefore : cas elt selected milieu */
    log_end( log );
    printf("d "); _log_view(log);
    


    /*Test de la fct de sauvegarde*/
    log_save( log, "save1" );
    printf("log save to save1\n");
    
    /* destroy */
    log_destroy(log);
    printf("log destroyed\n");
    
    /*Test de la fct de chargement*/
    log = log_load( "save1", sizeof(int) );
    _log_view(log);
    


    return (0);
}





void _log_view(log_t* log) {
    log_actions_t* a = NULL;
    
    assert( log != NULL);
    
    if (log->start == NULL) {
        printf("log empty\n");
        return;
    }
    
    a = log->start;
    while( a != NULL ) {
        if ( a == log->selected ) {
            printf("(%d) ", (int)(*((int*)a->data)));
        }
        else {
            printf("%d ", (int)(*((int*)a->data)));
        }
        a = a->next;
    }
    printf("\n");
}








