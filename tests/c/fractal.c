#include<X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void draw_ruler_r(Display *d, Window* w, int s, float xl, float xr, float y, int h)
{
	float xm;
	if(h) {
		xm = (xl + xr) / 2;
		draw_ruler_r(d, w, s, xl, xm, y, h / 2);
		XDrawLine(d, *w, DefaultGC(d, s), xm, y, xm, y + h);
		draw_ruler_r(d, w, s, xm, xr, y, h / 2);
	}
}

void draw_ruler_v(Display *d, Window* w, int s, float xl, float xr, float y, int h)
{
	int i, j, t;
	float delta  = (xr -xl) / (2 * h);	
	for(i = 1, t = 1; t <= h; t *= 2, i *= 2)
		for(j = xl + i * delta; j < xr; j += 2 * i * delta)
			XDrawLine(d, *w, DefaultGC(d, s), j, y, j, y + t);	
}

void draw_star_r(Display* d, Window* w, int s, float x, float y, int l)
{
	if(l) {
		XFillRectangle(d, *w, DefaultGC(d, s), x - l / 2, y - l / 2, l, l);
		draw_star_r(d, w, s, x - l / 2, y - l / 2, l / 2);
		draw_star_r(d, w, s, x + l / 2, y - l / 2, l / 2);
		draw_star_r(d, w, s, x - l / 2, y + l / 2, l / 2);
		draw_star_r(d, w, s, x + l / 2, y + l / 2, l / 2);
	}
}

static void calculate_x_y(float x1, float y1, float ox, float oy, float* x2, float* y2, float a)
{
	x1 -= ox; 
	y1 -= oy;
	*x2 = x1 * cos(a) - y1 * sin(a) + ox;
	*y2 = x1 * sin(a) + y1 * cos(a) + oy;
 }

void draw_kox_star_r(Display* d, Window* w, int s, float x1, float y1, float x2, float y2, int i, int p)
{
	float xx, yy;
	if(i <= p) {
		calculate_x_y(x1, y1, (2 * x1 + x2) / 3, (2 * y1 + y2) / 3, &xx, &yy, 2 * 3.14159 / 3);
		draw_kox_star_r(d, w, s, x1, y1, (2 * x1 + x2) / 3, (2 * y1 + y2) / 3, i + 1, p);
		draw_kox_star_r(d, w, s, (2 * x1 + x2) / 3, (2 * y1 + y2) / 3, xx, yy, i + 1, p);
		draw_kox_star_r(d, w, s, xx, yy, (x1 + 2* x2) / 3, (y1 + 2 * y2) / 3, i + 1, p);
		draw_kox_star_r(d, w, s, (x1 + 2* x2) / 3, (y1 + 2 * y2) / 3, x2, y2, i + 1, p);
		if(i == p) {
			XDrawLine(d, *w, DefaultGC(d, s), x1, y1, (2 * x1 + x2) / 3, (2 * y1 + y2) / 3);
			XDrawLine(d, *w, DefaultGC(d, s), (2 * x1 + x2) / 3, (2 * y1 + y2) / 3, xx, yy);
			XDrawLine(d, *w, DefaultGC(d, s), xx, yy, (x1 + 2* x2) / 3, (y1 + 2 * y2) / 3);
			XDrawLine(d, *w, DefaultGC(d, s), (x1 + 2* x2) / 3, (y1 + 2 * y2) / 3, x2, y2);
		} 
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
			draw_kox_star_r(d, &w, s, 128, 700, 384, 700, 1, 4);
		}


		if(e.type == ClientMessage)
			break;
	}

	XDestroyWindow(d, w);
	XCloseDisplay(d);	
	return EXIT_SUCCESS;
}