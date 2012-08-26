CC = g++
OPT = -O2
LIBS = -lm
WALL = -Wall

all : hearding

cpp : hearding.o
	$(CC) $(WALL) $(OPT) -o cpp hearding.o $(LIBS)

hearding.o : hearding.cpp
	$(CC) $(OPT) -c hearding.cpp

clean: 
	rm *.o hearding
