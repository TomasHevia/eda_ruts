#include "maze/maze.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <vector>

namespace maze{

const unsigned char Maze::WALL  = '@';
const unsigned char Maze::EMPTY = '-';
const int Maze::NORTH= 0;
const int Maze::SOUTH= 1;
const int Maze::EAST= 2;
const int Maze::WEST= 3;
Maze::Maze(int h, int w):
		height(h),
		width(w),
		grid(nullptr){
	dir[0] = NORTH;
	dir[1] = SOUTH;
	dir[2] = EAST;
	dir[3] = WEST;
	std::srand(time(0));
	generate_maze(h, w);

}

void Maze::reset_maze(int h, int w){
	delete_maze();
	height = h;
	width= w;
	grid = new uchar*[height];
	for (int i = 0; i < height; i++){
		grid[i] = new uchar[width];
		for (int j = 0; j < width; j++){
			grid[i][j] = 1;
		}
	}
}

void Maze::generate_maze(int h, int w){
	reset_maze(h, w);
	visit(0,0);
}

void Maze::delete_maze(){
	if (grid != nullptr){
		for (int i = 0; i < height; i++){
			delete[] grid[i];
		}
		delete[] grid;
	}
}

void Maze::shuffle_dir(){
	for (int i = 0; i < 4; i++){
		int r = std::rand() & 3;
		int aux = dir[r];
		dir[r] = dir[i];
		dir[i] = aux;
	 }
}
bool Maze::inRange(int i, int j){
	return ((i >= 0) && (i< height) && (j >= 0) && (j< width));
}

void Maze::visit(int i, int j){

	int dx  = 0;
	int dy = 0;
	int i_next = 0;
	int j_next = 0;
	grid[i][j] = 0;
	shuffle_dir();
	//std::cout << dir[0] << " " << dir[1] << " " << dir[2] << " "<< dir[3] << std::endl;
	for(int k = 0; k <  4; k++){
		//std::cout << dir[k] << std::endl;
		if (dir[k] == NORTH){
			dy = -1;
			dx = 0;
		}
		else if (dir[k] == SOUTH){
			dy = 1;
			dx = 0;
		}
		else if (dir[k] == EAST){
			dy = 0;
			dx = 1;
		}
		else if (dir[k] == WEST){
			dy = 0;
			dx = -1;
		}
		i_next = i + (dy<<1);
		j_next = j + (dx<<1);
		if (inRange(i_next, j_next) && grid[i_next][j_next] == 1){
			grid[i_next - dy][j_next - dx] = 0;
			visit(i_next, j_next);

		}
	}
}

void Maze::print(){
	char LIMIT = '=';
	std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
	for (int i = 0; i < height; i++){
		std::cout << "|";
		for (int j = 0; j < width; j++){
			if (grid[i][j] == 0) {
				std::cout << EMPTY;
			}
			if(grid[i][j] == 1) {
				std::cout << WALL;
			}
			if(grid[i][j] == 2) {
				std::cout << EMPTY;
			}
			if(grid[i][j] == 3) {
				std::cout << "x";
			}
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
}

std::vector<std::pair<int,int>> Maze::solve_pila(int f1, int c1, int f2, int c2){
	std::stack<std::pair<int,int>> pila;
	pila.push({f1,c1});
	std::vector<std::pair<int,int>> camino;
	std::pair<int,int> actual;
	while(!pila.empty()){
		actual = pila.top();
		pila.pop();
		if(actual.first == f2 && actual.second == c2){
			while(actual.first != f1 || actual.second != c1){
				camino.push_back(actual);
				grid[actual.first][actual.second] = 3;
				std::pair<int,int> previo;
				if(inRange(actual.first-1,actual.second) && grid[actual.first-1][actual.second] == 2){
					previo = {actual.first-1,actual.second};
					actual = previo;
				}
				else if(inRange(actual.first,actual.second-1) && grid[actual.first][actual.second-1] == 2){
					previo = {actual.first,actual.second-1};
					actual = previo;
				}
				else if(inRange(actual.first+1,actual.second) && grid[actual.first+1][actual.second] == 2){
					previo = {actual.first+1,actual.second};
					actual = previo;
				}
				else if(inRange(actual.first,actual.second+1) && grid[actual.first][actual.second+1] == 2){
					previo = {actual.first,actual.second+1};
					actual = previo;
				}
			
			}
			camino.push_back(actual);
			std::reverse(camino.begin(),camino.end());
			return camino;
		}
		if(grid[actual.first][actual.second] == 0){
			grid[actual.first][actual.second] = 2;
			if(inRange(actual.first-1,actual.second) && grid[actual.first-1][actual.second] == 0){
				pila.push({actual.first-1,actual.second});
			}
			if(inRange(actual.first,actual.second-1) && grid[actual.first][actual.second-1] == 0){
				pila.push({actual.first,actual.second-1});
			}
			if(inRange(actual.first+1,actual.second) && grid[actual.first+1][actual.second] == 0){
				pila.push({actual.first+1,actual.second});
			}
			if(inRange(actual.first,actual.second+1) && grid[actual.first][actual.second+1] == 0){
				pila.push({actual.first,actual.second+1});
			}
			
		}
	}
}
std::vector<std::pair<int,int>> Maze::solve_cola(int f1, int c1, int f2, int c2){
	std::queue<std::pair<int,int>> cola;
	cola.push({f1,c1});
	std::vector<std::pair<int,int>> camino;
	std::pair<int,int> actual;
	while(!cola.empty()){
		actual = cola.front();
		cola.pop();
		if(actual.first == f2 && actual.second == c2){
			while(actual.first != f1 || actual.second != c1){
				camino.push_back(actual);
				grid[actual.first][actual.second] = 3;
				std::pair<int,int> previo;
				if(inRange(actual.first-1,actual.second) && grid[actual.first-1][actual.second] == 2){
					previo = {actual.first-1,actual.second};
					actual = previo;
				}
				else if(inRange(actual.first,actual.second-1) && grid[actual.first][actual.second-1] == 2){
					previo = {actual.first,actual.second-1};
					actual = previo;
				}
				else if(inRange(actual.first+1,actual.second) && grid[actual.first+1][actual.second] == 2){
					previo = {actual.first+1,actual.second};
					actual = previo;
				}
				else if(inRange(actual.first,actual.second+1) && grid[actual.first][actual.second+1] == 2){
					previo = {actual.first,actual.second+1};
					actual = previo;
				}
			
			}
			camino.push_back(actual);
			std::reverse(camino.begin(),camino.end());
			return camino;
		}
		if(grid[actual.first][actual.second] == 0){
			grid[actual.first][actual.second] = 2;
			if(inRange(actual.first-1,actual.second) && grid[actual.first-1][actual.second] == 0){
				cola.push({actual.first-1,actual.second});
			}
			if(inRange(actual.first,actual.second-1) && grid[actual.first][actual.second-1] == 0){
				cola.push({actual.first,actual.second-1});
			}
			if(inRange(actual.first+1,actual.second) && grid[actual.first+1][actual.second] == 0){
				cola.push({actual.first+1,actual.second});
			}
			if(inRange(actual.first,actual.second+1) && grid[actual.first][actual.second+1] == 0){
				cola.push({actual.first,actual.second+1});
			}
			
		}
	}
}
}