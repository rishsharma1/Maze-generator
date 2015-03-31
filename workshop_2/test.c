#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INITIAL 10

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main(int argc,char *argv[]) {

	int k = atoi(argv[1]);
	int num;
	int n = 0;
	int current_size = INITIAL;
	int *A = (int *)malloc(sizeof(int)*INITIAL);
	assert(A);
	while(scanf("%d",&num) == 1) {

		if(n >= current_size) {
			current_size *= 2;
			A = (int *)realloc(A,sizeof(int)*current_size);
			assert(A);
		}
		A[n++] = num;

	}
	qsort(A,n,sizeof(int),cmpfunc);
	printf("Expected value: %d\n",A[k]);

	return 0;
}