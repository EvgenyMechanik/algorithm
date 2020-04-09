#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

#define N 1000
#define d 0.01

struct point {
	double x;
	double y;
};

double distance(const point& a, const point& b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int main()
{
	int count = 0;
	point arr[N];
	srand(time(NULL));

	for(int i = 0; i < N; i++) {
		arr[i].x = 1.0 * rand() / RAND_MAX;
		arr[i].y = 1.0 * rand() / RAND_MAX;
	}

	for(int i = 0; i < N; i++)
		for(int j = i + 1; j < N; j++)
			if(distance(arr[i], arr[j]) < d)
				count++;
	cout << "count = " << count << endl;
	return EXIT_SUCCESS;
}