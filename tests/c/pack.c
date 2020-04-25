#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPACE 100
#define MAX_ITEMS 10
#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

typedef struct item {
	int size;
	int cost;
} item;
static const item items[] = { { 3, 4 }, {4, 5} , {7, 10}, {8, 11}, {9, 13} };


int optimum_pack_n(const item* items, int length, int space)
{
	int max, i, t, s;
	static int remember[MAX_SPACE];
	if(remember[space])
		return remember[space];
	for(i = 0, max = 0; i < length; i++)
		if((s = space - items[i].size) >=0)
			if((t = items[i].cost + optimum_pack_n(items, length, s)) > max)
				max = t;
	remember[space] = max;
	return max;
}

int optimum_pack_v(const item* items, int length, int space)
{
	int i, j, s, t, max;
	static int remember[MAX_SPACE];
	for(i = 0; i <= space; i++) {
		max = 0;
		for(j = 0; j < length; j++)
			if((s = i - items[j].size) >= 0)
				if((t = items[j].cost + remember[s]) > max)
					max = t;
		remember[i] = max;
	}
	return remember[space];
}

int optimum_pack_n1(const item* items, int length, int space)
{
	int i, j, s, t, tt, max;
	static int remember[MAX_SPACE];
	if(remember[space])
		return remember[space];

	for(i = 0, max = 0; i < length; i++) {
		s = space;
		t = 0;
		for(j = 0; s >= 0; j++, s -= items[i].size) {			
			if((tt = optimum_pack_n1(items + 1, length - 1, s) + t) > max)
				max = tt;
			t += items[i].cost;
		}
	}

	remember[space] = max;
	return max;
}

int optimum_pack_v1(const item* items, int length, int space)
{
	int i, s;
	static int remember[MAX_SPACE];

	for(i = 0; i < length; i++)
		for(s = 0; s <= space; s++)
			if(s + items[i].size <= space)
				if(remember[s] + items[i].cost > remember[s + items[i].size])
					remember[s + items[i].size] = remember[s] + items[i].cost;		

	return remember[space];
}

int main(int argc, char const *argv[])
{
	int i, n, v, n1, v1;
	for(i = 0; i <= MAX_SPACE; i++) {
		n = optimum_pack_n(items, ARRAY_SIZE(items), i);
		v = optimum_pack_v(items, ARRAY_SIZE(items), i);
		n1 = optimum_pack_n1(items, ARRAY_SIZE(items), i);
		v1 = optimum_pack_v1(items, ARRAY_SIZE(items), i);
		if(n != v || n != n1 || n != v1)
			printf("Test failed fo %d pack size: %d %d %d\n", i, n, v, n1);
	}

	printf("Pack test success\n");
	return 0;
}