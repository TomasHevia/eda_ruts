#ifndef SORT_UTILS_HPP
#define SORT_UTILS_HPP

namespace sort{
	void inverse_array(float A[], float B[], int n);
	void copy_array(float A[], float B[], int n);
	double get_time(void (*f)(float[], int), float A[], int n);
	float* createArray(int n);
	float* createRandomArray(int n);
	float* createRandomIntArray(int n, int minVal = 0, int maxVal = 100);
	void deleteArray(float* A);
	void printArray(float* A, int n);
	void setAll(float* A, int n, float value);
	void swap(float* A, int i, int j);
	int getRandomInt(int min, int max);
	int* linspace(int max, int n_parts);
}

#endif
