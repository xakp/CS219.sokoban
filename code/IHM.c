/**
 * \file IHM.c
 * \brief Mini-projet CS219 Sokoban
 * \author EYMARD Gabrielle - SCHLOTTERBECK Guillaume
 * \version 1.0
 * \date 03/06/2013
 *
 */


#include "IHM.h"

/**
  * @defgroup IHM
  * @{
  */



/**
 * \var static int _dimsprite = -1;
 * \brief dimention des sprite en pixels
 */
static int _dimsprite = -1;


/**
 * \var static ALLEGRO_BITMAP* spritesheet = NULL;
 * \brief pointeur sur la sprtiteshhep, globale mais protege
 */
static ALLEGRO_BITMAP* _spritesheet = NULL;



/**
 * \var static ALLEGRO_EVENT_QUEUE *keyboardQueue = NULL;
 * \brief 
 */
static ALLEGRO_EVENT_QUEUE *keyboardQueue = NULL;


/**
 * \var static ALLEGRO_EVENT_QUEUE *mouseQueue = NULL;
 * \brief 
 */
static ALLEGRO_EVENT_QUEUE *mouseQueue = NULL;


/**
 * \var static ALLEGRO_EVENT_QUEUE *displayQueue = NULL;
 * \brief 
 */
static ALLEGRO_EVENT_QUEUE *displayQueue = NULL;




/**
 * \fn ALLEGRO_DISPLAY* ihm_init(int w, int h, int flags)
 * \brief initilise tout
 * \retval le display
 * 
 */
ALLEGRO_DISPLAY* ihm_init(int w, int h, int flags) {
    ALLEGRO_DISPLAY *display;
    
    /* init */
    if ( !(al_init() && al_install_mouse() && al_install_keyboard()) ) {
        fprintf(stderr, "error init allegro or allegro's modules\n");
        return (NULL);
    }

    /* creer le display */
    al_set_new_display_flags(flags);
    display = al_create_display(w, h);
    
    /* teste la creation du display */
    if (display == NULL) {
        fprintf(stderr, "error to create display\n");
        return (NULL);
    }
    
    /* creer les 3 files d'evenement */
    keyboardQueue = al_create_event_queue();
    mouseQueue    = al_create_event_queue();
    displayQueue  = al_create_event_queue();
    
    /* teste les creations */
    if ( !(keyboardQueue && mouseQueue && displayQueue) ) {
        fprintf(stderr, "error to create event queue\n");
        al_destroy_display(display);
        return (NULL);
    }
    
    /* abonne les modules a leur file respective */
    al_register_event_source(keyboardQueue, al_get_keyboard_event_source());
    al_register_event_source(mouseQueue   , al_get_mouse_event_source());
    al_register_event_source(displayQueue , al_get_display_event_source(display));
    
    return display;
}



/**
 * \fn void ihm_close()
 * \brief 
 * \retval
 * 
 * \attention ne libere pas le lvl_t
 */
void ihm_close() {
    /* al_destroy_display(display); */
}



/**
 * \fn int ihm_loadSpriteSheet(char* path, int dimsprite)
 * \brief 
 * \retval
 * 
 */
int ihm_loadSpriteSheet(char* path, int dimsprite) {
    
    /* Load and create bitmaps with an alpha channel */
    al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ANY_32_WITH_ALPHA);
    
    /* Load some bitmap with alpha in it */
    _spritesheet = al_load_bitmap(path);
    
    if (_spritesheet != NULL ) {
        _dimsprite = dimsprite;
        return 0;
    }
    return (-1);
}



/**
 * \fn ihm_lab* ihm_loadLab(lvl_t* lvl, int margex, int margey)
 * \brief 
 * \retval
 * 
 */
ihm_lab* ihm_loadLab(lvl_t* lvl, int margex, int margey) {
    return NULL;
}



/**
 * \fn void ihm_closelab( ihm_lab* )
 * \brief 
 * \retval
 * 
 */
void ihm_closelab( ihm_lab*  lab) {
}



/**
 * \fn int ihm_drawSpriteInLab(ihm_lab* lab, int posx, int posy, Sprites sp)
 * \brief 
 * \retval
 * 
 */
int ihm_drawSpriteInLab(ihm_lab* lab, int posx, int posy, Sprites sp) {
    return 0;
}



/**
 * \fn int newkey( KEY_CODE* )
 * \brief 
 * \retval
 * 
 */
int newkey( KEY_CODE* key ) {
    ALLEGRO_EVENT event;
    if ( al_is_event_queue_empty(keyboardQueue) ) {
        return (0);
    }
    else {
        al_get_next_event(keyboardQueue, &event);
        
        if ( event.type == ALLEGRO_EVENT_KEY_CHAR ) {
            if (event.keyboard.keycode == (int)key) {
                return (1);
            }
        }
    }
    return (0);
}



/**
 * \fn int windowClosed()
 * \brief 
 * \retval
 * 
 */
int windowClosed() {
    ALLEGRO_EVENT event;
    if ( al_is_event_queue_empty(displayQueue) ) {
        return (0);
    }
    else {
        al_get_next_event(displayQueue, &event);
        
        if ( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
            return (1);
        }
    }
    return (0);
}



/**
 * \fn int mouseClicked(ihm_lab* , int*, int*)
 * \brief 
 * \retval
 * 
 */
int mouseClicked(ihm_lab* lab, int* posx, int* posy) {
    ALLEGRO_EVENT event;
    
    if ( al_is_event_queue_empty(mouseQueue) ) {
        return (0);
    }
    else {
        al_get_next_event(mouseQueue, &event);
        
        if ( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) {
            *posx = (event.mouse.x - (lab->margex*_dimsprite)) / _dimsprite;
            *posy = (event.mouse.y - (lab->margey*_dimsprite)) / _dimsprite;
            return (1);
        }
    }
    return (0);
}



/* endGroup IHM */
/** @} */ 

