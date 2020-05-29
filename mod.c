/* 20170201 NaJiwoong */
/* 2020 May 21th */

/*   Environment
 *	 
 *	 Ubuntu 16.04.12
 *	 gcc 5.4.0 
 */

/* 		Execution
 *
 *	 	"make"
 *	 	 - make execution file, and output.txt
 *	 	"make clean"
 *	 	 - clean execution file, and output.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <math.h>

/* Function for cacalculate multiple mod without overflow */

int64_t modmult(int64_t a, int64_t b, int64_t N){
	if (a == 0 || b < N / a){
		return (a*b)%N;
	}
	int64_t sum = 0;
	
	while (b > 0){
		if (b % 2 == 1){
			sum = (sum+a) % N;
		}
		a = (2*a) % N;
		b = b >> 1;
	}
	return sum;
}

/* Function for calculate mod
 * N for modulo, b is base, and e is exponent */
int64_t mod(int64_t N,int64_t b,int64_t e){
	int64_t base = b % N;
	
	int64_t exponent = e;
	int64_t result = 1;

	while (exponent > 0){
		if (exponent % 2 == 1){
			result = modmult(result, base, N);
		}
		exponent = exponent >> 1;
		base = modmult(base, base, N);
	}

	return result;
}


/* Function for get multiplicative inverse modulo N 
 * It uses Extended Euclidean Algorithm 	*/
int64_t inverse(int64_t a,int64_t N){
	int64_t s1 = 1;
	int64_t s2 = 0;
	int64_t t1 = 0;
	int64_t t2 = 1;
	int64_t R1 = N;
	int64_t R2 = a;

	int64_t Q = R1/R2;
	int64_t tempR = R2;
	R2 = R1%R2;
	R1 = tempR;
	
	int64_t ts, tt;
	while (R2 != 0){
		ts = s2;
		tt = t2;
		s2 = s1 - s2*Q;
		t2 = t1 - t2*Q;
		s1 = ts;
		t1 = tt;

		Q = R1/R2;
		tempR = R2;
		R2 = R1%R2;
		R1 = tempR;
	}
	if (t2  < 0){
		t2 = N + t2;
	}
	
	return t2;
}

int64_t moddiv(int64_t a, int64_t b, int64_t p){
	int64_t ib = inverse(b, p);
	return modmult(a, ib, p);
}

int64_t modplus(int64_t a, int64_t b, int64_t p){
	int64_t result = a+b;
	while (result < 0){
		result += p;
	}
	while (result >= p){
		result -= p;
	}
	return result;
}

int64_t modminus(int64_t a, int64_t b, int64_t p){
	return modplus(a, -b, p);
}


int64_t gcd(int64_t a,int64_t b){
	if (a < b){
		return gcd(b, a);
	}
	else if (a % b == 0){
		return b;
	}else{
		return gcd(b, a%b);
	}
}

int64_t * factorize(int64_t g, int64_t k, int64_t p, int64_t * s, int64_t plus, int len){
	int64_t quotient = (mod(p, g, k)+plus);
	int i;
	int64_t * relation = calloc(len+1, sizeof(int64_t));
	relation[len] = k;

	//printf("quotient: %li, len: %d \n", quotient, len);
	for (i=0; i<len; i++){
		while (1){
			if (quotient % s[i] == 0){
				quotient = quotient/s[i];
				relation[i]++;
			}else{
				break;
			}
		}
		if (quotient == 1){
			break;
		}
	}
	if (quotient == 1){
		return relation;
	}else{
		free(relation);
		return factorize(g, k, p, s, plus+p, len);
	}
}


