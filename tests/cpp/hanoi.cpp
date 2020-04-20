#include <iostream>
#include <cstdlib>

#define N 3

void hanoi(int src, int dst, int help, int n)
{
	if(n) {
		hanoi(src, help, dst, n - 1);
		std::cout << n << ":" << src << "->" << dst << std::endl;
		hanoi(help, dst, src, n -1); 
	}
}

int main()
{
	hanoi(0, 1, 2, N);
	return EXIT_SUCCESS;
}