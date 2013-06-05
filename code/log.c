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
    /*on alloue de la memoire de la taille d'un log_t*/
    log_t* logCreated = (log_t*)malloc( sizeof (log_t) ); 
    /*On verifie si l'allocation a bien ete faite, on arrete le programme sinon*/
    assert(logCreated != NULL);
    
    logCreated->start = NULL;
    logCreated->end = NULL;
    logCreated->selected = NULL;
    logCreated->size = s;
    
    /*On retourne l'element cree*/
    return (logCreated); 
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
void log_destroy( log_t* log ) 
{
    assert(log != NULL);
    
    /*Si le premier element de la chaine n'est pas nul, on supprime les maillons*/
    if (log->start != NULL) {
        /*Appel de la fonction supprimant les maillons*/
        _log_freeEltsForward(log->start); 
    }
    /*Liberation de la liste*/
    free (log); 
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
void log_save( log_t* logToSave, char* logName )
{
    /*On cree un pointeur sur fichier*/
    FILE* fd; 
    /*on cree un pointeur sur maillon*/
    log_actions_t* p; 
    
    assert(logToSave != NULL);
    
    /*On fait pointer sur le fichier ouvert*/
    fd = fopen(logName, "wb+"); 
    /*On verifie le pointeur ouvert*/
    assert(fd != NULL); 
    
    /*On parcours la liste chainee de start a end(next est alors egal a 0)*/
    for ( p = (logToSave->start); p != NULL; p = p->next ) {
        /*Ecrit les data des maillons dans le fichier*/
        fwrite(( p->data), logToSave->size, 1, fd); 
    }
    /*Referme le fichier*/
    fclose (fd); 


}
/**
 * \ingroup log
 * \fn log_t* log_load( char, size_t )
 * \brief Charger la liste
 * \param La liste a charger et la taille de la donnee a lire
 * place le curseur a la fin
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
    
    log_end(logLoaded);
   
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
void log_next( log_t* log ) 
{
    assert(log != NULL);

    /*Si l'elt selectionne n'est pas le dernier de la liste chainee*/
    if ( (log->selected)->next != NULL) {
        /*On decale le curseur sur l'elt suivant*/
        log->selected=(log->selected)->next; 
    }
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
void log_previous( log_t* log ) 
{
    assert(log != NULL);

    /*Si l'elt selectionne n'est pas le premier de la liste chainee*/
    if ( (log->selected)->previous != NULL)  {
        /*On decale le curseur sur l'elt suivant*/
        log->selected=(log->selected)->previous; 
    } 
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
void log_start( log_t* log ) 
{ 
    assert(log != NULL);

    /*S'il existe un premier elt*/
    if (log->start !=NULL) {
        /*On déplace le curseur sur le premier elt*/
        log->selected = log->start; 
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
void log_end( log_t* log ) 
{
    assert(log != NULL);

    /*S'il existe un dernier elt*/
    if (log->end !=NULL)  {
        /*On déplace le curseur sur le dernier elt*/
        log->selected = log->end; 
    }
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
void log_insertAfter( log_t* log, void* dataInsert ) 
{
    log_actions_t* eltInsert = NULL;
    
    assert(log != NULL);

    eltInsert = (log_actions_t*) malloc( sizeof (log_actions_t) );
    assert(eltInsert != NULL);
    eltInsert->data = dataInsert;


    /*Si la chaine est vide*/
    if (log->start == NULL) 
    {
       eltInsert->next = NULL;
       eltInsert->previous = NULL;
       log->start = eltInsert;
       log->selected = eltInsert;
       log->end = eltInsert;
       return ;
    }
    
    /* dans tout les autres cas */
    eltInsert->next = (log->selected)->next;
    eltInsert->previous = log->selected;
    
    if ( ((log->selected)->next) != NULL ) {
        ((log->selected)->next)->previous = eltInsert;
    }
    else {
        /*Maintenant, l'elt insere est le dernier, il faut donc le preciser !*/
        log->end = eltInsert; 
    }
    (log->selected)->next = eltInsert;
    
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
void log_insertBefore( log_t* log, void* dataInsert ) 
{
    log_actions_t *eltInsert = NULL;
    
    /*Si la chaine passee en paramètre est vide, on retourne une erreur*/
    assert(log != NULL);

    /* on allou le nouveau maillon */
    eltInsert = malloc( sizeof (log_actions_t) );
    assert( eltInsert != NULL );
    /*On insere la donnee*/
    eltInsert->data = dataInsert; 
    
    /*Si la chaine est vide*/
    if (log->start == NULL)
    {
       eltInsert->next = NULL;
       eltInsert->previous = NULL;
       log->start = eltInsert ;
       log->selected = eltInsert ;
       log->end =  eltInsert;
       return ;
    }
    
    eltInsert->previous = (log->selected)->previous;
    eltInsert->next = log->selected;
    
    if ( ((log->selected)->previous) != NULL ){
        ((log->selected)->previous)->next = eltInsert;
    }
    else {
        /*Maintenant, l'elt insere est le dernier, il faut donc le preciser !*/
        log->start = eltInsert; 
    }
    (log->selected)->previous = eltInsert;
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
        /*Recusrivite : on l'appelle a chaque fois pour l'elt suivant, jusqu'a ce qu'on se situe au dernier elt de la chaine*/
        _log_freeEltsForward(logDelete->next); 
    }
    /*On libere la donnee de chaque maillon*/
    free(logDelete->data); 
    /*On libere chaque maillon*/
    free(logDelete); 
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
        /*Recusrivite : on l'appelle a chaque fois pour l'elt suivant, jusqu'a ce qu'on se situe au dernier elt de la chaine*/
        _log_freeEltsBackward(logDelete->previous); 
    }
    /*On libere la donnee de chaque maillon*/
    free(logDelete->data); 
    /*On libere chaque maillon*/
    free(logDelete); 
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
void log_freeSelected( log_t* log ) 
{
    log_actions_t *sel = NULL; 
    
    assert(log != NULL);
    
    /* si la chaine est vide */
    if ( log-> selected == NULL) {
        return;
    }    
    
    /*On memorise l'elt selectionne*/
    sel = log->selected;
    
    /*Si l'elt selectionne est seul*/
    if ( (sel->next == NULL) && (sel->previous == NULL) ) {
        log->selected = NULL;
        log->start = NULL;
        log->end = NULL;
    }
    
    /*Sinon si c'est le dernier*/
    else if (sel->next == NULL) {
        /* on est sur qu'il y en a un avant */
        (sel->previous)->next = NULL;
        log->end = sel->previous;
        log->selected = sel->previous;
    }
    
    /*Sinon si c'est le premier*/
    else if (sel->previous == NULL) {
        /* on est sur qu'il y en a un avant */
        (sel->next)->previous = NULL;
        log->end = sel->next;
        log->selected = sel->next;
    }
    
    /* il est au milieu */
    else {
        (sel->next)->previous = sel->previous;
        (sel->previous)->next = sel->next;
        log->selected = sel->previous;
    }
    
    /* on libere le maillon et sa donnee */  
    free(sel->data);
    free(sel);
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
void log_freeForward( log_t* log ) 
{
    assert(log != NULL);
    
    if ( (log->selected) != NULL ) {
        if ( (log->selected)->next != NULL) {
            /*On appelle la fonction qui supprime les maillons suivants l'elt selectionne car on passe next en parametre*/
            _log_freeEltsForward((log->selected)->next);
            
            /*L'elt selectionne devient le dernier, son pointeur sur l'elt suivant est donc nul*/
            (log->selected)->next = NULL; 
            log->end = log->selected;
        }
    }
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
void log_freeBackward( log_t* log ) 
{
    assert(log != NULL);
    
    /*On appelle la fonction qui supprime les maillons precedant l'elt selectionne car on passe previous en parametre*/
    if ( (log->selected) != NULL ) {
        if ((log->selected)->previous != NULL) {
            _log_freeEltsBackward((log->selected)->previous); 
            
            /*L'elt selectionne devient le premier, son pointeur sur l'elt precedant est donc nul*/
            (log->selected)->previous = NULL;
            log->start = log->selected;
        }
    }
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
void log_freeAll( log_t* log ) 
{
    assert(log != NULL);

    if (log->start != NULL ) {
        _log_freeEltsForward(log->start); /*On supprime tout a partir du maillon start et lui meme*/
        log->start = NULL;
        log->end = NULL;
        log->selected = NULL;
    }
}

