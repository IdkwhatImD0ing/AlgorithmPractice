CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
OBJECTS = avlt.o wordrange.o

wordrange: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o wordrange avlt.o wordrange.o
	
wordrange.o: wordrange.cpp avlt.h avlt.cpp
	$(CXX) -g $(CXXFLAGS) -c wordrange.cpp
	
avlt.o: avlt.cpp avlt.h
	$(CXX) -g $(CXXFLAGS) -c avlt.cpp
		
clean:
	rm -f *.o
	rm -f wordrange