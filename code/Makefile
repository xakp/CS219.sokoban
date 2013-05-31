

CC=gcc 
CFLAGS=-c -Wall -pedantic -Wno-long-long 

LD=gcc 
LFLAGS= 


MAKE=make

OBJ=main.o level.o

EXEC=./sokoban

# windows
ifdef SystemRoot
	RM = del 
else
	ifeq ($(shell uname), Linux)
# linux
		RM = rm -f 
	endif
endif

#linux
	ifndef SystemRoot
	export LD_LIBRARY_PATH=LD_LIBRARY_PATH:
	endif


all: $(OBJ)
	$(LD) $(OBJ) $(LFLAGS) -o $(EXEC)

%o: %c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o $(EXEC)


install_allegro:
	cd ./allegro-5.0.9/build/ && sudo $(MAKE) install


