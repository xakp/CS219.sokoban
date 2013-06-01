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
 * \fn log_t* log_create()
 * \brief Creer une liste doublement chainee vide
 * \retval pointeur sur la liste nouvellement cree
 * 
 */
log_t* log_create() {
    return (NULL);
}

/**
 * \ingroup log
 * \fn int log_destroy( log_t* )
 * \brief detruit la liste
 * \param la liste a detruire
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
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
 * \fn int log_next( log_t* )
 * \brief selectionne l'element suivant de la liste
 * \param la liste
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 */
int log_next( log_t* log ) {
    return (0);
}

/**
 * \ingroup log
 * \fn int log_previous( log_t* )
 * \brief selectionne l'element precedent de la liste
 * \param la liste
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 */
int log_previous( log_t* log ) {
    return (0);
}

/**
 * \ingroup log
 * \fn int log_start( log_t* )
 * \brief selectionne le premier element de la liste
 * \param la liste
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 */
int log_start( log_t* log ) {
    return (0);
}

/**
 * \ingroup log
 * \fn int log_end( log_t* )
 * \brief selectionne le dernier element de la liste
 * \param la liste
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 */
int log_end( log_t* log ) {
    return (0);
}


/* *************************************************** */
/* ******************** Insertion ******************** */ 
/* *************************************************** */
/**
 * \ingroup log
 * \fn int log_insert after( log_t* , void* )
 * \brief ajout la donnee apres l'element selecionnee
 * \param la liste
 * \param la donnee
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 */
int log_insert after( log_t* log, void* data) {
    return (0);
}

/**
 * \ingroup log
 * \fn int log_insert before( log_t* log, void* data )
 * \brief ajout la donnee avant l'element selecionnee
 * \param la liste
 * \param la donnee
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
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
 * \fn int log_freeSelected( log_t* ) 
 * \brief detruit l'element selectionnee
 * \param la liste
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 * l'element selectionne sera le precedent, si il n'y a pas de precedent, alors ce sera le suivant, sinon, #selected vaudra NULL
 * \attention libere la memoire associee a la donnee
 */
int log_freeSelected( log_t* log ) {
    return (NULL);
}

/**
 * \ingroup log
 * \fn int log_freeForward( log_t* )
 * \brief detruit les elements suivant l'element selectionnee
 * \param la liste
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 * l'element selectionne n'est pas detruit
 * \attention libere la memoire associee a la donnee
 */
int log_freeForward( log_t* log ) {
    return (0);
}

/**
 * \ingroup log
 * \fn int log_freeBackward( log_t* )
 * \brief detruit les elements precedent l'element selectionnee
 * \param la liste
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 * l'element selectionne n'est pas detruit
 * \attention libere la memoire associee a la donnee
 */
int log_freeBackward( log_t* log ) {
    return (0);
}

/**
 * \ingroup log
 * \fn 
 * \brief detruit tous les elements
 * \param la liste
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 * \attention libere la memoire associee a la donnee
 */
int log_freeAll( log_t* log ) {
    return (0);
}

