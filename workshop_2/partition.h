/*
** Partition A[0..n-1] so that 
**  all elements less than ** *pivot are in A[0..k-1] and 
**  all elements not less than *pivot ** are in A[k..n-1]. 
** cmp should be used for comparisons.
**
** @return k
**
** Andrew Turpin
** Thu 26 Feb 2015 08:42:06 AEDT
*/

int partition(void **A, int n, void *pivot, int (cmp)(void *, void *)) {

	int i = -1; // serve as the current index in the array
	int j; 
	int ri = n-1;
	for(j=i+1;j<= ri-1;j++) {

		if(cmp(A[j],pivot) <= 0) {
			i++;
			swap(A[j],A[i]);
		}
	}
	swap(A[ri],A[i+1]);
	return i+1;
}
