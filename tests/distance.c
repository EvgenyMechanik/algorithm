#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

#include <list.h>

#define N 100000
#define d 0.01

typedef struct point {
	double x;
	double y;
} point;

static double distance(const point* a, const point* b)
{
	return sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
}

static int simple_d_point_count(const point* arr)
{
	int i, j, count = 0;
	for(i = 0; i < N; i++)
		for(j = i + 1; j < N; j++)
			if(distance(&arr[i], &arr[j]) < d)
				count++;
	return count;
}

static int fast_d_point_count(const point* arr)
{	
	typedef struct pnode {
		listhead node;
		point p;
	} pnode; 

	int i, j, p, X, Y, count = 0, G = 1 / d;
	listhead *x, *s;
	pnode *n;
	pnode **list = (pnode**)malloc((G + 2) * sizeof(pnode*));
	
	if(!list) {
		printf("Failed to allocate %u bytes\n", (G + 2) * sizeof(pnode*));
		return -1;
	}	

	for(i = 0; i < G + 2; i++) {
		list[i] = (pnode*)malloc((G + 2) * sizeof(pnode));
		if(!list[i]) {
			for(j = 0; j < i; j++)
				free(list[j]);
			free(list);
			return -1;	  
		}
		for(j = 0; j < G + 2; j++)
			INIT_LIST_HEAD(list[i][j].node);
	}

	for(p = 0; p < N; p++) {
		X = G * arr[p].x + 1;
		Y = G * arr[p].y + 1;
		pnode* newnode = (pnode*)malloc(sizeof(pnode));
		if(!newnode) {
			printf("Failed to allocate %u bytes\n", sizeof(pnode));
			count = -1;
			goto finish;
		}

		newnode->p = arr[p];
		INIT_LIST_HEAD(newnode->node);
		for(i = X - 1; i <= X + 1; i++)
			for(j = Y - 1; j <= Y + 1; j++) {
				list_for_each(list[i][j].node, x) {					
					n = container_of(x, pnode, node);
					if(distance(&newnode->p, &n->p) < d)
						count++;
				}
			}
		list_add_tail(&(list[X][Y].node), &newnode->node);			
	}

finish:
	for(i = 0; i < G + 2; i++)
		for(j = 0; j < G + 2; j++)
			list_for_each_safe(list[i][j].node, x, s) {
				n = container_of(x, pnode, node);
				free(n);
			}

	for(i = 0; i < G + 2; i++)
		free(list[i]);
	free(list);
	return count;
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

	printf("%d %d\n", simple_d_point_count(arr), fast_d_point_count(arr));
	return EXIT_SUCCESS;
}