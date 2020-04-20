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
	w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, 400, 400, 1,
    					  BlackPixel(d, s), WhitePixel(d, s));

	XSelectInput(d, w, ExposureMask);
	XMapWindow(d, w);
	while(true) {
		XNextEvent(d, &e);
		if(e.type==Expose)
			draw_ruler_r(d, &w, s, 100, 300, 100, 50);

		if(e.type == ClientMessage)
			break;
	}

	XDestroyWindow(d, w);
	XCloseDisplay(d);	
	return EXIT_SUCCESS;
}