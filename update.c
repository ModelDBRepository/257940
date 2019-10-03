#include "cell.init"


/**** this file contains functions to run the network *****/
                                                            

/** null all sets to zero all signals on synapses and neurons ****/

void NULL_ALL ()
{
int 	s, u, sig, hel, o;  
LINK	*help;
printf ("in null all N_STEPS %d N_UNITS %d \n", N_STEPS, N_UNITS);
	for (u = 0; u < N_UNITS; u++)
		{ 
		for (s = 0; s < N_STEPS; s++)
			{
			units[u].output[s] = 0.0;
			units[u].state[s] = 0.0;
			}                   
		units[u].old_state = 0.0;
		help = units[u].links_to_unit;  
		while (help)
		      {
		      for (sig = 0; sig < help->delay; sig++)
			  {
			  help->signal[sig] = 0.0; 
			  }
		      for (sig = 0; sig < 10; sig++)
			  {
			  help->spikes[sig] = 0; 
			  help->amps[sig] = 0.0;
			  }
		      	help = help->next;                 
			}
		} 
	for (s = 0; s < N_STEPS; s++)
		{
		AVSM[s] = 0.0;
		AVSG[s] = 0.0;
		AVSP[s] = 0.0;

		} 
	

}



		
/** propagate link signal propagates the signal in the synapse delays **/		

void PROPAGATE_LINK_SIGNAL (link, step)
LINK	*link;
{
float	signa;  
int	dell, sp;   
	if (units[link->from_unit].output[step] > 0.0)
		{
		for (sp = 9; sp > 0; sp--)
			{
			link->spikes[sp] = link->spikes[sp-1];
			link->amps[sp] = link->amps[sp-1]; 
			}
		link->spikes[0] = step; 
		link->amps[0] = units[link->from_unit].output[step]; 
		}
	for (dell= link->delay - 1; dell > 0; dell--)
		link->signal[dell] =  link->signal[dell-1]; 
	signa = 0.0;
	for (sp = 0; sp < 10; sp++)
		signa += link->amps[sp]*link->gmax*link->weight*link->mod*DEXP(link->tau1, link->tau2, (float)(step-link->spikes[sp]));  
	link->signal[0] = signa;                       
}                            

/** update neuron computes the input, potential and output of one neuron **/

void UPDATE_NEURON (unit,step)
int	unit,step;
{
float in, sta, out; 

	in = (*units[unit].input_function) (unit, step, units[unit].inpar1, units[unit].inpar2, 0.0);
	
	sta = (*units[unit].state_function) (&in, &units[unit].old_state, &units[unit].stpar1); 
	units[unit].state[step] = sta;    
	out = (*units[unit].output_function) (&sta, &units[unit].outpar1, &units[unit].outpar2); 
	units[unit].old_state = units[unit].state[step]; 
	units[unit].output[step] = out;                            
	

}


/** synchronous updating of all links **/

void UPDATE_LINKS (step)
int step;
{
LINK	*link;
int		del, unit;           
    for (unit = 0; unit < N_UNITS; unit++)                 
		{
		link = units[unit].links_to_unit;
		while (link != NULL)
			{   
			if (link->weight != 0.0)
				PROPAGATE_LINK_SIGNAL (link, step);   
			link = link->next;            
			}
		}
}



void UPDATE_NET (step)
int step;
{
int	unit, n;                                       
int	s, v, g, p, i;
float 	in, sum; 
LINK 	*link;
float   *delta;
	v = g = p = i = 0;       
	for (unit = 0; unit < N_UNITS; unit++)
		{
		UPDATE_NEURON (unit, step); 
		}
	UPDATE_LINKS (step);  

}

                       

#if 1
float RUN ()
{
int step;
 float sp, sy;
 int too, from, d, d2; 
 float amin, in_m, in_n, aplus, m, old_m, *old_p, *p, gmax, forgettime; 
 LINK *link;
int interval;
interval = 120; 
	/*GET_RUN_PARAMETERS ("para.dat");*/
	NULL_ALL ();
	printf ("0 dont 1 learn\n"); 
	scanf ("%d", &d);
	printf ("0 dont forget 1 forget\n");
	scanf ("%d", &d2);
	if (d2==1)
		{
		printf("how long?\n");
		scanf ("%f", &forgettime);
		}

	MEASURE_WEIGHTS1 ();
	MEASURE_WEIGHTS2 ();
	MEASURE_WEIGHTS3 ();
	if (d2 == 1)
		{
		/*FORGET_PC_ASS (FORGETASS, forgettime);*/
		FORGET_MC_GC (FORGETMCGC, forgettime);
		/*FORGET_PC_GC (FORGETMCGC, forgettime);*/
		}
	MEASURE_WEIGHTS1 ();
	MEASURE_WEIGHTS2 ();
	MEASURE_WEIGHTS3 ();
	
	for (step = 0; step < N_STEPS; step++)
	  {
		  UPDATE_NET (step);
	if ((step == interval) && (d==1))
		{GET_AVERAGES (step-interval, interval);
		/*HEBB_ASS_PC (RATEASS);*/
		HEBB_MC_GC (RATEMCGC);
		/*HEBB_PC_GC (RATEPCGC);*/ 
		interval += 120;}		
	}
	SYNCH ();
	MEASURE_WEIGHTS1 ();
	MEASURE_WEIGHTS2 ();
	MEASURE_WEIGHTS3 ();

}
#endif

#if 0
float RUN ()
{
int step;
 float sp, sy;
 int too, from; 
 float amin, in_m, in_n, aplus, m, old_m, *old_p, *p, gmax; 
 LINK *link;
	/*GET_RUN_PARAMETERS ("para.dat");*/
	NULL_ALL ();

	for (step = 0; step < N_STEPS; step++)
	  {
		  UPDATE_NET (step);
	}
}
#endif
float RUN2 ()
{
int step;
 float sp, sy;
 int too, from; 
 float amin, in_m, in_n, aplus, m, old_m, *old_p, *p, gmax; 
 LINK *link;
	/*GET_RUN_PARAMETERS ("para.dat");*/
	NULL_ALL ();

	for (step = 0; step < N_STEPS; step++)
	  {
		  UPDATE_NET (step);
		
	}
}


float RUN3 (weightfile)
FILE *weightfile;
{
int unit, step; 
LINK *link;
float wppav, wmgav, wpgav; 
int ppcount, mgcount, pgcount; 
int interval; 
 
	/*GET_RUN_PARAMETERS ("para.dat");*/
	NULL_ALL ();
	for (step = 0; step < 120; step++)
		  {
		  UPDATE_NET (step);
		}
	wmgav=0.0; wppav = 0.0; wpgav=0.0; 
	ppcount = 0; mgcount = 0; pgcount = 0; 
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == granule)
			{
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == mitral2)
					{
					wmgav += link->weight; 
					mgcount += 1; 
					}
				if (units[link->from_unit].type == pyr)
					{
					wpgav += link->weight;
					pgcount += 1; 
					}
				link = link->next;
				}
			}	
		if (units[unit].type == pyr)
			{
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == pyr)
					{
					wppav += link->weight; 
					ppcount += 1;
		 			}
				link = link->next; 
					
				}
			}
		}
		fprintf (weightfile, "%f %f %f\n", wmgav/mgcount, wpgav/pgcount, wppav/ppcount);
		HEBB_ASS_PC (RATEASS);
		HEBB_MC_GC (RATEMCGC);
		HEBB_PC_GC (RATEPCGC);
						

}	



float RUN4 (weightfile, interval)
FILE *weightfile;
float interval;
{
int unit, step; 
LINK *link;
float wppav, wmgav, wpgav; 
int ppcount, mgcount, pgcount; 
 
	/*GET_RUN_PARAMETERS ("para.dat");*/
	NULL_ALL ();
	
		wmgav=0.0; wppav = 0.0; wpgav=0.0; 
		ppcount = 0; mgcount = 0; pgcount = 0; 
		for (unit = 0; unit < N_UNITS; unit++)
			{
			if (units[unit].type == granule)
				{
				link = units[unit].links_to_unit;
				while (link)
					{
					if (units[link->from_unit].type == mitral2)
						{
						wmgav += link->weight; 
						mgcount += 1; 
						}
					if (units[link->from_unit].type == pyr)
						{
						wpgav += link->weight;
						pgcount += 1; 
						}
					link = link->next;
					}
				}
			if (units[unit].type == pyr)
				{
				link = units[unit].links_to_unit;
				while (link)
					{
					if (units[link->from_unit].type == pyr)
						{
						wppav += link->weight; 
						ppcount += 1; 
						}
					link = link->next; 
					}
				}
			}
		/*FORGET_PC_ASS (FORGETASS, interval);*/
		FORGET_MC_GC (FORGETMCGC, interval);
		/*FORGET_PC_GC (FORGETMCGC, interval);*/

		fprintf (weightfile, "%f %f %f\n", wmgav/mgcount, wpgav/pgcount, wppav/ppcount);
						

		

}	

			
		    
		
	  

			    
			

		    
		
 
		












