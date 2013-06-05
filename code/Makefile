

CC=gcc 
LD=gcc 
MAKE=make

OBJ=level.o IHM.o log.o engine.o

CFLAGS=-c -Wall -pedantic -Wno-long-long 


# windows
ifdef SystemRoot
	RM=rm
	EXEC=sokoban.exe
	EXEC_TU=a.exe
	LFLAGS= -lallegro-5.0.9-md  -lallegro-5.0.9-md -lallegro_image-5.0.9-md -lallegro_ttf-5.0.9-md -lallegro_font-5.0.9-md
# linux
else
	shell export LD_LIBRARY_PATH=/usr/lib/:$LD_LIBRARY_PATH
	RM=rm -f 
	EXEC=sokoban
	EXEC_TU=a.out
	LFLAGS= -lallegro -lallegro_image -lallegro_ttf -lallegro_font
endif


all: $(OBJ) main.o 
	$(LD) $^ $(LFLAGS) -o $(EXEC)
%o: %c
	$(CC) $^ $(CFLAGS) -o $@

tu: $(OBJ) testsUnitaires.o
	$(LD) $^ $(LFLAGS) -o $(EXEC_TU)


clean:
	$(RM) $(OBJ)
	$(RM) $(EXEC)
	$(RM) $(EXEC_TU) testsUnitaires.o


