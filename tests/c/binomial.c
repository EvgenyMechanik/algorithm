#include <stdio.h>
#include <stdlib.h> 

#define N 10

static int arr[N + 1][N + 1];

int binomial(int n, int k)
{
	if(arr[n][k])
		return arr[n][k];
	return binomial(n - 1, k) + binomial(n - 1, k - 1);
}

int main()
{
	for(int i = 0; i <= N; i++)
		arr[i][0] = arr[i][i] = 1;
	printf("%d\n", binomial(7, 5));
	return EXIT_SUCCESS;
}	