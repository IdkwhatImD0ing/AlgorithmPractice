CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
OBJECTS = graph.o sixdegrees.o linkedlist.o

sixdegrees: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o sixdegrees graph.o linkedlist.o sixdegrees.o

sixdegrees.o: sixdegrees.cpp graph.h linkedlist.h graph.cpp
	$(CXX) -g $(CXXFLAGS) -c sixdegrees.cpp
	
graph.o: graph.cpp graph.h
	$(CXX) -g $(CXXFLAGS) -c graph.cpp
	
linkedlist.o: linkedlist.cpp linkedlist.h
	$(CXX) -g $(CXXFLAGS) -c linkedlist.cpp

clean:
	rm -f *.o
	rm -f sixdegrees