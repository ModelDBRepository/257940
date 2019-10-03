/* FFT and cross correlations */

#include "cell.init"    


		
void list_fft (data,Nn, Signe)
double data[];
int   Nn;            
int Signe;
{ 
register int I,  J,   M;    
double   Wr, Wi, Wpr, Wpi,
         Wtemp, Theta;       
int      N,  Mmax,    Istep;
double Tempr,       Tempi;  

  N = 2*Nn;
  J = 1;
  for (I = 1; I<=N; I+=2)
    {
      if (J>I)
        {
          Tempr = data[J];          
          Tempi = data[J+1];
          data[J] = data[I];
          data[J+1] = data[I+1];
          data[I] = Tempr;
          data[I+1] = Tempi;
        } 
      M = N/2;                    

Diminut:

      if ((M>=2) && (J>M))
        { J=J-M; M=M/2; goto Diminut; }
/*      while ((M>=2) && (J>M))
        { J-=M; M/=2; }*/

      J+=M;
    } 
  Mmax = 2;

Danielson_Lanczos:
  if (N>Mmax)                       
    {
      Istep = 2*Mmax;
      Theta = 6.28318/(double)(Signe*Mmax);
      Wpr = sin ((float)(Theta*0.5)); Wpr*=Wpr; Wpr*= -2.;
      Wpi = sin ((float)(Theta));
      Wr = 1.0;
      Wi = 0.0;
      for (M = 1; M<=Mmax; M+=2)
        {
          for (I = M; I<=N; I+=Istep)
            {
              J = I+Mmax;          
              Tempr = (double)(Wr)*data[J]-(double)(Wi)*data[J+1];
              Tempi = (double)(Wr)*data[J+1]+(double)(Wi)*data[J];
              data[J] = data[I]-Tempr;
              data[J+1] = data[I+1]-Tempi;
              data[I]+=Tempr;
              data[I+1]+=Tempi;
            } 
          Wtemp = Wr;
          Wr = Wr*Wpr-Wi*Wpi+Wr;
          Wi = Wi*Wpr+Wtemp*Wpi+Wi;
        } 
      Mmax = Istep;
      goto Danielson_Lanczos;
    } 
 if (Signe==-1)
   for (I=1; I<=N; I++)
    data[I]/=Nn;
} 


#if 1
void CROSS (curve1, curve2, steps, i1, i2)
float *curve1, *curve2; 
int steps;     
int i1, i2;                    
{

double *dat1, *dat2, pii;
double *resul, *help, *spectre, *phase, *ccurve; 
float maxs, maxc, maxa;  
int i, j, imax; 
FILE *save_to;
char name[50];

printf ("save to file \n");
scanf ("%s", name);
save_to = fopen (name, "w");


pii =  3.141592653; 
printf (" in cross \n");
	i = 1;  
	while (steps >= i)
		i *= 2;
	points = i / 2;	 
printf ("points %d \n", points);
	dat1 = (double *) calloc (2*points+2, sizeof (double));
	dat2 = (double *) calloc (2*points+2, sizeof (double));
	resul = (double * ) calloc (2*points+2, sizeof (double));  
	help = (double *) calloc (2*points+2, sizeof (double));
	spectre = (double *) calloc (2*points+2, sizeof (double));
	phase = (double *) calloc (2*points+2, sizeof (double));
	ccurve = (double *) calloc (2*points+2, sizeof (double));
	for (i = 0; i < points; i++)	                 
		dat1[2*i+1] = curve1[i];
	list_fft (dat1, points, 1); 
	for (i = 0; i < points; i++)	                 
		dat2[2*i+1] = curve2[i];
	list_fft (dat2, points, 1);
printf (" before curve \n");
/*	CURVE (10, 100, 2 , 1, 1000, dat1);
	CURVE (10, 100, 2, 1, 1000, dat2);
*/
/*	for (i = 0; i < 2*points+2; i+=2)
		dat1[2*i+1] = -dat1[2*i+1]; 
	for (i = 0; i < 2*points+2; i++)
		resul[i] = dat1[i]*dat2[i];	
*/
	for (i = 0; i < 2*points+2; i+=2)
		{
		resul[i+1] = dat1[i+1] * dat2[i+1] + dat1[i+2]  * dat2[i+2];
		resul[i+2] = dat1[i+1] * dat2[i+2] - dat1[i+2] * dat2[i+1];
		}
maxs = maxc = 0.0;imax = 0;
    for (i = 0; i < points; i++)
		{
		spectre[i] = resul[2*i+1]*resul[2*i+1] + resul[2*i+2]*resul[2*i+2];
		if ((resul[2*i+2] != 0.0) && (resul[2*i+1] != 0.0))
			phase[i] = 180.0 * (float) atan (resul[2*i+1]/resul[2*i+2]) / pii;
		else phase[i] = 0.0;  

		}
	list_fft (resul, points, -1);
	for (i = 0; i < points; i++)
		ccurve[i] = resul[2*i+1]/points;
	for (j = points/2, i = 0; j < points; j++, i++)
		help[i] = ccurve[j];
	for (j = 0; j < points/2; j++, i++)
		help[i] = ccurve[j];
	for (i = 0; i < points; i++)
		ccurve[i] = help[i];
	for (i = i1; i < i2; i++)
		{
		if (ccurve[i] > maxc) maxc = ccurve[i];
		if (i > 0)
		if (spectre[i] > maxs) {maxs = spectre[i];imax = i;}
		}    
	if (imax != 0)
		printf (" found max spectre %5.3f at %5.3f ms or %5.3f Hz phase %f \n", sqrt (maxs), (float) DELTA * 1000.0 * points/imax, imax/(points*DELTA), phase[imax]);
	spectre[0] = 1.0;	
	for (i = i1; i < i2; i++)
		{     
		if (i > 0)
		if (maxs != 0.0) spectre[i] /= maxs;
	    if (maxc != 0.0) ccurve[i] /= maxc;
		phase[i] /= 180.0;
		}
	for (i = 0; i < i1; i++)
		{
		spectre[i] = 0.0;
		ccurve[i] = 0.0;
		phase[i] = 0.0;
		}
	for (i = i2; i < points; i++)
		{
		spectre[i] = 0.0;
		ccurve[i] = 0.0;
		phase[i] = 0.0;
		}
	for (i=0; i < 2*points+2; i++)
		fprintf (save_to, "%f %f %f %f \n", (float) i/points*DELTA, spectre[i], ccurve[i], phase[i]);
	fclose (save_to);
	
        free (dat1);
        free (dat2);
        free (resul);
        free (help);
	free (ccurve);
	free (spectre);
	free (phase);
printf (" after free \n");
}

#endif
#if 1
FFT *DO_FFT (curve, i1, i2, n)
float *curve;             
int i1, i2;                  
enum BOOLEAN n;
{                  
int		i, from, too;
FFT		*fft_curve;  
double	*data;
float	max, all_max;  
int		o, steps, step, freq;  
if (n == VRAI)  
	{
	
	fft_curve = (FFT *) calloc (NODS, sizeof (FFT));
	all_max = 0.0;
	for (o = 0; o < NODS; o++)
		{
		i = 1;  
		max = 0.0;   freq = 0;
		from = odors[o].from;
		too = odors[o].too; 
		steps = too - from + 50;
		while (steps >= i)
				i *= 2;
		points = i / 2;	
		data = (double *) calloc (2*points+2, sizeof (double));
		fft_curve[o].fft = (float *) calloc (points, sizeof (float));
		fft_curve[o].points = points;
		for (i = 0, step = from; i < points; i++, step++)	                 
			data[2*i+1] = curve[step];
		list_fft (data, points, 1);
    	for (i = 0; i < points; i++)
			{
			fft_curve[o].fft[i] = data[2*i+1]*data[2*i+1] + data[2*i+2]*data[2*i+2];
			if ((i > i1) && (fft_curve[o].fft[i] > max) && (i < i2))
				{
				max = fft_curve[o].fft[i];
				freq = i;
				}
			}    
		if (max > all_max)
			all_max = max;
		for (i = 0; i < i1+1; i++)
			fft_curve[o].fft[i] = 0.0;
		for (i = i2; i < points; i++)
			fft_curve[o].fft[i] = 0.0;
		fft_curve[o].max = max; 
		fft_curve[o].max_freq = freq;
		free (data);
		} 
if (all_max != 0.0)   
	for (o = 0; o < NODS; o++)
		for (i = i1; i < i2; i++)
			fft_curve[o].fft[i] /= all_max;
	}
	else
		{              
o = 0;
	fft_curve = (FFT *) calloc (1, sizeof (FFT));
	all_max = 0.0;
		i = 1;  
		max = 0.0;   freq = 0;
		steps = N_STEPS;
		while (steps >= i)
				i *= 2;
		points = i / 2;	
		data = (double *) calloc (2*points+2, sizeof (double));
		fft_curve[o].fft = (float *) calloc (points, sizeof (float));
		fft_curve[o].points = points;
		for (i = 0; i < points; i++)	                 
			data[2*i+1] = curve[i];
		list_fft (data, points, 1);
    	for (i = 0; i < points; i++)
			{
			fft_curve[o].fft[i] = data[2*i+1]*data[2*i+1] + data[2*i+2]*data[2*i+2];
			if ((i > i1) && (fft_curve[o].fft[i] > max) && (i < i2))
				{
				max = fft_curve[o].fft[i];
				freq = i;
				}
			}    
		for (i = 0; i < i1+1; i++)
			fft_curve[o].fft[i] = 0.0;
		for (i = i2; i < points; i++)
			fft_curve[o].fft[i] = 0.0;
		if (max != 0.0)
			for (i = i1; i < i2; i++)
				fft_curve[0].fft[i] /= max;
		fft_curve[o].max = max; 
		fft_curve[o].max_freq = freq;
		free (data);
		} 

	return (fft_curve);
}	

#endif


