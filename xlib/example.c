#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <assert.h>
Display *dpy;
Window win;
int scr;


void send_spot(XIC ic, XPoint nspot) {
	XVaNestedList preedit_attr;
	preedit_attr = XVaCreateNestedList(0, XNSpotLocation, &nspot, NULL);
	XSetICValues(ic, XNPreeditAttributes, preedit_attr, NULL);
	XFree(preedit_attr);
}

int main() {
	/* fallback to LC_CTYPE in env */
	setlocale(LC_CTYPE, "");
	XSetLocaleModifiers("");
	dpy = XOpenDisplay(NULL);
	scr = DefaultScreen(dpy);
	win = XCreateSimpleWindow(dpy,
			XDefaultRootWindow(dpy),
			0, 0, 100, 100, 5,
			BlackPixel(dpy, scr),
			BlackPixel(dpy, scr));
	XMapWindow(dpy, win);
	XIM xim = XOpenIM(dpy, NULL, NULL, NULL);
	XIC ic = XCreateIC(xim,
			/* the following are in attr, val format, terminated by NULL */
			XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
			XNClientWindow, win,
			NULL);
	/* focus on the only IC */
	XSetICFocus(ic);
	/* capture the input */
	XSelectInput(dpy, win, KeyPressMask);

XPoint spot;
spot.x = 0;
spot.y = 0;
send_spot(ic, spot);

	static char *buff;
	size_t buff_size = 16;
	buff = (char *)malloc(buff_size);
	for (;;)
	{
		KeySym ksym;
		Status status;
		XEvent ev;
		XNextEvent(dpy, &ev);
		printf("miong!");
		fflush(stdout);
		if (XFilterEvent(&ev, None))
			continue;
		if (ev.type == KeyPress)
		{
			size_t c = Xutf8LookupString(ic, &ev.xkey,
					buff, buff_size - 1,
					&ksym, &status);
			if (status == XBufferOverflow)
			{
				printf("reallocate to the size of: %lu\n", c + 1);
				buff = realloc(buff, c + 1);
				c = Xutf8LookupString(ic, &ev.xkey,
						buff, c,
						&ksym, &status);
			}
			if (c)
			{
				spot.x += 20;
				spot.y += 20;
				send_spot(ic, spot);
				buff[c] = 0;
				printf("delievered string: %s\n", buff);
			}
		}
	}
}

