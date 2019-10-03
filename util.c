#include "cell.init"

int ialea;
double alea;



void ALLOCATE_NEURONS (number)
int	number;
{
int i; 
 	units = (NEURON *) calloc (number, sizeof (NEURON));
       	if (molecules == NULL)
	    molecules = (MOLS * ) calloc (MOL, sizeof (MOLS));
	AVSM = (float *) calloc (N_STEPS, sizeof (float));
	AVSG = (float *) calloc (N_STEPS, sizeof (float));
	AVSP = (float *) calloc (N_STEPS, sizeof (float));
	POTSM = (float *) calloc (N_STEPS, sizeof (float));
	POTSG = (float *) calloc (N_STEPS, sizeof (float));
	POTSP = (float *) calloc (N_STEPS, sizeof (float));

	MAV = (float *) calloc (GLOM, sizeof (float));
	GAV = (float *) calloc (GLOM, sizeof (float));
	PAV = (float *) calloc (GLOM, sizeof (float));
	RAV = (float *) calloc (GLOM, sizeof (float));
	EAV = (float *) calloc (GLOM, sizeof (float));
	STIM = (float *) calloc (N_STEPS, sizeof (float));
	GUST = (float *) calloc (N_STEPS, sizeof (float));
	if (contex == NULL)
		{contex = (CONTEX *) calloc (GLOM, sizeof (CONTEX));
		for (i = 0; i < GLOM; i++)
			contex[i].stepp = (float *) calloc (N_STEPS, sizeof (float));
		}

}


void AVS ()
{
int step, unit;
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == mitral2)
			for (step = 0; step < N_STEPS; step++)
				AVSM[step] += units[unit].output[step];
		if (units[unit].type == granule)
			for (step = 0; step < N_STEPS; step++)
				AVSG[step] += units[unit].output[step];
		if (units[unit].type == pyr)
			for (step = 0; step < N_STEPS; step++)
				AVSP[step] += units[unit].output[step];
		}
	for (step = 0; step< N_STEPS; step++)
		{
		AVSM[step] /= GLOM;
		AVSG[step] /= GLOM;
		AVSP[step] /= GLOM;
		}
}

void SYNCH ()
{
int u1, u2, s; 
float synchlocal, spikeslocal; 
float synchm, spikesm, synchg, spikesg, synchp, spikesp; 
float squarem, squareg, squarep, devm, devg, devp; 
	synchm = spikesm = 0.0; 
	for (u1=0; u1< N_UNITS; u1++)
		for (u2=0; u2<N_UNITS; u2++)
			if (u1!=u2)
				{
				if ((units[u1].type == mitral2)&&(units[u2].type == mitral2))
					{
					synchlocal = 0.0; spikeslocal = 1.0; 
					for (s=0; s<N_STEPS; s++)
						{
						synchlocal += units[u1].output[s]*units[u2].output[s];
						spikeslocal += units[u1].output[s]+units[u2].output[s];
						}
					 synchm += synchlocal/spikeslocal; 
					 spikesm += spikeslocal; 
					}
				}
	printf ("mitral %f %f \n", spikesm, synchm); 
} 

void POTS ()
{
int step, unit;
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == mitral2)
			for (step = 0; step < N_STEPS; step++)
				POTSM[step] += units[unit].state[step];
		if (units[unit].type == granule)
			for (step = 0; step < N_STEPS; step++)
				POTSG[step] += units[unit].state[step];
		if (units[unit].type == pyr)
			for (step = 0; step < N_STEPS; step++)
				POTSP[step] += units[unit].state[step];
		}
	for (step = 0; step< N_STEPS; step++)
		{
		POTSM[step] /= GLOM;
		POTSG[step] /= GLOM;
		POTSP[step] /= GLOM;
		}
}

void SAVE_POTS (filename)
char *filename;
{
FILE *saveto;
int s; 
	saveto=fopen (filename, "w");
	for (s=0; s<N_STEPS; s++)
		{
		fprintf (saveto, "%f %f %f\n", POTSM[s], POTSG[s], POTSP[s]);
		}
	fclose (saveto);
}




void SAVE_MITRAL_SPIKES ()
{
	FILE *save_to;
	char name[50];
	int step, unit;
	printf ("save to file \n");
	scanf ("%s", name);
	save_to = fopen (name, "w");
	for (step = 0; step < N_STEPS; step++)
		{
		for (unit = 0; unit < N_UNITS; unit++)
			if (units[unit].type == mitral2)
				fprintf (save_to, "%f ", units[unit].state[step]+10*units[unit].output[step] );
		fprintf (save_to, "\n");
		}
	fclose (save_to);	
}

void SAVE_GRANULE_SPIKES ()
{
	FILE *save_to;
	char name[50];
	int step, unit;
	printf ("save to file \n");
	scanf ("%s", name);
	save_to = fopen (name, "w");
	for (step = 0; step < N_STEPS; step++)
		{
		for (unit = 0; unit < N_UNITS; unit++)
			if (units[unit].type == granule)
				fprintf (save_to, "%f ", units[unit].state[step]+10*units[unit].output[step] );
		fprintf (save_to, "\n");
		}
	fclose (save_to);	
}

void SAVE_PYR_SPIKES ()
{
	FILE *save_to;
	char name[50];
	int step, unit;
	printf ("save to file \n");
	scanf ("%s", name);
	save_to = fopen (name, "w");
	for (step = 0; step < N_STEPS; step++)
		{
		for (unit = 0; unit < N_UNITS; unit++)
			if (units[unit].type == pyr)
				fprintf (save_to, "%f ", units[unit].state[step]+10*units[unit].output[step] );
		fprintf (save_to, "\n");
		}
	fclose (save_to);	
}

void GET_AVERAGES (from, too)
int from, too; 
{
	int step, unit;
	int m, g, p, r, e;
	for (unit = 0; unit < GLOM; unit++)
		{
		MAV[unit]=0.0;
		GAV[unit]=0.0;
		PAV[unit]=0.0;
		RAV[unit]=0.0;
		EAV[unit]=0.0;
		}
	m=0; g=0; p=0; r=0;
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == mitral2)
			{
			for (step = from; step < too; step++)
				MAV[m] = MAV[m]+units[unit].output[step];
			m++;
			MAV[m] /= (too-from);
			}
		if (units[unit].type == granule)
			{
			for (step = from; step < too; step++)
				GAV[g] = GAV[g]+units[unit].output[step];
			g++;
			GAV[g] /= (too-from);
			}
		if (units[unit].type == pyr)
			{
			for (step = from; step < too; step++)
				PAV[p] = PAV[p]+units[unit].output[step];
			p++;
			PAV[p] /= (too-from);
			}
		if (units[unit].type == ET)
			{
			for (step = from; step < too; step++)
				EAV[e] = EAV[e]+units[unit].output[step];
			e++;
			EAV[e] /= (too-from);
			}
		if (units[unit].type == receptor)
			{
			for (step = from; step < too; step++)
				RAV[r] = RAV[r]+units[unit].output[step];
			r++;
			RAV[r] /= (too-from);
			}
		}
	
}

	
SAVE_SUMS (saveto)
FILE *saveto;
{
int step;
int g;
float gav, mav, pav; 
	gav = mav = pav = 0.0;
	for (g = 0; g < GLOM; g++)
		{
		gav += GAV[g];
		mav += MAV[g];
		pav += PAV[g];
		}
	fprintf (saveto, "%f %f %f \n", mav, gav, pav);
	
		
}

SAVE_AVERAGES ()
{
FILE *saveto;
char name[50];
int g;
	printf ("save to file ?\n");
	scanf ("%s", name);
	saveto = fopen (name, "w");

	for (g=0; g < GLOM; g++)
		fprintf (saveto, "%f %f %f %f %f\n", RAV[g], EAV[g], MAV[g], GAV[g], PAV[g]);
	fclose (saveto);
}

void CONTEXT_AON ()
{
int unit, step;
int ctex, from, too; 
	for (unit = 0; unit < GLOM; unit++)
		for (step = 0; step < N_STEPS; step++)
			contex[unit].stepp[step] = 0.0; 
		
	printf ("context 1 2? from too \n");
	scanf ("%d %d %d", &ctex, &from, &too);
	if (ctex == 1)
		{
			
		for (step = from; step< too; step++)
			for (unit = 25; unit < 35; unit++)
				{				

				contex[unit].stepp[step] = 1.0;
				}
		}
	if (ctex == 2)
		{for (step = from; step< too; step++)
			for (unit = 65; unit < 75; unit++)
				contex[unit].stepp[step] = 1.0;}

}

void BLACK_CONTEXT_AON ()
{
int unit, step;
int ctex, from, too; 
	for (unit = 0; unit < GLOM; unit++)
		for (step = 0; step < N_STEPS; step++)
			contex[unit].stepp[step] = 0.0; 
		
	for (step = 0; step< N_STEPS; step++)
		for (unit = 25; unit < 35; unit++)
			{				

			contex[unit].stepp[step] = 1.0;
			}

}
void WHITE_CONTEXT_AON ()
{
int unit, step;
int ctex, from, too; 
	for (unit = 0; unit < GLOM; unit++)
		for (step = 0; step < N_STEPS; step++)
			contex[unit].stepp[step] = 0.0; 
		
	for (step = 0; step< N_STEPS; step++)
		for (unit = 75; unit < 85; unit++)
			{				

			contex[unit].stepp[step] = 1.0;
			}

}

void NO_CONTEXT_AON ()
{
int unit, step;
int ctex, from, too; 
	for (unit = 0; unit < GLOM; unit++)
		for (step = 0; step < N_STEPS; step++)
			contex[unit].stepp[step] = 0.0; 
		

}

void OXT_AON (OXT)
float OXT; 
{
int unit, step;
int ctex, from, too; 
	for (unit = 0; unit < GLOM; unit++)
		for (step = 0; step < N_STEPS; step++)
			contex[unit].stepp[step] = OXT; 
		

}
void HEBB_AON_GC (rate)
float rate; 
{
int unit; 
LINK *link; 
int g; 
float ag;
	ag = 0.0;
	for (g=0; g < GLOM; g++)
		ag+=GAV[g];
	ag/=GLOM;
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == granule)
			{
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == pyr)
					{
					if (GAV[units[unit].couche] >= ag)
						{
						link->weight += GAV[units[unit].couche]*PAV[units[unit].couche]*rate;
						link->hebb = TRUE;
						}
					
					}
				link = link->next;
				}
			}
		}
}


void HEBB_MC_GC (rate)
float rate; 
{
int unit; 
LINK *link; 
int g; 
float ag;
	ag = 0.0;
	for (g=0; g < GLOM; g++)
		ag+=GAV[g];
	ag/=GLOM;
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == granule)
			{
			link = units[unit].links_to_unit;
			while (link)
				{
				if ((units[link->from_unit].type == mitral2) && (link->weight != 0.0))
					{
					if (GAV[units[unit].couche] >= 0.0)
						{
						link->weight += GAV[units[unit].couche]*MAV[units[unit].couche]*rate;
						link->hebb = TRUE;
						}
					
					}
				link = link->next;
				}
			}
		}
}

void MEASURE_WEIGHTS1 ()
{
int i, j, count; 
float max, min, av; 
LINK *link; 
max = 0; 
min = 1000; 
av = 0.0;
count = 0; 
for (i = 0; i < N_UNITS; i++)
	if (units[i].type == pyr)
		{
		link = units[i].links_to_unit;
		while (link)
			{		
			if (units[link->from_unit].type == pyr)
				{
				if (link->weight >= max)
					max = link->weight;
				if (link->weight <= min)
					min = link->weight;
				av += link->weight; 
				count++; 
		
				}
			link = link->next;
			}
		}

	printf ("pc to pc min %f max %f av %f\n", min, max, av/count); 	
}

void MEASURE_WEIGHTS2 ()
{
int i, j, count; 
float max, min, av; 
LINK *link; 
max = 0; 
min = 1000; 
av = 0.0;
count = 0; 
for (i = 0; i < N_UNITS; i++)
	if (units[i].type == granule)
		{
		link = units[i].links_to_unit;
		while (link)
			{		
			if (units[link->from_unit].type == pyr)
				{
				if (link->weight >= max)
					max = link->weight;
				if (link->weight <= min)
					min = link->weight;
				av += link->weight; 
				count++; 
		
				}
			link = link->next;
			}
		}

	printf ("pc to gra min %f max %f av %f\n", min, max, av/count); 	
}


void MEASURE_WEIGHTS3 ()
{
int i, j, count; 
float max, min, av; 
LINK *link; 
max = 0; 
min = 1000; 
av = 0.0;
count = 0; 
for (i = 0; i < N_UNITS; i++)
	if (units[i].type == granule)
		{
		link = units[i].links_to_unit;
		while (link)
			{		
			if (units[link->from_unit].type == mitral2)
				{
				if (link->weight >= max)
					max = link->weight;
				if (link->weight <= min)
					min = link->weight;
				av += link->weight; 
				count++; 
		
				}
			link = link->next;
			}
		}

	printf ("mi to gra min %f max %f av %f\n", min, max, av/count); 	
}
void SAVE_WEIGHTS3 (saveto)
FILE *saveto;
{
int i, j, count; 
float max, min, av; 
LINK *link; 
max = 0; 
min = 1000; 
av = 0.0;
count = 0; 
for (i = 0; i < N_UNITS; i++)
	if (units[i].type == granule)
		{
		link = units[i].links_to_unit;
		while (link)
			{		
			if (units[link->from_unit].type == mitral2)
				{
				if (link->weight >= max)
					max = link->weight;
				if (link->weight <= min)
					min = link->weight;
				av += link->weight; 
				count++; 
		
				}
			link = link->next;
			}
		}

	fprintf (saveto, "mi to gra min %f max %f av %f\n", min, max, av/count); 	
}

void HEBB_ASS_PC (rate)
float rate; 
{
int unit; 
LINK *link; 
int g; 
float ap;
	ap = 0.0;
	for (g=0; g < GLOM; g++)
		ap+=PAV[g];
	ap/=GLOM;
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == pyr)
			{
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == pyr)
					{link->weight += PAV[units[unit].couche]*PAV[units[link->from_unit].couche]*rate;
					if (link->weight > WMM1)
						link->weight = WMM1;
					}	
				link = link->next;	
				}
			
				
			}
		}
	/*MEASURE_WEIGHTS1 ();*/
}


void HEBB_PC_GC (rate)
float rate; 
{
int unit; 
LINK *link; 
int g; 
float ap;

	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == granule)
			{
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == pyr)
					{link->weight += GAV[units[unit].couche]*PAV[units[link->from_unit].couche]*rate;
					if (link->weight > WMM2)
						link->weight = WMM2;
					}	
				link = link->next;	
				}
			
				
			}
		}
	/*MEASURE_WEIGHTS2 ();*/
}


void FORGET_PC_ASS (tau, forgettime)
float tau, forgettime; 
{
int i, j; 
LINK *link; 
float old_weight, new_weight; 

	for (i = 0; i < N_UNITS; i++)
		if (units[i].type == pyr)
			{
			link = units[i].links_to_unit; 
			while (link)
				{
				if (units[link->from_unit].type == pyr)
					{
					old_weight = link->weight;
					new_weight = old_weight*exp(-(1*forgettime)/tau);
					link->weight = new_weight;
					}
				link = link->next;
				}
			}
}
	
void FORGET_PC_GC (tau, forgettime)
float tau, forgettime; 
{
int i, j; 
LINK *link; 
float old_weight, new_weight; 

	for (i = 0; i < N_UNITS; i++)
		if (units[i].type == granule)
			{
			link = units[i].links_to_unit; 
			while (link)
				{
				if (units[link->from_unit].type == pyr)
					{
					old_weight = link->weight;
					new_weight = old_weight*exp(-(1*forgettime)/tau);
					link->weight = new_weight;
					}
				link = link->next;
				}
			}
}


void FORGET_MC_GC (tau, forgettime)
float tau, forgettime; 
{
int i, j; 
LINK *link; 
float old_weight, new_weight; 

	for (i = 0; i < N_UNITS; i++)
		if (units[i].type == granule)
			{
			link = units[i].links_to_unit; 
			while (link)
				{
				if (units[link->from_unit].type == mitral2)
					{
					old_weight = link->weight;
					new_weight = old_weight*exp(-(1*forgettime)/tau);
					if (new_weight >= link->firstweight)
						link->weight = new_weight;
					else
						link->weight = link->firstweight;
					}
				link = link->next;
				}
			}
}

/*void HEBB_MOTOR (step)
int step;
{
int from, too; 
LINK *link;
	link = units[N_UNITS-1].links_to_unit;
	while (link)
		{
		if (units[link->from_unit].type == mitral2 && GUST[step] == 1.0 && link->weight < 1.0-RATE)
			link->weight += units[link->from_unit].output[step] * RATE; 
		if (units[link->from_unit].type == mitral2 && GUST[step] == 0.0 && link->weight > 0.0+RATE)
			link->weight -= units[link->from_unit].output[step] * RATE;
		link = link->next;
		}
}*/

void SHOW_MOTOR_LINKS ()
{
LINK *link;
	link = units[N_UNITS-1].links_to_unit;
	while (link)
		{
		printf ("link from glom %d is %f \n", units[link->from_unit].couche, link->weight);
		link = link->next;
		}
}

void SAVE_MOTOR_LINKSA ()
{
LINK *link;
FILE *saveto;
	saveto = fopen ("motor weightsA", "w");
	link = units[N_UNITS-1].links_to_unit;
	while (link)
		{
		fprintf (saveto, "link from glom %d is %f \n", units[link->from_unit].couche, link->weight);
		link = link->next;
		}
	fclose (saveto);
}

void SAVE_MOTOR_LINKSB ()
{
LINK *link;
FILE *saveto;
	saveto = fopen ("motor weightsB", "w");
	link = units[N_UNITS-1].links_to_unit;
	while (link)
		{
		fprintf (saveto, "link from glom %d is %f \n", units[link->from_unit].couche, link->weight);
		link = link->next;
		}
	fclose (saveto);
}
void NULL_STIM ()
{
int n;
	for (n=0; n < N_STEPS; n++)
		STIM[n]=0.0;
}

void STIMULATE ()
{
int n, l1, l2; 
float conc;
	printf ("concentration from too\n");
	scanf ("%f %d %d", &conc, &l1, &l2);
	for (n=0; n < l1; n++)
		STIM[n] = 0.0;
	for (n=l1; n < l2; n++)
		STIM[n] = conc;
	for (n=l2; n< N_STEPS; n++)
		STIM[n] = 0.0;
} 

void STEP_STIM ()
{
int s, l; 
float c; 

NULL_STIM ();
	s=10;
	l=5;
	c=0.05;
	for (s=10; s<N_STEPS-50;s+=50)
		{
		for (l=s; l<s+5; l++)
			STIM[l]=c;
		c+=0.05;
		}
}
		
void STEP_COUNT ()
{
int s, l, unit, count;
float ss[20];
FILE *saveto;
	saveto=fopen ("pyrtests", "a");
	for (s=0; s < 20; s++)
		ss[s] = 0.0;
	
	count = 0;
	for (s=10; s < N_STEPS-50; s+=50)
		{
		for (l=s; l<s+10; l++)
			{
			for (unit = 0; unit< N_UNITS; unit++)
				if (units[unit].type == pyr)
					{
					ss[count] += units[unit].output[l];

					}
			}
		count++;
		}
									

	for (s=0;s<20;s++)
		fprintf (saveto, "%f ", ss[s]);
	fprintf (saveto, "\n");
	fclose (saveto);
} 


void FREE_ALL ()
{        
int 	unit, r, m;
LINK	*link, *help;
	for (unit = 0; unit < N_UNITS; unit++)
		{
		free (units[unit].output);
		free (units[unit].state);
		link = units[unit].links_to_unit;
		while (link != NULL)
			{
			free (link->signal);
			help = link->next;
			free (link);
			link = help;
			}
		}                                              
	for (r = 0; r < REC; r++)
		free (recs[r].sensi);
	free (recs);
	free (molecules);
	free (STIM);

}             

void SETQ (ziel, word)
char *word, *ziel;
{
	strcpy (ziel, word);  
}

float F_REV (value, thresh, rev, uni, step)
float value, thresh, rev;
int uni, step;
{
	if (value > thresh) 
		return ((rev - units[uni].state[step]) * value);
	else 
		return (0.0);
}
	

/** random number generator **/

double RANF ()
{                                         
extern double alea;
extern int ialea; 
	do
		{ 
		ialea = ialea * 16087; 
		if (ialea < 0)
			ialea = ialea + 2147483647 + 1;
		alea = (double) ialea / 2147483647; 
        }
	while (alea >= 1);
	return ( alea);
}

/** equality of strings **/                                                    

enum BOOLEAN EQU (name, compare)
char	*name, *compare;
{
	if (strcmp (name, compare) == 0)
		return (VRAI);
	else
		return (FAUX);
} 

float DEXP (tau1, tau2, t)
float tau1, tau2, t; 
{
float tpeak, gpeak; 
extern double log (), exp (); 
	if (tau1 >= DELTA) 
		tau1 /= DELTA;
	else
		tau1 = DELTA; 
	if (tau2 >= DELTA) 
		tau2 /= DELTA; 
	else 
		tau2 = DELTA; 
	if (t >= DELTA) 
		t /= DELTA;
	else 
		t = DELTA; 
	if (tau1 != tau2) 
	  	{
		tpeak = ((tau1 * tau2) / (tau1 - tau2)) *  (log (tau1 / tau2)); 
		gpeak = ((tau1 * tau2) / (tau1 - tau2)) * (exp (- tpeak / tau1) - exp (- tpeak / tau2)); 
		return (((tau1 * tau2) / (gpeak * (tau1-tau2))) * (exp (- t/tau1) - exp (- t/tau2))); 
		}
	else
		return (t / (tau1 * exp (1)) * exp (- (t/tau1)));
}

int GAUSS (inf, sub, percent)
int 	inf, sub;
float 	percent;
{                 
int 	k;
float 	var, a, t, sig;     
int 	res;  
loop:    
	t = (sub - inf);
		var = 0;
		for (k = 0; k < 4000; k++)
			{
			a = RANF ();
			var += a;
			}
		var = (sqrt (12.0 / 4000)) * (var - 4000 / 2.0);
		sig = sqrt (( log (100.0 / percent)) *2.0);
		var = (sub + inf) / 2.0 + var * (t / (2.0 * sig));
		res = floor (var + 0.5);  
		if ((res > inf) && (res < sub))
			return (res);  
		else 
			goto loop; 
}



  
float GAUSSIENNE (x,d,s)
float x;              
float d,s;
{         
    float y;
    y=exp(-(x-d)*(x-d)/(s*s));
    return(y);
}
/*

void SN ()
{
FILE *saveto;
char name[50];
float sn[100];
float spont[100];
float or[100];
float mi[1000];
int unit, n, i;

printf ("save to file\n");
scanf ("%s", name);
saveto = fopen (name, "w");
for (i=0; i<GLOM;i++)
	{
	sn[i] = 0.0;
	spont[i] = 0.0;
	or[i]=0.0;
	mi[i]=0.0;
	}
printf ("one \n");
for (unit = 0; unit<N_UNITS;unit++)
	if (units[unit].type == mitral2)
		{
		for (n=0; n<200;n++)
			spont[units[unit].couche]+=units[unit].output[n];
		for (n=200; n < 1000; n++)
			or[units[unit].couche]+=units[unit].output[n];
		}
printf ("two\n");
for (i=0; i<GLOM;i++)
	{
	spont[i] /=200;
	or[i] /=800;
	sn[i]=or[i]/spont[i];
	mi[i] = (or[i]-spont[i])/(or[i]+spont[i]);
	fprintf(saveto, "%f %f %f %f\n", spont[i], or[i], sn[i], mi[i]);
	}
printf ("thre \n");
fclose (saveto);
}

*/

void SN ()
{
FILE *saveto;
char name[50];
float sn[5];
float spont[5];
float or[5];
float mi[5];
int g, unit, n, i;

saveto = fopen ("testSN3", "a");
for (i=0; i<5;i++)
	{
	sn[i] = 0.0;
	spont[i] = 0.0;
	or[i]=0.0;
	mi[i]=0.0;
	}
printf ("one \n");
g=0;
for (unit = 0; unit<N_UNITS;unit++)
	if ((units[unit].type == mitral2) && ((units[unit].couche == 10) || (units[unit].couche == 30) || (units[unit].couche == 50) || (units[unit].couche == 70) || (units[unit].couche == 90)))
		{
		for (n=0; n<500;n++)
			spont[g]+=units[unit].output[n];
		for (n=500; n < 1000; n++)
			or[g]+=units[unit].output[n];
		g++;	
		}
	
	
printf ("two\n");
for (i=0; i<5;i++)
	{
	spont[i]*=2;
	or[i]*=2;
	sn[i]=or[i]/spont[i];
	mi[i] = (or[i]-spont[i])/(or[i]+spont[i]);
	fprintf(saveto, "%f %f %f %f\n", spont[i], or[i], sn[i], mi[i]);
	}
printf ("thre \n");
fclose (saveto);
}






void MAKE_REC_SENS ()
{
int help;
int r, m, M0, x;  
float *toto; 
extern void SHOW_REC_SENS ();   
int		*flag, *first;

	toto = (float *) calloc (MOL, sizeof (float)); 
	flag = (int *) calloc (MOL, sizeof (int));
	first = (int *) calloc (MOL, sizeof (int));
	help = (int) MOL/REC;             
	recs = (REC_MOL *) calloc (REC, sizeof (REC_MOL));
	for (r = 0; r < REC; r++)
		recs[r].sensi = (float *) calloc (MOL, sizeof (float));
	for (r = 0; r < REC; r++)
		{
		M0 = (int) r*help;
		for (m = 0; m < MOL; m++)
			{                         
            		if (M0 < MOL/2)
				{
				if (m <= M0 + MOL/3)
					recs[r].sensi[m] = GAUSSIENNE ((float) m, (float) M0, 3.0);
				if (m > M0 + MOL/3)
					recs[r].sensi[m] = GAUSSIENNE ((float) (m), (float) MOL+M0, 3.0);
				}
			if (M0 == MOL/2)
				recs[r].sensi[m] = GAUSSIENNE ((float) m, (float) M0, 3.0);
			if (M0 > MOL/2) 
				{            
				if (m >= M0 - MOL/2)
					recs[r].sensi[m] = GAUSSIENNE ((float) m, (float) M0, 3.0);
				if (m < M0 - MOL/2)
					recs[r].sensi[m] = GAUSSIENNE ((float) (MOL+m), (float) M0, 3.0);
				} 

			}	
		} 

}



LATS *ZEROS (weight, decay, delay, increment, distance, total)
float 	weight, distance;
int 	delay, total;  
enum BOOLEAN decay, increment;
{
LATS *lats;
int g, gg;
  lats = (LATS *) calloc (total, sizeof (LATS));
	for (g = 0; g < total; g++)
		{
		lats[g].weight = (float *) calloc (total, sizeof (float));
		lats[g].delay = (int *) calloc (total, sizeof (int));
		}   
for (g = 0; g < total; g++)
    for (gg = 0; gg < total; gg++)
      {
	lats[g].weight[gg] = 0.0;
	lats[g].delay[gg] = 0;
      }
 return (lats);
}


LATS *FUNCTIONAL (weight, total, name)
float 	weight;
int 	total;  

char *name;

{
  int toto;
  LATS *lats; 
  FILE *readfrom;
  int g, gg, i, j, from, too;
  float w, tutu;

  printf (" in functional name %s \n", name);
  if ((readfrom = fopen (name, "r")) == NULL)
    printf ("no file for distance\n");

  lats = (LATS *) calloc (total, sizeof (LATS));
	for (g = 0; g < total; g++)
		{
		lats[g].weight = (float *) calloc (total, sizeof (float));
		lats[g].delay = (int *) calloc (total, sizeof (int));
		}  
  for (g = 0; g < total; g++)
    for (gg = 0; gg < total; gg++)
      {
	lats[g].weight[gg] = 0.0;
	lats[g].delay[gg] = 1;
      }

  for (from = 0; from < total; from++)
    {
      fscanf (readfrom, "%d", &toto);
      for (too = 0; too < total; too++)
	{
	  fscanf (readfrom, "%f", &w);
	  lats[from].weight[too] = weight*w;
	  lats[from].delay[too] = 1;

	}
    }

  fclose (readfrom);
  return (lats);
}





LATS *MAKE_NEIGHBORS (weight, total)
float 	weight;
int 	total;  

{

  LATS *lats; 
  FILE *readfrom;
  int g, gg, i, j;

  if ((readfrom = fopen ("neighbors.txt", "r")) == NULL)
    printf ("no file for distance\n");

  lats = (LATS *) calloc (total, sizeof (LATS));
	for (g = 0; g < total; g++)
		{
		lats[g].weight = (float *) calloc (total, sizeof (float));
		lats[g].delay = (int *) calloc (total, sizeof (int));
		}  
  for (g = 0; g < total; g++)
    for (gg = 0; gg < total; gg++)
      {
	lats[g].weight[gg] = 0.0;
	lats[g].delay[gg] = 1;
      }
 
  for (i = 0; i < total; i++)
    {
      fscanf (readfrom, "%d", &g);
      for (j = 0; j < 7; j++)
	{
	  fscanf (readfrom, "%d", &gg);
	  if (gg != 100)
	    {
	      lats[g].weight[gg] = weight;
	      lats[g].delay[gg] = 1;
	    }
	}

    }
  fclose (readfrom);
  return (lats);
}

LATS *RAN (weight, prob, total)
float 	weight, prob;
int 	total;  
{
LATS 	*lats;
 int g, gg;
lats = (LATS *) calloc (total, sizeof (LATS));
for (g = 0; g < total; g++)
  {
    lats[g].weight = (float *) calloc (total, sizeof (float));
    lats[g].delay = (int *) calloc (total, sizeof (int));
		
  }
 for (g = 0; g < total; g++)
   for (gg = 0; gg < total; gg++)
     if (g != gg)
       {
	 if (RANF () < prob)
	   {
	     lats[g].weight[gg] = weight;
	     lats[g].delay[gg] = 1;
	   }
       }
 return (lats);
}



LATS *MAKE_LATS (weight, decay, delay, increment, distance, total)
float 	weight, distance;
int 	delay, total;  
enum BOOLEAN decay, increment;
{
LATS 	*lats;
float 	help;
int	g, gg, G0, G;
	G = total;

    	lats = (LATS *) calloc (total, sizeof (LATS));
	for (g = 0; g < total; g++)
		{
		lats[g].weight = (float *) calloc (total, sizeof (float));
		lats[g].delay = (int *) calloc (total, sizeof (int));
		}
	if (distance != 0.0)
		help = 1/distance;  
	else help = 0.0;

/** make lateral weight distribution **/
	for (g = 0; g < G; g++)
		{
		G0 = g;
		for (gg = 0; gg < G; gg++)
			{                         
			if (G0 < G/2)
				{
				if (gg <= G0 + G/2)
					{    
					if (1 - help * abs ((gg - G0)) > 0.0)
						{
						if (decay == VRAI)
							lats[g].weight[gg] = weight * (1.0 - help * abs (gg - G0));
						else 
							lats[g].weight[gg] = weight;
						if (increment == VRAI)
						  	{
						    	lats[g].delay[gg] = delay * help * abs (gg - G0);
						    	if (lats[g].delay[gg] == 0) lats[g].delay[gg] = 1;
						  	}
						else 
						  	lats[g].delay[gg] = delay;
						}     

					else                                                         
						{
						lats[g].weight[gg] = 0.0;  
						lats[g].delay[gg] = 1;
						}
					}
				if (gg > G0 + G/2)
                    			{
					if (1 - help * abs ((gg - (G0 + G))) > 0.0)
						{
						if (decay == VRAI)
							lats[g].weight[gg] = weight * (1.0 - help * abs (gg - (G0 + G)));
						else 
							lats[g].weight[gg] = weight;
						if (increment == VRAI)
						  	{
						    	lats[g].delay[gg] = delay * help * abs (gg - (G0 + G));
						    	if (lats[g].delay[gg] == 0) lats[g].delay[gg] = 1;
						  	}
						else
							lats[g].delay[gg] = delay;
                        			}

					else                                                         
						{
						lats[g].weight[gg] = 0.0;  
						lats[g].delay[gg] = 1;
						}
                    			}
				}
			if (G0 == G/2)  
               			{
				if (1 - help * abs ((gg - G0)) > 0.0)
					{
					if (decay == VRAI)
						lats[g].weight[gg] = weight * (1.0 - help * abs (gg - G0));
					else 
						lats[g].weight[gg] = weight;
					if (increment == VRAI)
					  	{
					  	lats[g].delay[gg] = delay * help * abs (gg - G0);
					  	if (lats[g].delay[gg] == 0) lats[g].delay[gg] = 1;
						}
					else
					        lats[g].delay[gg] = delay;
					}
				else                                                         
					{
					lats[g].weight[gg] = 0.0;
					lats[g].delay[gg] = 1;
					}
                		}
			if (G0 > G/2) 
				{            
				if (gg >= G0 - G/2)   
                    			{
					if (1 - help * abs ((gg - G0)) > 0.0)
						{
						if (decay == VRAI)
							lats[g].weight[gg] = weight * (1 - help * abs (gg - G0));
    					else 
							lats[g].weight[gg] = weight;
						if (increment == VRAI)
						  	{
						  	lats[g].delay[gg] = delay * help * abs (gg - G0);
						  	if (lats[g].delay[gg] == 0) lats[g].delay[gg] = 1;
							}
						else 
							lats[g].delay[gg] = delay;
						}
					else                                                         
						{
						lats[g].weight[gg] = 0.0;
						lats[g].delay[gg] = 1;
						}
                    			}
				if (gg < G0 - G/2)
                    			{
					if (1 - help * abs ((G + gg - G0)) > 0.0)
						{
                       				 if (decay == VRAI)
							lats[g].weight[gg] = weight * (1 - help * abs ((G + gg - G0)));
						else 
							lats[g].weight[gg] = weight;
						if (increment == VRAI)
						  	{
						    	lats[g].delay[gg] = delay * help * abs(G + gg - G0);
						    	if (lats[g].delay[gg] == 0) lats[g].delay[gg] = 1;
						  	}
						else 
							lats[g].delay[gg] = delay; 
						}
					else                                                         
						{
						lats[g].weight[gg] = 0.0;
						lats[g].delay[gg]  = 1;
						}
                    			}
				} 
			}	
		}
   return (lats);
}

void SHOW_REC_SENS ()
{
int r, m;         
for (r = 0; r < REC; r++)
	{
	printf (" rec %d : ", r);
	for (m = 0; m < MOL; m++)
		printf ("m %d %f ", m, recs[r].sensi[m]);
	printf (" \n");
	}
}  

void SET_LINK_COMP (from, too, comp)
int from, too; 
enum COMPS comp; 
{
int unit; 
LINK *link; 	
	link = units[too].links_to_unit; 
	while (link)
		{
		if (link->from_unit == from) 
			link->from_comp = comp; 
		link = link->next; 
		}
}




#if 0
		 
void DO_CROSS ()
{
int index, index1, index2;
int cor, unit;    
EVENT maus; 

loop:

	printf (" 1. mi-mi 2. gr-gr 3. mi-gr 4. pyr-pyr 5. i2 -i2 6. pyr-i2 7. mi-pyr 8. gr-pyr\n"); 
	scanf ("%d", &cor);
	if ((cor < 1) && (cor > 8))
		{
		printf (" error  try again \n"); 
		goto loop; 
		}

	if (cor == 1)
		CROSS (m_pot, m_pot, fft_i1, fft_i2, FOURRIER);
	if (cor == 2)
		CROSS (g_pot, g_pot,  fft_i1, fft_i2, FOURRIER);
	if (cor == 3)
		CROSS (m_pot, g_pot, fft_i1, fft_i2, FOURRIER);  
	if (cor == 4)
		CROSS (p_pot, p_pot, fft_i1, fft_i2, FOURRIER);
	if (cor == 5)
		CROSS (i_pot, i_pot, fft_i1, fft_i2, FOURRIER);
	if (cor == 6)
		CROSS (p_pot, i_pot, fft_i1, fft_i2, FOURRIER);  
	if (cor == 7)
		CROSS (m_pot, p_pot, fft_i1, fft_i2, FOURRIER);
	if (cor == 8)
		CROSS (g_pot, p_pot, fft_i1, fft_i2, FOURRIER);
	maus.button = SHOW_CROSS ();
	if (maus.button == MIDDLE)
		goto loop;

}		                       
      
#endif	      

      


