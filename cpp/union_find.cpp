#include <iostream>
#include <cstdlib>
#include <errno.h>
#include <cstring>
#include <fstream>
using namespace std;

void fast_find(ifstream& f, int* arr, int length)
{
	int p, q, t;
	while(f >> p >> q) {
		if(p >= length || q >= length) {
			cout << "Invalid input (" << p << "," << q << ")," << " out of range(" << length << ")" << endl;
			continue;
		}
		if(arr[p] == arr[q])
			continue;
		
		t = arr[p];
		for(int i = 0; i < length; i++)
			if(arr[i] == t)
				arr[i] = arr[q];
		cout << p << " " << q << endl;	
	}
}

void fast_union(ifstream& f, int* arr, int length)
{
	int p, q, i, j;
	while(f >> p >> q) {
		if(p >= length || q >= length) {
			cout << "Invalid input (" << p << "," << q << ")," << " out of range(" << length << ")" << endl;
			continue;
		}

		for(i = p; i != arr[i]; i = arr[i]);
		for(j = q; j != arr[j]; j = arr[j]);

		if(i == j)
			continue;
		arr[i] = arr[j];
		cout << p << " " << q << endl;
	}
}

void weighted_fast_union(ifstream& f, int* arr, int* v, int length)
{
	int p, q, i, j;
	while(f >> p >> q) {
		if(p >= length || q >= length) {
			cout << "Invalid input (" << p << "," << q << ")," << " out of range(" << length << ")" << endl;
			continue;
		}

		for(i = p; i != arr[i]; i = arr[i]);
		for(j = q; j != arr[j]; j = arr[j]);

		if(i == j)
			continue;
		
		if(v[i] <= v[j]) {
			arr[i] = arr[j];
			v[j] += v[i];
		} else {
			arr[j] = arr[i];
			v[i] += v[j];
		}
		cout << p << " " << q << endl;
	}
}

void heighted_fast_union(ifstream& f, int* arr, int* h, int length)
{
	int p, q, i, j;
	while(f >> p >> q) {
		if(p >= length || q >= length) {
			cout << "Invalid input (" << p << "," << q << ")," << " out of range(" << length << ")" << endl;
			continue;
		}

		for(i = p; i != arr[i]; i = arr[i]);
		for(j = q; j != arr[j]; j = arr[j]);

		if(i == j)
			continue;
		
		if(h[i] < h[j]) {
			arr[i] = arr[j];
		} else if(h[i] > h[j]) {
			arr[j] = arr[i];
		} else {
			arr[i] = arr[j];
			h[j]++;
		}
		cout << p << " " << q << endl;
	}
}

void weighted_fast_union_half_path_compression(ifstream& f, int* arr, int* v, int length)
{
	int p, q, i, j;
	while(f >> p >> q) {
		if(p >= length || q >= length) {
			cout << "Invalid input (" << p << "," << q << ")," << " out of range(" << length << ")" << endl;
			continue;
		}

		for(i = p; i != arr[i]; i = arr[i])
			arr[i] = arr[arr[i]];
		for(j = q; j != arr[j]; j = arr[j])
			arr[j] = arr[arr[j]];

		if(i == j)
			continue;
		
		if(v[i] <= v[j]) {
			arr[i] = arr[j];
			v[j] += v[i];
		} else {
			arr[j] = arr[i];
			v[i] += v[j];
		}
		cout << p << " " << q << endl;
	}
}

void weighted_fast_union_full_path_compression(ifstream& f, int* arr, int* v, int length)
{
	int p, q, i, j;
	while(f >> p >> q) {
		if(p >= length || q >= length) {
			cout << "Invalid input (" << p << "," << q << ")," << " out of range(" << length << ")" << endl;
			continue;
		}

		for(i = p; i != arr[i]; i = arr[i]);
		for(j = q; j != arr[j]; j = arr[j]);

		if(i == j)
			continue;
		
		if(v[i] <= v[j]) {
			arr[i] = arr[j];
			v[j] += v[i];
			/* arr[j] is a new root */
			for(i = p; i != arr[i]; i = arr[i])
				arr[i] = arr[j];
		} else {
			arr[j] = arr[i];
			v[i] += v[j];
			/* arr[i] is a new root */
			for(j = p; j != arr[j]; j = arr[j])
				arr[j] = arr[i];
		}

		cout << p << " " << q << endl;
	}
}

static void prepare(ifstream& f, int* arr, int* v, int length)
{
	f.clear();
	f.seekg(0, ios_base::beg);
	for(int i = 0; i < length; i++) {
		arr[i] = i;
		v[i] = 1;
	}
}

int main(int argc, char** argv)
{
	int length;
	ifstream file;
	int* arr;
	int* v;


	if(argc != 3 || ((length = atoi(argv[2])) == 0)) {
		cout << "Invalid argc count, need file name and not zero array size" << endl;
		return EXIT_FAILURE;
	}

	file.open(argv[1]);
	if(!file.is_open()) {
		cout << "Error open file: " << strerror(errno) << endl;
		return EXIT_FAILURE;
	}

	arr = new int[length];
	if(!arr) {
		cout << "Failed to allocate " << sizeof(int) * length << " bytes" << endl;
		file.close();
		return EXIT_FAILURE;
	}

	v = new int[length];
	if(!arr) {
		cout << "Failed to allocate " << sizeof(int) * length << " bytes" << endl;
		delete[] arr;
		file.close();
		return EXIT_FAILURE;
	}

	cout << "Fast find:" << endl;
	prepare(file, arr, v, length);
	fast_find(file, arr, length);
	cout << endl;

	cout << "Fast union:" << endl;
	prepare(file, arr, v, length);
	fast_union(file, arr, length);
	cout << endl;

	cout << "Fast weighted union:" << endl;
	prepare(file, arr, v, length);
	weighted_fast_union(file, arr, v, length);
	cout << endl;

	cout << "Fast heighted union:" << endl;
	prepare(file, arr, v, length);
	heighted_fast_union(file, arr, v, length);
	cout << endl;	

	cout << "Fast weighted union with half path compression:" << endl;
	prepare(file, arr, v, length);
	weighted_fast_union_half_path_compression(file, arr, v, length);
	cout << endl;

	cout << "Fast weighted union with full path compression:" << endl;
	prepare(file, arr, v, length);
	weighted_fast_union_full_path_compression(file, arr, v, length);
	cout << endl;

	delete[] arr;
	delete[] v;
	file.close();
	return EXIT_SUCCESS;
}
