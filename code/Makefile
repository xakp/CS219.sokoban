

CC=gcc 
CFLAGS=-c -Wall -pedantic 

LD=gcc 
LFLAGS=

OBJ=main.o level.o

EXEC=./sokoban

# windows
ifdef SystemRoot
	RM = del /Q 
else
	ifeq ($(shell uname), Linux)
# linux
		RM = rm -f 
	endif
endif


all: $(OBJ)
	$(LD) $(OBJ) $(LFLAGS) -o $(EXEC)

%o: %c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o $(EXEC)