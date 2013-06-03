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
 * \struct ihm_context
 * \brief initilise tout
 * globale et static. c'est le contexte graphique et evenemenciel.
 * 
 */
 static struct {
    ALLEGRO_DISPLAY* display;
    lvl_t* lvl;
    ALLEGRO_BITMAP* background;
    int margex;                         /*!< en nombre de cellules de GROUND. */
    int margey;                         /*!< en nombre de cellules de GROUND. */
    
    int dimsprite;                      /*!< dimention des sprite en pixels */
    ALLEGRO_BITMAP* spritesheet;        /*!< pointeur sur la sprtiteshhep, globale mais proteges */
    
    ALLEGRO_EVENT_QUEUE *keyboardQueue; /*!< file pour les evenements clavier */
    ALLEGRO_EVENT_QUEUE *mouseQueue;    /*!< file pour les evenements sourie */
    ALLEGRO_EVENT_QUEUE *displayQueue;  /*!< file pour les evenements display */
    
} ihm_context = {NULL, NULL, NULL, 0, 0, -1, NULL, NULL, NULL, NULL}; 
 




/**
 * \fn int ihm_init(int w, int h, int flags)
 * \brief initilise tout
 * \retval le display
 * 
 */
int ihm_init(int w, int h, int flags) {

    /* init */
    if ( !(al_init() && al_install_mouse() && al_install_keyboard() && al_init_image_addon() ) ) {
        fprintf(stderr, "error init allegro or allegro's modules\n");
        return (-1);
    }

    /* creer le display */
    al_set_new_display_flags(flags);
    ihm_context.display = al_create_display(w, h);
    
    /* teste la creation du display */
    if (ihm_context.display == NULL) {
        fprintf(stderr, "error to create display\n");
        return (-1);
    }
    
    /* creer les 3 files d'evenement */
    ihm_context.keyboardQueue = al_create_event_queue();
    ihm_context.mouseQueue    = al_create_event_queue();
    ihm_context.displayQueue  = al_create_event_queue();
    
    /* teste les creations */
    if ( !(ihm_context.keyboardQueue && ihm_context.mouseQueue && ihm_context.displayQueue) ) {
        fprintf(stderr, "error to create event queue\n");
        al_destroy_display(ihm_context.display);
        return (-1);
    }
    
    /* abonne les modules a leur file respective */
    al_register_event_source(ihm_context.keyboardQueue, al_get_keyboard_event_source());
    al_register_event_source(ihm_context.mouseQueue   , al_get_mouse_event_source());
    al_register_event_source(ihm_context.displayQueue , al_get_display_event_source(ihm_context.display));
    
    return (0);
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
    ihm_context.spritesheet = al_load_bitmap(path);
    
    if (ihm_context.spritesheet != NULL ) {
        ihm_context.dimsprite = dimsprite;
        return (0);
    }
    return (-1);
}



/**
 * \fn void ihm_loadLab(lvl_t* lvl, int margex, int margey)
 * \brief 
 * \retval
 * 
 */
void ihm_loadLab(lvl_t* lvl, int margex, int margey) {
    ihm_context.lvl = lvl;
    ihm_context.margex = margex;
    ihm_context.margey = margey;
    
    /* resize en condition etc... */
}



/**
 * \fn int ihm_drawSpriteInLab(ihm_lab* lab, int posx, int posy, Sprites sp)
 * \brief 
 * \retval
 * 
 */
int ihm_drawSpriteInLab(int posx, int posy, Sprites sp) {
    
    al_set_target_backbuffer(ihm_context.display);
    al_draw_bitmap(ihm_context.spritesheet, 0, 0, 0);
    
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
    if ( al_is_event_queue_empty(ihm_context.keyboardQueue) ) {
        return (0);
    }
    else {
        al_get_next_event(ihm_context.keyboardQueue, &event);
        
        if ( event.type == ALLEGRO_EVENT_KEY_CHAR ) {
            *key = event.keyboard.keycode;
            return (1);
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
    if ( al_is_event_queue_empty(ihm_context.displayQueue) ) {
        return (0);
    }
    else {
        al_get_next_event(ihm_context.displayQueue, &event);
        
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
int mouseClicked(int* posx, int* posy) {
    ALLEGRO_EVENT event;
    
    if ( al_is_event_queue_empty(ihm_context.mouseQueue) ) {
        return (0);
    }
    else {
        al_get_next_event(ihm_context.mouseQueue, &event);
        
        if ( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) {
            *posx = (int)((event.mouse.x - (ihm_context.margex * ihm_context.dimsprite)) / ihm_context.dimsprite);
            *posy = (int)((event.mouse.y - (ihm_context.margey * ihm_context.dimsprite)) / ihm_context.dimsprite);
            return (1);
        }
    }
    return (0);
}



/* endGroup IHM */
/** @} */ 

