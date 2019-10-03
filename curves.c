/*display functions */

#include "gra.init"


void CURVE (x0, y0, xmul, ymul, steps, data)
int x0, y0, xmul, ymul, steps;
float *data;
{
int	x1, x2, y1, y2;
int	step;
	for (step = 0; step < steps; step++)
		{
		x1 = x0 + xmul * step;
		y1 = y0 - ymul * data[step];
		x2 = x0 + xmul * (step + 1);
		y2 = y0 - ymul * data[step+1];
		LINE (x1, y1, x2, y2);
		}
}

void SPIKES (x0, y0, xmul, ymul, steps, data)
int	x0, y0, xmul, ymul, steps;
float	*data;
{
int	x1, y1; 
int	step;
	for (step = 0; step < steps; step++)
		{
		x1 = x0 + xmul * step;
		y1 = y0 - ymul * data[step];
		LINE (x1, y0, x1, y1);
		}
}


void DOTS (x0, y0, xmul, ymul, steps, data)
     int x0, y0, xmul, ymul, steps;
     float *data;
{
  int x1, y1; 
  int step;
  for (step = 0; step < steps; step)
    {
      x1 = x0+xmul*step;
      if (data[step] > 0.0)
	CIRCLE (x0, y0, (int) floor (xmul/5));
    }
}
void ACTIVITY (x0, y0, xmul, ymul, ymul2, steps, data1, data2)
int 		steps;
int 		x0, y0, xmul, ymul, ymul2;   
float		*data1, *data2;
{
int		step; 
int 		x1, y1, x2, y2, y3;
 	for (step = 0; step < steps; step++)
		{
		x1 = x0 + xmul * step;
		y1 = y0 - ymul * data1[step];
		x2 = x0 + xmul * (step+1);
		y2 = y0 - ymul * data1[step+1]-ymul2*data2[step+1];    
		y3 = y1 - ymul2 * data2[step];
		LINE (x1, y1, x2, y2);
		/*LINE (x1, y1, x1, y3);*/
		}
/*	AXIS (x0, y0, xmul, 1, steps, 100);*/
}

void AXIS (x0, y0, xmul, hight, steps, ech)
 int 	x0, y0, hight;
int 	steps, ech;
{
char chain[2];
int index;          
int help;
	help = 0;
	LINE (x0, y0, (x0 + xmul* steps), y0); 
	LINE (x0, y0 + hight, x0, (y0 - hight)); 
	for (index = 0; index < steps; ++index)
		if (index == help)
	           	{ 
			LINE ((x0 + xmul * index), y0, (x0 + xmul * index), y0 - 3);
			help = help + ech;    
 			}   
} 





void SEQUENCE (x0, y0, x_mul,y_mul,steps, points) 
short int       x0, y0, steps, x_mul,y_mul; 
float           *points;
                {
short  int      x1, x2, y1, y2; 
int             step;
	for (step = 0; step < steps; step++)
		{   
		x1 = x0 + x_mul * step;
		y1 = y0 - y_mul * points[step]; 
		x2 = x0 + x_mul * (step + 1);
		y2 = y0 - y_mul * points[step + 1];  
		LINE (x1, y1, x2, y1);
		LINE (x2, y1, x2, y2);  
		}
}













