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


/**
 * \ingroup log
 * \fn log_t* log_create()
 * \brief Test la creation d'une liste doublement chainee vide
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 */

/*void test_log_create()
 {
    if (log_create() == 0)
    {
        printf ("La fonction fonctionne normalement !");
    }
    
    else
    {
        printf ("Erreur !");
    }
 }
 
 */


























int main (int argc, char* argv[]) 
{

    int i=25;
    int j=26;
    int k=27;
    int* dataInsert = &i;
    int* dataInsert2 = &j;
    int* dataInsert3= &k;
    
    /*Test des fonctions log_create et log_insertAfter*/
    log_t *log = log_create(sizeof (int));
    log_insertAfter( log , ((void*)dataInsert) );
    printf ("%d\n%d\n%d\n\n", *((int*)(log->start)->data), *((int*)(log->selected)->data), *((int*)(log->end)->data)); /*25 est à la fois start, selected et end car seul maillon de la chaine*/

    
    /*Test de log_insertBefore : cas elt selected est premier */
    log_insertBefore( log , ((void*)dataInsert2) );
    printf ("%d\n%d\n%d\n\n", (*((int*)(log->start)->data)), (*((int*)(log->selected)->data)), (*((int*)(log->end)->data))); /*26 est start car inséré avant 25, 25 reste selected et end*/
    
    /*Test de log_insertBefore : cas elt selected milieu */
    log_insertBefore( log , ((void*)dataInsert3) );
    log_previous( log );
    printf ("%d\n%d\n%d\n\n", (*((int*)(log->start)->data)), (*((int*)(log->selected)->data)), (*((int*)(log->end)->data))); /*26 reste le start, on insere 27 avant le selected 25 puis on deplace le curseur selected avant. On se trouve donc sur 27 qui devient le selected. Le end n'a pas bouge, c'est toujours 25*/
    
    /*Test de la fct de sauvegarde*/
    log_save( log, "save1" );
    
    /*Test de la fct de chargement*/
    log_t* logCreated = log_load( "save1", sizeof(int) );
    printf("%d", *((int*)(logCreated->selected)->data) );
    
    printf("a");
    
    
    /*Test de la fonction log_next*/
    /*log_next( log );
    printf ("%d\n", *((int*)(log->selected)->data));
    
    log_insertBefore( log, ((void*)dataInsert3));
    log_previous( log );
    printf("%d\n", *((int*)(log->selected)->data));
    log_start( log );
    printf("%d\n", *((int*)(log->selected)->data));
    log_end (log );
    printf("%d\n", *((int*)(log->selected)->data));*/
  

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