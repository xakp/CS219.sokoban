/**
 * \file engine.c
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/06/2013
 *
 */


#include "engine.h"


static struct {
    uint16_t x;
    uint16_t y;
} position_Player;
/* pour simplifier le codage */
#define px position_Player.x
#define py position_Player.y

#define lvl(X, Y) lvl->dat[Y][X] 


/**
 * \fn static void foundPlayer(lvl_t* lvl)
 * \brief set position_Player.x et py position_Player.y
 * \param le niveau concerne
 * 
 */
static void foundPlayer(lvl_t* lvl) {
    int i, j;
    
    /* l'affiche dans le terminal */
    for (i=0; lvl->dat[i] != NULL ; i++ ) {
        for (j=0; lvl->dat[i][j] != lvl_NULL ; j++ ) {
            if ( lvl->dat[i][j] == lvl_PLAYER) {
                px = j;
                py = i;
                return ;
            }
        }
    }
}




/**
 * \fn int testMove( lvl_t*, Move );
 * \brief test la validite du coup
 * \param le niveau concerne
 * \param la direction
 * \retval 0 : coup illegal, !0 sinon
 * 
 */
int testMove( lvl_t* lvl, Move mo ) {
    /* la case problematique relative au joueur */
    int ox, oy;
    

    if ( lvl(px, py) != lvl_PLAYER) {
         foundPlayer( lvl);
    }
    
    switch ( mo ) {
    case LEFT:
        ox = -1;
        oy = +0;
        break ;
        
    case DOWN:
        ox = +0;
        oy = +1;
        break;
        
    case RIGHT:
        ox = +1;
        oy = +0;
        break ;
        
    case UP:
        ox = +0;
        oy = -1;
        break;
        
    default :
        break ;
    }
    
    /* legal move */
    if ( (lvl(px+ox, py+oy) & lvl_access) == 0 ||
        (lvl(px+ox, py+oy) == lvl_BAG && (lvl(px+ox*2, py+oy*2) & lvl_access ) ) )
    {
        
        return (1);
    }
    else
        return (0);
    
}




/**
 * \fn movePlayed* playMove( lvl_t* , Move );
 * \brief joue le coup et renvoi la donnee a allouee
 * \param le niveau concerne
 * \param la direction
 * \retval le movement a logge (NULL => coup illegal)
 * 
 */
movePlayed* playMove( lvl_t* lvl , Move mo )  {
    /* la case problematique relative au joueur */
    int ox, oy;
    movePlayed* move = NULL;
    
    assert( move = malloc( sizeof (movePlayed) ) );
    /* configure le move */
    *move = mo;
    

    switch ( mo ) {
    case LEFT:
        ox = -1;
        oy = +0;
        break ;
        
    case DOWN:
        ox = +0;
        oy = +1;
        break;
        
    case RIGHT:
        ox = +1;
        oy = +0;
        break ;
        
    case UP:
        ox = +0;
        oy = -1;
        break;
        
    default :
        break ;
    }
    
    /* un sac doit bouger */
    if ( lvl(px+ox, py+oy) == lvl_BAG ) {
        /* leve le bit de poid fort */
        *move |= 0x80; /*0b10000000*/
        
        /* move bag by player */
        /* move bag P+2 */
        lvl(px+ox*2, py+oy*2) |= lvl_BAG;
        /* delete bag P+1 */
        lvl(px+ox, py+oy) &= ~lvl_BAG;
    }

    
    /* add player P+1 */
    lvl(px+ox, py+oy) |= lvl_PLAYER;
    /* delete player P */
    lvl(px, py) &= ~lvl_PLAYER;
    
    return (move);
}




/**
 * \fn void revertMove( lvl_t*, movePlayed*  );
 * \brief annule le coup passe en param
 * \param le niveau concerne
 * \param le coup
 * 
 */
void revertMove( lvl_t* lvl, movePlayed* mo) {
    
    
}



/**
 * \fn void replayMove( lvl_t*, movePlayed*  );
 * \brief retablie le coup passe en param
 * \param le niveau concerne
 * \param le coup
 * 
 */
void replayMove( lvl_t* lvl, movePlayed* mo ) {
    
    
}



#undef px
#undef py