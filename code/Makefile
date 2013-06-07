
# Les outils
CC=gcc 
LD=gcc 

# Les objets a obtenir
OBJ=level.o IHM.o log.o engine.o

# Les options de compilation
CFLAGS=-c -Wall -pedantic -Wno-long-long 


# windows
ifdef SystemRoot
	RM=rm
    # Les noms des executables de sortie
	EXEC=sokoban.exe
	EXEC_TU=a.exe
    # Les options de linkage
	LFLAGS= -lallegro-5.0.9-md  -lallegro-5.0.9-md -lallegro_image-5.0.9-md -lallegro_ttf-5.0.9-md -lallegro_font-5.0.9-md
# linux
else
    # On ajoute le repertoir d'installation d'allegro dans LD_LIBRARY_PATH
    # car sur notre version de linux, cette variable d'environnement est vide !
	shell export LD_LIBRARY_PATH=/usr/lib/:$LD_LIBRARY_PATH
	RM=rm -f 
    # Les noms des executables de sortie
	EXEC=sokoban
	EXEC_TU=a.out
    # Les options de linkage
	LFLAGS= -lallegro -lallegro_image -lallegro_ttf -lallegro_font
endif


# Construit le programme
all: $(OBJ) main.o 
	$(LD) $^ $(LFLAGS) -o $(EXEC)

# Regle pour compiler les fichiers sources en objets
%o: %c
	$(CC) $^ $(CFLAGS) -o $@

# Construire le programme de teste unitaire
tu: $(OBJ) testsUnitaires.o
	$(LD) $^ $(LFLAGS) -o $(EXEC_TU)


clean:
	$(RM) $(OBJ)
	$(RM) $(EXEC)
	$(RM) $(EXEC_TU) testsUnitaires.o


