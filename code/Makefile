

CC=gcc 
LD=gcc 
MAKE=make

OBJ=main.o level.o IHM.o

CFLAGS=-c -Wall -pedantic -Wno-long-long -g


# windows
ifdef SystemRoot
	RM=rm
	EXEC=sokoban.exe
	LFLAGS= -lallegro-5.0.9-md  -lallegro-5.0.9-md -lallegro_image-5.0.9-md -lallegro_ttf-5.0.9-md -lallegro_font-5.0.9-md
# linux
else
	shell export LD_LIBRARY_PATH=/usr/lib/:$LD_LIBRARY_PATH
	RM=rm -f 
	EXEC=sokoban
	LFLAGS= -lallegro -lallegro_image -lallegro_ttf -lallegro_font
endif


all: $(OBJ)
	$(LD) $^ $(LFLAGS) -o $(EXEC)
%o: %c
	$(CC) $^ $(CFLAGS) -o $@

tu: testsUnitaires.o log.o
	$(LD) $^ $(LFLAGS)


clean:
	$(RM) $(OBJ)
	$(RM) $(EXEC)


