CC=g++
CFLAGS= -Wall
EXE=graph

all: graph.o graph.cpp
	rm -f $(EXE)
	$(CC) $(CFLAGS) graph.cpp -o $(EXE) 

test.o: graph.cpp graph.h
	$(CC) $(CFLAGS) -c graph.cpp

clean:
	rm -f *.o
	rm -f $(EXE)

