/**
 * \file log.c
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/04/2013
 *
 */

#include <stdlib.h>
#include "log.h"


/* *************************************************** */
/* ****************** instanciation ****************** */ 
/* *************************************************** */

/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
log_t* log_create() {
    return (NULL);
}

/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int log_destroy( log_t* log ) {
    return (0);
}



/* *************************************************** */
/* ********************** Move *********************** */ 
/* *************************************************** */
 
/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int log_next( log_t* ) {
    return (0);
}

/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int     log_previous( log_t* ) {
    return (0);
}

/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int log_start( log_t* ) {
    return (0);
}

/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int log_end( log_t* ) {
    return (0);
}


/* *************************************************** */
/* ******************** Insertion ******************** */ 
/* *************************************************** */
/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int log_insert after( log_t* , void* data) {
    return (0);
}

/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int log_insert before( log_t* log, void* data ) {
    return (0);
}


/* *************************************************** */
/* ******************* Suppression ******************* */ 
/* *************************************************** */
 /**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int log_freeSelected( log_t* log ) {
    return (NULL);
}

/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int log_freeForward( log_t* log ) {
    return (0);
}

/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int log_freeBackward( log_t* log ) {
    return (0);
}

/**
 * \ingroup log
 * \fn 
 * \brief 
 * \param 
 * \retval 
 * 
 */
int log_freeAll( log_t* log ) {
    return (0);
}

