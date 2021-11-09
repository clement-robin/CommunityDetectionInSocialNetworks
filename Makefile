CC=g++
CFLAGS= -Wall
EXE=graph

all: partie1.o partie2.o partie3.o 
	rm -f $(EXE)
	$(CC) $(CFLAGS) partie1.o partie2.o partie3.o -o $(EXE)
	./graph

partie1.o: partie1.cpp partie1.h
	$(CC) $(CFLAGS) -c partie1.cpp

partie2.o: partie2.cpp partie2.h
	$(CC) $(CFLAGS) -c partie2.cpp

partie3.o: partie3.cpp partie3.h
	$(CC) $(CFLAGS) -c partie3.cpp

clean:
	rm -f *.o
	rm -f $(EXE)

