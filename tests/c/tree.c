#include<X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <c/tree.h>

#define SIZE 10
#define SIZE_OF_ARR(arr) sizeof(arr) / sizeof(arr[0])

static int generate_union_find_tree(int* arr, const int size)
{
	int i, j, p, q, root, n = 0;
	for(i = 0; i < size; i++)
		arr[i] = i;	
	while(n < size - 1) {
		p = rand()%size;
		q = rand()%size;
		for(i = p; i != arr[i]; i = arr[i]);
		for(j = q; j != arr[j]; j = arr[j]);
		if(arr[i] == arr[j])
			continue;
		arr[i] = arr[j];
		root = arr[j];
		n++;
	}
	return root;
}

void draw_tree(Display* d, Window* w, int s, const int* arr, const int size, int rx, int ry, int root, int level)
{
	int x, y;
	if(level == 0) {
		XDrawArc(d, *w, DefaultGC(d, s), rx, ry, 20, 20, 0, 64 * 360);
		draw_tree(d, w, s, arr, size, rx, ry, root, level + 1);
	} else {
		x = rx - 100 / level;
		y = ry + 50;
		for(int i = 0; i < size; i++)
			if(arr[i] == root && i != root) {
				XDrawArc(d, *w, DefaultGC(d, s), x, y, 20, 20, 0, 64 * 360);
				XDrawLine(d, *w, DefaultGC(d, s), x + 10, y + 10, rx + 10, ry + 10);
				draw_tree(d, w, s, arr, size, x, y, i, level + 1);
				x += 100 / level;
			}
	}
}

static int is1[] = { 2, 2, 3, 3, 3};
static int is2[] = { 0, 2, 0, 2, 3};
static int is3[] = { 2, 2, 2, 2, 3};

int main()
{
	int arr_1[SIZE], arr_2[SIZE];
	Display *d;
	int s, root_1, root_2;
	Window w;
	XEvent e;
	srand(time(NULL));

	if(!is_isomorphic_tree(is1, is2, SIZE_OF_ARR(is1)) || !is_isomorphic_tree(is1, is3, SIZE_OF_ARR(is1)) ||
	   !is_isomorphic_tree(is2, is3, SIZE_OF_ARR(is1))) {
		printf("Simple isomorphic tree test failed\n");
		return EXIT_FAILURE;
	}

	d = XOpenDisplay(NULL);
	if(d == NULL) {
    	printf("Cannot open display\n");
     	return EXIT_FAILURE;
	}
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, 2000, 2000, 1,
    					  BlackPixel(d, s), WhitePixel(d, s));

	XSelectInput(d, w, ExposureMask);
	XMapWindow(d, w);
	while(true) {
		XNextEvent(d, &e);
		if(e.type==Expose) {
			while(true) {
				/* generate and draw isomorphic trees */
				root_1 = generate_union_find_tree(arr_1, SIZE);
				root_2 = generate_union_find_tree(arr_2, SIZE);
				if(!is_isomorphic_tree(arr_1, arr_2, SIZE))
					continue;
				else
					break;
			}

			draw_tree(d, &w, s, arr_1, SIZE, 500, 50, root_1, 0);
			draw_tree(d, &w, s, arr_2, SIZE, 500, 550, root_2, 0);			
		}


		if(e.type == ClientMessage)
			break;
	}

	XDestroyWindow(d, w);
	XCloseDisplay(d);	
	return EXIT_SUCCESS;
}