# Makefile
CXX := g++
CXXFLAGS := -std=c++17

main:   build run

build:  clean cleangch
	$(CXX) $(CXXFLAGS) -o parser src/main.cpp

out:
	$(CXX) $(CXXFLAGS) -c src/.cpp src/*.h

run:
	./parser

clean:
	rm -f *.o src/*.gch out

cleangch:
	rm -f src/*.gch

