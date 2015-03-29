#include <stdio.h>
#include <stdlib.h>
#include "partition.h"





int partition(void **A, int n, void *pivot, int (cmp)(void *, void *)) {

	int i = -1; // serve as the current index in the array
	int j; 
	int ri = n-1; // last element index, also the pivot index
	for(j=i+1;j<= ri-1;j++) {

		if(cmp(A[j],pivot) <= 0) {
			i++;
			swap(A[j],A[i]);
		}
	}
	//put the pivot where array index ends+1
	swap(A[ri],A[i+1]);

	//return pivot index 
	return i+1;
}
