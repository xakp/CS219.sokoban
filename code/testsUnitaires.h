/**
 * \file testsUnitaires.h
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 04/06/2013
 *
 */
 
#ifndef TESTSUNITAIRES_H
#define TESTSUNITAIRES_H


/* <instanciation */ 
int     test_log_create(); /*Cree une instance de liste chainee*/
int     test_log_destroy( log_t* ); /*Libere toute la liste chainee et l'instance de la liste*/

/* Deplacement du  curseur de selection */
int     test_log_next( log_t* );
int     test_log_previous( log_t* );
int     test_log_start( log_t* );
int     test_log_end( log_t* );

/* Insertion de coups, maillons */
int     test_log_insertAfter( log_t* , void* );
int     test_log_insertBefore( log_t* , void* ); /*pas utile maintenant*/

/* Suppression : libere les datas, des maillons */
int     test_log_freeSelected( log_t* ); /*Pas utile maintenant*/
int     test_log_freeForward( log_t* );
int     test_log_freeBackward( log_t* ); /*Not now*/
int     test_log_freeAll( log_t* );

#endif

