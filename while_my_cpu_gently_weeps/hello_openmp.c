//Compile with gcc -fopenmp hello_openmp.c
//https://hpc-tutorials.llnl.gov/openmp/
#include "stdio.h" 
#include "time.h" 
#include <omp.h>

int main(int argc, char *argv[])
{
/*#pragma omp parallel
	{
		int np = omp_get_num_procs();
		int tid = omp_get_thread_num();
		int nt = omp_get_num_threads();
		int mt = omp_get_max_threads();
#pragma omp critical 
		{
			if (tid == 0) {
				printf("Number of CPUs = %i\n",np);
				printf("Number of Threads = %i\n",nt);
				printf("Max Threads = %i\n",mt);
			}
			printf("Hello OMP, I am thread #%i uWu\n",tid);
		}
	}*/
	double sum = 0.;
	int start = clock();
#pragma omp parallel for
	for (int i = 0; i < 1000000; i++) 
		sum += i;
	int end = clock();
	printf("Sum: %f Time Elapsed: %i\n",sum,end-start);
}
