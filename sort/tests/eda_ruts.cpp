#include "sort/sort.hpp"
#include "sort/utils.hpp"
#include <chrono>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>


long getElapsedTime(std::chrono::time_point<std::chrono::high_resolution_clock> t1,
		std::chrono::time_point<std::chrono::high_resolution_clock> t2){
	auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	return static_cast<long>(int_ms.count());
}

float getArrayFromtxt(float* A, int n, std::string filename){
	std::ifstream file(filename);
	if (file.is_open()){
		
		std::string line;
		int i = 0;
		while (getline(file, line)){
			std::istringstream iss(line);
			float a;
			if (!(iss >> a)){
				std::cout << "error leyendo archivo" << std::endl;
				break;
			}
			A[i] = a;
			i++;

		}
		file.close();
	}
	return *A;
}

int extractIntFromString(std::string& str){
	size_t pos = str.find_first_of("0123456789");
	if(pos != std::string::npos){
		std::string number = str.substr(pos);
		int result = std::stoi(number);
		return result;
	}
}

void getTxtFromArray(float* A, int n, std::string filename){
	filename = filename + ".sorted";
	std::ofstream file(filename);
	if (file.is_open()){
		for (int i = 0; i < n; i++){
			file << A[i] << std::endl;
		}
		file.close();
		std::cout << "archivo generado: " << filename << std::endl;
	}
}


int main(int nargs, char** args){
	// ./eda_ruts <filename> <method>
    std::string fileroute = "../datos/";
    std::string filename = fileroute + args[1];
	std::string file;
	file = args[1];
	int n = extractIntFromString(file);
	float* A;
	A = new float[n];
    getArrayFromtxt(A, n, filename);
	std::string Q = "Q";
	std::string I = "I";
	std::string M = "M";
	std::string R = "R";
	
	std::string method;
	std::cout << "metodo: " << args[2] << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	if (args[2] == Q){
		sort::quickSort(A, n);
		method = "quickSort";
	}
	else if (args[2] == I){
		std::cout << "entro a insertionSort" << std::endl;
		sort::insertionSort(A, n);
		method = "insertionSort";
	}
	else if (args[2] == M){
		int i = 0;
		int j = n - 1;
		sort::mergeSort(A, i, j);
		method = "mergeSort";
	}
	else if (args[2] == R){
		std::cout << "entro a radixSort" << std::endl;
		sort::radixSort(A, n);
		method = "radixSort";
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "ordenado con: " << method << std::endl;
	long elapsed =  getElapsedTime(start, end);
	std::cout << "tiempo: " << elapsed << std::endl;
	getTxtFromArray(A, n, filename);
	sort::deleteArray(A);
	std::cout << " [" << n << "," << elapsed << "]" << std::endl;
}

