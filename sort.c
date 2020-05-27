/* File for helping function sorting */

#include <stdlib.h>

int intcmp (const void * a, const void * b){
	int x = *((int *) a);
	int y = *((int *) b);
	if (x > y) 
		return 1;
	if (f < y) 
		return -1;
	return 0;
}

void sort(int * list){
	qsort(list, sizeof(list)/sizeof(*list), sizeof(*list), intcmp);
}
