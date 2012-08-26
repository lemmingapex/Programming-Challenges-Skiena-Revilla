CC = g++
OPT = -O3
LIBS = -lm
WALL = -Wall

all : cpp

cpp : cpp.o
	$(CC) $(WALL) $(OPT) -o cpp cpp.o $(LIBS)

cpp.o : cpp.cpp
	$(CC) $(OPT) -c cpp.cpp

clean: 
	rm *.o cpp
