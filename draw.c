
/* display neural activities */

#include "cell.init"


char *NTEXT (unit)
int 	unit;
{
char chain[20];   
  if (units[unit].type == mitral)
	sprintf (chain, "m1 %d", units[unit].couche);
  if (units[unit].type == PG)
      	sprintf (chain, "pg %d", units[unit].couche);
  if (units[unit].type == mitral2)
      	sprintf (chain, "m2 %d", units[unit].couche);
  if (units[unit].type == granule)
      	sprintf (chain, "gr %d", units[unit].couche);
  if (units[unit].type == receptor)
      	sprintf (chain, " R %d", unit);  
  if (units[unit].type == pyr)
      	sprintf (chain, "p %d", units[unit].couche);
  if (units[unit].type == inhib1)
      	sprintf (chain, "i1 %d", units[unit].couche);
  if (units[unit].type == inhib2)
      	sprintf (chain, "i2 %d", units[unit].couche);
  /*if (units[unit].type == chol)
	sprintf (chain,"chol");*/
  if (units[unit].type == pyr)
	sprintf (chain, "p1 %d", units[unit].couche);
  /*if (units[unit].type == pyr2)
	sprintf (chain, "p2 %d", units[unit].couche);*/

  return (chain);
}

void SELECT (y, ymul, w)
int   	  y, ymul;
WIND      w;
{
int   max, min;
int   unit;
  for (unit = w.from; unit < w.too; unit++)
      {
      max = units[unit].y_coor + ymul;
      min = units[unit].y_coor - ymul;
      if ((y > min) && (y < max))
      	  break;
      }
  units[unit].selected = VRAI;
  CIRCLE (units[unit].x_coor-5, units[unit].y_coor, 2);
}

void DESELECT (y, ymul, w)
int   	  y, ymul;
WIND	  w;
{
int   max, min;
int   unit;
  for (unit = w.from; unit < w.too; unit++)
      {
      max = units[unit].y_coor + ymul;
      min = units[unit].y_coor - ymul;
      if ((y > min) && (y < max))
      	  break;
      }
  units[unit].selected = FAUX;
  INVERT ();
  CIRCLE (units[unit].x_coor-5, units[unit].y_coor, 2);
  SETBACK ();
}


void RESET_COOR ()
{
int unit;
	for (unit = 0; unit < N_UNITS; unit++)
		units[unit].x_coor = units[unit].y_coor = 0;
}

void DESELECT_ALL ()
{
int unit;                               
	for (unit = 0; unit < N_UNITS; unit++)
	  if (units[unit].selected == VRAI)
	      {
	      units[unit].selected = FAUX;                           
		INVERT ();
		CIRCLE (units[unit].x_coor-5, units[unit].y_coor, 2);
		SETBACK ();
		}
}


void DRAW_MOLECULES (x, y, xmul)
int x, y, xmul;
{
         
int x0, x1, m, o, y1;
	for (o = 0; o < NODS; o++)    
		{
		x1 = x + odors[o].from * xmul;
		for (m = 0; m < MOL; m++)
			{ 
			if (odors[o].values[m] != 0.0)
				FILLED_CIRCLE (x1, y, 5);
			else 
				CIRCLE (x1, y, 5);
			x1 += 10;
			}	   
		x1 = x + odors[o].from * xmul;
              	y1 = y - 10;
		FILLED_TRIANGLE (x1, y1, x1+6, y1, x1+3, y1-10);
		x1 = x + odors[o].too * xmul;
		FILLED_TRIANGLE (x1+3, y1, x1, y1-10, x1+6, y1-10);

		}   

}

void SHOW_WEIGHTS ()

{
int unit, x, y, y0;
LINK *link;
char chain[20];
y = 20;
	if (weight_window == NULL)
  		weight_window = OPEN_WINDOW (0, 0, 450, 100, blanc);
	CHOOSE_WINDOW (weight_window);
	CLEAR();
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == granule)
			{
			y += 10;
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == pyr)
					{
					x = units[link->from_unit].couche * 20 + 20;

					FILLED_CIRCLE (x, y, (int) (link->weight * 200));
						
					}     
				link = link->next;
				}
			}
		}
 
			
}

#if 0
void DRAW_FFT (x, y, x_mul, y_mul, ffts)
FFT *ffts; 
short int	x, y, x_mul, y_mul;
{             
int	  step, steppi, steppo, from, too, o, point;
char	  chain[50];  
short int x1;
float	  help;   
	if (FOURRIER == FAUX)
		{   
		point = ffts[0].points;
		for (step = 0, steppi = 0; step < point/8; step++)
			{
			if (step == steppi)
				{
				help = ceil (step / (point*(DELTA/1000)));                                                            
				/*sprintf (chain, "%3.0f", help);
				x1 = x + 4*x_mul * step;
				TEXT (chain, x1-10, y + 15);*/

				steppi += 6;	
				} 
			}		
 		if (ffts[0].max_freq != 0.0)
			help = (DELTA*point) / ffts[0].max_freq;
		else help = 0.0;
		CURVE (x, y, 4*x_mul, y_mul, point/8, ffts[0].fft);
      	      	  AXIS (x, y, 4*x_mul, y_mul, point/8, 6);
		if (help != 0.0) 
		    sprintf (chain, " %5.3f at %5.3f ms or %5.3f Hz", sqrt (ffts[0].max), help/1000, 1000/help);	
		TEXT (chain, x + (step+1) * 2 * x_mul, y);

		}
	else
		{                         
		
		for (o = 0; o < NODS; o++)
			{
			from = odors[o].from; 
			too = odors[o].too;
			point = ffts[o].points;
			for (step = 0, steppi = 6; step < point/4; step++)
				{
				if (step == steppi)
					{
					help = ceil (step / (point*(DELTA/1000)));                                                            
					sprintf (chain, "%3.0f", help);
					x1 = from*x_mul + x + 2*x_mul * step;
					TEXT (chain, x1-10, y + 15);
/*					if ((step != 0) && (help != 0.0))
						sprintf (chain, "%3.0f", ceil (1000/help));
					else 
						sprintf (chain, "%3.0f", 0.0);
					TEXT (chain, x1-10, y + 20);
*/					steppi += 24;	
					} 
	              	      	  }
			if (ffts[o].max_freq != 0.0)
				help = DELTA*point / ffts[o].max_freq;
			else help = 0.0;

			CURVE (x+x_mul*from, y, x_mul*2, y_mul, point/4, ffts[o].fft);  
      	      	      	AXIS (x+x_mul*from, y, x_mul*2, y_mul, point/4, 12);
			if (help != 0.0) 
			    sprintf (chain, "%5.3f at %5.3f ms or %5.3f Hz", sqrt (ffts[o].max), help/1000, 1000/help);	
			TEXT (chain, x+x_mul*from+(step+1) * 2 * x_mul, y);
			}
		}	
		
}		


void DRAW_CROSS (x, y, xmul, yspectre, yphase, ycurve)
int   x, y, xmul, yspectre, yphase;
{
int steppi, step, points; 
float help;
char chain[20];
int i, x1;
	i = 1;  
	while (N_STEPS >= i)
		i *= 2;
	points = i / 2;	    
		for (step = 0, steppi = 0; step < points/2; step++)
			{
			if (step == steppi)
				{
				help = ceil (step / (points*DELTA));                                                            
				sprintf (chain, "%3.0f", help);
				x1 = x + xmul * step - 10;
				TEXT (chain, x1, y + 15);
/*				if (step != 0)
					sprintf (chain, "%3.1f", 1000 / help);
				else 
					sprintf (chain, "%3.1f", 0.0);
				TEXT (chain, x1, y + 20);
*/				if (help != 0.0)
					sprintf (chain, "%3.0f", 1.0/help * 1000.0);
				else 
					sprintf (chain, "0");
				TEXT (chain, x1, y+yphase+10+ycurve+10+20);
				steppi += 12;	
				} 
			}	
      	CURVE (x, y, xmul, yspectre, points/2, spectre);
      	AXIS (x, y, xmul, yspectre, points/2, 12);	
      	SPIKES (x, y+yphase+10, xmul, yphase, points/2, phase);
      	AXIS (x, y+yphase+10, xmul, yphase, points/2, 12);

	CURVE (x, y+yphase+10+ycurve+10, xmul, ycurve, points/2, ccurve);
	AXIS (x, y + yphase+10+ycurve+10, xmul, ycurve, points/2, 12);

      	TEXT ("click right for quit", 10, 10);
}


#endif























