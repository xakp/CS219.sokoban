/*! \mainpage Mini-projet CS210
 * \section intro_sec Introduction
 * 
 *
 * \subsection step1 Step 1: Opening the box
 */
/**
 * \file main.c
 * \brief Mini-projet CS210
 * \author SCHLOTTERBECK Guillaume - EYMARD Gabrielle
 * \version 1.0
 * \date 05/06/2013
 *
 */


 /* les includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include <allegro5/allegro5.h>

#define MARGEX 1
#define MARGEY 1
#define W_TEXT 7


#include "level.h"
#include "IHM.h"
#include "log.h"
#include "engine.h"

typedef enum {
    FROM_FILE,  /*!< on charge depuis le fichier de niveau */
    FROM_SAVE,  /*!< on charge une partie deja existence */
    FROM_SOLUTION   /*!< on charge la solution */
} Type_load ;

typedef enum {
    SOLUTION,   /*!< on sauvegarde un solution */
    SIMPLE      /*!< on sauvegarde une partie */
} Type_game ;


/* reset tout les compteur de jeu */
static void reset_counters(int *checked, int *nbrCanceled, int *nbrPushed, int *nbrPlayed);

/* configure les informations texte */
static void setVisu(visu_t*, int num, int cancel, int play, int push, int64_t t, int bagStocked, int nbrTarget);

/* sauvegarde la chaine des coups joues */
static void save( lvl_t*, log_t*, Type_game );

/* charge un niveau, selon le type, joue l'annimation */
static int load(int num, lvl_t**, log_t**, Type_load );

/* joue un coup selon une touche */
static int play( KEY_CODE, log_t*, lvl_t*, int*, int* );

/* renvoie un pointeur vers un maillon alloue contenant la donnee END */
static movePlayed_t* getEndElt();


/**
 * \fn int main()
 * \brief Point d'entree du programme
 * \param [in] int argc : nombre d'argument
 * \param [in] char **argv : arguments
 */
int main( int argc, char **argv )
{
    log_t* log = NULL;
    lvl_t* lvl = NULL;

    int run;
    int checked = 0;
    int bagStocked = 0;
    signed int num = 1;
    int nbrCanceled = 0;
    int nbrPushed = 0;
    int nbrPlayed = 0;
    
    visu_t visu[7];
    
    KEY_CODE key_k;
    
    /* ouvre le fichier de level */
    if (lvl_openFileLvl("../data/levels.lvl") != 0) {
        puts("erreur\n");
        return (-1);
    }

    
    /* init l'IHM */
    assert( ihm_init(800, 440, 0) == 0 );
    if ( ihm_loadSpriteSheet("../data/spritesheet.png", 32) != 0 ) {
        puts("erreur chargement spritesheet\n");
        return (-1);
    }
    
    /* affiche quelque ligne d'explication */
    ihm_drawIntro();
    
    /* load le lvl 1 */
    if ( load( num, &lvl, &log, FROM_FILE ) != 0 ) {
        printf("erreur to load lvl");
        return (-1);
    }
    restartTime(); 
    
    run = 1;
    while ( !windowClosed() && run ) {
    
        if ( newkey(&key_k) ) {
        switch ( key_k ) {

            /*On quitte le programme*/  
            case ALLEGRO_KEY_ESCAPE :
                run = 0;
                break;
            
            /* Jouer un coup */
            case ALLEGRO_KEY_R: /* redo */
            case ALLEGRO_KEY_E: /* undo */
            case ALLEGRO_KEY_Z: /* haut */
            case ALLEGRO_KEY_Q: /* gauche */
            case ALLEGRO_KEY_S: /* bas */
            case ALLEGRO_KEY_D: /* droite */
                /* si on a gagne, on interdit le deplacement */
                if ( checked ) 
                    break;
                if ((*(Move*)((log->selected)->data)) == END) {
                    break ;
                }
                nbrPlayed += play( key_k, log, lvl, &nbrCanceled, &nbrPushed );
                
                /* save log & load next */
                
                break ;
                
        /*Recommencer, precedent, suivant niveau */
            case ALLEGRO_KEY_T :
                if ( load( num, &lvl, &log, FROM_FILE ) == 0 ) {
                    reset_counters(&checked, &nbrCanceled, &nbrPushed, &nbrPlayed);
                }
                break;
            case ALLEGRO_KEY_LEFT :
                num = ( --num < 1 ) ? 1 : num;
                if ( load( num, &lvl, &log, FROM_FILE ) == 0 ) {
                    reset_counters(&checked, &nbrCanceled, &nbrPushed, &nbrPlayed);
                }
                break;
            case ALLEGRO_KEY_RIGHT :
                num = ( ++num > getNbrLvl() ) ? getNbrLvl() : num;
                if ( load( num, &lvl, &log, FROM_FILE ) == 0 ) {
                    reset_counters(&checked, &nbrCanceled, &nbrPushed, &nbrPlayed);
                }
                else {
                    num = ( --num < 1 ) ? 1 : num;
                }
                break;
            /* sauvegarde la partie en cours */
            case ALLEGRO_KEY_W :
                /* si on a gagne, on interdit le deplacement */
                if ( checked ) 
                    break;
                save( lvl, log, SIMPLE );
                break;
            
            /* charge la partie sauvegardee */
            case ALLEGRO_KEY_X :
                if (load(num, &lvl, &log, FROM_SAVE ) == 0) {
                    reset_counters(&checked, &nbrCanceled, &nbrPushed, &nbrPlayed);
                }
                break;
                
            /* charge la solution */
            case ALLEGRO_KEY_C :
                if (load(num, &lvl, &log, FROM_SOLUTION ) == 0) {
                    reset_counters(&checked, &nbrCanceled, &nbrPushed, &nbrPlayed);
                    stopTime();
                }
                break;
            
            case ALLEGRO_KEY_ENTER :
                if (checked) {
                    /* passe au niveau suivant */
                    num = ( ++num > getNbrLvl() ) ? getNbrLvl() : num;
                    if (load(num, &lvl, &log, FROM_SAVE ) == 0) {
                        reset_counters(&checked, &nbrCanceled, &nbrPushed, &nbrPlayed);
                        restartTime();
                    }
                }
                break ;
            /*Ne rien faire*/
            default : break ;
            
            }/* !switch */

        
        } /* ! if key */
        
        
        /* on affiche */
        ihm_drawBackground();
        bagStocked = ihm_drawMovable();
        setVisu( visu, lvl->num, nbrCanceled, nbrPlayed, nbrPushed, get_time(), bagStocked, lvl->nbrTarget );
        ihm_drawInterface(visu, (checked) ? 7 : 6 );
        
        al_flip_display();
        
        /* SI victoire ET victoire non prise en compte */
        if ( (bagStocked == lvl->nbrTarget) && !(checked) ) {
            /* prise en conpte de la victoire */
            checked = 1; 
            
            /* arrete le timer */
            stopTime();
            
            /* ajoute le maillon END */
            log_insertAfter( log, getEndElt() );
            log_next( log );
            
            /* save la solution */
            save( lvl, log, SOLUTION );
            
            printf("TERMINE\n");
            
        }
        
        
    } /* ! while */

    
    lvl_closeLevel(lvl);
    lvl_closeFileLvl();
    ihm_close();
    
    return (0);
}





int play( KEY_CODE key, log_t* log, lvl_t* lvl, int* nbrCanceled, int* nbrPushed ) {
    movePlayed_t *move;
    
    switch ( key ) {

    /*annuler/retablir*/
    /*retablir*/
    case ALLEGRO_KEY_R :
        if ( ( (log->selected) != NULL ) && ( ((log->selected)->next) != NULL ) ) {
            log_next( log );
            
            move = (movePlayed_t*)(log->selected)->data;
            (*nbrPushed) += ((*move) & PUSHED) ? 1 : 0;
            
            replayMove(lvl, move );
            printf("Move replayed\n");
            return (1);
        }
        break;

    /*annuler*/  
    case ALLEGRO_KEY_E :
        if ( ( (log->selected) != NULL ) && ( *(movePlayed_t*)((log->selected)->data) != START ) ) {
            
            move = (movePlayed_t*)(log->selected)->data;
            (*nbrPushed) -= ((*move) & PUSHED) ? 1 : 0;
                 
            revertMove(lvl, move );
            /* si le premier coup est revert, on se place sur start */
            log_previous( log );
            printf("Move reverted\n");
            *nbrCanceled = *nbrCanceled +1 ;
            return (-1);
        }
        break;

    
    /*Deplacements*/
    /*on deplace vers le haut*/
    case ALLEGRO_KEY_Z :
        if ( testMove(lvl, UP) != 0 ) 
        {
            move = playMove(lvl,UP);
            (*nbrPushed) += ((*move) & PUSHED) ? 1 : 0;
            
            log_freeForward(log);
            log_insertAfter(log, move);
            log_next(log);
            return (1);
        }
        break ;
        
    /*on deplace vers le bas*/
    case ALLEGRO_KEY_S :
        if ( testMove(lvl, DOWN) != 0 ) 
        {
            move = playMove(lvl,DOWN);
            (*nbrPushed) += ((*move) & PUSHED) ? 1 : 0;
            
            log_freeForward(log);
            log_insertAfter(log, move);
            log_next(log);
            return (1);
        }
    
        break ;
        
    /*on deplace vers le gauche*/
    case ALLEGRO_KEY_Q :
        if ( testMove(lvl, LEFT) != 0 ) 
        {
            move = playMove(lvl,LEFT);
            (*nbrPushed) += ((*move) & PUSHED) ? 1 : 0;
            
            log_freeForward(log);
            log_insertAfter(log, move);
            log_next(log);
            return (1);
        }
    
        break ;
        
    /*on deplace vers le droite*/
    case ALLEGRO_KEY_D :
        if ( testMove(lvl, RIGHT) != 0 ) 
        {
            move = playMove(lvl, RIGHT);
            (*nbrPushed) += ((*move) & PUSHED) ? 1 : 0;
            
            log_freeForward(log);
            log_insertAfter(log, move);
            log_next(log);
            return (1);
        }
        
        break;
        
    /*Ne rien faire*/
    default : break ;
    
    }/* !switch */
    return (0);
}


movePlayed_t* getEndElt() {
    movePlayed_t* end;
    
    assert( end = malloc( sizeof ( movePlayed_t ) ) );
    *end = END;
    
    return (end);
}



int load(int num, lvl_t** plvl, log_t** plog, Type_load ty ) {

    movePlayed_t* _start = NULL;
    KEY_CODE key_k;
    log_actions_t* sel = NULL;
    char buff[32] = {0};
    
    /* on regarde si on a fini le niveau precedent */
    sprintf(buff, "../save/level%d_(f).sav", num-1);
    if ( (num != 1) && (!( al_filename_exists(buff) )) ) {
        printf("error : %s doesn't exist\n", buff);
        return (-1);
    }
    
    printf("Tentative de chargement du niveau %d\n", num);
    
    lvl_closeLevel( *plvl );
    *plvl = NULL;
 
    assert( (*plvl) = lvl_readLevel( num ) );
    
    /* on veut charger un niveau qui est entame => nouvelle chaine */
    if ( (ty == FROM_SAVE) || (ty == FROM_SOLUTION) ) {
        /* une liste existe */
        if ( *plog != NULL ) {
            log_destroy( *plog );
        }
        if (ty == FROM_SOLUTION) {
            sprintf(buff, "../save/level%d_(f).sav", num );
        }
        else {
            sprintf(buff, "../save/level%d.sav", num );
        }
        
        *plog = log_load( buff, ( sizeof (movePlayed_t) ));
        
        /* echec du chargement de la chaine => on charge le niveau normal */
        if ( *plog == NULL )  {
            ty = FROM_FILE;
        }
        /* reussite du chargement */
        else {
            ihm_loadLab( *plvl, MARGEX, MARGEY, W_TEXT );
            log_start(*plog);
            
            for ( sel=(((*plog)->start)->next) ; sel != NULL ; sel = sel->next ) {
                replayMove(*plvl, (movePlayed_t*)sel->data );
                
                /* si on veut la solution, on l'affiche */
                if (ty == FROM_SOLUTION) {
                    al_rest(0.05);
                    ihm_drawBackground();
                    ihm_drawMovable();
                    al_flip_display();
                    
                    /* arrete l'affichage de la solution */
                    if ( newkey(&key_k) && (key_k == ALLEGRO_KEY_ESCAPE) ) {
                        ty = FROM_SAVE;
                    }
                }
            }
            log_end( *plog );
            return (0);
        }
    }
    
    if ( ty == FROM_FILE ) {
        /* la liste n'est pas instanciee */
        if ( *plog == NULL ) {
            *plog = log_create( sizeof (movePlayed_t) );
            
            /* initialise le maillon start    */
            assert( _start = malloc( sizeof ( movePlayed_t ) ) );
            *_start = START;
            log_insertAfter(*plog, _start);
        }
        /* reinitialise la liste */
        else {
            log_start( *plog );
            log_freeForward( *plog );
        }
    }
    
    ihm_loadLab( *plvl, MARGEX, MARGEY, W_TEXT );
    
    return (0);
    
}



void save( lvl_t* lvl, log_t* log, Type_game type ) {


    char buff[32] = {0};
    
    /* si il y a que le maillon start */
    if ( (*(Move*)((log->start)->data)) == (*(Move*)((log->end)->data)) ) {
        return ;
    }
    
    if ( type == SOLUTION ) {
        sprintf(buff, "../save/level%d_(f).sav", lvl->num);
    }
    else {
        sprintf(buff, "../save/level%d.sav", lvl->num);
    }
    log_save( log, buff );
    printf("Savegarde dans %s\n", buff);
}




void setVisu(visu_t* visu, int num, int cancel, int play, int push, int64_t t, int bagStocked, int nbrTarget) {
    static char t_num   [32];
    static char t_cancel[32];
    static char t_play  [32];
    static char t_push  [32];
    static char t_t     [32];
    static char t_bagStocked [32];
    static char t_vict[] = "VICTOIRE";

    visu[0].color = al_map_rgb(0, 0, 0);
    visu[1].color = al_map_rgb(0, 0, 255);
    visu[2].color = al_map_rgb(0, 0, 255);
    visu[3].color = al_map_rgb(0, 0, 255);
    visu[4].color = al_map_rgb(0, 0, 255);
    visu[5].color = al_map_rgb(0, 150, 0);
    visu[6].color = al_map_rgb(0, 150, 0);
    visu[0].size = BIG;
    visu[1].size = SMALL;
    visu[2].size = SMALL;
    visu[3].size = SMALL;
    visu[4].size = SMALL;
    visu[5].size = SMALL;
    visu[6].size = BIG;
    
    sprintf(t_num, "NIVEAU %d", num);
    visu[0].txt = t_num;
    
    sprintf(t_cancel, "Nombre d'annulations : %d", cancel);
    visu[1].txt = t_cancel;
    
    sprintf(t_play, "Nombre de coups : %d", play);
    visu[2].txt = t_play;
    
    sprintf(t_push, "Nombre de poussees : %d", push);
    visu[3].txt = t_push;
    
    sprintf(t_t, "Temps : %d", (int)t);
    visu[4].txt = t_t;
    
    sprintf(t_bagStocked, "Stock : %d/%d", bagStocked, nbrTarget);
    visu[5].txt = t_bagStocked;
    
    visu[6].txt = t_vict;

}



void reset_counters(int *checked, int *nbrCanceled, int *nbrPushed, int *nbrPlayed) {
    *checked = 0;
    *nbrCanceled = 0;
    *nbrPushed = 0;
    *nbrPlayed = 0;
    restartTime();
}






