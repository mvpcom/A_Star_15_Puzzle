all : 15puzzle 

8puzzle : 15puzzle.cpp stlastar.h
	g++ -Wall 15puzzle.cpp -o 8puzzle



