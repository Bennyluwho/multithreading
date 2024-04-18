//Demo of how easy it is to parallelize code with OpenMP
//Compile with \g++ -O3 -fopenmp summer.cc
#include <iostream>
#include <omp.h> 
using namespace std;

int main() {               
	double sum{};
	const int N = 900'000'000;

//    #pragma omp parallel for
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++)
        sum += i / (N/10);

    cout << "Sum = " << sum << endl;        
}
