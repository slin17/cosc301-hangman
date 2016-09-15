#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

int main () {
	int r,i;
	//int N = 0;
	//int M = 100;
	srand (time(NULL));
	for (i = 0; i<10; i++) {
		//r = M+rand()/(RAND_MAX/(N - M+1) +1);
		r = rand()%49; 
		printf("random number:%d\n", r); 
	}
	return 0;
}
