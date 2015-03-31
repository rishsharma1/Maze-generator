#include <stdio.h>
#include <stdlib.h>
#include "partition.h"





int partition(int *A, int n, int pivot) {

	int i = -1; // serve as the current index in the array
	int j; 
	int ri = n-1; // last element index, also the pivot index
	for(j=i+1;j<= ri-1;j++) {

		if(A[j] <= pivot) {
			i++;
			swap(&A[j],&A[i]);
		}
	}
	//put the pivot where array index ends+1
	swap(&A[ri],&A[i+1]);

	//return pivot index 
	return i+1;
}


int swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

