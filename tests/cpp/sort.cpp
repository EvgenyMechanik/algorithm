#include <cpp/sort.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define N 10000
#define M 10
#define SZARR(arr) sizeof(arr) / sizeof(arr[0])

typedef struct {
	int first_key;
	int second_key;
} stable_sort_test;

static int stable_test_cmp_f(const stable_sort_test& i1, const stable_sort_test& i2)
{
	if(i1.first_key < i2.first_key)
		return -1;
	else if(i1.first_key > i2.first_key)
		return 1;
	return 0;
}

static int stable_test_cmp_s(const stable_sort_test& i1, const stable_sort_test& i2)
{
	if(i1.second_key < i2.second_key)
		return -1;
	else if(i1.second_key > i2.second_key)
		return 1;
	return 0;
}

static int compare(const int& i1, const int& i2)
{
	if(i1 < i2)
		return -1;
	else if(i1 > i2)
		return 1;
	return 0;
}

template <class T>
static bool test_stable_sort(void (*sort)(T* arr, int l, int r, int (*cmp)(const T&, const T&)), 
	                         int (*first_key_cmp)(const T&, const T&), int (*second_key_cmp)(const T&, const T&))
{
	stable_sort_test s_test[N];
	for(int i = 0; i < N; i++) {
		s_test[i].first_key = rand() % M;
		s_test[i].second_key = rand() % M;
	}

	sort(s_test, 0, N - 1, first_key_cmp);
	if(!check_sort(s_test, 0, N - 1, first_key_cmp))
		return false;
	sort(s_test, 0, N - 1, second_key_cmp);
	if(!check_sort(s_test, 0, N - 1, second_key_cmp))
		return false;
	return is_stable_sort(s_test, 0, N - 1, first_key_cmp, second_key_cmp);
}

int main()
{
	srand(time(NULL));
	int arr_choice[N], arr_insert[N], arr_bubble[N], arr_sheyker[N], arr_shell[N];
	for(int i = 0; i < N; i++)
		arr_choice[i] = arr_insert[i] = arr_bubble[i] = arr_sheyker[i] = arr_shell[i] = rand() % N;  
	choice_sort(arr_choice, 0, N - 1, compare);
	if(!check_sort(arr_choice, 0, N - 1, compare)) {
		std::cout << "Bad choice sort" << std:: endl;
		return EXIT_FAILURE;
	}

	if(test_stable_sort(choice_sort, stable_test_cmp_f, stable_test_cmp_s))
		std:: cout << "Choice sort is stable" << std::endl;
	else
		std:: cout << "Choice sort is unstable" << std::endl;

	insert_sort(arr_insert, 0, N - 1, compare);
	if(!check_sort(arr_insert, 0, N - 1, compare)) {
		std::cout << "Bad insert sort" << std:: endl;
		return EXIT_FAILURE;
	}

	if(test_stable_sort(insert_sort, stable_test_cmp_f, stable_test_cmp_s))
		std:: cout << "Insert sort is stable" << std::endl;
	else
		std:: cout << "Insert sort is unstable" << std::endl;

	bubble_sort(arr_bubble, 0, N - 1, compare);
	if(!check_sort(arr_bubble, 0, N - 1, compare)) {
		std::cout << "Bad bubble sort" << std:: endl;
		return EXIT_FAILURE;
	}

	if(test_stable_sort(bubble_sort, stable_test_cmp_f, stable_test_cmp_s))
		std:: cout << "Bubble sort is stable" << std::endl;
	else
		std:: cout << "Bubble sort is unstable" << std::endl;

	sheyker_sort(arr_sheyker, 0, N - 1, compare);
	if(!check_sort(arr_sheyker, 0, N - 1, compare)) {
		std::cout << "Bad sheyker sort" << std:: endl;
		return EXIT_FAILURE;
	}

	if(test_stable_sort(sheyker_sort, stable_test_cmp_f, stable_test_cmp_s))
		std:: cout << "Sheyker sort is stable" << std::endl;
	else
		std:: cout << "Sheyker sort is unstable" << std::endl;

	shell_sort(arr_shell, 0, N - 1, compare);
	if(!check_sort(arr_shell, 0, N - 1, compare)) {
		std::cout << "Bad shell sort" << std:: endl;
		return EXIT_FAILURE;
	}

	if(test_stable_sort(shell_sort, stable_test_cmp_f, stable_test_cmp_s))
		std:: cout << "Shell sort is stable" << std::endl;
	else
		std:: cout << "Shell sort is unstable" << std::endl;

	std:: cout << "All sort test success" << std::endl;

	return EXIT_SUCCESS;
}