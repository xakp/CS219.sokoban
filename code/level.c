/**
 * \file level.c
 * \brief Fichier source : Gestion des fichier *.lvl
 * \author SCHLOTTERBECK Guillaume - EYMARD Gabrielle
 * \version 1.0
 * \date 16/05/2013
 *
 */

#include "level.h"


/**
 * \addtogroup Level
 * \{
 */


/**
 * \var datafile
 * \brief Contient l'instance du fichier level.lvl ainsi que le nombre de niveaux
 * Cette variable est globale parce que toutes les fonctions de ce fichier ont besoin de ces informations.
 * Cette variable est static pour la proteger car elle est globale.
 *
 */
static struct datafile_t {
    char name[32];         /*!< Nom du fichier. */
    uint32_t nbrLvl;    /*!< Contient le nombre de niveaux. */
    FILE *fd;           /*!< Pointeur sur l'instance du fichier */
} datafile = {{0}, 0, NULL};



/**
 * \fn int8_t lvl_openFileLvl( char * )
 * \brief Ouvre le fichier de levels et configure datafile
 * \param [in] char *
 *  Nom du fichier contenant les niveaux a ouvrir
 * \retval int8_t
 * Renvoie 0 si OK, sinon, renvoie -1.
 * 
 */
int8_t lvl_openFileLvl( char *fileName )
{
    /* buffer pour lire les lignes */
    char buff[BUFFER_SIZE];
    
    if (fileName == NULL) {
        fprintf(stderr, "error: openFileLvl(): nom du fichier non renseigne.\n");
    }
    
    /* ouvre le fichier et test l'ouverture */
    datafile.fd = fopen(fileName, "r");
    if (datafile.fd == NULL) {
        fprintf(stderr, "error: openFileLvl(): nom du fichier non renseigne.\n");
    }
    strcpy(datafile.name, fileName);
    
    /* cherche le nombre de niveaux */
    while ( fgets(buff, BUFFER_SIZE, datafile.fd) != NULL ) {
    
        /* on cherche l'occurence de ";MAXLEVEL" */
        if ( strstr(buff, ";MAXLEVEL") != NULL ) {
            sscanf(buff, ";MAXLEVEL %u\n", &(datafile.nbrLvl));
            return (0);
        }
    }
    return (-1);
}


/**
 * \fn lvl_t* lvl_readLevel( int16_t num )
 * \brief Creer un objet lvl_t
 * \param [in] int16_t
 *  Le numero du niveau a lire.
 * \retval lvl_t * 
 *  Renvoie NULL si la lecture echoue, sinon renvoie le pointeur sur lvl_t
 */
lvl_t* lvl_readLevel( int16_t num )
{
    /* buffer pour lire les lignes */
    char buff[BUFFER_SIZE];
    /* contiendra le motif a rechercher */
    char motif[16];
    /* position du debut du niveau */
    fpos_t pos;
    uint16_t nbL = 0;
    uint16_t l;
    int playerFound = 0;
    uint16_t len;
    int i;
    lvl_t* lvl = NULL;
    assert( lvl = malloc( sizeof (lvl_t) ) );
    
    /* cree le motif pour rechercher le niveau */
    sprintf(motif, ";LEVEL %d\n", num);
    
    /* Se place au debut des niveaux */
    rewind(datafile.fd);
    
    /* cherche le numero du niveau */
    while ( fgets(buff, BUFFER_SIZE, datafile.fd) != NULL ) {
        /* on cherche l'occurence de ";LEVEL #" */
        if ( strstr(buff, motif) != NULL ) {
            break;
        }
    }
    if ( feof(datafile.fd) ) {
        fprintf(stderr, "error: readLevel(): fichier corrompu.\n");
        return NULL;
    }
    
    /* passe les commentaires du niveau (auteur...) */
    do {
        /* curseur au debut de la ligne */
        fgetpos(datafile.fd, &pos);
        
        /* le fichier s'est termine trop tot */
        if ( fgets(buff, BUFFER_SIZE, datafile.fd) == NULL ) {
            fprintf(stderr, "error: readLevel(): fichier corrompu.\n");
            return NULL;
        }
        /* c'est un commentaire : ca commence par un ';' */
    } while ( buff[0] == ';' );

    /* si on est la c'est qu'on a trouve une ligne valide */
    nbL++;

    /* compte le nombre de ligne dans le niveau */
    while ( fgets(buff, BUFFER_SIZE, datafile.fd) != NULL ) {
        if ( buff[0] == ';' )
            break;
        nbL++;
    }
    
    /* nbL contient le nombre de lignes +1 (pour la sentinelle) */
    assert( lvl->dat = malloc( (nbL+1) * sizeof (char*) ) );
    
    /* on se replace au debut du niveau */
    rewind(datafile.fd);
    fsetpos(datafile.fd, &pos);
    
    lvl->nbrTarget = 0;
    
    /* charge le niveau ligne par ligne */
    for (l=0 ; l<nbL ; l++) {
        /* on sait que la lecture est possible car on l'a deja faite */
        assert( fgets(buff, BUFFER_SIZE, datafile.fd) );
        
        len = strlen(buff);
        /* on alloue et verifie l'allocation de la ligne */
        assert( lvl->dat[l] = malloc( (len) * sizeof (lvl_cell) ) );

        /* on rempli la ligne */
        for (i=0 ; i<len ; i++) {
            lvl->dat[l][i] = lvl_NULL;
            switch ( buff[i] ) {
                case ENCODE_WALL:
                    lvl->dat[l][i] = lvl_WALL;
                    break;
                case ENCODE_TARGET:
                    lvl->dat[l][i] = lvl_TARGET;
                    lvl->nbrTarget = lvl->nbrTarget + 1;
                    break;
                case ENCODE_BAG:
                    lvl->dat[l][i] = lvl_BAG | lvl_GROUND;
                    break;
                case ENCODE_PLAYER:
                    lvl->dat[l][i] = lvl_PLAYER | lvl_GROUND;
                    playerFound = 1;
                    break;
                case ENCODE_BAG_TARGETED:
                    lvl->dat[l][i] = lvl_TARGET | lvl_BAG;
                    lvl->nbrTarget = lvl->nbrTarget + 1;
                    break;
                case ENCODE_GROUND:
                default:
                    lvl->dat[l][i] = lvl_GROUND;
                    break;
            
            }/* end switch */
        }/* end for */
        
        lvl->dat[l][len-1] = lvl_NULL;
        
    }/* end for */
    
    lvl->dat[nbL] = NULL;
    lvl->num = num;
    
    if (playerFound == 0) {
        lvl_closeLevel( lvl );
        return (0);
    }
    
    return (lvl);
}


/**
 * \fn int getNbrLvl()
 * \brief Renvoie le nombre de niveaux dans le fichier
 * \retval int
 * Le nombre de niveaux dans le fichier
 */
int getNbrLvl() {
    return (datafile.nbrLvl);
}



/**
 * \fn void lvl_closeFileLvl();
 * \brief Ferme le fichier de niveaux
 * 
 */
void lvl_closeFileLvl() {
    fclose(datafile.fd);
}




/**
 * \fn void lvl_closeLevel( lvl_t * )
 * \brief Libere le level
 * \param [in] lvl_t * 
 *  Level a liberer
 * 
 */
void lvl_closeLevel(lvl_t* lvl) {
    lvl_cell** l;

    if ( lvl == NULL )
        return ;

    l = lvl->dat;
    
    /* libere les lignes */
    while (*l) free( *(l++) );
    
    /* libere le tableau de pointeurs de lignes */
    free(lvl->dat);
    
    /* libere le lvl_t */
    free(lvl);
}

/**
 * \}
 */

