#include "cell.init"


/** sets foreground to a specific color (0: balck, 1: white) **/
/** predefined colors (palette = 1) are indexed from 300 - 315, user defined colors **/
/** (palette = 2) are indexed from 400 - 400+NCOLORS2-1 **/

void SET_COLOR (color, palette)
int color, palette;
{
int i;
  if ((palette == 1) && (color > 1))
    {
      i = color - 300;
      if (i > NCOLORS1)
	printf (" wrong color allocation \n");
      i = color_offset1[i];
    }
  if ((palette == 2) && (color > 1))
    {
      i = color - 400;
      if (i > NCOLORS2)
	printf (" wrong color allocation \n");
      i = color_offset2[i];
    }
  if (color > 1)
  XSetForeground (DISPLAY, CONTEXT, i);
else 
  if (color == 0)
    XSetForeground (DISPLAY, CONTEXT, BlackPixelOfScreen (DefaultScreenOfDisplay (DISPLAY)));
else
  if (color == 1)
    XSetForeground (DISPLAY, CONTEXT, WhitePixelOfScreen (DefaultScreenOfDisplay (DISPLAY)));

    

}


/** stores 16 predefined colors (as defined in gra.init ) **/ 

void COULEURS ()

{
        unsigned long  cellules[16];
	int ncouleurs;
	XColor	col;
	XColor  colors[16];
	int 	i;

	color_offset1 = (int *) calloc (16, sizeof (int));

	ncouleurs = XDisplayCells(DISPLAY, DefaultScreen (DISPLAY));

	XAllocColorCells(DISPLAY, 
			 DefaultColormap(DISPLAY, DefaultScreen (DISPLAY)), 
			 True,		/* True = cellules contigues */
			 NULL, 		/* plane mask return */
			 0, 	        /* nplanes */
			 cellules,      /* pixels_return */
			 16);
	for (i=0;i<=16;i++)
	     color_offset1[i] = cellules[i];
	 col.flags = DoRed|DoGreen|DoBlue;
	 
        col.red = 65535;	col.green = 0;		col.blue = 0;		col.pixel=cellules[0];	colors[0]=col;
	col.red = 0;		col.green = 65535;	col.blue = 0;		col.pixel=cellules[1];	colors[1]=col;
	col.red = 0;		col.green = 0;		col.blue = 65535;	col.pixel=cellules[2];	colors[2]=col;
	col.red = 65535;	col.green = 65535;	col.blue = 0;		col.pixel=cellules[3];	colors[3]=col;
	
        col.red = 40000;	col.green = 16000;	col.blue = 60000;	col.pixel=cellules[4];	colors[4]=col;
	col.red = 65000;	col.green = 33000;	col.blue = 0;		col.pixel=cellules[5];	colors[5]=col;
	col.red = 65000;	col.green = 0;		col.blue = 65000;	col.pixel=cellules[6];	colors[6]=col;
	col.red = 0;		col.green = 65535;	col.blue = 65000;	col.pixel=cellules[7];	colors[7]=col;
	
	col.red = 33000;	col.green = 33000;	col.blue = 33000;	col.pixel=cellules[8];	colors[8]=col;
	col.red = 0;		col.green = 40000;	col.blue = 45000;	col.pixel=cellules[9];	colors[9]=col;
	col.red = 65000;	col.green = 45000;	col.blue = 45000;	col.pixel=cellules[10];	colors[10]=col;
	col.red = 33000;	col.green = 0;		col.blue = 0;		col.pixel=cellules[11];	colors[11]=col;
	
	
	col.red = 0;		col.green = 33000;	col.blue = 0;		col.pixel=cellules[12];	colors[12]=col;
        col.red = 0;		col.green = 0;		col.blue = 33000;	col.pixel=cellules[13];	colors[13]=col;
	col.red = 65000;	col.green = 57000;	col.blue = 46000;	col.pixel=cellules[14];	colors[14]=col;
	col.red = 39000;	col.green = 27000;      col.blue = 27000;	col.pixel=cellules[15];	colors[15]=col;

	XStoreColors(DISPLAY, DefaultColormap(DISPLAY, DefaultScreen (DISPLAY)), colors, 16);
	NCOLORS1 = 16;

}

/** loads colors defined in file "filename" **/
/** first line of file contains number of colors in file, **/
/** subsequent lines integer values for red, green and blue pixels **/

void COLORMAP (filename)
char *filename;
{
FILE *read_from;
int nr, ng, nb;
        unsigned long  *cellules;
	int ncouleurs;
	XColor	col;
	XColor  *colors;
	int 	i;
        if ((read_from = fopen (filename, "r")) == NULL)
	  {
	    printf (" error in open file \n");
	    exit (0);
	  }
        fscanf (read_from, "%d", &ncouleurs);
	color_offset2 = (int *) calloc (ncouleurs, sizeof (int));
        colors = (XColor *) calloc (ncouleurs, sizeof (XColor));
        cellules = (unsigned long * ) calloc (ncouleurs, sizeof (unsigned long));
	XAllocColorCells(DISPLAY, 
			 DefaultColormap(DISPLAY, DefaultScreen (DISPLAY)), 
			 True,		/* True = cellules contigues */
			 NULL, 		/* plane mask return */
			 0, 	        /* nplanes */
			 cellules,      /* pixels_return */
			 ncouleurs);
	for (i = 0; i <= ncouleurs; i++)
	     color_offset2[i] = cellules[i];
	
        col.flags = DoRed|DoGreen|DoBlue;

        for (i = 0; i < ncouleurs; i++)
	  {
	    fscanf (read_from, "%d %d %d", &nr, &ng, &nb);
	    col.red = nr; col.green = ng; col.blue = nb; col.pixel = cellules[i]; colors[i] = col;
	  }
        fclose (read_from);
	 
	XStoreColors(DISPLAY, DefaultColormap(DISPLAY, DefaultScreen (DISPLAY)), colors, ncouleurs);
        NCOLORS2 = ncouleurs;
}
