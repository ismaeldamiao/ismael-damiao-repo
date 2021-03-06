/* *****************************************************************************
Gerador de numeros aleatorios.
"Numerical Recipes in C" (Cambridge Univ. Press)
The Art of Scientific Computing, 2nd Edition, 1992 p 280
by W.H. Press, S.A. Teukolsky, W.T. Vetterling, and B.P. Flannery
***************************************************************************** */

/* *****************************************************************************
Nao usar para gerar mais de 100000000 de numeros, use ran2 ou ran3
double var = ran1(&semente); // Guarda em var um numero aleatorio em [0, 1)
***************************************************************************** */
#define IA 16807L
#define IM 2147483647L
#define IQ 127773L
#define IR 2836L
#define NTAB 32L
#define EPS 1.2e-7
/* *****************************************************************************
“Minimal” random number generator of Park and Miller with Bays-Durham shuffle
and added safeguards. Returns a uniform random deviate between 0.0 and 1.0
(exclusive of the endpoint values). Call with idum a negative integer to
initialize; thereafter, do not alter idum between successive deviates in a
sequence. RNMX should approximate the largest floating value that is less
than 1.
***************************************************************************** */
double ran1(long int *idum){
   static long int iy=0L, iv[NTAB];
   long int k;
   long int NDIV = 1L+(IM-1L)/NTAB;
   int j;
   double AM = 1.0/((double)IM);
   double RNMX = 1.0-EPS;
   double temp;
   if(*idum <= 0L || !iy){ /* Inicialise */
      if (-(*idum) < 1L) *idum = 1L; /* Garantir que idum != 0 */
      else *idum = -(*idum);
      for(j = NTAB + 7L; j >= 0L; j--){
         k = (*idum) / IQ;
         *idum = IA * (*idum - k * IQ) - IR * k;
         if(*idum < 0L) *idum += IM;
         if(j < NTAB) iv[j] = *idum;
      }
      iy = iv[0];
   }
   k = (*idum) / IQ; /* Comece aqui quando nao inicializado */
   *idum = IA * (*idum - k * IQ) - IR * k;
   if(*idum < 0L) *idum += IM;
   j = iy / NDIV;
   iy = iv[j];
   iv[j] = *idum;
   if((temp=AM*(double)iy) > RNMX) return RNMX;
   else return temp;
}
