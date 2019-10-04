#include "cell.init"
                                                          
/** this file contains personal organization and menue routines **/
/** new routines for menue choices may be included **/


#if 1
void CHANGE_FUNCTIONS ()
{
int t, f1, f2, f3, unit;
enum TYPES type;
  	printf (" change functions of 0. recs 1. inhib 2. excit 3. proj 4. vum .. \n");
loop:
  	scanf ("%d", &t);
  	if (t > 4)
      		{
      		printf (" wrong choice, try again \n");
      		goto loop;
      		}
	if (t == 0) type = receptor;
	if (t == 1) type = inhib;
	if (t == 2) type = excit;
	if (t == 3) type = proj;
	if (t == 4) type = vum;
  	printf (" input : 1. get_mols 2. sum 3. sat 4. mixed\n");
  	printf (" state : 1. lin      2. decay \n");
  	printf (" out   : 1. lin      2. sat 3. sig 4. spike \n"); 
  	printf (" new input .. state .. output .. \n");
  	scanf ("%d %d %d", &f1, &f2, &f3);
  	for (unit = 0; unit < N_UNITS; unit++)
      	if (units[unit].type == type)
      	  	{
      	  	if (f1 == 1) units[unit].input_function = GET_MOLECULES;
      	  	if (f1 == 2) units[unit].input_function = SUM_INPUTS;
      	  	if (f1 == 3) units[unit].input_function = SAT_INPUTS;
      	  	if (f1 == 4) units[unit].input_function = GUST_INPUT;
      	  	if (f2 == 1) units[unit].state_function = LINEAR;
      	  	if (f2 == 2) units[unit].state_function = DECAY;
      	  	if (f3 == 1) units[unit].output_function = LINEAR;
      	  	if (f3 == 2) units[unit].output_function = SAT;
      	  	if (f3 == 3) units[unit].output_function = FALSE_SIG;
      	  	if (f3 == 4) units[unit].output_function = FALSE_SPIKE;
      		}
}


void CHANGE_NEURONS (type1)
enum TYPES 	type1;                
{
FILE 	*read_from;   
char 	reset[10], first[10];
int 	unit, test, loc;  
NEURON	uni;                                    
float	par1, par2, par3, par, par0;
	if (type1 == vum)
		{
		printf (" 1. local 2. global \n");
		scanf ("%d", &loc);
		}
	for (unit = 0; unit < N_UNITS; unit++)
	     if (	((units[unit].type == type1) && (type1 != vum)) || 
			((type1 == vum) && (loc == 1) && (units[unit].type == vum) && (units[unit].couche != 100)) || 
			((type1 == vum) && (loc == 2) && (units[unit].type == vum) && (units[unit].couche == 100)))

		   break;                    
	uni = units[unit];
	printf (" old in-par1 %5.3f inpar2 %5.3f old state-para %5.3f old output-para1 %5.3f old output-para2 %5.3f\n", 
	         uni.inpar1, uni.inpar2, uni.stpar1, uni.outpar1, uni.outpar2);
	printf (" new in-par1 .. in-par2 .. state-par... output-par1... output-par2...\n");
	scanf ("%f %f %f %f %f", &par, &par0, &par1, &par2, &par3);
	for (unit = 0; unit < N_UNITS; unit++)
	     if (	((units[unit].type == type1) && (type1 != vum)) || 
			((type1 == vum) && (loc == 1) && (units[unit].type == vum) && (units[unit].couche != 100)) || 
			((type1 == vum) && (loc == 2) && (units[unit].type == vum) && (units[unit].couche == 100)))

	        {     
		units[unit].inpar1 = par;  
		units[unit].inpar2 = par0;
		units[unit].stpar1 = par1;
		units[unit].outpar1 = par2;
	        units[unit].outpar2 = par3;
		} 


}   


void SET_ALL_HEBBS ()
{
FILE *read_hebbs;
enum BOOLEAN iv, pv, vi, vp;
float riv, rpv, rvi, rvp;
float wiv, wvi, wpv, wvp;
float tiv, tvi, tpv, tvp;
LINK *link;
int unit;
char dumi[50];
	if ((read_hebbs = fopen ("hebb.dat", "r")) == NULL)
		printf (" noo file hebb.dat \n");
	if (fscanf (read_hebbs, "%s %s %d %f %f %f %s %d %f %f %f %s %d %f %f %f %s %d %f %f %f", 
				dumi, dumi, &iv, &riv, &wiv, &tiv, dumi, &pv, &rpv, &wpv, &tpv, dumi, &vi, &rvi, &wvi, &tvi, dumi, &vp, &rvp, &wvp, &tvp) != 21) 
		printf (" error in reading file hebb.dat \n");
	
			
	for (unit = 0; unit < N_UNITS; unit++)
		{
		if (units[unit].type == vum)
			{
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == inhib)
					{
					link->hebb = iv;
					link->learning_rate = riv;
					link->max_weight = wiv;
					link->learning_thresh = tiv;
					}
				if ((units[link->from_unit].type == proj) || (units[link->from_unit].type == excit))
					{
					link->hebb = pv;
					link->learning_rate = rpv;
					link->max_weight = wpv;
					link->learning_thresh = tpv;
					}
				link = link->next;
				}
			}
		if (units[unit].type == inhib)
			{
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == vum)
					{
					link->hebb = vi; 
					link->learning_rate = rvi; 
					link->max_weight = wvi;
					link->learning_thresh = tvi;
					}
				link = link->next;
				}
			}
		if (units[unit].type == proj)
			{
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == vum)
					{
					link->hebb = vp;
					link->learning_rate = rvp;
					link->max_weight = wvp;
					link->learning_thresh = tvp;
					}
				link = link->next;
				}
			}
		}
}

void RESET_HEBBS ()
{
int unit; 
LINK *link;

	for (unit = 0; unit < N_UNITS; unit++)
		{
		link = units[unit].links_to_unit;
		while (link)
			{
			if (link->hebb == VRAI)
				link->hebb = FAUX;
			link = link->next;
			}
		}
}




void CHANGE_CONNECTIONS ()

{
int		unit, test, couche_too, couche_from, delay, helpi;                                          
float		w, random, help, psi, center , pg_help;                 
LINK		*link; 
enum BOOLEAN 	flag, flag1, decay, incr;     
enum TYPES 	from_type, too_type;
enum LINK_TYPES  link_type;    
LATS 		*lats;      
int		 G0, g, gg, ll;
	flag1 = VRAI;
loop:
	printf (" AFFERENT 10. to inhib 11. to excit \n LOCAL 20. inhib-excit 21. excit-inhib 22. inhib-proj 23. excit-proj\n LATERAL 30. inhib-excit 31. inhib-inhib 32. inhib-proj \n VUM 40 i-v 41 e-v 42 p-v 43 v-i 44 p-e 45 v-p\n");
	scanf ("%d", &test); 
	if ((test != 22) && ( test != 10) && (test != 11) && (test != 20) && (test != 21) && (test != 30) && (test != 31) && (test != 23) && (test != 34) && (test != 40) && (test != 41) && (test != 42) && (test != 43))
		{printf (" wrong choice, try again\n"); goto loop;}               
	if (test == 10)
		{link_type = aff; from_type = receptor; too_type = inhib;}
	if (test == 11)
		{link_type = aff; from_type = receptor; too_type = excit;}
	if (test == 20)
		{link_type = local; from_type = inhib; too_type = excit; }
	if (test == 21)
		{link_type = local; from_type = excit; too_type = inhib; }
	if (test == 22)
		{link_type = local; from_type = inhib; too_type = proj;}
	if (test == 23)
		{link_type = local; from_type = excit; too_type = proj;}
	if (test == 31)
		{link_type = lateral; from_type = inhib; too_type = inhib;  flag1 = FAUX;}
	if (test == 30)
		{link_type = lateral; from_type = inhib; too_type = excit; flag1 = FAUX;}
	if (test == 32) 
		{link_type = local; from_type = inhib; too_type = proj;}
	if (test == 40)
		{link_type = local; from_type = inhib; too_type = vum;}
	if (test == 41)
		{link_type = local; from_type = excit; too_type = vum;}
	if (test == 42)
		{link_type = local; from_type = proj; too_type = vum;}
	if (test == 43)
		{link_type = local; from_type = vum; too_type = inhib;}
	if (test == 44) 
		{link->type = local; from_type = vum; too_type = excit;}
	if (test == 45)
		{link_type = local; from_type = vum; too_type = proj;}

	
	if (flag1 == VRAI)
		{
		flag = VRAI;
		for (unit = 0; (unit < N_UNITS) && (flag == VRAI); unit++)
			if (units[unit].type == too_type)
				{
				link = units[unit].links_to_unit;
				while (link)
					{
					if ((units[link->from_unit].type == from_type) && (link->type == link_type))
						{
						w = link->weight;
						delay = link->delay;
						flag = FAUX;
						break;
						}
					link = link->next;
					}
				}
		if (flag == FAUX)
			printf (" old weight %5.3f delay %d \n", w, delay);
		else
			printf (" no weight found \n");	
			
		printf ("new weight... delay .. \n");
		scanf ("%f %d", &w, &delay);random = 10.0;
		for (unit = 0; unit < N_UNITS; unit++)
	    		{
	    		link = units[unit].links_to_unit;
	    		while (link != NULL)
		  		{
		  		if ((units[link->from_unit].type == from_type) && (link->type == link_type))
		      			if ((units[unit].type == too_type) || (too_type == all))
			 			{   
			 			if (random != 0.0)       
			      				help = w/random;
		         			else 	
			      				help = 0.0;
			  			help = RANF () * (2*help) + (w - help);
			  			link->weight = help;
			  			link->delay = delay;
		      	  			free (link->signal);
		      	  			link->signal = (float *) calloc (link->delay, sizeof (float));
			 			}
		   		link = link->next;
	           		} /** while .. **/
	     		} /** for .. **/
		}
    	else 
		{
		flag = VRAI;
		for (unit = 0; (unit < N_UNITS) && (flag == VRAI); unit++)
			if (units[unit].type == too_type)
				{
				link = units[unit].links_to_unit;
				while (link)
					{
					if ((units[link->from_unit].type == from_type ) && (link->type == link_type))
						{
						w = link->weight;
						delay = link->delay;
						flag = FAUX;
						break;
						}
					link = link->next;
					}
				}
		if (flag == FAUX)
			printf (" old weight %5.3f delay %d \n", w, delay);
		else
			printf (" no weight found \n");
		
		printf (" new weight .. delay .. distance .. decay .. incr .. ? (0,1)\n");
		scanf ("%f %d %f %d %d", &center, &delay, &psi, &decay, &incr);random = 10.0;
/** make lateral gaussian weight distribution **/
	  	lats = MAKE_LATS (center, decay, delay, incr, psi, GLOM);
		for (unit = 0; unit < N_UNITS; unit++)
			{
			link = units[unit].links_to_unit;
			while (link != NULL)
				{
				if ((units[link->from_unit].type == from_type) && (link->type == link_type))
					if ((units[unit].type == too_type) || (too_type == all))
						{   
						w = lats[units[link->from_unit].couche].weight[units[unit].couche];
						/*  w = center;*/
						if (random != 0.0)
							help = w/random;
						else 
							help = 0.0;
						help = RANF () * (2*help) + (w - help);
						link->weight = help;
						
      	      	      	      			helpi = lats[units[link->from_unit].couche].delay[units[unit].couche];
						 link->delay = helpi;
      	      	      	      			free (link->signal);
      	      	      	      			link->signal = (float *) calloc (link->delay, sizeof (float));
						}
				link = link->next;
				} /** while .. **/
	              	  } /** for .. **/

  		
		for (unit = 0; unit < GLOM; unit ++)
  			{
    			free (lats[unit].weight);
    			free (lats[unit].delay);
	      		}
		free (lats);
		}

}

void SET_HEBBS ()
{
int t, f, unit;
enum TYPES from_type, too_type;
float nuu, max;
LINK *link;
	printf (" from 1. inhib 2. proj 3. vum too 1. inhib 2. proj 3. vum \n learning rate .. max_weight .. \n");
	scanf ("%d %d %f %f", &f, &t, &nuu, &max);
	if (f == 1) from_type = inhib;
	if (f == 2) from_type = proj;
	if (f == 3) from_type = vum;
	if (t == 1) too_type = inhib;
	if (t == 2) too_type = proj;
	if (t == 3) too_type = vum;
	for (unit = 0; unit < N_UNITS; unit++)
		if (units[unit].type == too_type)
			{
			link = units[unit].links_to_unit;
			while (link)
				{
				if (units[link->from_unit].type == from_type)
					{
					link->hebb = VRAI;
					link->learning_rate = nuu;
					link->max_weight = max;
					}
				link = link->next;
				}
			}
}

#endif

void DO_CROSS ()
{
int index, index1, index2;
int cor, unit;    
EVENT maus; 

loop:
	printf ("0. p_pot-p_out 1. p_pot-p 2. p_out-p 3. p_pot-inhib \n 4. p-inhib 5. p-p 6. pote-e 7. autopn 8. autin\n");
	scanf ("%d", &cor);
	if (cor == 7)
		CROSS (p_pot, p_pot, N_STEPS, fft_i1, fft_i2);
	if (cor == 8)
		CROSS (i_pot, i_pot, N_STEPS, fft_i1, fft_i2);
	if (cor == 0)
		CROSS (p_pot, p_out, N_STEPS, fft_i1, fft_i2);
	if (cor == 1)
		{
		printf ("proj index .. \n");
		scanf ("%d", &index);
		for (unit = 0; unit < N_UNITS; unit++)
			if ((units[unit].couche == index) && (units[unit].type == excit))
				index = unit;
		   CROSS (units[index].state, p_pot, N_STEPS, fft_i1, fft_i2); 
		}
	if (cor == 2)
		{
		printf ("proj index .. \n");
		scanf ("%d", &index);
		for (unit = 0; unit < N_UNITS; unit++)
			if ((units[unit].couche == index) && (units[unit].type == excit))
				index = unit;
		CROSS (units[index].output, p_pot, N_STEPS, fft_i1, fft_i2); 
		}
	if (cor == 3)
		{
		CROSS (i_pot, p_pot, N_STEPS, fft_i1, fft_i2);
		}
	if (cor == 4)
		{
		printf ("pn index .. \n");
		scanf ("%d", &index);
		for (unit = 0; unit < N_UNITS; unit++)
			if ((units[unit].couche == index) && (units[unit].type == inhib))
				index = unit;
		CROSS (units[index].output, i_pot, N_STEPS, fft_i1, fft_i2); 
		}
	if (cor == 5)
		{
		printf ("excit index .. index .. \n");
		scanf ("%d %d", &index1, &index2);
		for (unit = 0; unit < N_UNITS; unit++)
			{
			if ((units[unit].couche == index1) && (units[unit].type == excit))
				index1 = unit;
			if ((units[unit].couche == index2) && (units[unit].type == excit))
				index2 = unit;
			}

		CROSS (units[index1].output, units[index2].output, N_STEPS, fft_i1, fft_i2); 
		}
	if (cor == 6)
		{
		printf ("proj index1 .. index2 .. \n");
		scanf ("%d %d", &index1, &index2);
		for (unit = 0; unit < N_UNITS; unit++)
			{
			if ((units[unit].couche == index1) && (units[unit].type == excit))
				index1 = unit;
			if ((units[unit].couche == index2) && (units[unit].type == excit))
				index2 = unit;
			}
		CROSS (units[index1].state, units[index2].state, N_STEPS, fft_i1, fft_i2); 
		}
	maus.button = SHOW_CROSS ();
	if (maus.button == MIDDLE)
		goto loop;

}		                       
                 
				
void MENU ()
{
int	      step_number, x_ext, y_ext, x_mul, y_mul, y_mul2, end, delta;  
FILE	      *read_from; 
char 	      dummy[10], to[50];
int 	      h, test, testi, testo, tot, o;  
enum BOOLEAN  flag, glob, cc;                                       
int	      points, count, t1, t2;  
int	      yc, yp, ys, crossx, cor, index, unit, index1, index2;
 float *inter;
int toto;
EVENT maus;
	cc = FAUX;
	N_UNITS = 0; 	   
	GET_RUN_PARAMETERS ("para.dat");
printf ("after para THRESH %f THRESH2 %f \n", THRESH, THRESH2);
        INIT_GRAPHICS ();
	main_window = OPEN_WINDOW (0, 0, WIDTH, HEIGHT, blanc);  
      	maus = GET_EVENT (); 
	count = 0;
/***/first_loop:/***/
	GET_RUN_PARAMETERS ("para.dat");
	printf (" 1. set up new 2. load config 3. exit\n");
	scanf ("%d", &test);   
	if ((test != 1) && (test != 2) && (test != 3) && (test != 4))
		{
		printf (" wrong choice, try again\n");
		goto first_loop;
		}
      	if (test == 3)    
		{
		DESTROY_WINDOW (main_window);
		return;        
		}
	if (test == 2)
		{ 
		READ_CONFIG (); 
		MAKE_REC_SENS ();
	goto last_loop;
		} /** if (test == 2 **/
	if (test == 1)
		{

/***/set_up_loop:/***/   
		GET_RUN_PARAMETERS ("para.dat");
		SET_UP ();	
		SHOW_UNITS ();getchar ();
		getchar ();
		
		goto last_loop;
        	} /** if (test == 1 **/

/***/get_odors_loop:/***/ 
	GET_RUN_PARAMETERS ("para.dat");
	NULL_ODORS ();
	GET_ODORS ();
	/*SCHOCK ();*/

/***/run_loop:/***/  

	printf (" in run loop \n");
	/*	GET_PLASTICITY ("plasticity.dat");*/
	RUN ();
	/*COUNTSPIKES ();*/
	printf (" spikes %d \n", COUNT1);
/***/draw_loop:/***/

	SHOW ();  

/***/last_loop:/***/

	printf ("100. interspike interval 1. draw again 11. draw_map 12. draw_lasts 14. draw weights 15. vp weights 16 pi weights \n20. aldehydes 2. new input 21. same input 22. gust input 23. read input 24. save input 3. change par 31. set hebbs 32. reset hebbs 4. set up new 5.save config 6. save outputs 7. save weights 8. read weights 13. exit\n"); 

	scanf ("%d", &test);
	if ((test != 100) && (test != 20) && (test != 11) && (test != 14) && (test != 15) && (test != 12) && (test != 1) && (test != 21) && (test != 2) && (test != 3) && (test != 4) && (test != 5) && (test != 13) && (test != 22) && (test != 23) && (test != 24) && (test != 14) && (test != 31) && (test != 32) && (test != 15) && (test != 16) && (test != 6) && (test != 7) && (test != 8))
		{
		printf (" wrong choice, try again\n");
		goto last_loop;
		}         



	if (test == 6) 
		{
		SAVE_DATA (); 	

		goto last_loop;
		}
	if (test == 7) 
		{
		SAVE_WEIGHTS (); 
		goto last_loop;
		}
	if (test == 8) 
		{
		READ_WEIGHTS ();
		goto last_loop;
		}
	if (test == 14)
		{
       		CHOOSE_WINDOW (weight_window);
		SHOW_WEIGHTS ();getchar ();
		goto last_loop;
		}
	if (test == 15)
		{
		SHOW_PV (1, 10);
		goto last_loop;
		}
	if (test == 16)
		{
		SHOW_VI (1, 10);
		goto last_loop;
		}
	if (test == 31)
		{
		SET_ALL_HEBBS ();
		goto last_loop;
		}
	if (test == 32)
		{
		RESET_HEBBS ();
		goto last_loop;
		}
	if (test == 13)  
		{                         
		FREE_ALL ();
		goto first_loop;
		}   /** test == 13 **/          

	if (test == 2)                
		goto get_odors_loop;     

	if (test == 20)
		{
		NULL_ODORS ();
		ALDEHYDES ();
		goto run_loop;
		}
	if (test == 22)
		{
		GET_GUST ();
		goto last_loop;
		}
	if (test == 23)
		{
		READ_ODORS ();
		goto run_loop;
		}
	if (test == 24)
		{
		SAVE_ODORS ();
		goto last_loop;
		}
	if (test == 21)
		goto run_loop;           

	if (test == 100)
		{ 
		  printf (" max interval .. \n");
		  scanf ("%d", &points);

		  DRAW_INTER (points);
	       
		  
       		cc = VRAI;
		goto last_loop;
		} /** endif test == 100 **/

	if (test == 3)                         
		{  
		flag = FAUX;
		while (flag == FAUX)
			{          
			loopp:	
			printf (" change 1. receptor 2. inhibs 3. excits 4. projs 5. vum 6. connections 7. functions\n");
			scanf ("%d", &testi);   
			if (testi > 7)
				{
				printf ("wrong choice, try again \n");
				goto loopp;
				}
			if (testi == 2)
				{
				CHANGE_NEURONS (inhib);  
				}
			if (testi == 3)  
				{
				CHANGE_NEURONS (excit);   
				}
			if (testi == 4)
				CHANGE_NEURONS (proj);
			if (testi == 5)
				CHANGE_NEURONS (vum);
			if (testi == 7)
				CHANGE_FUNCTIONS ();
			if (testi == 6) 
				CHANGE_CONNECTIONS ();
			if (testi == 1)
				CHANGE_NEURONS (receptor);	

loopu:
			printf (" 1. change others 2. run\n");
			scanf ("%d", &end);
			if ((end != 1) && (end != 2))
				{
				printf (" wrong choice, try again \n");
				goto loopu;
				}	
			if (end == 2)
				flag = VRAI;
			}	/** while (flag == false **/		
		goto run_loop;
		} /** endif (test == 3 **/

	if (test == 4)
		{
		FREE_ALL ();
		goto set_up_loop; 
		}

	if (test == 5)
		{                     
		SAVE_CONFIG ();  
/*		  SAVE_OUT ();*/
		goto last_loop;
		}   

	if (test == 1)
		{     
		goto draw_loop;
		} 

	if (test == 11)
		{
loopuu:
		printf (" odor .. type .. (0. rec 1. inhib 2. excit 3. proj 4. vum)\n");
		scanf ("%d %d", &o, &t1);
		if (o >= NODS)
			{
			printf (" wrong, try again \n");
			goto loopuu;
			}
		DRAW_ODOR (o, t1+1);  
		goto last_loop;
		}   

	if (test == 12)
		{                 

		DRAW_MEANS ();
		goto last_loop;
		}
   
}

int DISTANCE (o1, o2)
int o1, o2; 
{
int dist, dist1; 
 int d;
	dist = abs (o1-o2); 
	if (dist > (MOL-1)/2)
		{
		  for (d=1; d <= (int) (MOL-1)/2; d++)
		    if (dist == MOL-d)
			dist1 = d; 
	
		}
	else
		dist1 = dist;

	return (dist1); 
} 
		 
				
void SAVE ()
{

FILE 		*saveto, *saveto2, *saveto3;
float *vumm;
int	od, o1, o2, step;
float *value, *dev;
int *nn;
int dist,c; 
char name1[50], name2[50], name3[50];
 float con;
 int unit; 
 LINK *link;
/** SET UP A NETWORK ***/
	N_UNITS = 0; 	   
	GET_RUN_PARAMETERS ("para.dat");
	GET_PLASTICITY ("plasticity.dat");
       	SET_UP ();

/***********************/


vumm = (float *) calloc (MOL, sizeof (float));
value = (float *) calloc (MOL, sizeof (float)); 
dev = (float *) calloc (MOL, sizeof (float));
 nn = (int *) calloc (MOL, sizeof (int));

/** DO A LOOP FOR CONCENTRATION **/
       for (con = 0.25; con < 1.0; con += 0.25)
	   {
	     printf (" at con %f \n", con);
/** PREPARE **/
c=(int)(con*100);
	    sprintf(name1, "vum_theta8e_c%d", c);
	    sprintf(name2, "av_theta8e_c%d", c);
	    sprintf(name3, "weights_theta8e_c%d", c);
	    saveto = fopen (name1, "w");
	    saveto2 = fopen (name2, "w");
	    saveto3 = fopen (name3,"w"); 
	    for (o1 = 0; o1 < MOL; o1++)
		{nn[o1] = 0; value[o1] = dev[o1] = 0.0; }


/** LEARN ONE AND TEST ALL ***/
	for (o1 = 0; o1 < 15; o1++)
	    	{
		  printf (" learn %d \n", o1);
		/*NULL_ALL ();*/
		RESET_VUM (); /** SET ALL WEIGHTS TO VUM TO ZERO **/
		LEARN = VRAI;    /** TURN ON LEARNING **/
		NULL_ODORS (); /** RESET ODORS **/
/** MAKE o1 ACTIVE **/
		for (step = 0; step < N_STEPS; step++)
			molecules[o1].stim[step] = con*1.0;

/** RUN NETWORK AND LEARN VUM WEIGHTS **/ 
		RUN (); 

		for (o2=0;o2<MOL;o2++)
		     vumm[o2] = 0.0;
/** NOW TEST VUM RESPONSE TO ALL ODORS **/
		for (o2 = 0; o2 < MOL; o2++)
			{
 printf (" test %d \n", o2);

			 NULL_ALL ();
			NULL_ODORS (); 
			LEARN = FAUX; 
			for (step = 0; step < N_STEPS; step++)
				molecules[o2].stim[step] = con*1.0; 
			RUN (); 
			vumm[o2] = VUM (); /** AVERAGE VUM POTENTIAL DURING ODOR **/
			dist = DISTANCE (o1, o2); /** DISTANCE BETWEEN TRAIN-TEST **/
				value[dist] += vumm[o2]; 
			dev[dist] += vumm[o2]*vumm[o2];
			nn[dist] += 1;  
				}
/** SAVE RESPONSE **/
		fprintf (saveto3, "o1 %d \n", o1); 
		for (unit = 0; unit < N_UNITS; unit++)
			if ((units[unit].type == vum ) && (units[unit].couche == 100))
				{
				link = units[unit].links_to_unit; 	
				while (link) 
					{
       					fprintf (saveto3, "%f ", link->weight); 
					link = link->next; 
					}
				fprintf (saveto3, "\n"); 
				}
	

		fprintf (saveto, "o1 %d\n", o1);
		for (o2 = 0; o2 < MOL; o2++)
			fprintf (saveto, "%f ", vumm[o2]); 
		fprintf (saveto, "\n"); 
		}
     
		fclose (saveto);
		fclose (saveto3);	
       		for (o1 = 0; o1 <= (int)((MOL-1)/2); o1++)
			{
		if (nn[o1] != 0) value[o1] /= nn[o1];
			if (nn[o1] != 0) dev[o1] /= nn[o1];
			dev[o1] = sqrt (fabs (dev[o1] - value[o1]*value[o1]));
			fprintf (saveto2, "dist %d n %d value %f dev %f \n", o1, nn[o1], value[o1], dev[o1]); 
			}
		printf (" before close \n");
		fclose (saveto2);
		}

}

				
void SAVE4 ()
{

  FILE 		*c11, *c12, *c13, *c21, *c22, *c23, *c31, *c32, *c33;
  float vumm;
int	od, o1, o2, step;
float *value, *dev;
int *nn;
int dist,c1, c2; 
char name1[50], name2[50], name3[50];
 float con1, con2;
 int unit; 
 LINK *link;
/** SET UP A NETWORK ***/
	N_UNITS = 0; 	   
	GET_RUN_PARAMETERS ("para.dat");
	GET_PLASTICITY ("plasticity.dat");
       	SET_UP ();

/***********************/
	c11 = fopen ("c11_theta8e", "w");
	c12 = fopen ("c12_theta8e", "w");
	c13 = fopen ("c13_theta8e", "w");	
	c21 = fopen ("c21_theta8e", "w");	
	/*	c22 = fopen ("c22_theta8e", "w");	
	c23 = fopen ("c23_theta8e", "w");	
	c31 = fopen ("c31_theta8e", "w");
	c32 = fopen ("c32_theta8e", "w");	
	c33 = fopen ("c33_theta8e", "w");
	*/
	for (o1 = 0; o1 < 15; o1++)
	    	{
		  for (con1 = 0.15; con1 < 1.0; con1+=0.6)
		    {
		      printf (" learn %d con1 %f\n", o1, con1);
		      /*NULL_ALL ();*/
		      RESET_VUM (); /** SET ALL WEIGHTS TO VUM TO ZERO **/
		      LEARN = VRAI;    /** TURN ON LEARNING **/
		      NULL_ODORS (); /** RESET ODORS **/
/** MAKE o1 ACTIVE **/
		      for (step = 0; step < N_STEPS; step++)
			molecules[o1].stim[step] = con1*1.0;

/** RUN NETWORK AND LEARN VUM WEIGHTS **/ 
		      RUN (); 

		      
		   
/** NOW TEST VUM RESPONSE TO ALL ODORS **/
		     for (con2 = 0.15; con2 < 1.0; con2+=0.6)
		       {
			 printf ("con1 %f con2 %f \n", con1, con2);
		        NULL_ALL ();
			NULL_ODORS (); 
			LEARN = FAUX; 
			for (step = 0; step < N_STEPS; step++)
				molecules[o1].stim[step] = con2*1.0; 
			RUN (); 
			vumm = VUM (); /** AVERAGE VUM POTENTIAL DURING ODOR **/
			printf ("con1 %f con2 %f \n", con1, con2);
		    	if ((fabs (con1-0.15) < 0.01) && (fabs (con2-0.15)< 0.01))
			  {
			    printf("writing to c11 \n");
			  fprintf (c11, "o %d con1 %f con2 %f vum %f \n", o1, con1, con2, vumm);
			  }
		       
			if ((abs (con1-0.15)<0.01) && (abs(con2-0.75) < 0.01)) 
			  {
			    printf ("writing to c12\n");
			  fprintf (c12, "o %d con1 %f con2 %f vum %f \n", o1, con1, con2, vumm);
			  }

			if ((abs (con1-0.75) < 0.01) && (abs (con2-0.15)<0.01))
			  {printf ("writing to c13\n");
			  fprintf (c13, "o %d con1 %f con2 %f vum %f \n", o1, con1, con2, vumm);}
			if ((abs (con1-0.75) < 0.01) && (abs (con2-0.75) < 0.01)) 
			  {printf ("writing to c21\n");
			  fprintf (c21, "o %d con1 %f con2 %f vum %f \n", o1, con1, con2, vumm);}
			/*	if ((con1 == 0.5) && (con2 == 0.5))
			    fprintf (c22, "o %d con1 %f con2 %f vum %f \n", o1, con1, con2, vumm);
			if ((con1 == 0.5) && (con2 == 0.75))
			    fprintf (c23, "o %d con1 %f con2 %f vum %f \n", o1, con1, con2, vumm);
			if ((con1 == 0.75) && (con2 == 0.25))
			    fprintf (c31, "o %d con1 %f con2 %f vum %f \n", o1, con1, con2, vumm);
			if ((con1 == 0.75) && (con2 == 0.5))
			    fprintf (c32, "o %d con1 %f con2 %f vum %f \n", o1, con1, con2, vumm);
			if ((con1 == 0.75) && (con2 == 0.75))
			fprintf (c33, "o %d con1 %f con2 %f vum %f \n", o1, con1, con2, vumm);*/
		       }
		    }
		}
	fclose (c11); fclose (c21); fclose (c31);
	fclose (c12); /*fclose (c22); fclose (c32);
			fclose (c13); fclose (c23); fclose (c33);*/
}

				
void SAVE2 ()
{
FILE 		*saveto, *saveto2, *saveto3;
float *vumm;
int	od, o1, o2, step;
float nspikes, devnspikes;
 float help, sync, devsync;
int *nn;
int dist,c; 
char name1[50], name2[50], name3[50];
 float con;
 int unit; 
 LINK *link;
/** SET UP A NETWORK ***/
	N_UNITS = 0; 	   
	GET_RUN_PARAMETERS ("para.dat");
       	SET_UP ();

/***********************/


	saveto = fopen ("spikes_theta6", "w");
	LEARN = FAUX;
/** DO A LOOP FOR CONCENTRATION **/
       for (con = 0.25; con < 1.0; con += 0.25)
	   {
	
     printf (" at con %f \n", con);
/** PREPARE **/
	    nspikes = devnspikes = sync = devsync = 0.0;



	for (o1 = 0; o1 < MOL; o1++)
	    	{
		  printf (" learn %d \n", o1);
		/*NULL_ALL ();*/
		NULL_ODORS (); /** RESET ODORS **/
/** MAKE o1 ACTIVE **/
		for (step = 0; step < N_STEPS; step++)
			molecules[o1].stim[step] = con*1.0;

/** RUN NETWORK AND LEARN VUM WEIGHTS **/ 
		RUN (); 
		help = COUNTSPIKES (); nspikes += help; devnspikes += help*help;

		help = SYNC_COUNT (0, N_STEPS); sync += help; devsync += help*help;

		}
		nspikes /= MOL; sync /= MOL;
		devnspikes /= MOL; devsync /= MOL;
		devnspikes = sqrt (fabs (devnspikes - nspikes*nspikes));
		devsync = sqrt (fabs (devsync - sync*sync));
		    
		fprintf (saveto, "conc %f nspikes %f dev %f sync %f dev %f \n", con, nspikes, devnspikes, sync, devsync);
	}
     
		fclose (saveto);


}

				
void SAVE_DIST ()
{
FILE 		*saveto1, *saveto2, *saveto3;
float *vumm;
int	od, o1, o2, step;
float vum[3], dev[3];
 float sync, devsync;
int *nn;
int dist,c, i, ex; 
char name1[50], name2[50], name3[50];
 float pn1[75], pn2[75], pn3[75];
 float con1, con2, help, normpn1, normpn2;
 int unit, e; 
 LINK *link;
/** SET UP A NETWORK ***/
	N_UNITS = 0; 	   
	GET_RUN_PARAMETERS ("para.dat");
       	GET_PLASTICITY ("plasticity.dat");
	SET_UP ();

/***********************/
	LEARN = FAUX;

	saveto1 = fopen ("dist1c", "w");
	saveto2 = fopen ("dist2c", "w");
	saveto3 = fopen ("dist3c", "w");
#if 0
	con1 = 0.25;

	ex = 0;
	for (o1 = 0; o1 < MOL; o1++)
	  for (o2 = 0; o2 < MOL; o2++)
	    if (abs (o1-o2) == 4)
	      {
		for (i=0; i < 75; i++)
		  {
		    pn1[i] = 0.0;
		    pn2[i] = 0.0;
		  }
		printf ("at c %f o %d %d\n", con1, o1, o2);
		NULL_ODORS ();
		NULL_ALL ();
		for (step = 0; step < N_STEPS; step++)
		  molecules[o1].stim[i] = con1;
		RUN ();
		for (unit = 0, e=0; unit < N_UNITS; unit++)
		  if (units[unit].type == excit)
		    {
		    for (step = 0; step < N_STEPS; step++)
		      pn1[e] += units[unit].output[step];
		    e++;
		    }
		NULL_ODORS ();
		NULL_ALL ();
		for (step = 0; step < N_STEPS; step++)
		  molecules[o2].stim[i] = con1;
		RUN ();
		e = 0;
		for (unit = 0, e=0; unit < N_UNITS; unit++)
		  if (units[unit].type == excit)
		    {
		    for (step = 0; step < N_STEPS; step++)
		      pn2[e] += units[unit].output[step];
		    e++;
		    }
		help = 0.0;normpn1 = 0.0; normpn2 = 0.0;
		for (e = 0; e < 75; e++)
		  {
		    normpn1 += pn1[e]*pn1[e];
		    normpn2 += pn2[e]*pn2[e];
		  }
		normpn1 = sqrt(normpn1);normpn2 = sqrt(normpn2);
		if ((normpn1 != 0.0) && (normpn2 != 0.0))
		  for (e = 0; e < 75; e++)
		      help += (pn1[e]/normpn1-pn2[e]/normpn2)*(pn1[e]/normpn1-pn2[e]/normpn2);

		
		fprintf (saveto1, "con %f o1 %d o2 %d dist %f \n", con1, o1, o2, sqrt(help));
		
	      }
	fclose (saveto1);
	

con1 = 0.75;
	
	for (o1 = 0; o1 < MOL; o1++)
	  for (o2 = 0; o2 < MOL; o2++)
	    if (abs (o1-o2) == 4)
	      {
for (i=0; i < 75; i++)
	  {
	    pn1[i] = 0.0;
	    pn2[i] = 0.0;
	  }
printf (" at c %f o %d %d\n", con1, o1, o2);
		NULL_ODORS ();
		NULL_ALL ();
		for (step = 0; step < N_STEPS; step++)
		  molecules[o1].stim[i] = con1;
		RUN ();
		for (unit = 0, e=0; unit < N_UNITS; unit++)
		  if (units[unit].type == excit)
		    {
		    for (step = 0; step < N_STEPS; step++)
		      pn1[e] += units[unit].output[step];
		    e++;
		    }
		NULL_ODORS ();
		NULL_ALL ();
		for (step = 0; step < N_STEPS; step++)
		  molecules[o2].stim[i] = con1;
		RUN ();
		for (unit = 0, e=0; unit < N_UNITS; unit++)
		  if (units[unit].type == excit)
		    {
		    for (step = 0; step < N_STEPS; step++)
		      pn2[e] += units[unit].output[step];
		    e++;
		    }

		help = 0.0;normpn1 = 0.0; normpn2 = 0.0;
		for (e = 0; e < 75; e++)
		  {
		    normpn1 += pn1[e]*pn1[e];
		    normpn2 += pn2[e]*pn2[e];
		  }
		normpn1 = sqrt(normpn1);normpn2 = sqrt(normpn2);
		if ((normpn1 != 0.0) && (normpn2 != 0.0))
		  for (e = 0; e < 75; e++)
		    help += (pn1[e]/normpn1-pn2[e]/normpn2)*(pn1[e]/normpn1-pn2[e]/normpn2);
		
		fprintf (saveto2, "con %f o1 %d o2 %d dist %f \n", con1, o1, o2, sqrt(help));
	      
	      }
	fclose (saveto2);
	
 #endif
	for (o1 = 0; o1 < MOL; o1++)
	  {
     	for (i=0; i < 75; i++)
	  {
	    pn1[i] = 0.0;
	    pn2[i] = 0.0;
	    pn3[i] = 0.0;
	  }
printf (" at o %d \n", o1);
	    con1 = 0.25; con2 = 0.75;
	    NULL_ODORS ();
		NULL_ALL ();
		for (step = 0; step < N_STEPS; step++)
		  molecules[o1].stim[step] = con1;
		RUN ();
		for (unit = 0, e=0; unit < N_UNITS; unit++)
		  if (units[unit].type == excit)
		    {
		    for (step = 0; step < N_STEPS; step++)
		      pn1[e] += units[unit].output[step];
		    e++;
		    }
	    
		NULL_ALL ();
		NULL_ODORS ();
		for (step = 0; step < N_STEPS; step++)
		  molecules[o1].stim[step] = con1;
		RUN ();
		for (unit = 0, e=0; unit < N_UNITS; unit++)
		  if (units[unit].type == excit)
		    {
		    for (step = 0; step < N_STEPS; step++)
		      pn2[e] += units[unit].output[step];
		    e++;
		    }

		help = 0.0;normpn1 = 0.0; normpn2 = 0.0;
		for (e = 0; e < 75; e++)
		  {
		    normpn1 += pn1[e]*pn1[e];
		    normpn2 += pn2[e]*pn2[e];
		  }
		normpn1 = sqrt(normpn1);normpn2 = sqrt(normpn2);
		if ((normpn1 != 0.0) && (normpn2 != 0.0))
		  for (e = 0; e < 75; e++)
		    help += (pn1[e]/normpn1-pn2[e]/normpn2)*(pn1[e]/normpn1-pn2[e]/normpn2);
		
		  fprintf (saveto2, "con %f con2 %f o %d dist %f \n", con1, con1, o1, sqrt(help));
	     
	    
		NULL_ALL ();
		NULL_ODORS ();
		for (step = 0; step < N_STEPS; step++)
		  molecules[o1].stim[step] = con2;
		RUN ();
		for (unit = 0, e=0; unit < N_UNITS; unit++)
		  if (units[unit].type == excit)
		    {
		    for (step = 0; step < N_STEPS; step++)
		      pn3[e] += units[unit].output[step];
		    e++;
		    }

		help = 0.0;normpn1 = 0.0; normpn2 = 0.0;
		for (e = 0; e < 75; e++)
		  {
		    normpn1 += pn1[e]*pn1[e];
		    normpn2 += pn3[e]*pn3[e];
		  }
		normpn1 = sqrt(normpn1);normpn2 = sqrt(normpn2);
		if ((normpn1 != 0.0) && (normpn2 != 0.0))
		  for (e = 0; e < 75; e++)
		    help += (pn1[e]/normpn1-pn3[e]/normpn2)*(pn1[e]/normpn1-pn3[e]/normpn2);
		
		  fprintf (saveto3, "con %f con2 %f o %d dist %f \n", con1, con2, o1, sqrt(help));
		  
	
  }

	fclose (saveto3);
	fclose (saveto2);
}






void main ()
{                
int test, goon;
printf (" here we go\n");  
        alea = 0.22;
	ialea =  alea * 2147483647;  
loppo:
		printf (" 1. play 2. save \n"); scanf ("%d", &test);
	if (test == 1)	
	MENU (); 
 	if (test == 2)
	  {
	    /* SAVE ();*/
	    SAVE_DIST ();
	  }
/*	 
	printf (" 1. ciao 2. hii \n");
	scanf ("%d", &goon);
	if (goon == 2)
		goto loppo;
	printf (" ciao \n"); 

SAVE();*/
} 



