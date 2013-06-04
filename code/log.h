/**
 * \file log.h
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/06/2013
 *
 */


#ifndef LOG_H
#define LOG_H

#include <stdlib.h>
#include <assert.h>


/** @defgroup log : Historique des coups joues
 * Permet de conserver en memoire chaque coup que le joueur aura effectue tout au long de la partie. Ainsi, il est possible de revenir en arriere ou de rejouer le coup suivant.
 * Remarque : Si le joueur revient en arriere et joue une nouveau coup, tous les coups suivants sauvegardes en memoire sont supprimes pour que le coup qui vient d'etre joue devient le dernier coup joue. 
 */


/**
 * \ingroup log
 * \struct log_actions_t
 * \brief Maillon
 */

struct log_actions_t {
    /* donnees */
    void* data;             /*!< donne definissant un coup, a definir avec gab*/
    /* double chainage */
    struct log_actions_t* next;   /*!< Le coup suivant*/
    struct log_actions_t* previous; /*!< Le coup precedent*/
};

typedef struct log_actions_t log_actions_t;


/**
 * \ingroup log
 * \struct log_t
 * \brief Chaine, definie par le premier et le dernier maillon, ainsi que d'un maillon selectionne
 */
typedef struct {
    size_t size;
    log_actions_t* start;    /*!< Le premier maillon de la liste*/
    log_actions_t* end;      /*!< Le dernier maillon de la liste*/
    log_actions_t* selected; /*!< Le maillon selectionne*/
} log_t;


/* <instanciation */ 
log_t*  log_create(size_t); /*Cree une instance de liste chainee*/
void    log_destroy( log_t* ); /*Libere toute la liste chainee et l'instance de la liste*/

/*Enregistrement et chargement de la chaine*/
void    log_save( log_t*, char* ); /*Permet de sauvegarder la partie souhaitee*/
log_t*  log_load( char*, size_t ); /*Permet de charger la partie souhaitee*/

/* Deplacement du  curseur de selection */
void    log_next( log_t* );
void    log_previous( log_t* );
void    log_start( log_t* );
void    log_end( log_t* );

/* Insertion de coups, maillons */
void    log_insertAfter( log_t* , void* );
void    log_insertBefore( log_t* , void* ); /*pas utile maintenant*/

/* Suppression : libere les datas, des maillons */
void    log_freeSelected( log_t* ); /*Pas utile maintenant*/
void    log_freeForward( log_t* );
void    log_freeBackward( log_t* ); /*Not now*/
void    log_freeAll( log_t* );
 


#endif

