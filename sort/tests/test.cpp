#include "sort/sort.hpp"
#include "sort/utils.hpp"
#include <chrono>
#include <iostream>
#include <ctime>
#include <fstream>

long getElapsedTime(std::chrono::time_point<std::chrono::high_resolution_clock> t1,
		std::chrono::time_point<std::chrono::high_resolution_clock> t2){
	auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	return static_cast<long>(int_ms.count());
}

float getArrayFromtxt(float* A, int n, std::string filename){
	std::ifstream file(filename);
	if (file.is_open()){
		for (int i = 0; i < n; i++){
			file >> A[i];
		}
		file.close();
	}
	else{
		std::cout << "Unable to open file";
	}
	return *A;
}



void testSort(int max_size, int n_sizes){
	int* sizes = sort::linspace(max_size, n_sizes);
	float* A = nullptr;
	int n = 0;
	for (int i = 0; i < n_sizes; i++){
		n = sizes[i];
		A = sort::createRandomIntArray(n, 0, 100);
		auto start = std::chrono::high_resolution_clock::now();
		//change the sort method here
		sort::quickSort(A, n);
		//
		auto end = std::chrono::high_resolution_clock::now();
		long elapsed =  getElapsedTime(start, end);
		sort::deleteArray(A);
		std::cout << " [" << n << "," << elapsed << "]" << std::endl;
	}
	delete[] sizes;
}


int main(int nargs, char** args){

	std::srand(std::time(nullptr));
	int n = 10000;
	float* A = sort::createRandomIntArray(n, 0, 100);
	float B[n], C[n], D[n];
	
	sort::quickSort(A, n); //ordenar arreglo A

	sort::inverse_array(A, B, n); // invertir arreglo A y guardarlo en B
	sort::copy_array(B, C, n); // hacer copia de B
	sort::copy_array(B, D, n); // otra copia de B

	//tiempos en ordenar arreglo ordenado de forma descendente
	double insertion_time = sort::get_time(sort::insertionSort, B, n);
	double quicksort_time = sort::get_time(sort::quickSort, C, n);
	double selection_time = sort::get_time(sort::selectionSort, D, n);
	
	std::cout << "insertion time " << insertion_time << std::endl;
	std::cout << "quicksort time " << quicksort_time << std::endl;
	std::cout << "selection time " << selection_time << std::endl;
	
	return 0;
}
