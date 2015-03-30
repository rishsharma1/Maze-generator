#include <stdio.h>
#include <stdlib.h>
#include "hoare.h"
#include "partition.h"

int hoare(int *A, int n, int k) {

	int p_index = partition(A,n,A[n-1]);

	if(k < p_index) {
		hoare(A,p_index,k);
	}
	else if (k > p_index) {
		hoare(A+p_index+1,n-p_index-1,k-p_index-1);
	}
	else {
		return A[p_index];
	}

}

int quickselect(int *A,int li,int n,int k) {
	int ri = n-1;

	swap(&A[(li+ri)/2],&A[ri]);

	int p_index = partition(A,n,A[ri])+li;
	printf("p_index = %d\n",p_index);

	if(k< p_index) {
		printf("k < p_index\n");
		quickselect(A,li,p_index-li,k);
	}
	else if (k > p_index) {
	printf("k > p_index\n");
		quickselect(A,p_index+1,ri-p_index,k);
	}
	else {
		printf("p_index = %d\n",p_index);

		return A[p_index];
	}


}