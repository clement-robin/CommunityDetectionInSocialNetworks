CC=g++
CFLAGS= -Wall
EXE=graph

all: test.o test.cpp
	rm -f $(EXE)
	$(CC) $(CFLAGS) test.cpp -o $(EXE) 

test.o: test.cpp test.h
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm -f *.o
	rm -f $(EXE)

