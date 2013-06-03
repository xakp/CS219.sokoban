/**
 * \file log.c
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/06/2013
 *
 */

 
#include <stdlib.h>
#include "log.h"

/**
 * \fn static void _log_freeElt(log_actions_t* logDelete)
 * \brief supprime un maillon
 * \param maillon a supprimer
 * Cette fonction est statique car elle ne doit pas etre utilisee ailleurs. L'utilisateur doit passer seulement par les fonctions proposees.
 *
 */
 
static void _log_freeElt(log_actions_t* logDelete)
{
    if (logDelete->next != NULL)
    {
        _log_freeElt(logDelete->next); /*Recusrivite : on l'appelle a chaque fois pour l'elt suivant, jusqu'a ce qu'on se situe au dernier elt de la chaine*/
    }
    free(logDelete->data); /*On libere la donnee de chaque maillon*/
    free(logDelete); /*On libere chaque maillon*/
}
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
log_t* log_create() 
{
    log_t *logCreated = malloc (sizeof(log_t*)); /*on alloue de la memoire de la taille d'un log_t*/
    assert(logCreated != NULL);/*On verifie si l'allocation a bien ete faite, on arrete le programme sinon*/
    return (logCreated); /*On retourne l'element cree*/
}

/**
 * \ingroup log
 * \fn int log_destroy( log_t* )
 * \brief detruit la liste
 * \param la liste a detruire
 * \retval code d'erreur
 * renvoie 0 si succes
 * renvoie une valeur differente de 0 si echec
 * 
 */
int log_destroy( log_t* log ) 
{
    if (log == NULL) /*Si la chaine passee en paramètre est vide, on retourne -1*/
    {
        return (-1);
    }
    
    if (log->start != NULL) /*Si le premier element de la chaine n'est nul, on supprime les maillons*/
    {
        _log_freeElt(log->start); /*Appel de la fonction supprimant les maillons*/
    }
    free (log); /*Liberation de la liste*/
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
int log_next( log_t* log ) 
{
    if (log == NULL) /*Si la chaine passee en paramètre est vide, on retourne -1*/
    {
        return (-1);
    }
    
    if ( (log->selected)->next != NULL) /*Si l'elt selectionne n'est pas le dernier de la liste chainee*/
    {
        log->selected=(log->selected)->next; /*On decale le curseur sur l'elt suivant*/
        return (0);
    } 
    
    else /*Si l'elt selectionne est le dernier, on retourne une erreur*/
    {
        return (-1);
    }
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
int log_previous( log_t* log ) 
{
    if (log == NULL) /*Si la chaine passee en paramètre est vide, on retourne -1*/
    {
        return (-1);
    }
    
    if ( (log->selected)->previous != NULL) /*Si l'elt selectionne n'est pas le premier de la liste chainee*/
    {
        log->selected=(log->selected)->previous; /*On decale le curseur sur l'elt suivant*/
        return (0);
    } 
    else /*Si l'elt selectionne est le premier, on retourne une erreur*/
    {
        return (-1);
    }
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
int log_start( log_t* log ) 
{
     if (log == NULL) /*Si la chaine passee en paramètre est vide, on retourne -1*/
    {
        return (-1);
    }
    if (log->start !=NULL) /*S'il existe un premier elt*/
    {
        log->selected = log->start; /*On déplace le curseur sur le premier elt*/
        return (0);
    }
    else /*S'il n'existe pas de premier elt, on retourne une erreur*/
    {
        return (-1);
    }
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
int log_end( log_t* log ) 
{
     if (log == NULL) /*Si la chaine passee en paramètre est vide, on retourne -1*/
    {
        return (-1);
    }
    if (log->end !=NULL) /*S'il existe un dernier elt*/
    {
        log->selected = log->end; /*On déplace le curseur sur le dernier elt*/
        return (0);
    }
    else /*S'il n'existe pas de dernier elt, on retourne une erreur*/
    {
        return (-1);
    }
    return (0);
}


/* *************************************************** */
/* ******************** Insertion ******************** */ 
/* *************************************************** */
/**
 * \ingroup log
 * \fn int log_insertAfter( log_t* , void* )
 * \brief ajout la donnee apres l'element selecionnee
 * \param la liste
 * \param la donnee
 * \retval code d'erreur
 * renvoie 0 si succes
 * renvoie une valeur differente de 0 si echec
 * 
 */
int log_insertAfter( log_t* log, void* data) 
{
     if (log == NULL) /*Si la chaine passee en paramètre est vide, on retourne -1*/
    {
        return (-1);
    }
    else
    {
        log_actions_t *eltInsert = malloc (sizeof(log_actions_t));
        assert (eltInsert !=NULL);
        
    }
    return (0);
}

/**
 * \ingroup log
 * \fn int log_insertBefore( log_t* log, void* data )
 * \brief ajout la donnee avant l'element selecionnee
 * \param la liste
 * \param la donnee
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 */
int log_insertBefore( log_t* log, void* data ) 
{
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
int log_freeSelected( log_t* log ) 
{
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
int log_freeForward( log_t* log ) 
{
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
int log_freeBackward( log_t* log ) 
{
    return (0);
}

/**
 * \ingroup log
 * \fn int log_freeAll( log_t* )
 * \brief detruit tous les elements
 * \param la liste
 * \retval code d'erreur
 * renvoie 0 si succee
 * renvoie une valeur differente de 0 si echec
 * 
 * \attention libere la memoire associee a la donnee
 */
int log_freeAll( log_t* log ) 
{
    return (0);
}

