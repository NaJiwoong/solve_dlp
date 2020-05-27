/* 20170201 NaJiwoong */
/* 2020 May 26th */

/*   Environment
 *	 
 *	 Ubuntu 16.04.12
 *	 gcc 5.4.0 
 */

/* 		DLP Solver
 *
 *	 	Shanks' methods, and Index Calculus
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>

#include "mod.h"
#include "dlp.h"

int tupcmp (const void * a, const void * b){
	int64_t x = (*((struct tuple *) a)).value;
	int64_t y = (*((struct tuple *) b)).value;
	if (x > y) 
		return 1;
	if (x < y) 
		return -1;
	return 0;
}

void sort(struct tuple * list, size_t len){
	qsort(list, len, sizeof(*list), tupcmp);
}


/* This function is for shanks' algorithm
	 Input is p, alpha, beta where we are going to solve
	 "log_{alpha}(beta) mod p"	*/
int64_t * shanks(int64_t p,int64_t alpha,int64_t beta){
	
	int64_t m = (int)ceil(sqrt((double)p));

	struct tuple * list1 = malloc(sizeof(struct tuple) * m);
	struct tuple * list2 = malloc(sizeof(struct tuple) * m);
	
	int64_t j;
	for (j = 0; j<m; j++){
		list1[j].index = j;
		list1[j].value = mod(p, alpha, m*j);
	}
	
	int64_t i;
	int64_t alphamod;
	for (i = 0; i<m; i++){
		list2[i].index = i;
		alphamod = mod(p, inverse(alpha, p), i);
		list2[i].value = modmult (beta, alphamod, p);
	}

	sort(list1, m);
	sort(list2, m);

	i = 0;
	j = 0;
	int cmpresult;
	while (1){
		cmpresult = tupcmp(&(list1[j]), &(list2[i]));
		if (cmpresult == 0){
			break;
		}else if (cmpresult == 1){
			i++;
		}else{
			j++;
		}
		
		if (i >= m || j >= m){
			printf("Cannot find answer!!\n");
			free(list1);
			free(list2);
			exit(0);
		}
	}

	int64_t answer = modmult(m, list1[j].index, p);
	answer = (answer+list2[i].index) %(p-1);

	int64_t * result_list = malloc(sizeof(int64_t)*5);
	result_list[0] = m;
	result_list[1] = list1[j].value;
	result_list[2] = list1[j].index;
	result_list[3] = list2[i].index;
	result_list[4] = answer;

	return result_list;
}






















