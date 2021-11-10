CC=g++
CFLAGS= -Wall
EXE=graph

all: graph.o bronkerbosch.o partie3.o 
	rm -f $(EXE)
	$(CC) $(CFLAGS) graph.o bronkerbosch.o partie3.o -o $(EXE)
	./$(EXE)
partie1.o: graph.cpp graph.h
	$(CC) $(CFLAGS) -c graph.cpp

bronkerbosch.o: bronkerbosch.cpp bronkerbosch.h
	$(CC) $(CFLAGS) -c bronkerbosch.cpp

partie3.o: partie3.cpp partie3.h
	$(CC) $(CFLAGS) -c partie3.cpp

clean:
	rm -f *.o
	rm -f $(EXE)

