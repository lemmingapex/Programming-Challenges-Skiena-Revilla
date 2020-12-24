CFLAGS = -lm -O2 -pipe
CC = g++
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
PROG = fire-station

LINKFLAGS = -L.

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)
