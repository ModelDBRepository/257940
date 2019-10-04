#include "cell.init"





void SAVE2 ()
{
FILE *weights, *cells;
char as[20], ws[20]; 
int	step, interval, i, trial; 
	alea = .761;
	ialea =  alea * 2147483647; 
	N_UNITS = 0; 	   
	N_LINKS = 0;
	GET_RUN_PARAMETERS ("para.dat");
	GET_CHANNELS (); 
	if ((MOL != 0) && (REC != 0))
		MAKE_REC_SENS ();
	TEST_SETUP (); 
	printf ("save weights to \n");
	scanf ("%s", ws);
	printf ("save activities to \n");
	scanf ("%s", as);
	weights = fopen (ws, "w");
	cells = fopen (as, "w");

for (trial = 0; trial < 1; trial++)
	{
	SAVE_WEIGHTS3 (weights);
	NULL_ODORS (); 
	FAMILIAR ();
	NULL_ALL ();
	for (step = 0; step < 150; step++)
		UPDATE_NET (step);
	GET_AVERAGES (0, 150);	
	SAVE_SUMS(cells); 
 	NULL_ODORS ();
	NOVEL1 ();
	NULL_ALL ();
	for (step = 0; step < 150; step++)
		UPDATE_NET (step);
	GET_AVERAGES (0, 150);	
	SAVE_SUMS(cells); 
	NULL_ODORS ();
	NOVEL2 ();
	NULL_ALL ();
	for (step = 0; step < 150; step++)
		UPDATE_NET (step);
	GET_AVERAGES (0, 150);	
	SAVE_SUMS(cells);
	NULL_ODORS ();
	NOVEL3 ();
	NULL_ALL ();
	for (step = 0; step < 150; step++)
		UPDATE_NET (step);
	GET_AVERAGES (0, 150);	
	SAVE_SUMS(cells);
	interval = 150;
	
	NULL_ODORS ();
	FAMILIAR ();
	NULL_ALL ();
	for (step = 0; step < 1500; step++)
		{
		UPDATE_NET (step);
		if (step == interval)
			{
			GET_AVERAGES (interval-150, interval);
			/*HEBB_MC_GC (RATEMCGC);*/
			HEBB_PC_GC(RATEPCGC);
			SAVE_WEIGHTS3(weights);
			SAVE_SUMS(cells);
			interval += 150;
			}
		}

/** get after learning activity for familiar odor **/
	NULL_ALL ();	
	for (step = 0; step < 150; step++)
		UPDATE_NET (step);
	GET_AVERAGES(0, 150);
	/*fprintf (cells, "after learning familiar ");*/	
	SAVE_SUMS (cells);	
/** get after learning activity for novel odor **/
	NULL_ODORS ();
	NOVEL1 ();
	NULL_ALL ();	
	for (step = 0; step < 150; step++)
		UPDATE_NET (step);
	GET_AVERAGES(0, 150);
/*fprintf (cells, "after learning familiar ");*/	
	SAVE_SUMS (cells);	
/** forget in 5 minute intervals and each time save weights, familiar and novel odor response **/
/** get after learning activity for novel odor **/
	NULL_ODORS ();
	NOVEL2 ();
	NULL_ALL ();	
	for (step = 0; step < 150; step++)
		UPDATE_NET (step);
	GET_AVERAGES(0, 150);
/*fprintf (cells, "after learning familiar ");*/	
	SAVE_SUMS (cells);	
/** forget in 5 minute intervals and each time save weights, familiar and novel odor response **/
/** get after learning activity for novel odor **/
	NULL_ODORS ();
	NOVEL3 ();
	NULL_ALL ();	
	for (step = 0; step < 150; step++)
		UPDATE_NET (step);
	GET_AVERAGES(0, 150);
/*fprintf (cells, "after learning familiar ");*/	
	SAVE_SUMS (cells);	
/** forget in 5 minute intervals and each time save weights, familiar and novel odor response **/

	for (i=0; i < 6; i++)
		{
/*FORGET_MC_GC (FORGETMCGC, 2000.0);*/

FORGET_PC_GC(FORGETPCGC, 2000.0);
		/*fprintf (weights, "forget %d  ", i);	*/
		SAVE_WEIGHTS3 (weights);
		NULL_ODORS ();
		FAMILIAR ();
		NULL_ALL ();
		for (step = 0; step < 150; step++)
			UPDATE_NET (step);
		GET_AVERAGES(0, 150); 
		/*fprintf (cells, "familiar forget %d  ", i); */
		SAVE_SUMS(cells);
		NULL_ODORS ();
		NOVEL1 ();
		NULL_ALL ();
		for (step = 0; step < 150; step++)
			UPDATE_NET (step);
		GET_AVERAGES(0, 150); 
		/*fprintf (cells, "novel forget %d  ", i);	*/
		SAVE_SUMS(cells); 
		NULL_ODORS ();
		NOVEL2 ();
		NULL_ALL ();
		for (step = 0; step < 150; step++)
			UPDATE_NET (step);
		GET_AVERAGES(0, 150); 
		/*fprintf (cells, "novel forget %d  ", i);	*/
		SAVE_SUMS(cells); 

		NULL_ODORS ();
		NOVEL3 ();
		NULL_ALL ();
		for (step = 0; step < 150; step++)
			UPDATE_NET (step);
		GET_AVERAGES(0, 150); 
		/*fprintf (cells, "novel forget %d  ", i);	*/
		SAVE_SUMS(cells); 

		}
	fprintf (cells, "\n"); fprintf(weights, "\n");
	}
	fclose (weights);
	fclose (cells);
}				
	


void SAVE ()
{
FILE 	*prelearn;
FILE 	*weightfile; 
int s, g;
	alea = .761;
	ialea =  alea * 2147483647; 
	N_UNITS = 0; 	   
	N_LINKS = 0;
	GET_RUN_PARAMETERS ("para.dat");
	GET_CHANNELS (); 
	if ((MOL != 0) && (REC != 0))
		MAKE_REC_SENS ();
	TEST_SETUP (); 
/** run different odors in first setup and save activities to pre-learning file**/
	printf ("pretests\n");
	prelearn = fopen ("prelearnaoxt", "w");
	weightfile = fopen ("weightfileaoxt", "w");
	OXT_AON (0.0);
	NULL_ODORS ();
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[10].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
	fprintf (prelearn, "c10\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
	NULL_ODORS ();
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[12].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
	fprintf (prelearn, "c12\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
	NULL_ODORS ();
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[20].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
	fprintf (prelearn, "c20\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
		NULL_ODORS ();
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
	fprintf (prelearn, "c25\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
	

/** learn c25 and save weights as you go **/
	printf ("learning 1\n");	

	NULL_ODORS ();
	printf ("oxt %f \n", OXT);
	OXT_AON (OXT);
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN3 (weightfile);printf ("done once\n");
	NO_CONTEXT_AON ();
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
	fprintf (prelearn, "c25 after learn 1\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");

	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");

	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");

	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");
	OXT_AON (OXT);	
	RUN3 (weightfile);printf ("done twice \n");
	NO_CONTEXT_AON ();	
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
fprintf (prelearn, "c25 after learn 2\n");
		
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");

	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");
	OXT_AON (OXT);	
	RUN3 (weightfile);printf ("done three\n");
	NO_CONTEXT_AON ();
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
fprintf (prelearn, "c25 after learn 3\n");
	
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");
	OXT_AON (OXT);	
	RUN3 (weightfile);printf ("done four\n");
	NO_CONTEXT_AON ();
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
fprintf (prelearn, "c25 after learn 4\n");

	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");
	OXT_AON (OXT);	
	RUN3 (weightfile);printf ("done five\n");
	NO_CONTEXT_AON ();	
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();

fprintf (prelearn, "c25 after learn 5\n");

	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
	

/** test responses to all odors without learning **/
	NULL_ODORS ();
printf ("test1\n");
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[10].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
	fprintf (prelearn, "test c10\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
		NULL_ODORS ();
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[20].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
fprintf (prelearn, "test c20\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
		NULL_ODORS ();
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[23].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
fprintf (prelearn, "test c23\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
	
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
fprintf (prelearn, "test c25\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
	
/** forget and save weights and save responses to c25 **/
	printf ("lets forget \n");
	RUN4 (weightfile, 1000.0); printf ("done once \n");
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
fprintf (prelearn,"test after forget 1\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
		
	RUN4 (weightfile, 1000.0);printf ("done twice \n");
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
fprintf (prelearn, "test after forget 2\n");

	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
		RUN4 (weightfile, 1000.0);printf ("three times \n");
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
fprintf (prelearn, "test after forget 3\n");

	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");		
	RUN4 (weightfile, 1000.0);printf ("done four \n");
	for (s = 0; s < N_STEPS; s++)
		{
		molecules[25].stim[s] = 1.0;
		}	
	RUN2 ();	
	GET_AVERAGES ();
fprintf (prelearn, "test after forget 4\n");

	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", RAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", MAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", GAV[g]);
	fprintf (prelearn, "\n");
	for (g=0; g< GLOM; g++)
		fprintf (prelearn, "%f ", PAV[g]);
	fprintf (prelearn, "\n\n");	
	fclose (prelearn); fclose (weightfile);	
}	

void SAVE_CONC ()
{
FILE 	*mitrals;
FILE 	*synch; 
FILE	*pyrs;
FILE	*recs, *ets, *grans;
int s, g, t, step;
float c;
	alea = .761;
	ialea =  alea * 2147483647; 
	N_UNITS = 0; 	   
	N_LINKS = 0;
	GET_RUN_PARAMETERS ("para.dat");
	GET_CHANNELS (); 
	if ((MOL != 0) && (REC != 0))
		MAKE_REC_SENS ();
	TEST_SETUP (); 
	mitrals=fopen ("cont_mitral", "w"); 
	pyrs=fopen ("cont_pyr", "w");
	recs=fopen ("cont_rec", "w");
	ets=fopen ("cont_et", "w");
	grans=fopen ("cont_gran", "w");
	synch=fopen ("cont_units", "w");
	for (t=0; t < 20; t++)
		{
		for (c=0; c<0.25; c+=0.05)
			{
			
			NULL_ODORS ();
			RESP(c, 20, 60);
			RUN2 ();	
			GET_AVERAGES (0, N_STEPS);
			fprintf(mitrals, "odor C0 conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (mitrals, "%f ", MAV[g]);
			fprintf(mitrals, "\n");
			fprintf(pyrs, "odor C0 conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (pyrs, "%f ", PAV[g]);
			fprintf(pyrs, "\n");
						
			fprintf(recs, "odor C0 conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (recs, "%f ", RAV[g]);
			fprintf(pyrs, "\n");
			
			fprintf(grans, "odor C0 conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (grans, "%f ", GAV[g]);
			fprintf(grans, "\n");
			
			fprintf(ets, "odor C0 conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (ets, "%f ", EAV[g]);
			fprintf(ets, "\n");
			
			AVS ();
			fprintf (synch, "odor C0 conc %f ", c);
			for (step = 0; step<N_STEPS; step++)
				fprintf(synch, "%f ", AVSM[step]);
			fprintf (synch, "\n");
			for (step = 0; step<N_STEPS; step++)
				fprintf(synch, "%f ", AVSG[step]);
			fprintf (synch, "\n");
			for (step = 0; step<N_STEPS; step++)
				fprintf(synch, "%f ", AVSP[step]);
			fprintf (synch, "\n");
			NULL_ODORS ();
			RESP(c, 25, 65);
			RUN2 ();	
			GET_AVERAGES (0, N_STEPS);
			fprintf(mitrals, "odor C1 conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (mitrals, "%f ", MAV[g]);
			fprintf(mitrals, "\n");
			fprintf(pyrs, "odor C1 conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (pyrs, "%f ", PAV[g]);
			fprintf(pyrs, "\n");
						
			fprintf(recs, "odor C1 conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (recs, "%f ", RAV[g]);
			fprintf(pyrs, "\n");
			
			fprintf(grans, "odor C1 conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (grans, "%f ", GAV[g]);
			fprintf(grans, "\n");
			
			fprintf(ets, "odor C1 conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (ets, "%f ", EAV[g]);
			fprintf(ets, "\n");
			
			AVS ();
			fprintf (synch, "odor C1 conc %f ", c);
			for (step = 0; step<N_STEPS; step++)
				fprintf(synch, "%f ", AVSM[step]);
			fprintf (synch, "\n");
			for (step = 0; step<N_STEPS; step++)
				fprintf(synch, "%f ", AVSG[step]);
			fprintf (synch, "\n");
			for (step = 0; step<N_STEPS; step++)
				fprintf(synch, "%f ", AVSP[step]);
			fprintf (synch, "\n");



			NULL_ODORS ();
			RESP(c, 0, 90);
			RUN2 ();	
			GET_AVERAGES (0, N_STEPS);
			fprintf(mitrals, "odor X conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (mitrals, "%f ", MAV[g]);
			fprintf(mitrals, "\n");
			fprintf(pyrs, "odor X conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (pyrs, "%f ", PAV[g]);
			fprintf(pyrs, "\n");
						
			fprintf(recs, "odor X conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (recs, "%f ", RAV[g]);
			fprintf(pyrs, "\n");
			
			fprintf(grans, "odor X conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (grans, "%f ", GAV[g]);
			fprintf(grans, "\n");
			
			fprintf(ets, "odor X conc %f ", c);
			for (g=0; g<GLOM; g++)
				fprintf (ets, "%f ", EAV[g]);
			fprintf(ets, "\n");
			
			AVS ();
			fprintf (synch, "odor X conc %f ", c);
			for (step = 0; step<N_STEPS; step++)
				fprintf(synch, "%f ", AVSM[step]);
			fprintf (synch, "\n");
			for (step = 0; step<N_STEPS; step++)
				fprintf(synch, "%f ", AVSG[step]);
			fprintf (synch, "\n");
			for (step = 0; step<N_STEPS; step++)
				fprintf(synch, "%f ", AVSP[step]);
			fprintf (synch, "\n");
			
			}
	}
fclose (mitrals);
fclose (synch);
fclose (ets);
fclose(grans);
fclose(pyrs);
}			
void main ()
{                
int test, goon;
	

    	SAVE2 ();      
	printf (" ciao \n"); 
} 



