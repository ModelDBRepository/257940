/* this file contains definitions of neural input, state and output functions */

#include "cell.init"

/*****************************************************************/
/************** NEURON FUNCTIONS *********************************/
/*****************************************************************/

  
/** input functions are float and take two parameters: 	**/
/** index of neuron and a float help parameter 		**/	
                  
#if 1

float SUM_INPUTS (uni, step, in1, in2, dummi)
int	uni, step;
float	dummi, in1, in2;
{
int	l_number, del;
float	input_sum, signal;          
LINK	*link;
	input_sum = 0.0;             
	link = units[uni].links_to_unit;
		while (link != NULL)
			{                                      
			del = link->delay;  
			if (step > 1) 
				signal = link->signal[del-1] *(link->reversal-units[uni].state[step-1])/fabs (link->reversal);
			input_sum += signal;
			link = link->next;
			}
	if (step <= 1)
		input_sum = 0.0;
	return (input_sum); 
}

#endif

#if 0
float SUM_INPUTS (uni, step, in1, in2, dummi)
int	uni, step;
float	dummi, in1, in2;
{
int	l_number, del;
float	input_sum, signal;          
LINK	*link;
	input_sum = 0.0;             
	link = units[uni].links_to_unit;
		while (link != NULL)
			{                                      
			del = link->delay;   
			signal = link->signal[del-1];
			 input_sum += signal;
			if ((step > 3) && (link->hebb == VRAI) && (GUST[step-1] > 0.0))
				if (fabs (link->weight) < fabs (link->max_weight))
				  link->weight += link->learning_rate *  (units[uni].output[step-1] * units[link->from_unit].output[step-1]);
			link->weight_change[step] = link->weight;
			link = link->next;
			}
	return (input_sum); 
}

#endif


float ELECTRICAL_IN (uni, step, in1, in2, dummi)
int uni, step; 
float dummi, in1, in2; 
{
	float input; 
	input = SUM_INPUTS (uni, step, in1, in2, dummi);
	input += contex[units[uni].couche].stepp[step];
	return (input);
	
}



float ADAPT_INPUT (uni, step, in1, in2, dummi)
int uni, step;
float dummi, in1, in2;
{
float input;
float calcium;
	input = SUM_INPUTS (uni, step, in1, in2, dummi);
	if (step > 0)
		units[uni].calcium[step] = (1-exp(-DELTA/in1)) * 10*units[uni].output[step-1]  + units[uni].calcium[step-1]*exp(-DELTA/in1) ;
	else
		units[uni].calcium[step] = 0.0;
	input -= in2 * units[uni].calcium[step];
	return (input);
}



float ADAPT_ELECTRICAL (uni, step, in1, in2, dummi)
int uni, step;
float dummi, in1, in2;
{
float input;
float calcium;
	input = ELECTRICAL (uni, step, in1, in2, dummi);
	if (step > 0)
		units[uni].calcium[step] = (1-exp(-DELTA/in1)) * 1.0*units[uni].output[step-1]  + units[uni].calcium[step-1]*exp(-DELTA/in1) ;
	else
		units[uni].calcium[step] = 0.0;

	input -= in2 * units[uni].calcium[step];
	return (input);
}


float LOOK_UP (uni, step, in1, in2, dummi)
int uni, step; 
float dummi, in1, in2;
{
float in;
int m;
    in = molecules[uni].stim[step];
return (in);
} 

float GET_MOLECULES (uni, step, in1, in2, dummi)
int	uni, step;
float dummi, in1, in2;
{
float in;
int		m;
	in = 0.0;
	for (m = 0; m < MOL; m++)
		in += recs[uni].sensi[m]*molecules[m].stim[step];
	return (in);
}


float MIXED_INPUTS (uni, step, in1, in2, outside)  /** units which receive input from world and from system **/
int 	uni, step;                  
float	outside, in1, in2;
{            
float 	in;   
	in = SUM_INPUTS (uni, step, in1, in2, 0.0);
	in += in2 * outside;
	return (in);
}

float MIXED_SATS (uni, step, in1, in2, outside)  /** units which receive input from world and from system **/
int 	uni, step;                  
float	outside, in1, in2;
{            
float 	in;   
	in = SAT_INPUTS (uni, step, in1, in2, outside);
	in += outside;
	return (in);
}

/** state functions are float and take one float parameter **/                           

float LINEAR (input, dummy, dummi)
float *input, *dummy, *dummi;
{                                   
float help;
	help = *input;  
	return (help);
}


float SAT (input, down, up)
float *input, *down, *up;
{                                   
float help;
	if (*input >= *up)
		help = *up;
	if (*input <= *down)
		help = *down;
	if ((*input > *down) && (*input < *up))
		help = *input;
return (help);
}


float DECAY (input, old_state, decay)
float	*input, *old_state, *decay;
{
float help;
double exp();

	help = exp (- (DELTA / *decay));
	return ((1.0-help) * *input + (help) * *old_state);
}




float FALSE_DECAY (input, old_state, decay)
float *input, *old_state, *decay;
{

  	return (*input + *decay * *old_state);

}


float POT_REC (input, old_state, alpha)
float *input, *old_state, *alpha;
{
float help, beta, p, q;  
	beta = 0.95;
	help = *alpha * *input + beta * *old_state;
	return (help);
}



                                                            


/** output functions are float, and have 3 float parameters **/

float SIG (value, offset, slope)
float 	*value, *offset, *slope;    
{
double 	exp ();  
float	theta;
float 	help; 
 	theta = 1.0 / (4.0* *slope);                                     
	help = 1.0 / (1.0 + exp (- (*value - *offset) / theta));
	return (help);
}
                                                    

float FALSE_SIG (value, seuil_inf, seuil_sup)
float *value, *seuil_inf, *seuil_sup;
{
float slope, result;
 
	slope = 1 / (*seuil_sup - *seuil_inf);
	
	if (*value < *seuil_inf) 
		return (0.0);
	if (*value > *seuil_sup)
		return (1.0);
	if ((*value >= *seuil_inf) && (*value <= *seuil_sup))
		return ((*value - *seuil_inf) * slope);
}


float THRESHOLD (state, thresh, prob)
float *state, *thresh, *prob;
{                  
float help;  
	help = 0.0;
	if ((*state < *thresh) && (RANF () < (1.0 - *prob)))
		{
		help = 1.0;  
		*state = 0.0;
		}
	if ((*state >= *thresh) && (RANF () < *prob))
		{
		help = 1.0;		
		*state = 0.0;
	    }
                   
	return (help);
}


float SPIKE (state, offset, slope)
float *state, *offset, *slope;
{
float help, r, v;  
double RANF ();
float SIG ();                              
	if (*state < 0.0)
		help = 0.0;
	else
		if (SIG (state, offset, slope) > RANF ())
			{
			help = 1.0;
			*state = 0.0;
			}
		else
			help = 0.0;   
	return (help);
}

float FALSE_SPIKE (state, offset, slope)
float *state, *offset, *slope;
{
float help, r, v;  
double RANF ();
float FALSE_SIG (); 
	if (FALSE_SIG (state, offset, slope) > RANF ())
		{
		help = 1.0;
		*state = 0.0;
		}
	else
		help = 0.0;   
	return (help);
}



float ADAPT_SPIKE (state, seuil_inf, seuil_sup)
float *state, *seuil_inf, *seuil_sup;
{
float help, r, v;  
double RANF ();
float SIG (); 
	if (*state < 0.0)
		help = 0.0;
	else
		if (FALSE_SIG (state, seuil_inf, seuil_sup) > RANF ())
			{
			help = 1.0;
			*state = 0.0;
			}
		else
			help = 0.0;             
	if (*state > 0.0)
		*seuil_sup += DOFF;
	if (*state < 0.0)
		*seuil_sup = 1.0;
	return (help);
}










