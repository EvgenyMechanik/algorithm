#include <iostream>
#include <cstdlib>
using namespace std;

#define N 100

void simple_numbers_s(unsigned long number)
{
	unsigned char* arr = new unsigned char[number];
	if(!arr) {
		cout << "Failed to allocate " << number << " bytes";
		return;
	}

	for(unsigned long i = 0; i < number; i++)
		arr[i] = 1;

	for(unsigned long i = 2; i < number; i++)
		if(arr[i])
			for(unsigned long j = i; i * j < number; j++)
				arr[i*j] = 0;

	for(unsigned long i = 1; i < number; i++)
		if(arr[i])
			cout << i << " ";

	delete[] arr;
}

void simple_numbers_m(unsigned long number)
{
	unsigned char* arr = new unsigned char[number / 8 + 1];
	if(!arr) {
		cout << "Failed to allocate " << number << " bytes";
		return;
	}

	for(unsigned long i = 0; i < number / 8 + 1; i++)
		arr[i] = 0xFF;

	for(unsigned long i = 2; i < number; i++)
		if(arr[i / 8] & (1 << (i % 8)))
			for(unsigned long j = i; i * j < number; j++)
				arr[i * j / 8] &= ~(1 << ((i * j) % 8));

	for(unsigned long i = 1; i < number; i++)
		if(arr[i / 8] & (1 << (i % 8)))
			cout << i << " ";		

	delete[] arr;	
}

int main()
{
	simple_numbers_s(N);
	cout << endl;
	simple_numbers_m(N);
	cout << endl;
	return EXIT_SUCCESS;
}	
