#ifndef SORT_SORT_HPP
#define SORT_SORT_HPP

namespace sort {
	void insertionSort(float* A, int n);
	void selectionSort(float* A, int n);
	int split_qs(float* A, int i, int j);
	void quickSort(float* A, int i, int j);
	void quickSort(float* A, int n);
	int  k_smallest(float* A, int i, int j, int k);
	int  k_smallest(float* A, int n, int k);
	void merge(float* A, int i, int j, int k);
	void mergeSort(float* A, int i, int j);
	void radixSort(float* A, int n);
	int getMax(float* A, int n);
	void countSort(float* A, int n, int exp);
}

#endif
