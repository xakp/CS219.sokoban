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
 * \brief Initialise tout
 * Globale et static : c'est le contexte graphique et evenementiel.
 * 
 */
 static struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER *timer;
    lvl_t* lvl;
    ALLEGRO_BITMAP* background;
    int margex;                         /*!< en nombre de cellules de GROUND. */
    int margey;                         /*!< en nombre de cellules de GROUND. */
    
    int wlvl;                           /*!< largeur du lvl en sprite */
    int hlvl;                           /*!< hauteur du lvl en sprite. */
    
    int dimText;                        /*!< largeur du text en nombre de sprite. */
    
    int dimSprite;                      /*!< dimension des sprites en pixels */
    ALLEGRO_BITMAP* spritesheet;        /*!< pointeur sur la sprtitesheet */
    ALLEGRO_BITMAP** sprites;           /*!< tableau des sprites */
    
    ALLEGRO_EVENT_QUEUE *keyboardQueue; /*!< file pour les evenements clavier */
    ALLEGRO_EVENT_QUEUE *mouseQueue;    /*!< file pour les evenements souris */
    ALLEGRO_EVENT_QUEUE *displayQueue;  /*!< file pour les evenements display */
  
    ALLEGRO_FONT *fontB;
    ALLEGRO_FONT *fontS;
    
} ihm_context = {NULL, NULL, NULL, NULL, 0, 0, 0, 0, 5, -1, NULL, NULL, NULL, NULL, NULL}; 
 

/**
 * \fn static int init_event()
 * \brief initialise les files d'evennements
 * \retval 0 : ok
 * 
 */
static int init_event() {
    /* cree les 3 files d'evenement */
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
 * \brief initialise le module texte graphique : font, ttf
 * \param les tailles des petite et grande polices
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
 * \brief iniatilise tout
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
    
    /* initialise le timer */
    ihm_context.timer = al_create_timer( 1 );
    if (ihm_context.timer == NULL) {
        fprintf(stderr, "error to create timer\n");
        return (-1);
    }
    
    /* cree le display */
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
 * \brief ferme tout les addons et libere les files d'events
 * \retval
 * 
 * \attention ne libere pas le lvl_t
 */
void ihm_close() {
    int i;
    
    /* Detache les modules de leur file d'event */
    al_unregister_event_source(ihm_context.keyboardQueue, al_get_keyboard_event_source());
    al_unregister_event_source(ihm_context.mouseQueue, al_get_mouse_event_source());
    al_unregister_event_source(ihm_context.displayQueue, al_get_display_event_source(ihm_context.display));
     
    /* detruit les files */
	al_destroy_event_queue(ihm_context.keyboardQueue);
	al_destroy_event_queue(ihm_context.mouseQueue);
	al_destroy_event_queue(ihm_context.displayQueue);

    /* ferme et libere le display */
    al_destroy_display(ihm_context.display);
    
    /* libere les bitmaps */
    if ( ihm_context.sprites != NULL ) {
        for (i=0 ; i<NBR_SPRITES ; i++) {
            al_destroy_bitmap( ihm_context.sprites[i] );
        }
    }
    if ( ihm_context.spritesheet != NULL ) 
        al_destroy_bitmap( ihm_context.spritesheet );
    if ( ihm_context.background != NULL ) 
        al_destroy_bitmap( ihm_context.background );
    
    
    /* libere les polices */
    al_destroy_font(ihm_context.fontB);
    al_destroy_font(ihm_context.fontS);
    
    /* ferme les addon */
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_image_addon();
}



/**
 * \fn int ihm_loadSpriteSheet(char* path, int dimSprite)
 * \brief Charge la spritesheet, et la decoupe en tableau de sprites
 * \retval
 * 
 */
int ihm_loadSpriteSheet(char* path, int dimSprite) {
    int i;
    
    /* Charge et cree les bitmap avec un cannal alpha */
    al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ANY_32_WITH_ALPHA);
    
    /* Charge la spritesheet */
    ihm_context.spritesheet = al_load_bitmap(path);
    
    if (ihm_context.spritesheet != NULL ) {
        ihm_context.dimSprite = dimSprite;
        
        /* Decoupe la spritesheet */
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
 * \brief Cree un bitmap contenant le fond du niveau, ce qui ne change pas 
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
    
    /* Determine les dimensions du niveau */
    for (l=0; lvl->dat[l] != NULL ; l++ ) {
        for (c=0; lvl->dat[l][c] != lvl_NULL ; c++ ) ;
        ihm_context.wlvl = (c > ihm_context.wlvl) ? c : ihm_context.wlvl;
    }
    ihm_context.hlvl = l;
    
    /* dimension de la fenetre en nombre de sprite */
    w = ihm_context.wlvl + 2*(ihm_context.margex) + ihm_context.dimText;
    h = ihm_context.hlvl + 2*(ihm_context.margey);
    
    /* Place correctement la fenetre */
    al_set_window_position( ihm_context.display, 100, 100);
    
    /* redimensione la fenetre */
    al_resize_display( ihm_context.display, L*w, L*h );
    
    /* alloue l'image de fond */
    if ( ihm_context.background != NULL )
        al_destroy_bitmap( ihm_context.background );
    
    al_set_new_bitmap_flags( ALLEGRO_VIDEO_BITMAP ); /* carte grphique */
    al_set_new_bitmap_format( ALLEGRO_PIXEL_FORMAT_ANY_32_WITH_ALPHA  );
    ihm_context.background = al_create_bitmap(L*w, L*h);
    
    assert( ihm_context.background != NULL );
    
    /* cree l'image de fond qui ne change pas pendant tout le niveau */
    al_set_target_bitmap( ihm_context.background );
    al_clear_to_color( al_map_rgb(0, 0, 0) );

    /* Pour chaque carreau */
    for (l=0; l<h ; l++ ) {
        for (c=0; c<w ; c++ ) {
            /* si on est dans le cadre */
            if ( (c<ihm_context.margex) || (c >= (ihm_context.margex + ihm_context.wlvl)) 
                || (l<ihm_context.margey) || (l >= (ihm_context.margey + ihm_context.hlvl)) ) {
                
                /* Dessine une terre */
                al_draw_bitmap( ihm_context.sprites[ ihm_GROUND ], c * L, l * L , 0);
            }
            
            /* si on est dans le labyrinthe */
            else {
                cell = (ihm_context.lvl->dat[l-ihm_context.margey][c-ihm_context.margex]);
                
                /* si on rencontre la sentinelle, on affiche des sols jusqu'a la marge */
                if ( cell == lvl_NULL ) {
                    meet_sentinel = 1;
                }
                
                /* Sinon on dessine le sprite correspondant a la cellule */
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
                    /* Dessine un sol */
                    al_draw_bitmap( ihm_context.sprites[ ihm_GROUND ], c * L, l * L , 0);
                }
            }/* ! else */
        }/* ! for c */
        meet_sentinel = 0;
    }/* ! for l */
    
    /* Change le titre de la fenetre en fonction du numero du niveau */
    sprintf(buff, "Sokoban - Niveau %d", lvl->num);
    al_set_window_title(ihm_context.display, buff);

}

/* *************************************************** */
/* ******************* dessin ************************ */ 
/* *************************************************** */


/**
 * \fn void ihm_drawBackground();
 * \brief afffiche le fond
 * \retval
 * 
 */
void ihm_drawBackground() {

    al_set_target_backbuffer(ihm_context.display);
    al_draw_bitmap(ihm_context.background, 0, 0, 0);
    
}



/**
 * \fn void ihm_drawMovable();
 * \brief dessine les sacs et le joueur
 * \retval le nombre de sacs bien plasses
 * C'est cette fonction qui renvoie le nombre de sacs bien places car c'est la 
 * derniere a parcourir le lvl apres que le coup soit joue.
 * on optimise donc un peu le temps de calcul
 * 
 */
int ihm_drawMovable() {
    int l, c;
    int bagStocked = 0;
    
    al_set_target_backbuffer(ihm_context.display);

    for (l=0; ihm_context.lvl->dat[l] != NULL ; l++ ) {
        for (c=0; ihm_context.lvl->dat[l][c] != lvl_NULL ; c++ ) {
        
            if ( ((ihm_context.lvl->dat[l][c]) & lvl_movable) != 0) {

                if (ihm_context.lvl->dat[l][c] & lvl_BAG)    
                    al_draw_bitmap( ihm_context.sprites[ ihm_BAG ], (c+ihm_context.margex) * ihm_context.dimSprite,  (l+ihm_context.margey) * ihm_context.dimSprite, 0);
                else 
                    al_draw_bitmap( ihm_context.sprites[ ihm_PLAYER_DOWN ], (c+ihm_context.margex) * ihm_context.dimSprite,  (l+ihm_context.margey) * ihm_context.dimSprite, 0);


                if ( ihm_context.lvl->dat[l][c] == lvl_bagStocked ) {
                    bagStocked++;
                }

            }
        }
    }
    return bagStocked;
}




/**
 * \fn void ihm_drawInterface();
 * \brief Dessine le texte
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



/**
 * \fn void ihm_drawIntro();
 * \brief Affiche une image avec les instruction de jeu 
 * 
 */
void ihm_drawIntro() {
    int W;
    int y = 15;
    int64_t t = 0;
    KEY_CODE key;
    ALLEGRO_COLOR colorText = al_map_rgb(255, 255, 255);
     
    W = al_get_display_width( ihm_context.display );
    
    restartTime();
    
    al_set_window_title(ihm_context.display, "Sokoban : Tutorial");
    al_set_window_position( ihm_context.display, 100, 100);
    al_set_target_backbuffer(ihm_context.display);
    
    while ( key != ALLEGRO_KEY_ENTER ) {
        if (t != get_time()) {
            t = get_time();
            colorText = al_map_rgb(rand()%100+150, rand()%100+150, rand()%100+150);
        }
        newkey(&key);
        al_rest(0.05);
        y = 0;

   
        al_set_target_backbuffer(ihm_context.display);
        al_clear_to_color( al_map_rgb(100, 100, 100) );
        
        y += 10;
        al_draw_text(ihm_context.fontB, colorText, W/2, y, ALLEGRO_ALIGN_CENTRE, 
            "Sokoban : SCHLOTTEYMARD");
        
        y += al_get_font_line_height( ihm_context.fontB ) + 10;
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "Z: Aller en haut");
            
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "Q: Aller a gauche");
            
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "S: Aller en bas");
            
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "D: Aller a droite");
            
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "E: Annuler un coup");
            
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "R: Retablir un coup");
            
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "T: Recommencer le niveau");
        
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "C: Montre votre solution pour ce niveau");
            
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "W: Sauvegarder le niveau");
            
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "X: Charger la sauvegarde de ce niveau");
            
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "Fleche de gauche: Niveau precedent");
            
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "Fleche de droite: Niveau suivant (si debloque bien sur)");
        
        y += al_get_font_line_height( ihm_context.fontS );
        al_draw_text(ihm_context.fontS, colorText, W/5, y, ALLEGRO_ALIGN_LEFT, 
            "Echap: Quitter");
        
        y += al_get_font_line_height( ihm_context.fontS )*1.5;
        al_draw_text(ihm_context.fontS, colorText, W/2, y, ALLEGRO_ALIGN_CENTRE, 
            "Appuyez sur [Enter] pour commencer...");
                
        al_flip_display();
    }

}



/* *************************************************** */
/* ******************* Evenements ******************** */ 
/* *************************************************** */


/**
 * \fn int newkey( KEY_CODE* )
 * \brief Les evenements clavier
 * \param [out] KEY_CODE * 
 * la touche pressee
 * \retval int
 * 1 si une touche a ete pressee, sinon 0
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
 * \brief Informe si la croix a ete cliquee
 * \retval int
 * 1 si la croix a ete cliquee, sinon 0
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
 * \brief Les evenements souris
 * \param [out] int * Absisse du clique
 * \param [out] int * ordonne du clique
 * \retval int
 * 1 s'il y a eu un clique, sinon 0
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


/**
 * \fn int get_time()
 * \brief Renvoie le nombre de seconde depuis le dernier restartTime()
 * \retval int64_t le nombre de seconde depuis le dernier restartTime()
 * 
 */
int64_t get_time() {
    
    return ( al_get_timer_count(ihm_context.timer) );
}

/**
 * \fn int restartTime()
 * \brief Demarre ou redemarre le timer * 
 */
void restartTime() {
    al_set_timer_count(ihm_context.timer, 0);
    
    if ( !al_get_timer_started( ihm_context.timer ) ) {
        al_start_timer( ihm_context.timer );
    }
}


/**
 * \fn int stopTime()
 * \brief Arrete le timer
 * 
 */
void stopTime() {
    al_stop_timer( ihm_context.timer );
}


/* endGroup IHM */
/** @} */ 

