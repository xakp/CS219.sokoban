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
 * \brief 
 * 
 */
static struct datafile_t {
    char *name;         /*!< Nom du fichier. */
    uint32_t nbrLvl;    /*!< Contient le numero du niveau. */
    FILE *fd;           /*!< Instance du fichier */
    fpos_t lvlCur;      /*!< Indique le debut des niveau. */
} datafile = {NULL, 0, NULL};



/**
 * \fn uint8_t openFileLvl( char *file );
 * \brief ouvre le fichier de levels
 * 
 */
int8_t openFileLvl( char *file )
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
            fgetpos( datafile.fd, &(datafile.lvlCur) );
            return (0);
        }
    }
    return (-1);
}


/**
 * \fn Level* readLevel( char *file, uint16_t num );
 * \brief Creer un objet %Level
 * 
 * C'est tres pratique !!
 */
Level* readLevel( int16_t num )
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
    Level* lvl = NULL;
    assert( lvl = malloc( sizeof (Level) ) );
    
    /* creer le motif pour rechercher le niveau */
    sprintf(motif, ";LEVEL %d\n", num);
    
    /* Se place au debut des niveaux */
    fsetpos(datafile.fd, &(datafile.lvlCur));
    
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
    fsetpos(datafile.fd, &pos);
        
    /* charge le niveau ligne par ligne */
    for (l=0 ; l<nbL ; l++) {
        /* on sait que la lecture est possible car on la deja fait */
        assert( fgets(buff, BUFFER_SIZE, datafile.fd) );
        
        len = strlen(buff);
        /* on allou et verivie l'allocation de la ligne */
        assert( lvl->dat[l] = malloc( (len) * sizeof (char) ) );
        
        /* on remplie la ligne */
        buff[len-1] = '\0';
        strcpy(lvl->dat[l], buff);
    }
    
    lvl->dat[nbL] = NULL;
    lvl->num = num;
    
    return (lvl);
}




/**
 * \fn void closeFileLvl();
 * \brief ferme le fichier de levels
 * 
 */
void closeFileLvl() {
    fclose(datafile.fd);
}

/**
 * \fn void closeLevel();
 * \brief Libere le level
 * \param Level a liberer
 * 
 */
void closeLevel(Level* lvl) {
    char** l;
    l = lvl->dat;
    
    /* libere les lignes */
    while (*l) free( *(l++) );
    
    /* libere le tableau de pointeur de lignes */
    free(lvl->dat);
    
    /* libere le lvl */
    free(lvl);
}


