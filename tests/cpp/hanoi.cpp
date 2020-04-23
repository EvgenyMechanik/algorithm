#include <iostream>
#include <cstdlib>

#define N 5

enum { left, right, _last };
struct hanoi {	
	int disk;
	int src;
	int dst;
};

static int ipow(int v, int n)
{
	int r = 1;
	for(int i = 0; i < n; i++)
		r *= v;
	return r;
}

void hanoi_r(int src, int dst, int help, int n)
{
	if(n) {
		hanoi_r(src, help, dst, n - 1);
		std::cout << n << ":" << src << "->" << dst << std::endl;
		hanoi_r(help, dst, src, n -1); 
	}
}

void hanoi_n_r(int src, int dst, int help, int n)
{
	int t_src, i, j, t, s = ipow(2, n), direction = (n % 2 ? right : left);
	hanoi *arr = new hanoi[s + 1];
	if(!arr)
		return;
	for(t = 1, i = 1; t <= n; t++, i *= 2, direction = (direction + 1) % _last)
		for(j = i, t_src = src; j < s; t_src = arr[j].dst, j += 2 * i) {
			arr[j].disk = t;
			arr[j].src = t_src;
			arr[j].dst = (direction == right ? (arr[j].src + 1) % (help + 1) : (arr[j].src - 1 >= 0 ? arr[j].src - 1 : help));
		}

	for(i = 1; i < s; i++)
		std::cout << arr[i].disk << ":" << arr[i].src << "->" << arr[i].dst << std::endl;

	delete[] arr;
}

int main()
{
	hanoi_r(0, 1, 2, N);
	std::cout << std::endl << std::endl;
	hanoi_n_r(0, 1, 2, N);
	return EXIT_SUCCESS;
}