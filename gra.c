/*window and graphic functions */

#include "cell.init"
void INIT_GRAPHICS ()
{
  if ((DISPLAY = XOpenDisplay (NULL)) == NULL)
      {
      printf (" error in open display\n");
      exit (0);
      }
  CONTEXT = DefaultGCOfScreen (DefaultScreenOfDisplay (DISPLAY));
 /*COULEURS ();*/
printf (" end of init graphics \n");
}


Window OPEN_WINDOW (x0, y0, width, height, backg)
int x0, y0; 
int width, height;
int backg;
{
Window window;
int black, white;

	black = BlackPixelOfScreen (DefaultScreenOfDisplay (DISPLAY));
	white = WhitePixelOfScreen (DefaultScreenOfDisplay (DISPLAY));
  	if (backg == blanc)
	  window = XCreateSimpleWindow (DISPLAY, 
      	      	      	      	 	DefaultRootWindow (DISPLAY),
      	      	      	      	  	x0, y0, width, height, 1,
      	      	      	      	  	black, white
      	      	      	      	  	);
  	if (backg == noir)
	  window = XCreateSimpleWindow (DISPLAY, 
      	      	      	      	 	DefaultRootWindow (DISPLAY),
      	      	      	      	  	x0, y0, width, height, 1,
      	      	      	      	  	white, black
      	      	      	      	  	);

	XSelectInput (DISPLAY, window, ExposureMask|ButtonPressMask|KeyPressMask);

	XMapWindow (DISPLAY, window);
/*        XSetWindowColormap (DISPLAY, window, DefaultColormap (DISPLAY, DefaultScreen (DISPLAY)));
*/
  return (window);

}


void DESTROY_WINDOW (window)
Window window;
{
  XDestroyWindow (DISPLAY, window);
}


EVENT GET_EVENT ()

{
EVENT one;
char buf[30];
KeySym keys;
XEvent event;
      XNextEvent (DISPLAY, &event);
	if (event.type == ButtonPress)
		{
  		one.flag = mouse;
		one.button = event.xbutton.button;
		one.xpos = event.xbutton.x;
		one.ypos = event.xbutton.y;
		}	
	if (event.type == KeyPress)
		{
		one.flag = key;
		XLookupString (&event.xkey, buf, 10, &keys, NULL);
		one.key = XKeysymToString (keys);
		one.xpos = event.xkey.x;
		one.ypos = event.xkey.y;
		}
      	if (event.type == Expose)
      	  one.flag == expose;
	return (one);
}
	


void LINE (x1, y1, x2, y2)
int x1, y1, x2, y2;
{
  	XDrawLine (DISPLAY, CURRENTW, CONTEXT, x1, y1, x2, y2);
}

void CHOOSE_WINDOW (window)
Window window;
{
  	CURRENTW = window;
  	XRaiseWindow (DISPLAY, CURRENTW);
}

void TEXT (text, x, y)
char *text;
int   x, y;
{
  	XDrawString (DISPLAY, CURRENTW, CONTEXT, x, y, text, strlen (text));
}


void CLEAR ()
{
  	XClearWindow (DISPLAY, CURRENTW);
}

void CIRCLE (x, y, radius)
int x, y, radius;
{
  	XDrawArc (DISPLAY, CURRENTW, CONTEXT, x-radius, y-radius, radius, radius, 0, 360*64);
}


void FILLED_CIRCLE (x, y, radius)
int x, y, radius;
{
  	XFillArc (DISPLAY, CURRENTW, CONTEXT, x-radius, y-radius, radius, radius, 0, 360*64);
}

void BOX (x1, y1, x2, y2)
int   x1, y1, x2, y2;
{
  XDrawRectangle (DISPLAY, CURRENTW, CONTEXT, x1, y2, abs (x1 - x2), abs (y1 - y2));
}

void FILLED_BOX (x1, y1, x2, y2)
int x1, y1, x2, y2;
{
  XFillRectangle (DISPLAY, CURRENTW, CONTEXT, x1, y2, abs (x1-x2), abs (y1 - y2));
}



void TRIANGLE (x1, y1, x2, y2, x3, y3)
int x1, y1, x2, y2, x3, y3;
{
XPoint points[4];
  points[0].x = x1; 
  points[0].y = y1;
  points[1].x = x2; 
  points[1].y = y2; 
  points[2].x = x3;
  points[2].y = y3;
  points[3].x = x1;
  points[3].y = y1;
  XDrawLines (DISPLAY, CURRENTW, CONTEXT, points, 4, CoordModeOrigin);
}

void FILLED_TRIANGLE (x1, y1, x2, y2, x3, y3)
int x1, y1, x2, y2, x3, y3;
{
XPoint points[4];
  points[0].x = x1; 
  points[0].y = y1;
  points[1].x = x2; 
  points[1].y = y2; 
  points[2].x = x3;
  points[2].y = y3;
  points[3].x = x1;
  points[3].y = y1;
  XFillPolygon  (DISPLAY, CURRENTW, CONTEXT, points, 4, Nonconvex, CoordModeOrigin);
 
}

void INVERT ()
{
  XSetState (DISPLAY, CONTEXT, 0, 1, GXcopy, AllPlanes);
}

void SETBACK ()
{
  XSetState (DISPLAY, CONTEXT, 1, 0, GXcopy, AllPlanes);
}




void DRAW_POINT (x, y)
int x, y;
{
  XDrawPoint (DISPLAY, CURRENTW, CONTEXT, x, y);
}
