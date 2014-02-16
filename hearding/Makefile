CFLAGS = -O3 -funroll-loops -g -Wall -ansi
CC = g++
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
PROG = giftwrapping
LINKFLAGS = -lm

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm $(OBJS) $(PROG)