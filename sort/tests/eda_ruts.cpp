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
		for (int i = 0; i < n; i++){
			file >> A[i];
		}
		file.close();
	}
	return *A;
}

int extractIntFromString(std::string str){
	std::stringstream ss;
	ss << str;
	std::string temp;
	int found;
	while (!ss.eof()){
		ss >> temp;
		if (std::stringstream(temp) >> found){
			return found;
		}
		temp = "";
	}
	return -1;
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
	int n = extractIntFromString(args[2]);
	float* A = nullptr;
    getArrayFromtxt(A, n, filename);

	std::string Q = "Q";
	std::string I = "I";
	std::string M = "M";
	std::string R = "R";
	
	std::string method;

	auto start = std::chrono::high_resolution_clock::now();

	if (args[2] == Q){
		sort::quickSort(A, n);
		method = "quickSort";
	}
	else if (args[2] == I){
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
		sort::radixSort(A, n);
		method = "radixSort";
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "ordenado con: " << method << std::endl;
	long elapsed =  getElapsedTime(start, end);
	getTxtFromArray(A, n, filename);
	sort::deleteArray(A);
	std::cout << " [" << n << "," << elapsed << "]" << std::endl;
}

