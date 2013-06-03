

CC=gcc 
CFLAGS=-c -Wall -pedantic -Wno-long-long

LD=gcc 
LFLAGS= -lallegro-5.0.9-md  -lallegro-5.0.9-md -lallegro_image-5.0.9-md


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


