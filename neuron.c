#include "cell.init"
                                                          
/** this file contains personal organization and menue routines **/
/** new routines for menue choices may be included **/





void MENU ()
{
int	      	step_number, x_ext, y_ext, x_mul, y_mul, y_mul2, end, delta, n;  
FILE	      	*read_from; 
FILE		*raster_file; 
char 	      	dummy[10], to[50], name[50];
 int            oo[100];
int 	      	h, test, testi, testo, tot, o, s, nods;  
enum BOOLEAN  	flag, glob, cc, ia;                                   
int	      	points, count, t1, t2, t0;  
int	      	yc, yp, ys, crossx, cor, index, unit, index1, index2;
int 		toto, i, m, from, too;
float		mul, c, value;
EVENT maus;

	
	cc = FAUX;
	N_UNITS = 0; 	   
	N_LINKS = 0;
	GET_RUN_PARAMETERS ("para.dat");
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
		  GET_RUN_PARAMETERS ("para.dat");
		  GET_CHANNELS (); 
		/*READ_CONFIG ();*/ 
		if ((MOL != 0) && (REC != 0))
		  MAKE_REC_SENS ();
		goto last_loop;
		} /** if (test == 2 **/
	if (test == 1)
		{

/***/set_up_loop:/***/   
		GET_RUN_PARAMETERS ("para.dat");
		TEST_SETUP ();	
		printf (" Nunits %d Nlinks %d \n", N_UNITS, N_LINKS) ;
		
		goto last_loop;
        	} /** if (test == 1 **/




/***/run_loop:/***/  

	printf (" in run loop \n");
	RUN ();
	/*STEP_COUNT ();*/
	AVS ();
	GET_AVERAGES (0, N_STEPS-1);
	POTS ();
	SAVE_POTS("test11");
	/*HEBB_AON_PC (RATE);*/

/***/draw_loop:/***/
	SHOW ();  
/***/last_loop:/***/
	printf (" 1. draw again  31. odor stim 32. electrical 21. same input 3. save pyrs 4. set up new 5.save mits 6. save grans 7. save averages  8. correlations 9. show weights 10. save_weigts 11. save time avs 13. exit\n"); 

	scanf ("%d", &test);
	if ((test != 1) && (test != 21) && (test != 4) && (test != 5) && (test != 6) && (test != 7) && (test != 3) && (test != 8) && (test != 13) && (test != 2) && (test != 31) && (test != 32) && (test !=13) && (test != 9) && (test != 10) && (test != 11) && (test != 12))
		{
		printf (" wrong choice, try again\n");
		goto last_loop;
		} 

	if (test == 13)  
		{                         
		FREE_ALL ();
		goto first_loop;
		}
	if (test ==12)
		{
		NULL_ODORS ();
		TESTSN ();
		goto run_loop;
		}
	if (test == 31)
		{
		NULL_ODORS ();
		/*printf ("number of mols? .. conc ?\n");
		scanf ("%d %f", &nods, &c);
		for (o=0; o < nods; o++)
		  {oo[o] = floor (RANF ()*GLOM);printf ("o %d \n", oo[o]);}
		for (o=0; o < nods; o++)
		       for (s=0; s < N_STEPS; s++)
			 molecules[oo[o]].stim[s] = c;
		*/
		RESP (1.0, 25, 75);
		/*CONTEXT_AON ();
		printf ("gust from .. too .. \n");
		scanf ("%d %d", &from, &too);
		for (s = 0; s<N_STEPS; s++)
			GUST[s] = 0.0;
		for (s=from; s<too;s++)
			GUST[s] = 1.0;*/
		goto run_loop;
		}
	if (test == 32)
		{
		STIMULATE ();
		goto run_loop;
		}

	if (test == 21)
		goto run_loop;           

	if (test == 4)
		{
		 goto set_up_loop; 
		}

	if (test == 5)
		{                     
		SAVE_MITRAL_SPIKES ();  
		goto last_loop;
		}   
	if (test == 6)
		{
		SAVE_GRANULE_SPIKES ();
		goto last_loop;
		}
	if (test == 3)
		{
		SAVE_PYR_SPIKES ();
		goto last_loop;
		}
	if (test == 7)
		{
		GET_AVERAGES ();
		SAVE_AVERAGES ();
		goto last_loop;
		}	
	if (test == 11)
		{
		SAVE_SUMS ();
		goto last_loop;
		}		
	if (test == 8)
		{

		CROSS (AVSM, AVSM, N_STEPS, 1, 100);
		CROSS (AVSG, AVSG, N_STEPS, 1, 100);
		CROSS (AVSP, AVSP, N_STEPS, 1, 100);
		CROSS (AVSM, AVSP, N_STEPS, 1, 100);
		CROSS (AVSM, AVSG, N_STEPS, 1, 100);
		CROSS (AVSG, AVSP, N_STEPS, 1, 100); 
		goto last_loop;
		}
	if (test == 9)
		{
		SHOW_WEIGHTS ();
		goto last_loop;
		}
	if (test == 10)
		{
		SAVE_WEIGHTS ();
		goto last_loop;
		}
	if (test == 1)
		{     
		goto draw_loop;
		} 

   
}




void main ()
{                
int test, goon;
	/*printf (" here we go\n");  
	printf ("alea \n");
	scanf ("%lf", &alea);*/
	alea = .89;
	ialea =  alea * 2147483647;  
loppo:	

    MENU ();       
	printf (" 1. ciao 2. hii \n");
	scanf ("%d", &goon);
	if (goon == 2)
		goto loppo;
	printf (" ciao \n"); 
} 



