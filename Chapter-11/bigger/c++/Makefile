CC = g++
OPT = -O2
WALL = -Wall
NAME = bigger

all: $(NAME)

$(NAME): $(NAME).o
	$(CC) -lm -lcrypt -O2 -pipe -o $(NAME) $(NAME).o

$(NAME).o:
	$(CC) $(OPT) -c $(NAME).cpp

clean: 
	rm *.o $(NAME)
