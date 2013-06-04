/**
 * \file log.c
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/06/2013
 *
 */

 
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "log.h"

static void _log_freeEltsBackward(log_actions_t* );
static void _log_freeEltsForward(log_actions_t* );


/* *************************************************** */
/* ****************** Instanciation ****************** */ 
/* *************************************************** */

/**
 * \ingroup log
 * \fn log_t* log_create()
 * \brief Creer une liste doublement chainee vide
 * \retval Pointeur sur la liste nouvellement cree
 * 
 */
log_t* log_create(size_t s) 
{
    log_t *logCreated = malloc (sizeof (log_t*) ); /*on alloue de la memoire de la taille d'un log_t*/
    assert(logCreated != NULL);/*On verifie si l'allocation a bien ete faite, on arrete le programme sinon*/
    logCreated->start = NULL;
    logCreated->end = NULL;
    logCreated->selected = NULL;
    logCreated->size = s;
    return (logCreated); /*On retourne l'element cree*/
}

/**
 * \ingroup log
 * \fn int log_destroy( log_t* )
 * \brief Detruit la liste
 * \param La liste a detruire
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 */
int log_destroy( log_t* log ) 
{
    if (log == NULL) /*Si la chaine passee en paramètre est vide, on retourne -1*/
    {
        return (-1);
    }
    
    if (log->start != NULL) /*Si le premier element de la chaine n'est pas nul, on supprime les maillons*/
    {
        _log_freeEltsForward(log->start); /*Appel de la fonction supprimant les maillons*/
    }
    free (log); /*Liberation de la liste*/
    return (0);
}

/* *************************************************** */
/* ***********Enregistrement et chargement************ */ 
/* *************************************************** */

/**
 * \ingroup log
 * \fn log_t*  log_save( log_t*, char* )
 * \brief Sauvegarde la liste
 * \param La liste a sauver et le nom
 * \retval Code d'erreur
 * \attention Ecrase la sauvegarde precedente si le fichier existe deja
 * 
 */
int  log_save( log_t* logToSave, char* logName )
{
    FILE* fd; /*On cree un pointeur sur fichier*/
    log_actions_t* p; /*on cree un pointeur sur maillon*/
    
    fd = fopen(logName, "wb+"); /*On fait pointer sur le fichier ouvert*/
    assert(fd != NULL); /*On verifie le pointeur ouvert*/
    
    for ( p = (logToSave->start); p != NULL; p = p->next ) /*On parcours la liste chainee de start a end(next est alors egal a 0)*/
    {
        fwrite(( p->data), logToSave->size, 1, fd); /*Ecrit les data des maillons dans le fichier*/
    }
    fclose (fd); /*Referme le fichier*/
    return (0);


}
/**
 * \ingroup log
 * \fn log_t* log_load( char, size_t )
 * \brief Charger la liste
 * \param La liste a charger et la taille de la donnee a lire
 * \retval Code d'erreur
 * 
 */
log_t* log_load( char* logName, size_t s )
{
    int run;
    FILE* fd;
    void* tmp = NULL;
    log_t* logLoaded = log_create(s);
    assert( logLoaded != NULL);
    
    
    fd = fopen(logName, "rb");
    if (fd == NULL)
    {
        return (NULL);
    }
    
    run = 1;
    do
    {
        tmp = malloc( s );
        assert(tmp != NULL);
        
        /*Si lecture reussie*/
        if ( fread( tmp, s, 1, fd) == 1 ) 
        {
            /*Insere un maillon avec la donne lue*/
            log_insertAfter( logLoaded, tmp );
            /*On deplace le curseur pour se trouver sur le dernier elt insere*/
            log_next( logLoaded ); 

        }
        
        /*Si la lecture est finie ou que le fichier est vide*/
        else
        {
            /*On libere le tmp*/
            free(tmp);
            /*tmp = NULL; On place le tmp a null pour la condition de sortie*/
            run=0;
        }
    } while (run);
    
   
    return (logLoaded);
}

/* *************************************************** */
/* ********************** Move *********************** */ 
/* *************************************************** */
 
/**
 * \ingroup log
 * \fn int log_next( log_t* )
 * \brief Selectionne l'element suivant de la liste
 * \param La liste
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 */
int log_next( log_t* log ) 
{
    /*Si la chaine passee en paramètre est vide, on retourne -1*/
    if (log == NULL) 
    {
        return (-1);
    }
    
    /*Si l'elt selectionne n'est pas le dernier de la liste chainee*/
    if ( (log->selected)->next != NULL) 
    {
        log->selected=(log->selected)->next; /*On decale le curseur sur l'elt suivant*/
    } 
    return (0);
}

/**
 * \ingroup log
 * \fn int log_previous( log_t* )
 * \brief Selectionne l'element precedent de la liste
 * \param La liste
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 */
int log_previous( log_t* log ) 
{
    /*Si la chaine passee en paramètre est vide, on retourne une erreur*/
    if (log == NULL) 
    {
        return (-1);
    }
    
    /*Si l'elt selectionne n'est pas le premier de la liste chainee*/
    if ( (log->selected)->previous != NULL) 
    {
        log->selected=(log->selected)->previous; /*On decale le curseur sur l'elt suivant*/
        return (0);
    } 
    
    /*Si l'elt selectionne est le premier, on retourne une erreur*/
    else
    {
        return (-1);
    }
    
    return (0);
}

/**
 * \ingroup log
 * \fn int log_start( log_t* )
 * \brief Selectionne le premier element de la liste
 * \param La liste
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 */
int log_start( log_t* log ) 
{ 
    /*Si la chaine passee en paramètre est vide, on retourne -1*/
     if (log == NULL)
    {
        return (-1);
    }
    
    /*S'il existe un premier elt*/
    if (log->start !=NULL)
    {
        log->selected = log->start; /*On déplace le curseur sur le premier elt*/
        return (0);
    }
    
    /*S'il n'existe pas de premier elt, on retourne une erreur*/
    else
    {
        return (-1);
    }
}

/**
 * \ingroup log
 * \fn int log_end( log_t* )
 * \brief Selectionne le dernier element de la liste
 * \param La liste
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 */
int log_end( log_t* log ) 
{
    /*Si la chaine passee en paramètre est vide, on retourne une erreur*/
    if (log == NULL) 
    {
        return (-1);
    }
    
    /*S'il existe un dernier elt*/
    if (log->end !=NULL) 
    {
        log->selected = log->end; /*On déplace le curseur sur le dernier elt*/
        return (0);
    }
    
    /*S'il n'existe pas de dernier elt, on retourne une erreur*/
    else 
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
 * \brief Ajout la donnee apres l'element selecionnee
 * \param La liste
 * \param La donnee
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 */
int log_insertAfter( log_t* log, void* dataInsert) 
{
    log_actions_t *eltInsert = NULL;
    
    /*Si la chaine passee en paramètre est vide, on retourne -1*/
    if (log == NULL) 
    {
        return (-1);
    }
    
    eltInsert = malloc( sizeof (log_actions_t) );
    assert ( eltInsert != NULL );
    eltInsert->data = dataInsert; /*On insere la donnee*/
   
    /*Si la chaine est vide*/
    if (log->start == NULL) 
    {
       log->start = eltInsert ;
       log->selected = eltInsert ;
       log->end =  eltInsert;
       eltInsert->next = NULL;
       eltInsert->previous = NULL;
    }
    
    /* dans tout les autres cas */
    eltInsert->next = (log->selected)->next;
    eltInsert->previous = log->selected;
    
    if ( ((log->selected)->next) != NULL )
        ((log->selected)->next)->previous = eltInsert;
    else 
        log->end = eltInsert; /*Maintenant, l'elt insere est le dernier, il faut donc le preciser !*/
        
    (log->selected)->next = eltInsert;
    
    return (0);
}

/**
 * \ingroup log
 * \fn int log_insertBefore( log_t* log, void* data )
 * \brief Ajout la donnee avant l'element selecionnee
 * \param La liste
 * \param La donnee
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 */
int log_insertBefore( log_t* log, void* dataInsert ) 
{
    log_actions_t *eltInsert = NULL;
    
    /*Si la chaine passee en paramètre est vide, on retourne une erreur*/
    if (log == NULL)
        return (-1);

    /* on allou le nouveau maillon */
    eltInsert = malloc( sizeof (log_actions_t) );
    assert( eltInsert != NULL );
    eltInsert->data = dataInsert; /*On insere la donnee*/
    
    /*Si la chaine est vide*/
    if (log->start == NULL) {
       log->start = eltInsert ;
       log->selected = eltInsert ;
       log->end =  eltInsert;
       eltInsert->next = NULL;
       eltInsert->previous = NULL;
    }
    
    eltInsert->previous = (log->selected)->previous;
    eltInsert->next = log->selected;
    
    if ( ((log->selected)->previous) != NULL )
        ((log->selected)->previous)->next = eltInsert;
    else 
        log->start = eltInsert; /*Maintenant, l'elt insere est le dernier, il faut donc le preciser !*/
        
    (log->selected)->previous = eltInsert;
    
    return (0);
}


/* *************************************************** */
/* ******************* Suppression ******************* */ 
/* *************************************************** */


/**
 * \fn static void _log_freeEltsForward(log_actions_t* logDelete)
 * \brief Supprime le maillon suivant
 * \param Maillon a supprimer
 * Cette fonction est statique car elle ne doit pas etre utilisee ailleurs. L'utilisateur doit passer seulement par les fonctions proposees.
 *
 */

static void _log_freeEltsForward(log_actions_t* logDelete)
{
    if (logDelete->next != NULL)
    {
        _log_freeEltsForward(logDelete->next); /*Recusrivite : on l'appelle a chaque fois pour l'elt suivant, jusqu'a ce qu'on se situe au dernier elt de la chaine*/
    }
    free(logDelete->data); /*On libere la donnee de chaque maillon*/
    free(logDelete); /*On libere chaque maillon*/
}

/**
 * \fn static void _log_freeEltsBackward(log_actions_t* logDelete)
 * \brief Supprime le maillon precedent
 * \param Maillon a supprimer
 * Cette fonction est statique car elle ne doit pas etre utilisee ailleurs. L'utilisateur doit passer seulement par les fonctions proposees.
 *
 */
 
static void _log_freeEltsBackward(log_actions_t* logDelete)
{
    if (logDelete->previous != NULL)
    {
        _log_freeEltsBackward(logDelete->previous); /*Recusrivite : on l'appelle a chaque fois pour l'elt suivant, jusqu'a ce qu'on se situe au dernier elt de la chaine*/
    }
    free(logDelete->data); /*On libere la donnee de chaque maillon*/
    free(logDelete); /*On libere chaque maillon*/
}


 /**
 * \ingroup log
 * \fn int log_freeSelected( log_t* ) 
 * \brief Detruit l'element selectionne
 * \param La liste
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 * L'element selectionne sera le precedent, s'il n'y a pas de precedent, alors ce sera le suivant, sinon, #selected vaudra NULL
 * \attention Libere la memoire associee a la donnee
 */
int log_freeSelected( log_t* log ) 
{
    log_actions_t *tmp = NULL; 
    
    /*Si la chaine passee n'existe pas, on retourne une erreur*/
    if (log == NULL) 
    {
        return (-1);
    }
    
    tmp = log->selected;/*On memorise l'elt selectionne*/
    
    /*Si l'elt selectionne est seul*/
    if ( ((log->selected)->next == NULL) && ((log->selected)->next == NULL) )
    {
        log->selected = NULL;
        log->start = NULL;
        log->end = NULL;
    }
    
    /*Si l'elt selectionne est le dernier*/
    else if ((log->selected)->next == NULL)
    {
        ((log->selected)->previous)->next = NULL; /*On refait les liens*/
        log->selected = (log->selected)->previous;
    }
    
    /*Si l'elt selectionne est le premier*/
    else if ((log->selected)->previous == NULL)
    {
       ((log->selected)->next)->previous = NULL ;/*On refait les liens*/
       log->selected = (log->selected)->next;   
    }
    
    /*Cas general*/
    else
    {
        ((log->selected)->previous)->next = (log->selected)->next; /*On refait les liens*/
        ((log->selected)->next)->previous = (log->selected)->previous ;
        log->selected = (log->selected)->previous;
    }
        
    free(tmp->data);
    free(tmp);
    return (0);
}

/**
 * \ingroup log
 * \fn int log_freeForward( log_t* )
 * \brief Detruit les elements suivant l'element selectionne
 * \param La liste
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 * L'element selectionne n'est pas detruit
 * \attention Libere la memoire associee a la donnee
 */
int log_freeForward( log_t* log ) 
{
    /*Si la chaine passee en paramètre est vide, on retourne une erreur*/
    if (log == NULL) 
    {
        return (-1);
    }
    if ( (log->selected)->next != NULL) {
        _log_freeEltsForward((log->selected)->next); /*On appelle la fonction qui supprime les maillons suivants l'elt selectionne car on passe next en parametre*/
        (log->selected)->next = NULL; /*L'elt selectionne devient le dernier, son pointeur sur l'elt suivant est donc nul*/
    }
    return (0);
}

/**
 * \ingroup log
 * \fn int log_freeBackward( log_t* )
 * \brief Detruit les elements precedent l'element selectionne
 * \param La liste
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 * L'element selectionne n'est pas detruit
 * \attention Libere la memoire associee a la donnee
 */
int log_freeBackward( log_t* log ) 
{
    /*Si la chaine passee en paramètre est vide, on retourne une erreur*/
    if (log == NULL) 
    {
        return (-1);
    }
    if ((log->selected)->previous != NULL) {
        _log_freeEltsBackward((log->selected)->previous); /*On appelle la fonction qui supprime les maillons precedant l'elt selectionne car on passe previous en parametre*/
        (log->selected)->previous = NULL;/*L'elt selectionne devient le premier, son pointeur sur l'elt precedant est donc nul*/
    }
    return (0);
}

/**
 * \ingroup log
 * \fn int log_freeAll( log_t* )
 * \brief Detruit tous les elements
 * \param La liste
 * \retval Code d'erreur
 * Renvoie 0 si succes
 * Renvoie une valeur differente de 0 si echec
 * 
 * \attention Libere la memoire associee a la donnee
 */
int log_freeAll( log_t* log ) 
{
    /*Si la chaine passee en paramètre est vide, on retourne une erreur*/
    if (log == NULL) 
    {
        return (-1);
    }
    if (log->start != NULL ) {
        _log_freeEltsForward(log->start); /*On supprime tout a partir du maillon start et lui meme*/
        log->start = NULL;
        log->end = NULL;
        log->selected = NULL;
    }
    return (0);
}

