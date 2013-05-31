

CC=gcc 
CFLAGS=-c -Wall -pedantic -Wno-long-long 

LD=gcc 
LFLAGS= 


MAKE=make

OBJ=main.o level.o

EXEC=./sokoban

# windows
ifdef SystemRoot
	RM=del 
else
	RM=rm -f 
endif


all: $(OBJ)
	$(LD) $(OBJ) $(LFLAGS) -o $(EXEC)

%o: %c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o
	$(RM) $(EXEC)

