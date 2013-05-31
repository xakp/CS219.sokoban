/**
 * \ingroup log.h
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/04/2013
 *
 */


#ifndef LOG_H
#define LOG_H


/** @defgroup log : Historique des coups joues
 * bla bla bla
 */


/**
 * \ingroup log
 * \struct log_actions_t
 * \brief maillon
 */
typedef struct {
    /* donnees */
    void* data;             /*!< donne definissant un coup, a definir avec gab*/

    /* double chainage */
    ActionsLog_t* cursor;   /*!< le coup selectionne*/
    ActionsLog_t* previous; /*!< Le coup precedent*/
} log_actions_t;


/**
 * \ingroup log
 * \struct log_t
 * \brief 
 */
typedef struct {
    ActionsLog_t* start;    /*!< le coup selectionne*/
    ActionsLog_t* end;      /*!< Le coup precedent*/
    ActionsLog_t* cursor;   /*!< Le coup precedent*/
} log_t;


/* instanciation */ 
log_t*  log_create();
int     log_destroy( log_t* );

/* move */
int     log_next( log_t* );
int     log_previous( log_t* );
int     log_start( log_t* );
int     log_end( log_t* );

/* insertion */
int     log_insert after( log_t* , void* );
int     log_insert before( log_t* , void* );

/* suppression : libere les datas */
int     log_freeSelected( log_t* );
int     log_freeForward( log_t* );
int     log_freeBackward( log_t* );
int     log_freeAll( log_t* );



#endif

