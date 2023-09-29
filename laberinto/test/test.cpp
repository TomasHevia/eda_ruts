#include <iostream>

#include "maze/maze.hpp"
int main(int nargs, char** vargs){
	std::cout << "Laberinto resuelto con pila" << std::endl;
	maze::Maze laberintopila(21,21);
	laberintopila.print();
	laberintopila.solve_pila(0,0,20,0);
	laberintopila.print();

	std::cout << "Laberinto resuelto con cola" << std::endl;
	maze::Maze laberintocola(21,21);
	laberintocola.print();
	laberintocola.solve_cola(0,0,20,0);
	laberintocola.print();

	return 0;
}
