#include<X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void draw_ruler_r(Display *d, Window* w, int s, int xl, int xr, int y, int h)
{
	int xm;
	if(h) {
		xm = (xl + xr) / 2;
		draw_ruler_r(d, w, s, xl, xm, y, h / 2);
		XDrawLine(d, *w, DefaultGC(d, s), xm, y, xm, y + h);
		draw_ruler_r(d, w, s, xm, xr, y, h / 2);
	}
}

void draw_ruler_v(Display *d, Window* w, int s, int xl, int xr, int y, int h)
{
	int i, j, t , delta  = (xr -xl) / (2 * h);	
	for(i = 1, t = 1; t <= h; t *= 2, i *= 2)
		for(j = xl + i * delta; j < xr; j += 2 * i * delta)
			XDrawLine(d, *w, DefaultGC(d, s), j, y, j, y + t);	
}

void draw_star_r(Display* d, Window* w, int s, int x, int y, int l)
{
	if(l) {
		XFillRectangle(d, *w, DefaultGC(d, s), x - l / 2, y - l / 2, l, l);
		draw_star_r(d, w, s, x - l / 2, y - l / 2, l / 2);
		draw_star_r(d, w, s, x + l / 2, y - l / 2, l / 2);
		draw_star_r(d, w, s, x - l / 2, y + l / 2, l / 2);
		draw_star_r(d, w, s, x + l / 2, y + l / 2, l / 2);
	}
}

void draw_kox_star_r(Display* d, Window* w, int s, int x1, int y1, int x2, int y2, int i, int p)
{
	if(i <= p) {
		draw_kox_star_r(d, w, s, x1, y1, (2 * x1 + x2) / 3, (2 * y1 + y2) / 3, i + 1, p);
		draw_kox_star_r(d, w, s, (2 * x1 + x2) / 3, (2 * y1 + y2) / 3,/**/, i + 1, p);
		draw_kox_star_r(d, w, s,/**/, (x1 + 2* x2) / 3, (y1 + 2 * y2) / 3, i + 1, p);
		draw_kox_star_r(d, w, s, (x1 + 2* x2) / 3, (y1 + 2 * y2) / 3, x2, y2, i + 1, p);

	}
}

int main()
{
	Display *d;
	int s;
	Window w;
	XEvent e;
	d = XOpenDisplay(NULL);
	if(d == NULL) {
    	printf("Cannot open display\n");
     	return EXIT_FAILURE;
	}
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, 512, 800, 1,
    					  BlackPixel(d, s), WhitePixel(d, s));

	XSelectInput(d, w, ExposureMask);
	XMapWindow(d, w);
	while(true) {
		XNextEvent(d, &e);
		if(e.type==Expose) {
			draw_ruler_r(d, &w, s, 128, 384, 100, 64);
			draw_ruler_v(d, &w, s, 128, 384, 300, 64);
			draw_star_r(d, &w, s, 256, 500, 64);
		}


		if(e.type == ClientMessage)
			break;
	}

	XDestroyWindow(d, w);
	XCloseDisplay(d);	
	return EXIT_SUCCESS;
}