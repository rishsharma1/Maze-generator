/*
** COMP20007 Design of Algorithms
** Semester 1 2015
** Workshop 2 
**
** Andrew Turpin (aturpin@unimelb.edu.au)
** Thu 26 Feb 2015 08:52:41 AEDT
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "radixSort.h"
#include "hoare.h"

#define MAX_NUMBER_STRING_LEN 64  /* maximum length in chars of number */

/*
** Print usage message
*/
void
usage(char *exeName) { 
    fprintf(stderr,"Usage: %s [h | r] k < filename\n",exeName);
    fprintf(stderr,"       where\n");
    fprintf(stderr,"          h - Hoare's partitioning\n");
    fprintf(stderr,"          r - Radix sort\n");
    fprintf(stderr,"          k - rank of item to find\n");
    fprintf(stderr,"          filename - file name of text file of numbers, one per line\n");
}

/*
** Read input, call getKth, print time
*/
int 
main(int argc, char *argv[]) {

    if (argc != 3) {
        usage(argv[0]);
        return(-1);
    }

    char method = argv[1][0];
    int k;
    sscanf(argv[2], "%d", &k);

    /*
    ** Read in the numbers, and keep increasing the array size
    ** if necessary.
    */
    int maxArraySize = 64;  /* any number > 0 */
    int n  = 0;
    int *A = (int *)malloc(sizeof(int) * maxArraySize);
    if (A == NULL) {
        fprintf(stderr, "Out of memory for A\n");
        return -1;
    }
    char buff[MAX_NUMBER_STRING_LEN];
    while (fgets(buff, MAX_NUMBER_STRING_LEN, stdin) != NULL) {
        if (n >= maxArraySize) {
            maxArraySize *= 2;  /* double the size of the array */
            A = (int *)realloc(A, sizeof(int) * maxArraySize);
            if (A == NULL) {
                fprintf(stderr, "Out of memory for A\n");
                return -1;
            }
        }
        sscanf(buff, "%d", &A[n]);
        n++;
    }
    
    printf("Read %d numbers\n",n);

    if (method == 'h') {
        clock_t startTime = clock();
        int m = hoare(A, n, k);
        clock_t endTime = clock();
        printf("Time taken to find %d th element (%20d) using Hoare on %10d elements = %ldms\n", k, m, n, (endTime-startTime+500)/1000);
    } else {
        clock_t startTime = clock();
        radixSort(A, n);
        int m = A[k-1];
        clock_t endTime = clock();
        printf("Time taken to find %d th element (%20d) using radix  on %10d elements = %ldms\n", k, m, n, (endTime-startTime+500)/1000);
    }
    
    return 0;
}
