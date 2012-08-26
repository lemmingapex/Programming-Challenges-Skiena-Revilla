CC = g++
OPT = -O2
LIBS = -lm
WALL = -Wall

all : moth

cpp : moth.o
	$(CC) $(WALL) $(OPT) -o cpp moth.o $(LIBS)

moth.o : moth.cpp
	$(CC) $(OPT) -c moth.cpp

clean: 
	rm *.o moth
