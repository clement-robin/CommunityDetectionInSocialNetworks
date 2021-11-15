CC=g++
CFLAGS= -Wall
EXE=graph

all: graph.o bronkerbosch.o partie3.o main.cpp
	rm -f $(EXE)
	$(CC) $(CFLAGS) graph.o bronkerbosch.o partie3.o main.cpp -o $(EXE)

exe: graph.o bronkerbosch.o partie3.o main.cpp
	clear
	./$(EXE)

graph.o: graph.cpp graph.h
	$(CC) $(CFLAGS) -c graph.cpp

bronkerbosch.o: bronkerbosch.cpp bronkerbosch.h
	$(CC) $(CFLAGS) -c bronkerbosch.cpp

partie3.o: partie3.cpp partie3.h
	$(CC) $(CFLAGS) -c partie3.cpp

clean:
	rm -f *.o
	rm -f $(EXE)