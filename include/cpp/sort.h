#ifndef _SORT_H
#define _SORT_H

template <class T>
bool check_sort(const T* arr, int l, int r, int (*cmp)(const T&, const T&))
{
	for(int i = l; i < r; i++)
		if(cmp(arr[i], arr[i + 1]) > 0)
			return false;
	return true;
}

template <class T>
bool is_stable_sort(const T* arr, int l, int r , int (*first_key_cmp)(const T&, const T&), 
	                int (*second_key_cmp)(const T&, const T&))
{
	for(int i = l; i < r; i++)
		if(!second_key_cmp(arr[i], arr[i + 1]) && first_key_cmp(arr[i], arr[i + 1]) > 0)
			return false;
	return true;
}

template <class T>
void choice_sort(T* arr, int l, int r, int (*cmp)(const T&, const T&))
{
	int min;
	T t;
	for(int i = l; i < r; i++) {
		min = i;
		for(int j = i + 1; j <= r; j++)
			if(cmp(arr[j], arr[min]) < 0)
				min =  j;
		t = arr[min];
		arr[min] = arr[i];
		arr[i] = t; 
	}
}

template <class T>
void insert_sort(T* arr, int l, int r, int (*cmp)(const T&, const T&))
{
	T v;
	int j;	
	for(int i = l + 1; i <= r; i++) {
		j = i;
		v = arr[j];
		while(j >= l + 1 && cmp(v, arr[j - 1]) < 0) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = v;
	}
}

template <class T>
void bubble_sort(T* arr, int l, int r, int (*cmp)(const T&, const T&))
{
	T t;
	for(int i = l; i < r; i++)
		for(int j = r; j > i; j--)
			if(cmp(arr[j], arr[j - 1]) < 0) {
				t = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = t; 
			}
}

template <class T>
void sheyker_sort(T* arr, int l, int r, int (*cmp)(const T&, const T&))
{
	T t;
	bool need = true;
	while(l < r && need) {
		need = false;
		for(int i = l; i < r; i++)
			if(cmp(arr[i], arr[i + 1]) > 0) {
				t = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = t;
				need = true;
			}
		r--;
		for(int i = r; i > l; i--)
			if(cmp(arr[i], arr[i - 1]) < 0) {
				t = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = t;
				need = true;
			}
		l++;
	}
}

template <class T>
void shell_sort(T* arr, int l, int r, int (*cmp)(const T&, const T&))
{
	T v;
	int h, j;
	for(h = 1; h <= (r - l) / 9; h = 3 * h + 1);
	for(; h > 0; h /= 3) {
		for(int i = l + h; i <= r; i ++) {
			j = i;
			v = arr[j];
			while(j >= l + h && cmp(v, arr[j - h]) < 0) {
				arr[j] = arr[j - h];
				j -= h;
			}
			arr[j] = v;
		}
	}
}

#endif