CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

OBJECTS = queenlist.o nqueens.o

nqueen: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o nqueens queenlist.o nqueens.o
	
nqueen.o: nqueen.cpp queenlist.h queenlist.cpp
	$(CXX) -g $(CXXFLAGS) -c nqueen.cpp
	
queenlist.o: queenlist.cpp queenlist.h
	$(CXX) -g $(CXXFLAGS) -c queenlist.cpp
	
clean:
	rm -f *.o
	rm nqueens