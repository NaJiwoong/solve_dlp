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
#include <time.h>

#include "mod.h"
#include "dlp.h"
#include "matrix.h"

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

int is_prime(int64_t p){
	int i, N;
	N = sqrt(p);
	for (i=2; i<N+1; i++){
		if (p%i == 0){
			return 0;
		}
	}
	return 1;
}

int64_t * less_prime(int64_t p){
	int i, n, j;
	n = 0;
	j = 0;
	for (i=2; i<p; i++){
		if (is_prime(i)){
			n++;
		}
	}
	int64_t * prime_list = malloc(sizeof(int64_t)*n);
	for (i=2; i<p; i++){
		if (is_prime(i)){
			prime_list[j] = i;
			j++;
		}
	}
	return prime_list;
}

/* This function is for index_calculus algorithm
	 Input is p, alpha, beta where we are going to solve
	 "log_{alpha}(beta) mod p"	*/
int64_t index_calculus(int64_t p, int64_t g, int64_t y, FILE *fp){
	int64_t b = 10;
	int64_t * s = less_prime(b);
	int n=0;
	int u=0;
	for (u=2; u<b; u++){
		if (is_prime(u)){
			n++;
		}
	}
	
	

	int64_t rel_num = 0;

	int64_t **rel_mat = malloc(sizeof(int64_t)*(n+1));

	int check = 0;
	int i = 0;
	int j = 0;
	int64_t k = 1;
	while (rel_num < n){
		rel_mat[i] = factorize(g, k, p, s, 0, n);

		/*
		for (j=0; j<i; j++){
			if (!independent(rel_mat[i], rel_mat[j], n+1)){
				check = 1;
			}
		}*/

		if (!ref(rel_mat, i+1, n+1, p-1)){
			check = 1;
		}

		for (j=0; j<i+1; j++){
			if (rel_mat[j][j] != 1){
				check = 1;
			}
		}

		if (check == 1){
			k++;
			check = 0;
			continue;
		}

		k++;
		i++;
		rel_num ++;
	}

	
	rel_mat[n] = malloc(sizeof(int64_t)*n+1);
	for (i=0; i<n+1; i++){
		rel_mat[n][i] = 0;
	}

	ref2(rel_mat, n+1, n+1, p-1);
	

	int64_t * sv = malloc(sizeof(int64_t)*n);
	for (i=0; i<n; i++){
		sv[i] = moddiv(rel_mat[i][n], rel_mat[i][i], p-1);
	}

	
	srand((uint32_t)(time(NULL)));
	int64_t r = rand()%100;
	int64_t ygr = modmult(y, mod(p, g, r), p);
	rel_mat[n] = factorize(ygr, 1, p, s, 0, n);
	
	int64_t x = -r;
	for (i=0; i<n; i++){
		x += rel_mat[n][i]*sv[i];
	}

	for (i=0; i<n; i++){
		fprintf(fp, "log_(%li) (%li) = %li  multiple number: %li \n", g, s[i], sv[i], rel_mat[n][i]);
	}

	x = modplus(x, 0, p-1);

	free(sv);
	
	for (i=0; i<n+1; i++){
		free(rel_mat[i]);
	}
	free(rel_mat);

	return x;
}
















