#include "cell.init"




void DRAW_INTER (msec)
int msec;
{
int i,j; 
EVENT maus;
float *inter, *dist, sum, med, spikes;
char text[20];
int o;
      inter = (float *) calloc (msec, sizeof (float));
      dist = (float *) calloc (15, sizeof (float));
       if (spike_window == NULL)
		     spike_window = OPEN_WINDOW (0, 0, 600, 500, blanc);
       CHOOSE_WINDOW (spike_window);	
       CLEAR ();
       for (;;)
	   {
	   for (o = 0; o < NODS; o++)
	       {
	       sum = 0.0;spikes = 0;
	       inter = INTERSPIKE (p_out, msec, o);
	       for (i = 0; i < 15; i++)
		   sum += inter[i];
	       for (i = 0; i < 15; i++)
		   if (sum != 0.0)
		      {
		      med = 0.0;
		      for (j = 0; j <=i; j++)
			  {med += inter[j];
			   }
		      dist[i] = (med)/sum;
		      }
	       for (i = odors[o].from; i < odors[o].too; i++)
		   spikes += p_out[i];
		   for (i = 0; i < msec; i++)
		       inter[i] /= 10;
	       AXIS (50, 50+100*o, 2, 1, msec, 10);
	       SPIKES (50, 50+100*o, 2, 1, msec, inter);
	       sprintf (text, "%f spikes", spikes);
	       TEXT (text, 50, 50+100*o+20); 
	       AXIS (350, 300, 20, 200, 15, 1);
	       CURVE (350, 300, 20, 200, 14, dist); 
	       }
	   maus.flag = expose;
	   while (maus.flag != mouse)
			maus = GET_EVENT ();
		if (maus.button == RIGHT)
			break;
	   }
free (inter);
}




       


void DRAW_ONE_STEP (step, x, y, type)
int	step, x, y;                     
enum TYPES type;
{        
int g, unit, r, i;
float value[50];
	for (i = 0; i < GLOM; i++)
		value[i] = 0.0;                                           
	for (unit = 0; unit < N_UNITS; unit++)
	  	{
	  	if ((type != receptor) && (units[unit].type == type) && (units[unit].couche < GLOM))
	      		value[units[unit].couche] = units[unit].output[step];   
		if (type == receptor)
	  		{
	  		 for (r = 0; r < REC; r++)
	       			for (g = 0; g < GLOM; g++)
		   			{
		   			if ((g >= r * (int) (GLOM/REC)) && (g < (r+1)* (int) (GLOM/REC)))
		      				value[g] += units[r].output[step];
		   			}
	   		}	
		}
	BOX (x, y, x+5*GLOM, y-50);  
	for (g = 0; g < GLOM; g++, x+= 5)
		{
		if ((value[g] > 0.0) && (value[g] < 1.0))
			FILLED_BOX (x, y, x+4, (int) (y - 100*value[g])); 
                else 
                   if (value[g] >= 1.0)
		     FILLED_BOX (x, y, x+4, (int) (y - 50));
		}
}	



void SHOW_WEIGHTS ()

{
int unit, x, y, y0;
LINK *link;
char chain[20];
y0 = 10;
	if (weight_window == NULL)
  		weight_window = OPEN_WINDOW (0, 0, 450, 100, blanc);
	CHOOSE_WINDOW (weight_window);
	CLEAR ();
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == granule)
			{
			y = y0+25+50; 
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == pyr)
					{
					x = units[link->from_unit].couche * 20 + 20;

					CIRCLE (x, y, 10); 
					FILLED_CIRCLE (x, y, (int) (link->weight * 5));
						
					}     
				link = link->next;
				}
			}
		}
			
}



void SHOW_PV (xmul, ymul)
int xmul, ymul;
{
int g, unit, y;
LINK *link;
EVENT maus;
char chain[10];
	if (pv_window == NULL)
		pv_window = OPEN_WINDOW (0, 0, 1000, 500, blanc);
	CHOOSE_WINDOW (pv_window);
	CLEAR ();
	for (;;)
		{
		for (g = 0, y = 20; g < GLOM; g++, y += 2*ymul)
			{
			for (unit = 0; unit < N_UNITS; unit++)
				if ((units[unit].type == vum) && (units[unit].couche == g))
					{
					link = units[unit].links_to_unit;
					break;
					}
			while (link)
				{
				if ((units[link->from_unit].type == proj) && (units[link->from_unit].couche == g))
					break;
				link = link->next;
				}
			CURVE (50, y, xmul, ymul, N_STEPS, link->weight_change);
			AXIS (50, y, xmul, ymul, N_STEPS, 10);
			sprintf (chain, "%d", g);
			TEXT (chain, 20, y);
			}
		maus.flag = expose;
		while (maus.flag != mouse)
			maus = GET_EVENT ();
		if (maus.button == RIGHT)
			break;
		
		}
}



void SHOW_VI (xmul, ymul)
int xmul, ymul;
{
int g, unit, y;
LINK *link;
EVENT maus;
char chain[10];
	if (vi_window == NULL)
		vi_window = OPEN_WINDOW (0, 0, 1000, 500, blanc);
	CHOOSE_WINDOW (vi_window);
	CLEAR ();
	for (;;)
		{
		for (g = 0, y = 20; g < GLOM; g++, y += 2*ymul)
			{
			for (unit = 0; unit < N_UNITS; unit++)
				if ((units[unit].type == inhib) && (units[unit].couche == g))
					{
					link = units[unit].links_to_unit;
					break;
					}
			while (link)
				{
				if ((units[link->from_unit].type == vum) && (units[link->from_unit].couche == g))
					break;
				link = link->next;
				}
			CURVE (50, y, xmul, ymul, N_STEPS, link->weight_change);
			AXIS (50, y, xmul, ymul, N_STEPS, 10);
			sprintf (chain, "%d", g);
			TEXT (chain, 20, y);
			}
		maus.flag = expose;
		while (maus.flag != mouse)
			maus = GET_EVENT ();
		if (maus.button == RIGHT)
			break;
		}
}
		

void DRAW_WEIGHTS ()
{
int y1, y2, x1, x2, y, g, unit;
float weighti, weightp;
LINK *link;
EVENT maus;
		weight_window = OPEN_WINDOW (0, 0, 600, 200, blanc);
	CHOOSE_WINDOW (weight_window);
	CLEAR ();
	for (;;)
		{
		x1 = 20; y1 = 80;y2 = 180;x2 = 100;
		BOX (x1, y1, x1+5*GLOM, y1 - 50);
		BOX (x1, y2, x1+5*GLOM, y2-50);
		BOX (x2, y1, x2+5*GLOM, y1 -50);
	/*	BOX (x2, y2, x2+5*GLOM, y2-50);*/
		for (g = 0; g < GLOM; g++, x1+= 5)
			{
			for (unit = 0; unit < N_UNITS; unit++)
				if ((units[unit].type == vum) && (units[unit].couche == 100))
					{
					link = units[unit].links_to_unit;
					break;
					}
			weighti = weightp = 0.0;

			while (link)
				{
				if ((units[link->from_unit].type == inhib) && (units[link->from_unit].couche == g))
					weighti = link->weight;
				if (((units[link->from_unit].type == proj) || (units[link->from_unit].type == excit)) && (units[link->from_unit].couche == g))
					weightp = link->weight;
				FILLED_BOX (x1, y2, x1+4, (int) (y2 - 50*fabs (weightp)));
				FILLED_BOX (x1, y1, x1+4, (int) (y1 - 50*fabs (weighti)));

				link = link->next;
				}
			}
		weighti = 0.0;
		for (g = 0; g < GLOM; g++, x2+=5)
			{
			for (unit = 0; unit < N_UNITS; unit++)
				if ((units[unit].type == inhib) && (units[unit].couche == g))
					{
					link = units[unit].links_to_unit;
					break;
					}
			while (link)
				{
				if ((units[link->from_unit].type == vum) && (units[link->from_unit].couche == 100))
					weighti = link->weight;
				FILLED_BOX (x2, y1, x2+4, (int) (y1 - 50*fabs (weighti)));
				link = link->next;
				}
			}
		maus.flag = expose;
		while (maus.flag != mouse)
			maus = GET_EVENT ();
		if (maus.button == RIGHT)
			break;


		}
		DESTROY_WINDOW (weight_window);
}
	
void DRAW_MEANS ()

{
int g, unit, r, i;
float value1[50];
float value2[50];
float value3[50];
float value4[50];
 float max;
int x1, x, y1, o, step, y2, y3, y4;
EVENT maus;
 x1 = 20; y1 = 80;y2 = 220;y3 = 360;y4 = 500;

	if (other_window == NULL)
		other_window = OPEN_WINDOW (0, 0, 600, 600, blanc);
	CHOOSE_WINDOW (other_window);
	CLEAR (); 
	for (;;)
		{
		for (o = 0, x1 = 20; o < NODS; o++, x1 += 5*GLOM + 30)
  			{
			for (i = 0; i < GLOM; i++)
			    {
			    value1[i] = 0.0;
			    value2[i] = 0.0;
			    value3[i] = 0.0;
			    value4[i] = 0.0;
			    }
		 
			max = 0.0;
			for (unit = 0; unit < N_UNITS; unit++)
	  			{
	  			if ((units[unit].type == proj) && (units[unit].couche < GLOM))
	    				{
	    				for (step = odors[o].from; step < odors[o].too; step++)
					  	{ 
						  value2[units[unit].couche] += units[unit].output[step];
						}
					value2[units[unit].couche] /= (odors[o].too - odors[o].from);
					if (value2[units[unit].couche] > max)
					  max = value2[units[unit].couche];

	  				}
				if ((units[unit].type == receptor) && (units[unit].couche < GLOM))
					{
					for (step = odors[o].from; step < odors[o].too; step++)
					  	value1[units[unit].couche] += units[unit].output[step];   
	    				value1[units[unit].couche] /= (odors[o].too - odors[o].from);
				    
	 				}
			
				}
			for (i = 0; i < GLOM; i++)
			  {
			    value3[i] = odors[o].outputs[i];
			    value2[i] /= max;
			    value4[i] = value3[i] - value2[i];
			  }
				BOX (x1, y1, x1+5*GLOM, y1-50);  
				for (g = 0, x = x1; g < GLOM; g++, x+= 5)
					{
					
					FILLED_BOX (x, y1, x+4, (int) (y1 - 50*value1[g])); 
                			
					}
			       
				BOX (x1, y1, x1+5*GLOM, y1-50);
				BOX (x1, y2, x1+5*GLOM, y2-50);
				BOX (x1, y3, x1+5*GLOM, y3-50);
				BOX (x1, y4, x1+5*GLOM, y4-50);
				for (g = 0, x = x1; g < GLOM; g++, x+= 5)
				     {
				       FILLED_BOX (x, y1, x+4, (int) (y1-50*value1[g]));
				     if (value2[g] >= 0.0)
					FILLED_BOX (x, y2, x+4, (int) (y2 - 50*value2[g])); 
					else
					FILLED_BOX (x, (int) (y2-50*value2[g]), x+4, y2);
				     FILLED_BOX (x, y3, x+4, (int) (y3-50*value3[g]));
				     if (value4[g] >= 0.0)
				       FILLED_BOX (x, y4, x+4, (int) (y4-50*value4[g]));
				     else
				       FILLED_BOX (x, (int) (y4-50*value4[g]), x+4, y4);
				     }

			}		
					
			
	TEXT ("for quit click right ", 10, 10);
	maus.flag = expose;
	while (maus.flag != mouse)
		maus = GET_EVENT ();
	if (maus.button == RIGHT)
		break;
	}
	/*DESTROY_WINDOW (new_window);*/
}
			      

void DRAW_LASTS (type)
enum TYPES type;
{                
extern void DRAW_MOL ();
int o, x1, y1;
EVENT maus;
x1 = 20; y1 = 60;    
        
	maus.flag = expose;
	if (new_window == NULL)
		new_window = OPEN_WINDOW (0, 0, 600, 200, blanc);
	CHOOSE_WINDOW (new_window);
	CLEAR (); 
	for (;;)
		{
		for (o = 0; o < NODS; o++, x1 += 5*GLOM + 30)
			{
			DRAW_ONE_STEP (odors[o].too-10, x1, y1, type);
			DRAW_MOL (x1, y1+20, o);     
			}
		while (maus.flag != mouse)
			maus = GET_EVENT ();
		if ((maus.flag == mouse) && (maus.button == RIGHT))
			break;
		}
/*	DESTROY_WINDOW (new_window);*/
}
				


void DRAW_MORE (from, last, type)
int from, last;                 
enum TYPES type;
{         
int x1, y1, i;
 	x1 = 20; y1 = 60;
 	for (i = from; i < from+5; i++, x1 += 5*GLOM + 10)
		DRAW_ONE_STEP (i, x1, y1, type);
 	y1 += 60; x1 = 20;
 	for (i = i; i < from + 9; i++, x1 += 5*GLOM+10)
      		DRAW_ONE_STEP (i, x1, y1, type);
 	y1 += 60; x1 = 20;
 	for (i = i; i < from + 13; i++, x1 += 5*GLOM+10)
   		DRAW_ONE_STEP (i, x1, y1, type);
 	DRAW_ONE_STEP (last, x1, y1, type);
}

void DRAW_MOL (x, y, odor)
int x, y, odor;
{
         
int m;                                              
	for (m = 0; m < MOL; m++)
		{ 
		if (odors[odor].values[m] != 0.0)
			FILLED_CIRCLE (x, y, 8);
		else 
			CIRCLE (x, y, 8);
		x += 8;
		}
}


void DRAW_ODOR (odor, type1)
int odor;                 
enum TYPES type1;
{
int from, last;
EVENT maus ;
	if (new_window == NULL)
		new_window = OPEN_WINDOW (0, 0, 600, 300, blanc);
	CHOOSE_WINDOW (new_window);  
	CLEAR ();
	for (;;)
		{
		DRAW_MORE (odors[odor].from+2, odors[odor].too, type1);
		DRAW_MOL (50, 220, odor);
		TEXT ("click right for quit", 10, 10);
	maus.flag = expose;

		while (maus.flag != mouse)
			maus = GET_EVENT ();
		if (maus.button == RIGHT)
			break;
		}
	/*DESTROY_WINDOW (new_window);*/
}
	













