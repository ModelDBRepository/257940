#include "cell.init"


WIND DRAW (xmul, outmul, potmul, delta, from_unit)
int xmul, outmul, potmul, delta, from_unit;
{
WIND draw_result;
int x0, x1, help, x, y;
int lasty;
char chain[20];
int unit;
	x0 = 10;
  	x1 = 50;
  	help = 50 + 2 * delta;
  	lasty = HEIGHT;
  	unit = from_unit;
  	CLEAR ();
  	RESET_COOR ();
  	while ((help < lasty) && (unit < N_UNITS))
    		{
      		if (ALL == VRAI)
      	  		{
      	  		if (((D_RECS == FAUX ) && (units[unit].type != receptor)) ||
      	      			(D_RECS == VRAI))
      	      			{
      	      			if (units[unit].type == mitral2)
					strcpy (chain, "m");
				if (units[unit].type == granule)
					strcpy (chain, "g");
				if (units[unit].type == receptor)
					strcpy (chain, "r");
				if (units[unit].type == pyr)
					strcpy (chain, "p");
				if (units[unit].type == ET)
					strcpy (chain, "ET");
				if (units[unit].type == PG)
					strcpy (chain, "PG");
				if (units[unit].type == motor)
					strcpy (chain, "mo");

      	      			TEXT (chain, x0, help);
	      			units[unit].x_coor = x0;
	      			units[unit].y_coor = help;
	      			if (units[unit].selected == VRAI)
					CIRCLE (units[unit].x_coor-5, units[unit].y_coor, 2);
      	      			if (D_OUT == VRAI)
      	      	  			{
      	      	  			if (D_SPIKES == VRAI)
      	      	      				SPIKES (x1, help, xmul, outmul, N_STEPS, units[unit].output);
      	      	  			else
      	      	      				CURVE (x1, help, xmul, outmul, N_STEPS, units[unit].output);
      	      	  			/*AXIS (x1, help, xmul, outmul, N_STEPS, 10);*/
      	      	  			help += delta;
		  			}
      	      			if (D_ACT == VRAI)
      	      	  			{
      	      	  			ACTIVITY (x1, help, xmul, potmul, outmul, N_STEPS, units[unit].state, units[unit].output);  
					
                 			help += delta;
					/*if (units[unit].type == pyr)
						{CURVE (x1, help, xmul, 5*potmul, N_STEPS, units[unit].calcium);
					help += delta;}*/
      	      	  			}
             			if (D_POT == VRAI)
      	      	  			{
      	      	  			CURVE (x1, help, xmul, potmul, N_STEPS, units[unit].state);
      	      	  			/*AXIS (x1, help, xmul, potmul, N_STEPS, 10);*/
      	      	  			help += delta;
      	      	  			}
	    			}
      	  		} /** endif (ALL == VRAI .. **/

      		if ((ALL == FAUX ) && (units[unit].selected == VRAI))
      	      		{
      	      		if (units[unit].type == mitral2)
					strcpy (chain, "m");
			if (units[unit].type == granule)
					strcpy (chain, "g");
			if (units[unit].type == receptor)
					strcpy (chain, "r");
			if (units[unit].type == ET)
					strcpy (chain, "ET");
			if (units[unit].type == PG)
					strcpy (chain, "PG");
			if (units[unit].type == pyr)
					strcpy (chain, "pyr");
			if (units[unit].type == motor)
					strcpy (chain, "mo");
      	      		TEXT (chain, x0, help);
	      		units[unit].x_coor = x0;
	      		units[unit].y_coor = help;
	      		if (units[unit].selected == VRAI)
			CIRCLE (units[unit].x_coor-5, units[unit].y_coor, 2);
      	      		if (D_OUT == VRAI)
      	      	  		{		
      	      	  		if (D_SPIKES == VRAI)
      	      	      			SPIKES (x1, help, xmul, outmul, N_STEPS, units[unit].output);
      	      	  		else
      	      	      			CURVE (x1, help, xmul, outmul, N_STEPS, units[unit].output);
      	      	  		/*AXIS (x1, help, xmul, outmul, N_STEPS, 10);*/
      	      	  		help += delta;
     	      	  		}
      	      		if (D_ACT == VRAI)
      	      	  		{
      	      	  		ACTIVITY (x1, help, xmul, potmul, outmul, N_STEPS, units[unit].state, units[unit].output);            
				help += delta;
				/*if (units[unit].type == pyr)
						{CURVE (x1, help, xmul, 5*potmul, N_STEPS, units[unit].calcium);
				help += delta;}*/

      	      	  		}
            		 if (D_POT == VRAI)
      	      	  		{
      	      	  		CURVE (x1, help, xmul, potmul, N_STEPS, units[unit].state);
      	      	  		/*AXIS (x1, help, xmul, potmul, N_STEPS, 10);*/
      	      	  		help += delta;
      	      	  		}
      	      		} /** endif (ALL == FAUX .. **/      	
      		unit++;
  	 	} /** endwhile (help < lasty .. **/
	
  	CURVE (x1,help, xmul, potmul*20, N_STEPS, POTSM);
	help += 2*delta;
	CURVE (x1,help, xmul, potmul*10, N_STEPS, POTSG);
	help += 2*delta;
	CURVE (x1,help, xmul, potmul*10, N_STEPS, POTSP);
	 
	
  	draw_result.too = unit;
  	TEXT ("click middle : select neuron", 10, 10);
  	TEXT ("click right  : deselect neuron", 10, 25);
  	TEXT ("x : deselect all", 200, 10);
  	TEXT ("s : draw selected", 200, 25);
  	TEXT ("q : quit     u : scroll up  d : scroll down", 500, 10);
  	TEXT ("m : m2  g : gr  p : pyr  b: pyr1 v : pyr2 i : inh1 e : inh2 ", 500, 25);  
  	return (draw_result);
}



void SHOW ()
{
int xmul, outmul, potmul, delta;
EVENT truc;
WIND  vertical[20];
WIND  draw_result;
int   ver, unit;
FILE *read_from;
char to[40];
ALL = VRAI;
printf (" in show first \n");
/** READ DRAW PARAMETERS FROM FILE DRAW.DAT **/

  if ((read_from = fopen ("draw.dat", "r")) == NULL)
    {
      printf (" problem in open file draw.dat \n");
      exit (0);
    }
 loop1:
  if (
      (fscanf (read_from, "%s %d     %s %d       %s %d       %s %d", 
      	      	           to,&xmul, to,&outmul, to,&potmul, to,&delta) != 8) ||


      (fscanf (read_from, "%s %d       %s %d        %s %d      %s %d      %s %d         %s %d", 
      	      	           to,&D_STIM, to, &D_RECS, to,&D_POT, to,&D_OUT, to,&D_SPIKES, to,&D_ACT) != 12) || 

      (fscanf (read_from, "%s %d       %s %d       %s %d ", 
      	      	           to,&D_MPOT, to,&D_MOUT, to,&D_FFTM) != 6) ||
	(fscanf (read_from, "%s %d %s %d", to, &D_VPOT, to, &D_VOUT) != 4) ||
	(fscanf (read_from, "%s %d %s %d %s %d", to, &D_GPOT, to, &D_GOUT, to, &D_FFTG) != 6))
    	
    {
      printf (" problem in reading draw.dat, change and return \n");

      getchar ();
      goto loop1;
    }
  fclose (read_from);
printf ("potmul %d xmul %d \n", potmul, outmul);

printf (" in show second \n");
  vertical[0].from = 0;
  ver = 0;

  CHOOSE_WINDOW (main_window);
  CLEAR ();
/*  truc = GET_EVENT ();*/
  
  draw_result = DRAW (xmul, outmul, potmul, delta, vertical[ver].from);

/** MAIN DRAW LOOP **/

  for (;;)
      {
      truc = GET_EVENT ();
      vertical[ver].too = draw_result.too;  
      if (truc.flag == key)
      	  {
      	  if (EQU (truc.key, "q") == VRAI)
      	      break;
      	  if (EQU (truc.key, "u") == VRAI)
      	      if (vertical[ver].too < N_UNITS)
      	      {
      	      ver += 1;
      	      vertical[ver].from = vertical[ver-1].too;
      	      draw_result = DRAW (xmul, outmul, potmul, delta, vertical[ver].from);    
      	      vertical[ver].too = draw_result.too;
      	      }
      	  if (EQU (truc.key, "d") == VRAI)
      	      if ((vertical[ver].from > 0) && (ver > 0))
      	      	  {
      	      	  ver -= 1;
      	      	  draw_result = DRAW (xmul, outmul, potmul, delta, vertical[ver].from);
      	      	  }
      	  if (EQU (truc.key, "s") == VRAI)
      	      {
      	      ver = 0; 
      	      vertical[ver].from = 0;
      	      ALL = FAUX;
      	      draw_result = DRAW (xmul, outmul, potmul, delta, vertical[ver].from);    
      	      vertical[ver].too = draw_result.too;
      	      }
      	  if (EQU (truc.key, "a") == VRAI)
      	      {
      	      ver = 0; 
      	      vertical[ver].from = 0;
      	      ALL = VRAI;
      	      draw_result = DRAW (xmul, outmul, potmul, delta, vertical[ver].from);    
      	      vertical[ver].too = draw_result.too;
      	      }
      	  if (EQU (truc.key , "x") == VRAI)
      	      DESELECT_ALL ();
     	  if (EQU (truc.key, "m") == VRAI)
      	      {
      	      for (unit = 0; unit < N_UNITS; unit++)
		if (units[unit].type == mitral2)
		  units[unit].selected = VRAI;
	      ver = 0; 
      	      vertical[ver].from = 0;
      	      ALL = FAUX;
      	      draw_result = DRAW (xmul, outmul, potmul, delta, vertical[ver].from);    
      	      vertical[ver].too = draw_result.too;    
	    }
     	  if (EQU (truc.key, "g") == VRAI)
      	      {
      	      for (unit = 0; unit < N_UNITS; unit++)
		if (units[unit].type == granule)
		  units[unit].selected = VRAI;
	      ALL = FAUX;
	      ver = 0; 
      	      vertical[ver].from = 0;
      	      draw_result = DRAW (xmul, outmul, potmul, delta, vertical[ver].from);    
      	      vertical[ver].too = draw_result.too;    
	    }
	if (EQU (truc.key, "e") == VRAI)
      	      {
      	      for (unit = 0; unit < N_UNITS; unit++)
		if (units[unit].type == ET)
		  units[unit].selected = VRAI;
	      ALL = FAUX;
	      ver = 0; 
      	      vertical[ver].from = 0;
      	      draw_result = DRAW (xmul, outmul, potmul, delta, vertical[ver].from);    
      	      vertical[ver].too = draw_result.too;    
	    }
     	  if (EQU (truc.key, "i") == VRAI)
      	      {
      	      for (unit = 0; unit < N_UNITS; unit++)
		if (units[unit].type == PG)
		  units[unit].selected = VRAI;
	      ALL = FAUX;
	      ver = 0; 
      	      vertical[ver].from = 0;
      	      draw_result = DRAW (xmul, outmul, potmul, delta, vertical[ver].from);    
      	      vertical[ver].too = draw_result.too;    
	    }
	if (EQU (truc.key, "p") == VRAI)
      	      {
      	      for (unit = 0; unit < N_UNITS; unit++)
		if (units[unit].type == pyr)
		  units[unit].selected = VRAI;
	      ALL = FAUX;
	      ver = 0; 
      	      vertical[ver].from = 0;
      	      draw_result = DRAW (xmul, outmul, potmul, delta, vertical[ver].from);    
      	      vertical[ver].too = draw_result.too;    
	    }
     	  
      	  } /** endif (truc.flag == **/
      if (truc.flag == mouse)
	{
	  if (truc.button == MIDDLE)
	    SELECT (truc.ypos, potmul, vertical[ver]);
	  if (truc.button == RIGHT)
	    DESELECT (truc.ypos, potmul, vertical[ver]);
	}
    }  /** end (for ;; **/
} /** end show **/

      	          
 /*     
int SHOW_CROSS ()
{
EVENT maus;
	if (cross_window == (Window) NULL)
	  cross_window = OPEN_WINDOW (0, 0, 800, 300, blanc);
	CHOOSE_WINDOW (cross_window);
	CLEAR ();
	for (;;)
	{
	DRAW_CROSS (10, 100, 4, 80, 40, 40);
	maus = GET_EVENT ();
	if (maus.flag == mouse)
		break;
	}
	return (maus.button);
} 
*/	
	      	      
      	      	      	      
      	  
      

  






