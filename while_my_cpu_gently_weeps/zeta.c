//Compile with gcc -O3 -fopenmp zeta.c -lm
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int main() {
	int loops = 0;
	printf("Enter how many iterations you want to do:\n");
	scanf("%i",&loops);

	//Compute sum
	//From https://www.linuxtoday.com/blog/openmp/
	double sum = 0.0;
	int start = clock();
#pragma omp parallel for reduction(+: sum)
	for(int i = loops; i >= 1; i--) {
		sum += 1.0/pow(i,2.);
	}
	int end = clock();
	//Euler solved the Basel problem a while back
	//The zeta function of order two computes pi^2 / 6, so we can use this to estimate pi:
	sum *= 6;
	sum = sqrt(sum);
	double duration = end-start;
	printf("Pi: %f\nComputation took %f secs\n",sum,duration/CLOCKS_PER_SEC);
}
