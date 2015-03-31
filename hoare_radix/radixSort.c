#include "radixSort.h"
#include <stdio.h>
#include <stdlib.h>

#define BASE 10

int max_num(int *A,int n) {
	int largest = A[0];
	int i;

	for(i=1;i<n;i++) {

		if(A[i] > largest) {
			largest = A[i];
		}
	}

	return largest;
}

void radixSort(int *A, int n) {

	/* we will store the semi sorted elements in temp*/
	int temp[n];
	int i;

	int current_selector = 1;

	/*need the largest number to figure out how many
	times we will need to multiply current_selector by base, in other
	words how many times we are going to have to loop*/
	int largest = max_num(A,n);

	while(largest/current_selector > 0) {

		/*intialise all from 0 to 9 buckets to 0*/
		int bucket[BASE] = {0};

		/*this will count the number of elements in
		each bucket index*/
		for(i=0;i<n;i++) {
			bucket[(A[i]/current_selector)%BASE]++;
		}

		/*once we have counted we need to perserve the index
		of each value*/

		/*go through each value in the bucket minus one, and then use
		that as the index for the temp array*/

		for(i=1;i<BASE;i++) {
			bucket[i] += bucket[i-1];
		}

		

		/*the idea behind this is, same values will produce, same index,
		given value A, and value B are the same index S in bucket, index in
		temp array, will be temp[--bucket[S]] = A, temp[--bucket[S]] = B*/

		/*NOTE: the "--" updates the index frequency in bucket*/

		for(i=n-1;i>=0;i--) {
			temp[--bucket[(A[i]/current_selector)%BASE]] = A[i];
		}

		/*copying contents of temp into A*/
		for(i=0;i<n;i++) {
			A[i] = temp[i];
		}

		current_selector *= BASE;

	}




	return;
}