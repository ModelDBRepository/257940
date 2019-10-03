#include "cell.init"

float act[25];

void main ()
{
  int test;
  int i, dummy,n;
  float dum, null;
  char toto[20];
  char filename[60];
  Window win;
  EVENT maus;
  FILE *readfrom;
INIT_GRAPHICS ();
  win = OPEN_WINDOW (0,0,500, 200, blanc);
  CHOOSE_WINDOW (win); 

loop:
  printf ("read from file \n");
  scanf ("%s", filename);
  readfrom = fopen (filename, "r");
  i=0;
  while ((fscanf (readfrom, "%s %d %s %d %s %f %s %f", toto, &dummy, toto, &dummy, toto, &act[i], toto, &dum)) != EOF)
    i++;
  fclose (readfrom);
  
  n=i;
  null = act[0];
  for (i=0;i<n;i++)
    if (null != 0.0) act[i] /= null;
  for (;;)
    {
      AXIS (10, 150, 20, 50, n, 1);
      CURVE (10, 150, 20, 50, n-1, act);
      maus = GET_EVENT ();
      if (maus.button == RIGHT)
	break;
    }
  printf ("1. more 2. exit\n");
  scanf ("%d", &test);
  if (test == 1)
    goto loop;


}
