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
    log_actions_t* start;    /*!< Le premier maillon de la liste*/
    log_actions_t* end;      /*!< Le dernier maillon de la liste*/
    log_actions_t* selected; /*!< Le maillon selectionne*/
} log_t;


/* <instanciation */ 
log_t*  log_create(); /*Cree une instance de liste chainee*/
int     log_destroy( log_t* ); /*Libere toute la liste chainee et l'instance de la liste*/

/* Deplacement du  curseur de selection */
int     log_next( log_t* );
int     log_previous( log_t* );
int     log_start( log_t* );
int     log_end( log_t* );

/* Insertion de coups, maillons */
int     log_insertAfter( log_t* , void* );
int     log_insertBefore( log_t* , void* ); /*pas utile maintenant*/

/* Suppression : libere les datas, des maillons */
int     log_freeSelected( log_t* ); /*Pas utile maintenant*/
int     log_freeForward( log_t* );
int     log_freeBackward( log_t* ); /*Not now*/
int     log_freeAll( log_t* );



#endif

