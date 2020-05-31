//Parallization of mandelbrotDefault.cpp using OpenMP

//All prints are commented to improve runtime of the solution

#include <complex>
#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <stdio.h>	
#include <fstream>

using namespace std;


int main(int argc, char **argv){

	//double inicio, fim;

	//inicio =  omp_get_wtime();

	ofstream ma ("printMatrix.txt", ios::app);
	if (!ma) {
   		cout << "Failed to open"; 
		return EXIT_FAILURE; 
	}
	/*
	ofstream da ("printMatrix.txt", ios::app);
	if (!da) {
   		cout << "Failed to open"; 
		return EXIT_FAILURE; 
	}
	*/
	int max_row, max_column, max_n, thread;

	max_row = 1024; //23
	max_column = 768; //79
	max_n = 18000; //24
	thread = 4; //2, 4, 8, 16

	if (thread != 2 && thread != 4 && thread != 8 && thread != 16){
		printf("Number of threads invalid!\n");	 
		return EXIT_FAILURE;
	}
	else{
		
  		//da << "Linhas: " << max_row << "\nColunas: " << max_column << "\nN: " << max_n << "\nThreads: " << thread << "\n";
	}

	//cin >> max_row;
	//cin >> max_column;
	//cin >> max_n;
	

	char **mat = (char**)malloc(sizeof(char*)*max_row);

	for (int i=0; i<max_row;i++)
		mat[i]=(char*)malloc(sizeof(char)*max_column);

	
	int r;
	int c;

	#pragma omp parallel for num_threads(thread) private(r,c) schedule(runtime) 
	for(r = 0; r < max_row; ++r){

		for(c = 0; c < max_column; ++c){
			complex<float> z;
			int n = 0;
			
			//for(;abs(z) < 2 && ++n < max_n;)
			while(abs(z) < 2 && ++n < max_n) 
				z = pow(z, 2) + decltype(z)(
					(float)c * 2 / max_column - 1.5,
					(float)r * 2 / max_row - 1
				);

			mat[r][c]=(n == max_n ? '#' : '.');
		}
	}
	
	/*
	for(int r = 0; r < max_row; ++r){
		for(int c = 0; c < max_column; ++c)
			cout << mat[r][c];
		cout << '\n';
	}
	*/

	for(int r = 0; r < max_row; ++r) {
		for(int c = 0; c < max_column; ++c)
   			ma << mat[r][c];
   		ma << '\n';
	}

	//fim =  omp_get_wtime();
	//da << "Tempo: " << fim - inicio << "\n\n";

	return 0;
}


