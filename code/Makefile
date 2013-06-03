

CC=gcc 
CFLAGS=-c -Wall -pedantic -Wno-long-long -g 

LD=gcc 
LFLAGS= -lallegro -lallegro_main


MAKE=make

OBJ=main.o level.o IHM.o


# windows
ifdef SystemRoot
	RM=rm
	EXEC=sokoban.exe
else
	RM=rm -f 
	EXEC=sokoban
endif


all: $(OBJ)
	$(LD) $(OBJ) $(LFLAGS) -o $(EXEC)

%o: %c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(EXEC)


