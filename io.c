/*input output functions */


#include "cell.init"



void SAVE_WEIGHTS ()

{
int unit, x, y;
LINK *link;
char chain[20], name[50];
FILE *saveto;
	printf ("save to file \n");
	scanf ("%s", name);
	saveto = fopen (name, "w");
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == granule)
			{ 
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == pyr)
					fprintf (saveto, "%f ", link->weight);
				link = link->next;
				}
			fprintf (saveto, "\n");
			}
		}
			
}

void GET_CHANNELS ()
{
FILE *read_from;
char dummy[50];
	if ((read_from = fopen ("channels.dat", "r")) == NULL)
		{
		printf (" error in open file channels.dat \n");
		exit (0);
		}

	if (fscanf (read_from, "%s %s %f %f %f %d %f %f %s %f %f %f %d %f %f %s %f %f %f %d %f %f %s %f %f %f %d %f %f", dummy, dummy, &channels[NMDA].nernst, &channels[NMDA].tau1, &channels[NMDA].tau2, &channels[NMDA].hebb, &channels[NMDA].max_weight, &channels[NMDA].nuu, dummy, &channels[AMPA].nernst, &channels[AMPA].tau1, &channels[AMPA].tau2, &channels[AMPA].hebb, &channels[AMPA].max_weight, &channels[AMPA].nuu, dummy, &channels[GABAA].nernst, &channels[GABAA].tau1, &channels[GABAA].tau2, &channels[GABAA].hebb, &channels[GABAA].max_weight, &channels[GABAA].nuu, dummy, &channels[GABAB].nernst, &channels[GABAB].tau1, &channels[GABAB].tau2 , &channels[GABAB].hebb, &channels[GABAB].max_weight, &channels[GABAB].nuu) != 29) 
	printf (" error in reading chanlles \n");
}


void SAVE_CONFIG ()
{
int 	unit, nlinks, in, sta, out;
FILE	*save_to;
char	filename[50];
LINK	*link;
	printf (" save config to file ... \n"); scanf ("%s", filename);
	save_to = fopen (filename, "w");  
	printf ("written %d\n", fprintf ( save_to, "%d       %s   %d   %d   %d    \n", 	
			N_UNITS, TEX, REC, MOL, GLOM));
    	for (unit = 0; unit < N_UNITS; unit++)  
		{ 
		nlinks = 0;       
		link = units[unit].links_to_unit;
		while (link != 0)
			{
			nlinks++;
			link = link->next;
                	}
		if (fprintf (save_to, "%d %f %f %f %f %f %s %d %d %d %d\n", 
		units[unit].type, units[unit].inpar1, units[unit].inpar2, units[unit].stpar1, units[unit].outpar1, units[unit].outpar2, units[unit].name, units[unit].flag, units[unit].selected, nlinks, units[unit].couche) == EOF) printf ("found EOF at unit %d \n", unit);
		if (units[unit].input_function == GET_MOLECULES)        in = 0;
		if (units[unit].input_function == SUM_INPUTS) 		in = 1;
		if (units[unit].input_function == MIXED_INPUTS) 	in = 2;      
		if (units[unit].input_function == GET_MOLECULES) 	in = 4;
		
		if (units[unit].input_function == SAT_INPUTS)		in = 6;
		if (units[unit].input_function == ADAPT_INPUT)		in = 7;
		if (units[unit].input_function == GUST_INPUT)		in = 8;
		if (units[unit].state_function == LINEAR) 		sta = 0;
		if (units[unit].state_function == DECAY) 		sta = 1;
		if (units[unit].state_function == FALSE_DECAY) 		sta = 3;
		if (units[unit].state_function == POT_REC) 		sta = 2;
		if (units[unit].output_function == SPIKE) 		out = 0;
		if (units[unit].output_function == THRESHOLD) 		out = 1;
		if (units[unit].output_function == LINEAR) 		out = 3;
		if (units[unit].output_function == SAT)			out = 31;
		if (units[unit].output_function == SIG) 		out = 4;
		if (units[unit].output_function == FALSE_SIG)	 	out = 5; 
		if (units[unit].output_function == FALSE_SPIKE) 	out = 6;
		if (units[unit].output_function == ADAPT_SPIKE)         out = 7;
		if (fprintf (save_to, "%d %d %d\n", in, sta, out) == EOF) printf (" found eof at unit %d\n", unit);
		link = units[unit].links_to_unit;
		while (link != NULL)
			{         
			if (fprintf (save_to, "%d %f %d %d\n", 
				link->from_unit, link->weight, link->delay, link->type) == EOF) printf ("found eof in links at unit %d\n", unit);
			link = link->next;
			}     
		
		}
fclose (save_to);

}              



                 

void SHOW_UNITS ()
{
int	unit, i;
LINK	*link;          
	i = 0;
	for (unit = 0; unit < N_UNITS; unit++)           
		printf (" neuron %d is a %d %s in layer %d out1 %f out2 %f \n", 
				unit, units[unit].type, units[unit].name, units[unit].couche, units[unit].outpar1, units[unit].outpar2);

}
void SHOW_LINKS ()
{
int unit; 
LINK *link;int i;
	for (unit = 0; unit < N_UNITS; unit++)
		{
		  i = 0;
		link = units[unit].links_to_unit;
		while (link != NULL)
			{
			printf ("link %d from neuron %d to neuron %d with weigth %f delay %d type %d\n",
				i, link->from_unit,  unit, 
				link->weight, link->delay, link->type);
			i++;
			link = link->next;
			}
		}

}

#if 0		
void READ_CONFIG ()
{
int	    	unit, nlinks, link, in, sta, out;
FILE    	*read_from;   
char		filename[50];                           
int 		nunits, type, sel, flag, from_unit, delay, couche;
float		inp1, inp2, par, out1, out2, weight;
char		name[10];                       
FUNCTION 	inf, staf, outf;     
LINK		*lin;
open_loop:
	printf (" read config from file ... \n");
	scanf ("%s", filename);
	if ((read_from = fopen (filename, "r")) == NULL)
		{
		printf (" file does not exist, try again\n");
		goto open_loop;		
		}
	if (fscanf (read_from, "%d       %s   %d    %d    %d     \n", 
						&nunits, TEX, &REC, &MOL, &GLOM) != 5) printf (" first error \n"); 
	ALLOCATE_NEURONS (nunits);
	N_UNITS = 0; 
	for (unit = 0; unit < nunits; unit++)
		{
		if (fscanf (read_from, "%d %f %f %f %f %f %s %d %d %d %d\n",&type, &inp1, &inp2, &par, &out1, &out2, name, &flag, &sel, &nlinks, &couche) != 11) printf (" error at unit %d \n", unit);
		if (fscanf (read_from, "%d %d %d\n", &in, &sta, &out) != 3) printf (" 2 error at unit %d \n", unit);
		if (in == 0) inf = GET_MOLECULES;
		if (in == 1) inf = SUM_INPUTS;
		if (in == 2) inf = MIXED_INPUTS;
		if (in == 4) inf = GET_MOLECULES;
		if (in == 5) inf = PROJ_INPUTS;                   
		if (in == 6) inf = SAT_INPUTS;
		if (in == 8) inf = GUST_INPUT;
		if (in == 7) inf = ADAPT_INPUT;
		if (sta == 0) staf = LINEAR;
		if (sta == 1) staf = DECAY;
		if (sta == 2) staf = POT_REC;
		if (sta == 3) staf = FALSE_DECAY;
		if (out == 0) outf = SPIKE;
		if (out == 1) outf = THRESHOLD;
		if (out == 3) outf = LINEAR;                    
		if (out == 31) outf = SAT;
		if (out == 4) outf = SIG;                              
		if (out == 5) outf = FALSE_SIG;  
		if (out == 6) outf = FALSE_SPIKE;
		if (out == 7) outf = ADAPT_SPIKE;
        	MAKE_NEURON (type, name, inf, staf, outf, inp1, inp2, par, out1, out2);
        	units[unit].selected = sel;  
		units[unit].flag = FAUX;                            
		units[unit].couche = couche;
        	for (link = 0; link < nlinks; link++)
			{
			if (fscanf (read_from, "%d %f %d %d\n", &from_unit, &weight, &delay, &type) != 4)
			  {printf (" error at unit %d link %d\n" ,unit, link);getchar ();}
            		MAKE_LINK (from_unit, unit, weight, delay, type);
                    
		}    
	      }


	fclose (read_from);
} 
#endif		
#if 0
void GET_CONFIG ()
{
int	    	unit, nlinks, link, in, sta, out;
FILE    	*read_from;   
char		filename[50];                           
int 		nunits, type, sel, flag, from_unit, delay, couche;
float		inp1, inp2, par, out1, out2, weight;
char		name[10];                       
FUNCTION 	inf, staf, outf;     
LINK		*lin;
open_loop:
	printf (" read config from file ... \n");
	scanf ("%s", filename);
	if ((read_from = fopen (filename, "r")) == NULL)
		{
		printf (" file does not exist, try again\n");
		goto open_loop;		
		}
	fscanf (read_from, "%d       %s   \n", 
						&nunits, TEX); 
	ALLOCATE_NEURONS (nunits);
	N_UNITS = 0; 
	for (unit = 0; unit < nunits; unit++)
		{
		if (fscanf (read_from, "%d %f %f %f %f %s %d %d %d \n",&type, &inp1, &par, &out1, &out2, name, &flag, &sel, &nlinks) != 9) printf (" error at unit %d \n", unit);
		fscanf (read_from, "%d %d %d\n", &in, &sta, &out);
		if (in == 0) inf = SUM_INPUTS;
		if (in == 1) inf = SUM_INPUTS;
		if (in == 2) inf = MIXED_INPUTS;
		if (in == 4) inf = GET_MOLECULES;
		if (in == 6) inf = SAT_INPUTS;
		if (sta == 0) staf = LINEAR;
		if (sta == 1) staf = DECAY;
		if (sta == 2) staf = POT_REC;
		if (sta == 3) staf = FALSE_DECAY;
		if (out == 0) outf = SPIKE;
		if (out == 1) outf = THRESHOLD;
		if (out == 3) outf = LINEAR;                    
		if (out == 31) outf = SAT;
		if (out == 4) outf = SIG;                              
		if (out == 5) outf = FALSE_SIG;  
		if (out == 6) outf = FALSE_SPIKE;
		if (out == 7) outf = FALSE_SPIKE;
        	MAKE_NEURON (type, name, inf, staf, outf, inp1, 0.0, par, out1, out2);
        	units[unit].selected = sel;  

		units[unit].couche = 0;
        	for (link = 0; link < nlinks; link++)
			{
			if (fscanf (read_from, "%d %f %d\n", &from_unit, &weight, &delay) != 3) printf (" error at unit %d link %d \n", unit, link);
            		MAKE_LINK (from_unit, unit, weight, delay, local);
			}
                    
		}    

	fclose (read_from);
} 
#endif
void NULL_ODORS ()
{
int step, o;
	for (o = 0; o < MOL; o++)
		for (step = 0; step < N_STEPS; step++)
			molecules[o].stim[step] = 0.0;   
}

void SHOW_ODORS ()
{
int step, o;
		for (step = 0; step < N_STEPS; step++)
		    	{
			for (o = 0; o < MOL; o++)
				printf ("%2.1f ", molecules[o].stim[step]); 
			printf ("\n");
			}  
}

void RESET_UNITS ()
{
int unit;
	for (unit = 0; unit < N_UNITS; unit++)
	        {
		units[unit].x_coor = units[unit].y_coor = 0;
		units[unit].flag = FAUX;
		units[unit].selected = FAUX;
		}
}

void FAMILIAR ()
{
int step; 
	for (step = 0; step < N_STEPS; step++)
		{
		molecules[10].stim[step] = 1.0;
		molecules[30].stim[step] = 1.0;
		molecules[50].stim[step] = 1.0; 
		molecules[70].stim[step] = 1.0;
		molecules[90].stim[step] = 1.0;
		}
}

void NOVEL3 ()
{
int step; 
	for (step = 0; step < N_STEPS; step++)
		{
		molecules[20].stim[step] = 1.0;
		molecules[40].stim[step] = 1.0;
		molecules[60].stim[step] = 1.0; 
		molecules[80].stim[step] = 1.0;
		molecules[99].stim[step] = 1.0;
		}
}

void NOVEL1 ()
{
int step; 
	for (step = 0; step < N_STEPS; step++)
		{
		molecules[12].stim[step] = 1.0;
		molecules[32].stim[step] = 1.0;
		molecules[52].stim[step] = 1.0; 
		molecules[72].stim[step] = 1.0;
		molecules[92].stim[step] = 1.0;
		}
}

void NOVEL2 ()
{
int step; 
	for (step = 0; step < N_STEPS; step++)
		{
		molecules[15].stim[step] = 1.0;
		molecules[35].stim[step] = 1.0;
		molecules[55].stim[step] = 1.0; 
		molecules[75].stim[step] = 1.0;
		molecules[95].stim[step] = 1.0;
		}
}

void C0 (conc)
{
int step; 
	for (step = 0; step < N_STEPS; step++)
		{
		molecules[20].stim[step] = conc;
		molecules[60].stim[step] = conc;
				}
}


void C1 (conc)
{
int step; 
	for (step = 0; step < N_STEPS; step++)
		{
		molecules[25].stim[step] = conc;
		molecules[65].stim[step] = conc;
				}
}
void C2 (conc)
{
int step; 
	for (step = 0; step < N_STEPS; step++)
		{
		molecules[30].stim[step] = conc;
		molecules[70].stim[step] = conc;
				}
}
void C3 (conc)
{
int step; 
	for (step = 0; step < N_STEPS; step++)
		{
		molecules[35].stim[step] = conc;
		molecules[75].stim[step] = conc;
				}
}


void X (conc)
{
int step; 
	for (step = 0; step < N_STEPS; step++)
		{
		molecules[0].stim[step] = conc;
		molecules[90].stim[step] = conc;
				}
}
void GET_RUN_PARAMETERS (filename)
char *filename;
{
FILE *read_from;
char to[30];
int help1, help2, points, i;
	if ((read_from = fopen (filename, "r")) == NULL)
  		{
  		printf (" error in open file para.dat \n");
  		exit (0);
  		}

	if (fscanf (read_from, "%s %s %d %s %d %s %d %s %f", 
	    TEX, to, &N_STEPS, to, &WIDTH, to, &HEIGHT, to, &DELTA) != 9)
	  	{
	    	printf (" error in reading file para.dat\n");
	    	exit (0); 
	  	}
	close (read_from);
	
}


void TESTSN ()
{
int i;
for (i=100; i < 200; i++)
	{
	molecules[10].stim[i]=0.0;
	molecules[15].stim[i] = 0.0;
	molecules[20].stim[i] = 0.0; 
	molecules[25].stim[i]=0.0;
	molecules[30].stim[i] = 0.0;
	}

for (i=500; i < 600; i++)
	{
	molecules[10].stim[i]=1.0;
	molecules[15].stim[i] = 1.0;
	molecules[20].stim[i] = 1.0; 
	molecules[25].stim[i]=1.0;
	molecules[30].stim[i] = 1.0;
	}
}

void RESP (conc, m1, m2)
float conc;
int m1, m2;
{
int n, o, s, i, from, too;
float c, c0;
c=conc;
s=0;
c0=0.0;
	for(i=0; i < N_STEPS; i++)
		for(o=0; o < GLOM; o++)
			{molecules[o].stim[i]=0.0;
			
			}
i=0;
while (i<N_STEPS)
	{
	for (i=s; i<s+20; i++)
		{molecules[m1].stim[i]=c0;
		molecules[m2].stim[i]=c0;
		c0+=c/20;
		}
	for (i=s+20;i<s+60;i++)
		{
		molecules[m1].stim[i]=c;
		molecules[m2].stim[i] =c;
		}
	c0=c;
	for (i=s+60; i < s+80; i++)
		{
		molecules[m1].stim[i]= c0;
		molecules[m2].stim[i] = c0;
		c0-=c/20;
		}
	s+=100;
	}
}

#if 0
void RESP_O ()
{
int n, o, s, i, from, too;
float c, c0;
int oo[100];
printf ("nmols ? c ? from ?");
scanf ("%d %f %d", &n, &c, &from);
for (o=0; o < n; o++)
	{oo[o]=floor(RANF()*GLOM);
	printf ("%d \n", oo[o]);}
s=from;
c0=0.0;
	for(i=0; i < too; i++)
		for (o=0; o<n;o++)
			molecules[oo[o]].stim[i]=0.0;

while (i<N_STEPS)
	{
	if ((RANF()> 0.6)&& (i > 400) && (i < 800))
		c=1.0;
	else
		c=0.05;
	for (i=s; i<s+1; i++)
		{
		for (o=0; o<n;o++)	
			molecules[oo[o]].stim[i]=c0;
		c0+=c/1;
		}
	for (i=s+1;i<s+6;i++)
		{
		for (o=0; o<n; o++)
			molecules[oo[o]].stim[i]=c;
		}
	c0=c;
	for (i=s+6; i < s+8; i++)
		{
		for (o=0;o<n;o++)
			molecules[oo[o]].stim[i]= c0;
		c0-=c/2;
		}
	for (i=s+8; i < s+10; i++)
		{
		for (o=0;o<n;o++)
			molecules[oo[o]].stim[i]= 0.0;
		}
	s+=10;
	}
printf ("end of resp\n");
}		

#endif
#if 1
void SAVE_DATA ()
{
FILE *save_to; 
char name[20]; 
int unit;
int step;
	printf ("save to file .. \n");
	scanf ("%s", name);
	save_to = fopen (name, "w"); 
	for (step = 0; step < N_STEPS; step++)
		{
		for (unit = 0; unit < N_UNITS; unit++)
			if (units[unit].type == mitral2)
				fprintf (save_to, "%f ", units[unit].output[step]); 
		}
	fclose (save_to);
}					
#endif


