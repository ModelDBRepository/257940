#include "cell.init"


/*************************************************************************/
/************** this file contains the main functions which serve ********/
/************** to build a network: make neurons and make link ***********/
/*************************************************************************/

 
/** make neuron creates a neuron belonging to a type-class and **********/
/** to which are associated three update functions and their parameters */

void MAKE_NEURON (type, name , in_fun, sta_fun, out_fun, in1, in2, sta, out1, out2)
char		*name; 
enum TYPES	type;
FUNCTION 	in_fun, sta_fun, out_fun;                                      
float		in1, in2, sta, out1, out2;
{ 
	units[N_UNITS].type 			= type;  
	strcpy (units[N_UNITS].name, name);
	units[N_UNITS].input_function 		= in_fun;
	units[N_UNITS].state_function 		= sta_fun;
	units[N_UNITS].output_function 		= out_fun;
	units[N_UNITS].inpar1			= in1;     
	units[N_UNITS].inpar2			= in2;
	units[N_UNITS].stpar1 			= sta;
	units[N_UNITS].outpar1			= out1;
	units[N_UNITS].outpar2			= out2;
	units[N_UNITS].old_state 		= 0.0;
	units[N_UNITS].calcium	 		= (float *) calloc (N_STEPS, sizeof (float));
	units[N_UNITS].selected   		= FAUX;    
	units[N_UNITS].links_to_unit		= NULL;
	units[N_UNITS].state 			= (float *) calloc (N_STEPS, sizeof (float));
	units[N_UNITS].output			= (float *) calloc (N_STEPS, sizeof (float));
	units[N_UNITS].flag 			= FAUX;
	N_UNITS++;       
} 


void MAKE_LINK (from_unit, to_unit, weight, delay, type, channel)
int 	from_unit, to_unit, delay, channel;
float	weight;                                         
enum LINK_TYPES type;
{
LINK	*link;
	link = 			(LINK *) malloc (sizeof (LINK));
	link->from_unit = 	from_unit;
	link->weight = 		weight;
	link->firstweight - 	weight;
	link->delay = 		delay;
        link->next = 		units[to_unit].links_to_unit; 
 	link->signal = 		(float *) calloc (delay, sizeof (float));
/*	link->weight_change = 	(float *) calloc (N_STEPS, sizeof (float));*/
	link->type = 		type;
	link->reverse = 	FAUX;
	link->nspikes = 	0; 
	link->spikes = 		(int *) calloc (10, sizeof (int));
	link->amps = 		(float *) calloc (10, sizeof (float));
	link->reversal = 	channels[channel].nernst; 
	link->tau1 = 		channels[channel].tau1/DELTA; 
	link->tau2 = 		channels[channel].tau2/DELTA;
	link->gmax = 		1.0;
	link->mod = 		1.0;
	link->hebb = 		FALSE;
	units[to_unit].links_to_unit = link;
}

void MAKE_LINK2 (from_unit, to_unit, comp, weight, delay, type, channel)
int 	from_unit, to_unit, delay;
float	weight;                                         
enum 	LINK_TYPES type;
int	channel, comp;
{
LINK	*link;
	link = 			(LINK *) malloc (sizeof (LINK));
	link->from_unit = 	from_unit;
	link->too_comp = 	comp; 
	link->from_comp = 	soma; 
	link->weight = 		weight;
	link->firstweight = 	weight;
	link->delay = 		delay;
        link->next = 		units[to_unit].links_to_unit; 
 	link->signal = 		(float *) calloc (delay, sizeof (float));
	link->type = 		type;
	link->reverse = 	VRAI;
	link->hebb = 		channels[channel].hebb;
	link->learning_rate = 	channels[channel].nuu;
	link->max_weight = 	channels[channel].max_weight;
	link->delta_weight = 	0.0;
	link->old_signal = 	0.0;
	link->old_help = 	0.0;
	link->tau1 = 		channels[channel].tau1/DELTA;
	link->tau2 = 		channels[channel].tau2/DELTA;
	link->gmax = 		1.0;
	link->reversal = 	channels[channel].nernst;
	link->nspikes = 	0;
	link->spikes = 		(int * ) calloc (10, sizeof (int));
	link->amps = 		(float *) calloc (10, sizeof (float));
	link->channel = 	channel; 
	link->mod =		1.0; 
	N_LINKS++; 
	units[to_unit].links_to_unit = link;

}









	

                                   







	

                                   
