#include <search.h>

template<class T>
int binary_search(const T* arr, const int l, const int r, const int v)
{
	int m;
	while(l <= r) {
		m = (l + r) / 2;
		if(v < arr[m])
			r = m - 1;
		else if(v > arr[m])
			l = m + 1;
		else
			return m;
	}

	return -1;
}

