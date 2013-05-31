

CC=gcc 
CFLAGS=-c -Wall -pedantic -I./allegro-5.0.9/include/ -I./allegro-5.0.9/build/include/ \
    -Wno-long-long

LD=gcc 
LFLAGS=-L./allegro-5.0.9/build/lib/ -lallegro -lallegro_main -lallegro_image -lallegro_memfile \
    -lallegro_primitives -lallegro_color -lallegro_font


MAKE=make

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


