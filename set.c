/*creates the network*/

#include "cell.init"

#define dummi 0.0


void BULB ()                                            
{
int 	nunits, unit, from, too, other, l, dum, g, m, old_nunits;
int	plus_max, plus_min, min_max, min_min;  
FILE	*read_from; 
char	dumi[10];           
int	test[50][50], i;
int	r, N, nmit, npg;
char	rec_i[20], rec_s[20], rec_o[20], pg_i[20], pg_s[20], pg_o[20], et_i[20], et_s[20], et_o[20], mit_i[20], mit_s[20], mit_o[20], g_i[20], g_s[20], g_o[20], mit2_i[20], mit2_s[20], mit2_o[20], pyr_i[20], pyr_s[20], pyr_o[20];

int	M, R, G, M0, gg, G0, neurs;


/** functions **/
FUNCTION	r_in, r_sta, r_out; 
FUNCTION	pg_in, pg_sta, pg_out; 
FUNCTION 	et_in, et_sta, et_out;
FUNCTION	g_in, g_sta, g_out; 
FUNCTION	mit2_in, mit2_sta, mit2_out;
FUNCTION 	pyr_in, pyr_sta, pyr_out;
/** function parameters **/
float		pr_in1, pr_in2, pr_sta, pr_out1, pr_out2;  
float		ppg_in1, ppg_in2, ppg_sta, ppg_out1, ppg_out2; 
float		pet_in1, pet_in2, pet_sta, pet_out1, pet_out2;
float		pgr_in1, pgr_in2, pgr_sta, pgr_out1, pgr_out2; 
float		pm2_in1, pm2_in2, pm2_sta, pm2_out1, pm2_out2;
float 		ppyr_in1, ppyr_in2, ppyr_sta, ppyr_out1, ppyr_out2;  
float		prob_grmit, prob_mitgr, prob_grgr, prob_mitpyr, prob_pyrmit, prob_pyrgr, prob_pyrpyr, prob_pyret;
float		prob_etpg, prob_etmit, prob_pget;  
float		percent, help, helpi;
char		tot[50];

/** afferents **/

float	      w_affmit, w_affpg, a_affmit, n_affmit, a_affpg, n_affpg, w_affet, n_affet, a_affet; 
int	      del_affmit, del_affpg, del_affet; 

/** local **/

float	  w_mitpg, w_pgmit, a_mitpg, n_mitpg, a_pgmit, b_pgmit;
int	  del_mitpg, del_pgmit; 
float	  w_etpg, w_etmit, w_pget, n_etpg, a_etpg, n_etmit, a_etmit, a_pget, b_pget; 
int	  del_etpg, del_etmit, del_pget; 

/** Deeper layer **/

float	   w_mitmit, w_mitgr, w_grmit, w_grgr; 
int	   del_mitmit, del_mitgr, del_grmit, del_grgr, dec_mitmit, dec_mitgr, dec_grmit, dec_grgr;    
float	   a_mitmit, n_mitmit, a_mitgr, n_mitgr, a_grmit, b_grmit, a_grgr, b_grgr;

/** central **/

float	w_mitpyr, w_pyrmit, w_pyrgr, w_pyret; 
float	a_mitpyr, a_pyrmit, a_pyrgr, a_pyret; 
float 	n_mitpyr, n_pyrmit, n_pyrgr, n_pyret; 
int 	del_pyrmit, del_pyrgr, del_mitpyr, del_pyret;
float	w_pyrpyr, a_pyrpyr, n_pyrpyr, wmm; 
int	del_pyrpyr;

enum BOOLEAN	flag;
	if ((read_from = fopen ("bulb.dat", "r")) == NULL)
		{
		printf (" error in open file bulb.dat\n");
		exit (0);  
		}


	if (fscanf (read_from, "%s", tot) != 1) printf (" error in reading network 1\n");
/** MOLS ECT **/

	if (fscanf (read_from, "%s %d  %s %d  %s %d %s %d", tot, &M, tot, &R, tot, &G, tot, &neurs) != 8) printf (" error in reading network2 \n");
/** RECS **/
	if (fscanf (read_from, "%s", tot) != 1) printf(" error in read neurons 1\n");

	if (fscanf (read_from, "%s %s %s %f %s %f %s %s %s %f %s %s %s %f %s %f", tot, rec_i, tot, &pr_in1, tot, &pr_in2, tot, rec_s, tot, &pr_sta, tot, rec_o, tot, &pr_out1, tot, &pr_out2) != 16) printf(" error in read neurons 2\n");
/** PGs **/
	if (fscanf (read_from, "%s", tot) != 1) printf(" error in read neurons 3\n");
	if (fscanf (read_from, "%s %s %s %f %s %f %s %s %s %f %s %s %s %f %s %f", tot, pg_i, tot, &ppg_in1, tot, &ppg_in2, tot, pg_s, tot, &ppg_sta, tot, pg_o, tot, &ppg_out1, tot, &ppg_out2) != 16) printf (" error in read neurons 4\n");
/** ETs **/
	if (fscanf (read_from, "%s", tot) != 1) printf(" error in read neurons 3\n");
	if (fscanf (read_from, "%s %s %s %f %s %f %s %s %s %f %s %s %s %f %s %f", tot, et_i, tot, &pet_in1, tot, &pet_in2, tot, et_s, tot, &pet_sta, tot, et_o, tot, &pet_out1, tot, &pet_out2) != 16) printf (" error in read neurons 4\n");

/** MITRALS **/
	if (fscanf (read_from, "%s", tot) != 1) printf(" error in read neurons 7\n");
	if (fscanf (read_from, " %s %s %s %f %s %f %s %s %s %f %s %s %s %f %s %f",	tot, mit2_i, tot, &pm2_in1, tot, &pm2_in2, tot, mit2_s, tot, &pm2_sta, tot, mit2_o, tot, &pm2_out1, tot, &pm2_out2) != 16) printf (" error in read neurons 8\n"); 

/** GRANULE **/
	if (fscanf (read_from, "%s", tot) != 1) printf(" error in read neurons 9\n");
	if (fscanf (read_from, " %s %s %s %f %s %f %s %s %s %f %s %s %s %f %s %f",	tot, g_i, tot, &pgr_in1, tot, &pgr_in2, tot, g_s, tot, &pgr_sta, tot, g_o, tot, &pgr_out1, tot, &pgr_out2) != 16) printf (" error in read neurons 10\n");

/** Pyrs **/

	if (fscanf (read_from, "%s", tot) != 1) printf(" error in read neurons 11\n");
	if (fscanf (read_from, " %s %s %s %f %s %f %s %s %s %f %s %s %s %f %s %f",tot, pyr_i, tot, &ppyr_in1, tot, &ppyr_in2, tot, pyr_s, tot, &ppyr_sta, tot, pyr_o, tot, &ppyr_out1, tot, &ppyr_out2) != 16) printf (" error in read neurons 12\n");

/** Afferents **/
	if (fscanf (read_from, "%s %s %f %d %f %f %s %f %d %f %f %s %f %d %f %f", tot, tot, &w_affmit, &del_affmit, &n_affmit, &a_affmit, tot, &w_affpg, &del_affpg, &n_affpg, &a_affpg, tot, &w_affet, &del_affet, &n_affet, &a_affet) != 16) printf (" error in affs \n");

/** Local in GLOM **/

	if (fscanf (read_from, "%s %s %f %d %f %f %s %f %d %f %f %s %f %d %f %f %s %f %d %f %f %s %f %d %f %f", tot, tot, &w_mitpg, &del_mitpg, &n_mitpg, &a_mitpg, tot, &w_pgmit, &del_pgmit, &a_pgmit, &b_pgmit, tot, &w_etpg, &del_etpg, &n_etpg, &a_etpg, tot, &w_etmit, &del_etmit, &n_etmit, &a_etmit, tot, &w_pget, &del_pget, &a_pget, &b_pget) != 26) printf (" error in gloms \n");


/** deeper **/

	if (fscanf (read_from, "%s %s %f %d %f %f %f  %s %f %d %f %f %f  %s %f %d %f %f %f", tot, tot, &w_mitgr, &del_mitgr, &prob_mitgr, &n_mitgr, &a_mitgr, tot, &w_grmit, &del_grmit, &prob_grmit, &a_grmit,&b_grmit, tot, &w_grgr, &del_grgr, &prob_grgr, &a_grgr, &b_grgr) != 19) printf ("error in reading deeper\n");

/** central **/

if (fscanf (read_from, "%s %s %f %d %f %f %f %s %f %d %f %f %f %s %f %d %f %f %f %s %f %d %f %f %f %s %f %d %f %f %f %s %f %s %f %s %f %s %f %s %f %s %f %s %f %s %f %s %f", tot, tot, &w_mitpyr, &del_mitpyr, &prob_mitpyr, &n_mitpyr, &a_mitpyr, tot, &w_pyrmit, &del_pyrmit, &prob_pyrmit, &n_pyrmit, &a_pyrmit, tot, &w_pyrgr, &del_pyrgr, &prob_pyrgr, &n_pyrgr, &a_pyrgr, tot, &w_pyret, &del_pyret, &prob_pyret, &n_pyret, &a_pyret, tot, &w_pyrpyr, &del_pyrpyr, &prob_pyrpyr, &n_pyrpyr, &a_pyrpyr, tot, &WMM1, tot, &WMM2, tot, &RATEASS, tot, &RATEMCGC, tot, &RATEPCGC, tot, &FORGETASS, tot, &FORGETMCGC, tot, &FORGETPCGC, tot, &OXT) != 49) printf ("error in reading central\n");



/*if (scanf (read_from, "%s %f", tot, &RATE) != 2) printf ("error in rate \n");*/

	if (EQU (rec_i, "GET_MOLECULES") == VRAI) 	r_in = GET_MOLECULES;   
	if (EQU (rec_i, "ELECTRICAL") == VRAI)		r_in = ELECTRICAL;
	if (EQU (rec_s, "DECAY") ==  VRAI) 		r_sta = DECAY;
	if (EQU (rec_s, "LINEAR") == VRAI) 		r_sta = LINEAR; 
	if (EQU (rec_o, "LINEAR") == VRAI) 		r_out = LINEAR;
	if (EQU (rec_o, "SIG") == VRAI)			r_out = FALSE_SIG;
	if (EQU (rec_o, "SPIKE") == VRAI)		r_out = FALSE_SPIKE;
	
	if (EQU (pg_i, "SUM_INPUTS") == VRAI) 		pg_in = SUM_INPUTS;
	if (EQU (pg_i, "ELECTRICAL") == VRAI)		pg_in = ELECTRICAL;
	if (EQU (pg_s, "LINEAR") == VRAI)		pg_sta = LINEAR;
	if (EQU (pg_s, "DECAY") == VRAI)		pg_sta = DECAY;      
	if (EQU (pg_o, "SIG") == VRAI)			pg_out = FALSE_SIG;
	if (EQU (pg_o, "SPIKE") == VRAI)		pg_out = FALSE_SPIKE;

	if (EQU (et_i, "SUM_INPUTS") == VRAI) 		et_in = SUM_INPUTS;
	if (EQU (et_i, "ADAPT_INPUT") == VRAI)		et_in = ADAPT_INPUT;
	if (EQU (et_i, "ELECTRICAL") == VRAI)		et_in = ELECTRICAL;
	if (EQU (et_i, "ADAPT_ELECTRICAL") == VRAI)	et_in = ADAPT_ELECTRICAL;
	if (EQU (et_s, "LINEAR") == VRAI)		et_sta = LINEAR;
	if (EQU (et_s, "DECAY") == VRAI)		et_sta = DECAY;      
	if (EQU (et_o, "SIG") == VRAI)			et_out = FALSE_SIG;
	if (EQU (et_o, "SPIKE") == VRAI)		et_out = FALSE_SPIKE;
	
	if (EQU (g_i, "SUM_INPUTS") == VRAI) 		g_in = SUM_INPUTS;
	if (EQU (g_i, "ELECTRICAL") == VRAI)		g_in = ELECTRICAL;
	if (EQU (g_s, "LINEAR") == VRAI)		g_sta = LINEAR;
	if (EQU (g_s, "DECAY") == VRAI)			g_sta = DECAY;    
	if (EQU (g_o, "SIG") == VRAI)			g_out = FALSE_SIG;
	if (EQU (g_o, "SPIKE") == VRAI)			g_out = FALSE_SPIKE;
	if (EQU (g_o, "THRESHOLD") == VRAI)		g_out = THRESHOLD;	


	if (EQU (mit2_i, "SUM_INPUTS") == VRAI)		mit2_in = SUM_INPUTS;
	if (EQU (mit2_i, "ELECTRICAL") == VRAI)		mit2_in = ELECTRICAL;
	if (EQU (mit2_i, "ADAPT_INPUT") == VRAI)	mit2_in = ADAPT_INPUT; 
	if (EQU (mit2_s, "LINEAR") == VRAI)		mit2_sta = LINEAR;
	if (EQU (mit2_s, "DECAY") == VRAI)		mit2_sta = DECAY;    
	if (EQU (mit2_o, "SIG") == VRAI)		mit2_out = FALSE_SIG;
	if (EQU (mit2_o, "SPIKE") == VRAI)		mit2_out = FALSE_SPIKE;


	if (EQU (pyr_i, "SUM_INPUTS") == VRAI)		pyr_in = SUM_INPUTS;
	if (EQU (pyr_i, "ADAPT_ELECTRICAL") == VRAI)	pyr_in = ADAPT_ELECTRICAL;
	if (EQU (pyr_i, "ADAPT_ELEC") == VRAI)		pyr_in=  ADAPT_ELECTRICAL;			
	if (EQU (pyr_i, "ADAPT_INPUT") == VRAI)		pyr_in = ADAPT_INPUT; 
	if (EQU (pyr_i, "ADAPT_AON") == VRAI) 		pyr_in = ADAPT_AON;
	if (EQU (pyr_i, "ELECTRICAL_IN") == VRAI)	pyr_in = ELECTRICAL_IN;
	if (EQU (pyr_s, "LINEAR") == VRAI)		pyr_sta = LINEAR;
	if (EQU (pyr_s, "DECAY") == VRAI)		pyr_sta = DECAY;    
	if (EQU (pyr_o, "SIG") == VRAI)			pyr_out = FALSE_SIG;
	if (EQU (pyr_o, "SPIKE") == VRAI)		pyr_out = FALSE_SPIKE;
	fclose (read_from);  
	if (EQU (TEX, "BULB") == VRAI)
	  GET_CHANNELS ();
percent = 10;
MOL = M;
REC = R;
GLOM = G; 
	nunits = R+G*5*neurs+1;
	if (EQU (TEX, "BULB") == VRAI)
		{
		ALLOCATE_NEURONS (nunits);   
		N_UNITS = 0; 
		N_LINKS = 0; 
		PYRS = 0; 
		}
	old_nunits = N_UNITS;    
/** make receptor neurons **/                 
	for (unit = 0, g=0; unit < R; g++,unit++)
		{
		MAKE_NEURON (receptor,"R", r_in , r_sta, r_out, pr_in1, pr_in2, pr_sta, pr_out1, pr_out2);  
		units[N_UNITS-1].couche = g;
		}
/** make mitrals, pgs and granules **/
	for (g = 0; g < G; g++)
		{    
		MAKE_NEURON (mitral2, "m2", mit2_in, mit2_sta, mit2_out, pm2_in1, pm2_in2, pm2_sta, pm2_out1, pm2_out2);
		units[N_UNITS-1].couche = g;
		MAKE_NEURON (PG,"pg", pg_in, pg_sta, pg_out, ppg_in1, ppg_in2, ppg_sta, ppg_out1, ppg_out2);
		units[N_UNITS-1].couche = g;
		MAKE_NEURON (ET,"et", et_in, et_sta, et_out, pet_in1, pet_in2, pet_sta, pet_out1, pet_out2);
		units[N_UNITS-1].couche = g;             
		MAKE_NEURON (granule,"g", g_in, g_sta, g_out, pgr_in1, pgr_in2, pgr_sta, pgr_out1, pgr_out2);
		units[N_UNITS-1].couche = g;   
		MAKE_NEURON (pyr,"p", pyr_in, pyr_sta, pyr_out, ppyr_in1, ppyr_in2, ppyr_sta, ppyr_out1, ppyr_out2);
		units[N_UNITS-1].couche = g; 
		} 
	MAKE_NEURON (motor, "mo", SUM_INPUTS, DECAY, FALSE_SIG, 0.0, 0.0, 4, 0.0, 2.0);
	units[N_UNITS-1].couche = 200; 
/** synapses **/
	N = (int) G/R;    

/** afferents **/
	for (r = old_nunits; r < old_nunits+R; r++)
		for (too = old_nunits+R; too < old_nunits+nunits; too++)
			{     
			if  ((units[too].couche >= r*N) && (units[too].couche < (r+1)*N))
				{
				if (units[too].type == mitral2)
					{
					if (a_affmit*w_affmit != 0.0) 
						{
						  MAKE_LINK (r, too, a_affmit * w_affmit, del_affmit, aff, AMPA);    
						}
					if (n_affmit * w_affmit != 0.0) 
						MAKE_LINK (r, too, n_affmit * w_affmit, del_affmit, aff, NMDA);
					}
 				if (units[too].type == PG)
					{
					if (a_affpg * w_affpg != 0.0) 
						MAKE_LINK (r, too, a_affpg * w_affpg, del_affpg, aff, AMPA); 	
					if (n_affpg * w_affpg != 0.0) 
						MAKE_LINK (r, too, n_affpg * w_affpg, del_affpg, aff, NMDA) ;
					} 
				if (units[too].type == ET)
					{
					if (a_affet * w_affet != 0.0) 
						MAKE_LINK (r, too, a_affet * w_affet, del_affet, aff, AMPA); 	
					if (n_affet * w_affet != 0.0) 
						MAKE_LINK (r, too, n_affet * w_affet, del_affet, aff, NMDA) ;
					} 

				}
			}  /** end for r .. **/

	for (from = R+old_nunits; from < nunits+old_nunits; from++)
		for (too = R+old_nunits; too < nunits+old_nunits; too++)     
			{

			if (units[from].couche == units[too].couche)
				{
				if ((units[from].type == mitral2)  && (units[too].type == PG))
					{
					help = w_mitpg / percent;
					help = RANF () * (2 * help) + (w_mitpg - help);
					if (n_mitpg * help != 0.0) 
						MAKE_LINK2 (from, too, soma, n_mitpg * help, del_mitpg, local, NMDA);		                        if (a_mitpg * help != 0.0) 
						MAKE_LINK2 (from, too, soma, a_mitpg * help, del_mitpg, local, AMPA);
					}				                  
				if ((units[from].type == PG) && (units[too].type == mitral2))             
					{
					help = w_pgmit / percent;
					help = RANF () * (2 * help) + (w_pgmit -help);
					if (a_pgmit * help != 0.0) 
						MAKE_LINK2 (from, too, dend1, a_pgmit * help, del_pgmit, local, GABAA);
					if (b_pgmit * help != 0.0) 
						MAKE_LINK2 (from, too, dend1, b_pgmit * help, del_pgmit, local, GABAB) ;
					}
				if ((units[from].type == ET) && (units[too].type == mitral2))             
					{
					help = w_etmit / percent;
					help = RANF () * (2 * help) + (w_etmit -help);
					if (n_etmit * help != 0.0) 
						MAKE_LINK2 (from, too, dend1, n_etmit * help, del_etmit, local, NMDA);
					if (a_etmit * help != 0.0) 
						MAKE_LINK2 (from, too, dend1, a_etmit * help, del_etmit, local, AMPA) ;
					}
				if ((units[from].type == PG) && (units[too].type == ET))             
					{
					help = w_pget / percent;
					help = RANF () * (2 * help) + (w_pget -help);
					if (a_pget * help != 0.0) 
						MAKE_LINK2 (from, too, dend1, a_pget * help, del_pget, local, GABAA);
					if (b_pget * help != 0.0) 
						MAKE_LINK2 (from, too, dend1, b_pget * help, del_pget, local, GABAB) ;
					}
				if ((units[from].type == ET) && (units[too].type == PG))             
					{
					help = w_etpg / percent;
					help = RANF () * (2 * help) + (w_etpg -help);
					if (n_etpg * help != 0.0) 
						MAKE_LINK2 (from, too, dend1, n_etpg * help, del_etpg, local, NMDA);
					if (a_etpg * help != 0.0) 
						MAKE_LINK2 (from, too, dend1, a_etpg * help, del_etpg, local, AMPA) ;
					}
				if ((units[from].type == granule) && (units[too].type == granule))
					{
					help = w_grgr/percent;
					help = RANF () * (2*help)+(w_grgr-help);
					if (a_grgr*help != 0.0)
						MAKE_LINK2(from, too, soma, 10*a_grgr*help, 1, local, GABAA);
					if (b_grgr*help != 0.0)
						MAKE_LINK2(from, too, soma, 10*b_grgr*help, 1, local, GABAB);
					}  
				if ((units[from].type == mitral2) && (units[too].type == granule))
					{
					MAKE_LINK2 (from, too, soma, 2*a_mitgr*w_mitgr, 1, local, AMPA);
					MAKE_LINK2 (from, too, soma, 2*n_mitgr*w_mitgr, 1, local, NMDA);
					}
				if ((units[from].type == granule) && (units[too].type == mitral2))
					{
					MAKE_LINK2 (from, too, soma, 10*a_grmit*w_grmit, 1, local, GABAA);
					MAKE_LINK2 (from, too, soma, 10*b_grmit*w_grmit, 1, local, GABAB);
					}	
				} /** end if couche[from] == couche[too] **/                              
				else					

				{

				if ((units[from].type == granule) && (units[too].type == granule) && (RANF () < prob_grgr))
					{		
                    			helpi = w_grgr;
					help = helpi/percent;
					help = RANF () * (2*help) + (helpi-help);
					if (a_grgr * help != 0.0) 
 						MAKE_LINK2 (from, too, soma, a_grgr * help, 1, lateral, GABAA);	
					if (b_grgr * help != 0.0)					
 						MAKE_LINK2 (from, too, soma, b_grgr * help, 1, lateral, GABAB);						
					}

				if ((units[from].type == mitral2) && (units[too].type == granule) && (RANF () < prob_mitgr))
					{		
                    			helpi = w_mitgr;
					help = helpi/percent;
					help = RANF () * (2*help) + (helpi-help);
					if (a_mitgr * help != 0.0) 
						MAKE_LINK2 (from, too, soma, a_mitgr * help, 1, lateral, AMPA);		
					if (n_mitgr * help != 0.0)		
						MAKE_LINK2 (from, too, soma, n_mitgr * help, 1, lateral, NMDA);	
					if ((help != 0.0) && ((a_mitgr != 0.00) || (n_mitgr != 0.0)))
						SET_LINK_COMP ( from, too, dend2) ;					
					
					}
				if ((units[from].type == granule) && (units[too].type == mitral2) && (RANF () < prob_grmit))
					{		
                    			helpi = w_grmit;
					help = helpi/percent;
					help = RANF () * (2*help) + (helpi-help);
					if (a_grmit * help != 0.0) 
						MAKE_LINK2 (from, too, dend2, a_grmit * help, 1, lateral, GABAA);	
					if (b_grmit * help != 0.0)					
						MAKE_LINK2 (from, too, dend2, b_grmit * help, 1, lateral, GABAB);						
					}

				if ((units[from].type == mitral2) && (units[too].type == pyr) && (RANF () < prob_mitpyr))
					{		
                    			helpi = w_mitpyr;
					help = helpi/percent;
					help = RANF () * (2*help) + (helpi-help);
					if (a_mitpyr * help != 0.0) 
						MAKE_LINK2 (from, too, soma, a_mitpyr * help, 1, central, AMPA);	
					if (n_mitpyr * help != 0.0)					
						MAKE_LINK2 (from, too, soma, n_mitpyr * help, 1, central,NMDA);					
					}
				if ((units[from].type == pyr) && (units[too].type == mitral2) && (RANF () < prob_pyrmit))
					{		
                    			helpi = w_pyrmit;
					help = helpi/percent;
					help = RANF () * (2*help) + (helpi-help);
					if (a_pyrmit * help != 0.0) 
						MAKE_LINK2 (from, too, soma, a_pyrmit * help, 1, central, AMPA);	
					if (n_pyrmit * help != 0.0)					
						MAKE_LINK2 (from, too, soma, n_pyrmit * help, 1, central,NMDA);					
					}
				if ((units[from].type == pyr) && (units[too].type == granule) && (RANF () < prob_pyrgr))
					{		
                    			helpi = w_pyrgr;
					help = helpi/percent;
					help = RANF () * (2*help) + (helpi-help);
					if (a_pyrgr * help != 0.0) 
						MAKE_LINK2 (from, too, soma, a_pyrgr * help, 1, central, AMPA);	
					if (n_pyrgr * help != 0.0)					
						MAKE_LINK2 (from, too, soma, n_pyrgr * help, 1, central,NMDA);					
					}
				if ((units[from].type == pyr) && (units[too].type == ET) && (RANF () < prob_pyret))
					{		
                    			helpi = w_pyret;
					help = helpi/percent;
					help = RANF () * (2*help) + (helpi-help);
					if (a_pyret * help != 0.0) 
						MAKE_LINK2 (from, too, soma, a_pyret * help, 1, central, AMPA);	
					if (n_pyret * help != 0.0)					
						MAKE_LINK2 (from, too, soma, n_pyret * help, 1, central,NMDA);					
					}	
				if ((units[from].type == pyr) && (units[too].type == pyr) && (RANF () < prob_pyrpyr))
					{		
                    			helpi = w_pyrpyr;
					help = helpi/percent;
					help = RANF () * (2*help) + (helpi-help);
					if (a_pyrpyr * help != 0.0) 
						MAKE_LINK2 (from, too, soma, a_pyrpyr * help, 1, central, AMPA);	
					if (n_pyrpyr * help != 0.0)					
						MAKE_LINK2 (from, too, soma, n_pyrpyr * help, 1, central,NMDA);					
					}
				if ((units[from].type == mitral2) && (units[too].type == motor))
					MAKE_LINK2 (from, too, soma, wmm, 1, central, AMPA);
				}
				

			} /** end for from **/  


/** make receptor matrix **/   
	MAKE_REC_SENS ();
	NULL_STIM ();

	printf (" at end of bulb NUNITS %d NLINKS %d \n", N_UNITS, N_LINKS);


/* SHOW_REC_LINKS ();*/


} /** end bulb **/




void TEST_SETUP ()
{

BULB ();
}	

