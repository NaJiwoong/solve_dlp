/* 20170201 NaJiwoong */
/* 2020 May 26th */

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
#include <stdint.h>
#include <malloc.h>

#include "mod.h"
#include "dlp.h"


int main(void){
	FILE *fp;
	fp = fopen("./output.txt", "wt");
	if (fp ==NULL){
		printf("Error: cannot open file\n");
		return -1;
	}
	
	int64_t p, alpha, beta;
	p = 809;
	alpha = 3;
	beta = 500;
	//p = 131;
	//alpha = 2;
	//beta = 37;


	int64_t * result_list = shanks(p, alpha, beta);

	fprintf(fp, "< RESULT FOR SOLVING DLP > \n");
	fprintf(fp, "20170201 NaJiwoong \n");

	fprintf(fp, "\n < SHANKS' ALGORITHM RESULT > \n\n");
	
	fprintf(fp, "Value of m: %li\n", result_list[0]);
	fprintf(fp, "Value of y: %li\n", result_list[1]);
	fprintf(fp, "Value of j: %li\n", result_list[2]);
	fprintf(fp, "Value of i: %li\n", result_list[3]);
	fprintf(fp, "Answer: %li\n", result_list[4]);

	fprintf(fp, "\n----------------------------------------------\n\n");

	/* CASE 2 */
	
	fprintf(fp, "< INDEX CALCULUS ALGORITHM RESULT > \n\n");
	//int64_t x = index_calculus(p, alpha, beta);
	int64_t x = index_calculus(p, alpha, beta, fp);
	fprintf(fp, "Answer: %li\n", x);
	fprintf(fp, "\n");

	fclose(fp);
	
	free(result_list);

	return 0;
}




