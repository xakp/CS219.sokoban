/**
 * \file level.c
 * \brief Mini-projet CS210
 * \author SCHLOTTERBECK Guillaume - EYMARD Gabrielle
 * \version 1.0
 * \date 16/05/2013
 *
 */

#include "level.h"

/**
 * \struct Datafile
 * \brief static....
 * 
 */
static struct datafile_t {
    char *name;         /*!< Nom du fichier. */
    uint32_t nbrLvl;    /*!< Contient le numero du niveau. */
    FILE *fd;           /*!< Instance du fichier */
} datafile = {NULL, 0, NULL};



/**
 * \fn int8_t lvl_openFileLvl( char *file );
 * \brief ouvre le fichier de levels
 * 
 */
int8_t lvl_openFileLvl( char *file )
{
    /* buffer pour lire les lignes */
    char buff[BUFFER_SIZE];

    if (file == NULL) {
        fprintf(stderr, "error: openFileLvl(): nom du fichier non renseigne.\n");
    }
    
    datafile.fd = fopen(file, "r");
    if (datafile.fd == NULL) {
        fprintf(stderr, "error: openFileLvl(): nom du fichier non renseigne.\n");
    }
    datafile.name = file;
    
    /* cherche le nombre de niveau */
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
 * \fn lvl_t* readLevel( char *file, uint16_t num );
 * \brief Creer un objet %Level
 * 
 * C'est tres pratique !!
 */
lvl_t* lvl_readLevel( int16_t num )
{
    /* buffer pour lire les lignes */
    char buff[BUFFER_SIZE];
    /* contiendra le motif a rechercher */
    char motif[16];
    /* positrion du debut du niveau */
    fpos_t pos;
    uint16_t nbL = 0;
    uint16_t l;
    uint16_t len;
    int i;
    lvl_t* lvl = NULL;
    assert( lvl = malloc( sizeof (lvl_t) ) );
    
    /* creer le motif pour rechercher le niveau */
    sprintf(motif, ";LEVEL %d\n", num);
    
    /* Se place au debut des niveaux */
    rewind(datafile.fd);
    
    /* cherche le numero du niveau */
    while ( fgets(buff, BUFFER_SIZE, datafile.fd) != NULL ) {
        /* on cherche l'occurence de ";LEVEL XX" */
        if ( strstr(buff, motif) != NULL ) {
            break;
        }
    }
    if ( feof(datafile.fd) ) {
        fprintf(stderr, "error: readLevel(): fichier corrompu.\n");
        return NULL;
    }
    
    /* passe les commentaire du niveau (auteur...) */
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

    /* si on est la c'est qu'on a trouver une ligne valide */
    nbL++;

    /* compt le nombre de ligne dans le niveau */
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
        /* on sait que la lecture est possible car on la deja fait */
        assert( fgets(buff, BUFFER_SIZE, datafile.fd) );
        
        len = strlen(buff);
        /* on allou et verivie l'allocation de la ligne */
        assert( lvl->dat[l] = malloc( (len) * sizeof (lvl_cell) ) );

        /* on remplie la ligne */
        for (i=0 ; i<len ; i++) {
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
    
    return (lvl);
}


int getNbrLvl() {

    return (datafile.nbrLvl);

}



/**
 * \fn void lvl_closeFileLvl();
 * \brief ferme le fichier de levels
 * 
 */
void lvl_closeFileLvl() {
    fclose(datafile.fd);
}




/**
 * \fn void lvl_closeLevel();
 * \brief Libere le level
 * \param Level a liberer
 * 
 */
void lvl_closeLevel(lvl_t* lvl) {
    lvl_cell** l;

    if ( lvl == NULL )
        return ;

    l = lvl->dat;
    
    /* libere les lignes */
    while (*l) free( *(l++) );
    
    /* libere le tableau de pointeur de lignes */
    free(lvl->dat);
    
    /* libere le lvl */
    free(lvl);
}


