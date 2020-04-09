#include <iostream>
#include <cstdlib> 
using namespace std;

#define M 1000
#define N 32

int main( void ) { 
	int cnt;
	int p[N];

	for(int i = 0; i < N; i++)   
		p[i] = 0;

	for(int i = 0; i < M; i++, p[cnt]++) {
		cnt = 0;
		for(int j = 0; j < N; j++)
			if(rand() > RAND_MAX / 2) 
				cnt++; 
	}

	for(int i = 0; i < N; i++) {
		if(p[i] >= 10) {
			for(int j = 0; j <= p[i]; j += 10)
				cout << "*";
			cout << endl;	  
		} else {
			cout << "." << endl;
		}
	} 

	return EXIT_SUCCESS; 
} 

