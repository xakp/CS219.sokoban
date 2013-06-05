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
    
    int wlvl;                           /*!< largeur du lvl en sprite */
    int hlvl;                           /*!< hauteur du lvl en sprite. */
    
    int dimText;                        /*!< largeur du text en nombre de sprite. */
    
    int dimSprite;                      /*!< dimention des sprite en pixels */
    ALLEGRO_BITMAP* spritesheet;        /*!< pointeur sur la sprtiteshhep, globale mais proteges */
    ALLEGRO_BITMAP** sprites;           /*!< tableau des sprites, globale mais proteges */
    
    ALLEGRO_EVENT_QUEUE *keyboardQueue; /*!< file pour les evenements clavier */
    ALLEGRO_EVENT_QUEUE *mouseQueue;    /*!< file pour les evenements sourie */
    ALLEGRO_EVENT_QUEUE *displayQueue;  /*!< file pour les evenements display */
    
    ALLEGRO_FONT *fontB;
    ALLEGRO_FONT *fontS;
    
} ihm_context = {NULL, NULL, NULL, 0, 0, 0, 0, 5, -1, NULL, NULL, NULL, NULL, NULL}; 
 

/**
 * \fn static int init_event()
 * \brief initilise les events
 * \retval 0 : ok
 * 
 */
static int init_event() {
    /* creer les 3 files d'evenement */
    ihm_context.keyboardQueue = al_create_event_queue();
    ihm_context.mouseQueue    = al_create_event_queue();
    ihm_context.displayQueue  = al_create_event_queue();
    
    /* teste les creations */
    if ( !(ihm_context.keyboardQueue && ihm_context.mouseQueue && ihm_context.displayQueue) ) {
        fprintf(stderr, "error to create event queue\n");
        al_destroy_display(ihm_context.display);
        al_shutdown_image_addon();
        return (-1);
    }
    
    /* abonne les modules a leur file respective */
    al_register_event_source(ihm_context.keyboardQueue, al_get_keyboard_event_source());
    al_register_event_source(ihm_context.mouseQueue   , al_get_mouse_event_source());
    al_register_event_source(ihm_context.displayQueue , al_get_display_event_source(ihm_context.display));

    return (0);
}


/**
 * \fn static int init_text(int sizeH, sizeL)
 * \brief la taille
 * \retval 0 : ok
 * 
 */
static int init_text(int sizeH, int sizeL) { 
    al_init_font_addon();
    al_init_ttf_addon();
    
    ihm_context.fontB = al_load_ttf_font("../data/font.ttf", sizeH, 0);
    ihm_context.fontS = al_load_ttf_font("../data/font.ttf", sizeL, 0);
    
    return ( ! ihm_context.fontB || ! ihm_context.fontS );
}
 

/**
 * \fn int ihm_init(int w, int h, int flags)
 * \brief initilise tout
 * \retval le display
 * 
 */
int ihm_init(int w, int h, int flags) {

    /* initialise allegro et installe correctement les addons */
    if ( !(al_init() && al_install_mouse() && al_install_keyboard() ) ) {
        fprintf(stderr, "error init allegro or allegro's modules\n");
        return (-1);
    }
    if ( !al_init_image_addon() ) {
        fprintf(stderr, "error init image module\n");
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
    
    /* init font, events */
    if ( init_event() || init_text(35, 20) ) {
        ihm_close();
        return (-1);
    }
    
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
    int i;

    al_unregister_event_source(ihm_context.keyboardQueue, al_get_keyboard_event_source());
    al_unregister_event_source(ihm_context.mouseQueue, al_get_mouse_event_source());
    al_unregister_event_source(ihm_context.displayQueue, al_get_display_event_source(ihm_context.display));
    
	al_destroy_event_queue(ihm_context.keyboardQueue);
	al_destroy_event_queue(ihm_context.mouseQueue);
	al_destroy_event_queue(ihm_context.displayQueue);

    al_destroy_display(ihm_context.display);
    
    if ( ihm_context.sprites != NULL ) {
        for (i=0 ; i<NBR_SPRITES ; i++) {
            al_destroy_bitmap( ihm_context.sprites[i] );
        }
    }
    if ( ihm_context.spritesheet != NULL ) 
        al_destroy_bitmap( ihm_context.spritesheet );
    if ( ihm_context.background != NULL ) 
        al_destroy_bitmap( ihm_context.background );
    
    al_destroy_font(ihm_context.fontB);
    al_destroy_font(ihm_context.fontS);
    
    
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_image_addon();
}



/**
 * \fn int ihm_loadSpriteSheet(char* path, int dimSprite)
 * \brief 
 * \retval
 * 
 */
int ihm_loadSpriteSheet(char* path, int dimSprite) {
    int i;
    
    /* Load and create bitmaps with an alpha channel */
    al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ANY_32_WITH_ALPHA);
    
    /* Load some bitmap with alpha in it */
    ihm_context.spritesheet = al_load_bitmap(path);
    
    if (ihm_context.spritesheet != NULL ) {
        ihm_context.dimSprite = dimSprite;
        
        ihm_context.sprites = (ALLEGRO_BITMAP**) malloc( NBR_SPRITES * sizeof (ALLEGRO_BITMAP*) );
        assert( ihm_context.sprites );
        
        for (i=0 ; i<NBR_SPRITES ; i++) {
            ihm_context.sprites[i] = 
                al_create_sub_bitmap(   ihm_context.spritesheet, /* l'image parente */
                                        ihm_context.dimSprite * ( i % 8 ), 
                                        ihm_context.dimSprite * ( i / 8 ), 
                                        ihm_context.dimSprite, ihm_context.dimSprite); /* largeur et hauteur */
            
            assert( ihm_context.sprites[i] != NULL );
        }
        
        
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
void ihm_loadLab(lvl_t* lvl, int margex, int margey, int dimText) {
    int l, c, w, h, L;
    char buff[32];
    lvl_cell cell;
    int meet_sentinel = 0;
    
    ihm_context.lvl = lvl;
    ihm_context.margex = margex;
    ihm_context.margey = margey;
    ihm_context.dimText = dimText;
    
    ihm_context.wlvl = 0;
    ihm_context.hlvl = 0;
    
    /* Largeur d'un sprite */
    L = ihm_context.dimSprite;
    
    /* l'affiche dans le terminal */
    for (l=0; lvl->dat[l] != NULL ; l++ ) {
        for (c=0; lvl->dat[l][c] != lvl_NULL ; c++ ) ;
        ihm_context.wlvl = (c > ihm_context.wlvl) ? c : ihm_context.wlvl;
    }
    ihm_context.hlvl = l;
    
    /* en nombre de sprite */
    w = ihm_context.wlvl + 2*(ihm_context.margex) + ihm_context.dimText;
    h = ihm_context.hlvl + 2*(ihm_context.margey);
    
    /* resize */
    al_resize_display( ihm_context.display, L*w, L*h );
    
    /* allou ll'image de fond */
    if ( ihm_context.background != NULL )
        al_destroy_bitmap( ihm_context.background );
    
    al_set_new_bitmap_flags( ALLEGRO_VIDEO_BITMAP ); /* carte grphique */
    al_set_new_bitmap_format( ALLEGRO_PIXEL_FORMAT_ANY_32_WITH_ALPHA  );
    ihm_context.background = al_create_bitmap(L*w, L*h);
    
    assert( ihm_context.background != NULL );
    
    /* creer l'image de fond qui ne change pas tout le long du niveau */
    al_set_target_bitmap( ihm_context.background );
    al_clear_to_color( al_map_rgb(0, 0, 0) );

    
    for (l=0; l<h ; l++ ) {
        for (c=0; c<w ; c++ ) {
            /* si on est dans le cadre */
            if ( (c<ihm_context.margex) || (c >= (ihm_context.margex + ihm_context.wlvl)) 
                || (l<ihm_context.margey) || (l >= (ihm_context.margey + ihm_context.hlvl)) ) {
                
                /* draw ground */
                al_draw_bitmap( ihm_context.sprites[ ihm_GROUND ], c * L, l * L , 0);
            }
            
            /* si on est dans le labyrinthe */
            else {
                cell = (ihm_context.lvl->dat[l-ihm_context.margey][c-ihm_context.margex]);
                
                /* si on rencontre la senti, on affiche des grounds jusqu'a la marge */
                if ( cell == lvl_NULL ) {
                    meet_sentinel = 1;
                }
                
                if ( meet_sentinel != 0 ) {
                    al_draw_bitmap( ihm_context.sprites[ ihm_GROUND ], c * L, l * L , 0);
                }
                else if (cell & lvl_WALL) {
                    al_draw_bitmap( ihm_context.sprites[ ihm_WALL ],   c * L, l * L , 0);
                }
                else if (cell & lvl_TARGET) {
                    al_draw_bitmap( ihm_context.sprites[ ihm_GROUND ], c * L, l * L , 0);               
                    al_draw_bitmap( ihm_context.sprites[ ihm_TARGET ], c * L, l * L , 0);
                }
                else { 
                    /* draw ground */
                    al_draw_bitmap( ihm_context.sprites[ ihm_GROUND ], c * L, l * L , 0);
                }
            }/* ! else */
        }/* ! for c */
        meet_sentinel = 0;
    }/* ! for l */
    
    /* Change le titre */
    sprintf(buff, "Sokoban - Niveau %d", lvl->num);
    al_set_window_title(ihm_context.display, buff);

}

/* *************************************************** */
/* ******************* dessin ************************ */ 
/* *************************************************** */


/**
 * \fn void ihm_drawBackground();
 * \brief 
 * \retval
 * 
 */
void ihm_drawBackground() {

    al_set_target_backbuffer(ihm_context.display);
    al_draw_bitmap(ihm_context.background, 0, 0, 0);
    
}



/**
 * \fn void ihm_drawMovable();
 * \brief dessine les sacs et le player
 * \retval le nombre de sac bien plasse
 * c'est cette fonction qui renvoi le nombre de sac bien place parce que c'est la 
 * derniere a parcourir le lvl apres que le coup soit joue.
 * on optimise donc le temps de calcul
 * 
 */
int ihm_drawMovable() {
    int l, c;
    int bagOK = 0;

    for (l=0; ihm_context.lvl->dat[l] != NULL ; l++ ) {
        for (c=0; ihm_context.lvl->dat[l][c] != lvl_NULL ; c++ ) {
        
            if ( ((ihm_context.lvl->dat[l][c]) & lvl_movable) != 0) {
                ihm_drawSpriteInLab(c+ihm_context.margex, l+ihm_context.margey, ihm_context.lvl->dat[l][c]);
                
                if ( ihm_context.lvl->dat[l][c] == lvl_bagOK ) {
                    bagOK++;
                }

            }
        }
    }
    return bagOK;
}




/**
 * \fn int ihm_drawSpriteInLab(ihm_lab* lab, int posx, int posy, Sprites sp)
 * \brief 
 * \retval
 * 
 */
void ihm_drawSpriteInLab(int posx, int posy, lvl_cell cell) {
    
    al_set_target_backbuffer(ihm_context.display);
    
    if (cell & lvl_BAG)    
        al_draw_bitmap( ihm_context.sprites[ ihm_BAG ], (posx) * ihm_context.dimSprite,  (posy) * ihm_context.dimSprite, 0);
    else 
        al_draw_bitmap( ihm_context.sprites[ ihm_PLAYER_DOWN ], (posx) * ihm_context.dimSprite,  (posy) * ihm_context.dimSprite, 0);

}





/**
 * \fn void ihm_drawInterface();
 * \brief 
 * \retval
 * 
 */
void ihm_drawInterface(visu_t* vtab, const int n) {
    int x, y, i;
    visu_t* v = vtab;
    
    al_set_target_backbuffer(ihm_context.display);
    
    x = (ihm_context.wlvl + 2*ihm_context.margex + ihm_context.dimText/2) * ihm_context.dimSprite;
    y = ihm_context.margey * ihm_context.dimSprite;
    
    for (i=0 ; i<n ; i++) {
        
        al_draw_text(  (v[i].size == BIG) ? ihm_context.fontB : ihm_context.fontS, v[i].color,      /* font et color */
                        x, y, ALLEGRO_ALIGN_CENTRE, v[i].txt); 
        
        y += al_get_font_line_height((v[i].size == BIG) ? ihm_context.fontB : ihm_context.fontS);
    }
}



/* *************************************************** */
/* ******************* evenements ******************** */ 
/* *************************************************** */


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
            *posx = (int)((event.mouse.x - (ihm_context.margex * ihm_context.dimSprite)) / ihm_context.dimSprite);
            *posy = (int)((event.mouse.y - (ihm_context.margey * ihm_context.dimSprite)) / ihm_context.dimSprite);
            return (1);
        }
    }
    return (0);
}



/* endGroup IHM */
/** @} */ 

