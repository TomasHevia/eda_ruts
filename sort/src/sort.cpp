#include <iostream>
#include "sort/sort.hpp"
#include "sort/utils.hpp"

namespace sort{
	void insertionSort(float* A, int n){
		for(int i=1; i<n; i++){
			int elem = A[i];
			int j = i-1;
			while(j>=0 && elem < A[j]){
				A[j+1] = A[j];
				j--;
			}
			A[j+1] = elem;
		}

	}

	void selectionSort(float* A, int n){
		int smallest = 0;
		int i = 0;
		int j = 0;
		for (i = 0; i < n - 1; i++){
			smallest = i;
			for (j = i + 1; j < n; j++){
				if (A[j] < A[smallest]){
					smallest = j;
				}
			}
			swap(A,i,smallest);
		}
	}

	int split_qs(float* A, int i, int j){
		
		int p = getRandomInt(i, j);

		while (i  < j) {

			while ( i < p && A[i] <= A[p]){
				i = i + 1;
			}
			while ( j > p && A[j] >= A[p]){
				j = j - 1;
			}

			swap(A, i, j);

			if (i == p){
				p = j;
			}
			else if (j == p){
				p = i;
			}
		}
		return p;
	}

	void quickSort(float* A, int i, int j){
		std::cout << i << " " << j << std::endl;
		if (i < j){
			int k = split_qs(A, i, j);
			quickSort(A, i, k-1);
			quickSort(A, k + 1, j);
		}
	}

	void quickSort(float* A, int n){
		quickSort(A, 0, n - 1);
	}

	int  k_smallest(float* A, int i, int j, int k){
		int p = split_qs(A, i, j);
		int val = 0;
		if (k == p){
			val = A[p];
		}
		else if (k < p){
			val = k_smallest(A, i, p-1, k);
		}
		else{
			val = k_smallest(A, p+1, j, k);
		}
		return val;
	}

	int  k_smallest(float* A, int n, int k){
		return k_smallest(A, 0, n-1, k);
	}

	void mergeSort(float* A, int i, int j){
		if (i < j){
			int m = (i + j) / 2;
			mergeSort(A, i, m);
			mergeSort(A, m + 1, j);
			merge(A, i, m, j);
		}
	}

	void merge(float* A, int i, int m, int j){
		int n1 = m - i + 1;
		int n2 = j - m;
		float* L = new float[n1];
		float* R = new float[n2];
		for (int x = 0; x < n1; x++){
			L[x] = A[i + x];
		}
		for (int y = 0; y < n2; y++){
			R[y] = A[m + 1 + y];
		}
		int x = 0;
		int y = 0;
		int k = i;
		while (x < n1 && y < n2){
			if (L[x] <= R[y]){
				A[k] = L[x];
				x++;
			}
			else{
				A[k] = R[y];
				y++;
			}
			k++;
		}
		while (x < n1){
			A[k] = L[x];
			x++;
			k++;
		}
		while (y < n2){
			A[k] = R[y];
			y++;
			k++;
		}
		delete[] L;
		delete[] R;
	}

	
	void radixSort(float* A, int n){
		int max = getMax(A, n);
		for (int exp = 1; max / exp > 0; exp *= 10){
			countSort(A, n, exp);
		}
	}
	int getMax(float* A, int n){
		int max = A[0];
		for (int i = 1; i < n; i++){
			if (A[i] > max){
				max = A[i];
			}
		}
		return max;
	}
	void countSort(float* A, int n, int exp){
		float* output = new float[n];
		int i, count[10] = { 0 };

		for (i = 0; i < n; i++){
			count[(int)(A[i] / exp) % 10]++;
		}

		for (i = 1; i < 10; i++){
			count[i] += count[i - 1];
		}

		for (i = n - 1; i >= 0; i--){
			output[count[(int)(A[i] / exp) % 10] - 1] = A[i];
			count[(int)(A[i] / exp) % 10]--;
		}

		for (i = 0; i < n; i++){
			A[i] = output[i];
		}
		delete[] output;
	}

}



