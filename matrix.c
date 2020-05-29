/* this code is for helping function
 * linear algebra */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "mod.h"

/* Check if two vectors are linearly independent */
int independent(int64_t * a, int64_t * b, int64_t len){
	assert(sizeof(a) == sizeof(b));

	int result = 0;
	int64_t q = 1;
	int i;
	int64_t qq;

	if ((a[0] == 0 && b[0] != 0) || (a[0] != 0 && b[0] == 0)){
		return 1;
	}
	q =  a[0] == 0 ? 0 : a[0] / b[0];
	for (i=1; i<len; i++){
		if ((a[i] == 0 && b[i] != 0) || (a[i] != 0 && b[i] == 0)){
			return 1;
		}
		qq = a[i] == 0 ? 0 : a[i] / b[i];
		if (q == 0 && qq != 0){
			q = qq;
		}
		if (q != 0 && qq == 0){
			continue;
		}
		if (q != qq){
			result = 1;
			return result;
		}
	}
	return result;
}


int ref(int64_t ** m, int64_t row, int64_t col, int64_t p){
	int64_t q;
	int i, j, k, c, r;

	int64_t * buffer = malloc(sizeof(int64_t)*col);
	
	r = 0;
	c = 0;
	while(r < row){
		if (m[r][c] == 0){
			for (j=r+1; j<row; j++){
				if (m[j][c] != 0){
					memcpy(buffer, m[j], sizeof(int64_t)*col);
					memcpy(m[j], m[r], sizeof(int64_t)*col);
					memcpy(m[r], buffer, sizeof(int64_t)*col);
				}
			}
			if (m[r][c] == 0){
				c++;
				continue;
			}
		}
		
		q = inverse(m[r][c], p);
		for (j=0; j<col; j++){				//Multiply the ratio that makes pivot 1
			m[r][j] = modmult(m[r][j], q, p);
		}
		
		for (j=r+1; j<row; j++){
			q = moddiv(m[j][c], m[r][c], p);
			for (k=0; k<col; k++){
				m[j][k] = modminus(m[j][k], modmult(m[r][k], q, p), p);
			}
		}

		r++;
		c++;
	}

	int zero = 0;
	int nonzero = 0;



	for (i=0; i<row; i++){
		for (k=0; k<col; k++){
			if (m[i][k] != 0){
				nonzero = 1;
				break;
			}
		}
		if (nonzero == 0){
			return 0;
		}
		nonzero = 0;
	}
	return 1;
}


void rref(int64_t ** m, int64_t size, int64_t p){
	int64_t n = size;
	
	int64_t q;
	int i, j, k;

	int64_t * buffer = malloc(sizeof(int64_t)*size);

	for (i=0; i<n-1; i++){
		if (m[i][i] == 0){
			for (j=i+1; j<n; j++){
				if (m[j][i] != 0){
					memcpy(buffer, m[i], sizeof(int64_t)*size);
					memcpy(m[i], m[j], sizeof(int64_t)*size);
					memcpy(m[j], buffer, sizeof(int64_t)*size);
					break;
				}
			}
		}

		q = inverse(m[i][i], p);
		for (j=i; j<n; j++){
			m[i][j] = modmult(m[i][j], q, p);
		}
		for (j=i+1; j<n; j++){
			for (k=i; k<n; k++){
				m[j][k] = modminus(m[j][k], m[i][k], p);
			}
		}
	}
	free(buffer);

}



int ref2(int64_t ** m, int64_t row, int64_t col, int64_t p){
	int64_t q;
	int i, j, k, c, r;

	int64_t * buffer = malloc(sizeof(int64_t)*col);
	
	r = 0;
	c = 0;
	while(r < row){
		if (m[r][c] == 0){
			for (j=r+1; j<row; j++){
				if (m[j][c] != 0){
					memcpy(buffer, m[j], sizeof(int64_t)*col);
					memcpy(m[j], m[r], sizeof(int64_t)*col);
					memcpy(m[r], buffer, sizeof(int64_t)*col);
				}
			}
			if (m[r][c] == 0){
				c++;
				continue;
			}
		}
		
		q = inverse(m[r][c], p);
		for (j=0; j<col; j++){				//Multiply the ratio that makes pivot 1
			m[r][j] = modmult(m[r][j], q, p);
		}
		
		for (j=0; j<row; j++){
			if (j == r){
				continue;
			}
			q = moddiv(m[j][c], m[r][c], p);
			for (k=0; k<col; k++){
				m[j][k] = modminus(m[j][k], modmult(m[r][k], q, p), p);
			}
		}

		r++;
		c++;
	}

	int zero = 0;
	int nonzero = 0;

	
	return 0;
}
