#include <bits/stdc++.h>
#include <chrono>
#include <omp.h>
using namespace std;


void printLineSierpinski(int n, int b)
{
    int y = n - b;
    std::string line; 

    for (int i = 0; i < y; i++) 
        line += " ";
 
    for (int x = 0; x + y < n; x++) 
        line +=(x & y)? "  ": "* ";

    #pragma omp critical
    {
        std::cout << line << std::endl;
    }
    
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    int n = 32;

    #pragma omp parallel for ordered
    for (int i = 0; i <= n; i++) {
    #pragma omp ordered
        {
	        printLineSierpinski(n, i);
        }  
    }
        
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    std::cout << "Tempo de execucao: " << duration.count() << " segundos" << std::endl;

	return 0;
}