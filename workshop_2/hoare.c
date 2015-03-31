#include <stdio.h>
#include <stdlib.h>
#include "hoare.h"
#include "partition.h"

int hoare(int *A, int n, int k) {

	/*partition the array A so everything <= to pivot
	is to the left and everything > pivot is to the right*/
	int p_index = partition(A,n,A[n-1]);

	/*p_index will be the same index in the sorted array*/

	/*so we can use it as information for where to go next*/

	/*if the kth index is smaller than p_index, we can focus on
	the left side*/
	if(k < p_index) {

		/*pass the left side, with size being
		equivalent to the p_index*/
		hoare(A,p_index,k);
	}

	/*if the kth index is bigger than p_index, we can focus on
	the right side*/
	else if (k > p_index) {
		/*here it gets a bit tricky*/

		/*we have to think a little*/

		/*we know we are going to pass A's right side not including
		the pivot index,thus we do A+p_index+1*/

		/*now since we passed the right side, our k value changes,
		so we must figure out the relative value to p_index*/

		hoare(A+p_index+1,n-p_index-1,k-p_index-1);
	}

	/*our p_index == kth index*/
	else {
		return A[p_index];
	}

}

