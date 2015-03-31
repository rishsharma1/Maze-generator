#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

void insert_random(FILE * f, int n, int limit){
	time_t t;
	int i = 0; 

	srand((unsigned) time(&t));

	for (i = 0;i < n;i++){ 
		char str[n];
		sprintf(str, "%d",rand() % n);
		fputs(str, f);
		fputs("\n", f);
	}

}

int main(int argc, char * argv[]){
	FILE * fp;
	int size;

	if (argc != 2){
		fprintf(stderr, "FU\n");
		exit(EXIT_FAILURE);
	}

	size = atoi(argv[1]);

	if (size <= 1){
		fprintf(stderr, "Size not big\n");
		exit(EXIT_FAILURE);
	}

	fp = fopen("input.txt", "w");
	insert_random(fp, size, size);

	fclose(fp);
	


	return 0;
}

