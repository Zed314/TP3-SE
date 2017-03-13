#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <assert.h>

// returns a human-friendly string describing this many bytes e.g. 1024 -> "1kB"
char * hsize(int64_t bytes)
{
const char *units[]={"B","kB","MB","GB","TB","PB","EB","ZB","YB"};
int unit=0;
// 7 bytes is our worst-case: three significant digits, a decimal point in the middle,
// the two-letter unit, and then the terminating NUL byte
char* result = malloc(7);
assert(result != NULL);
// the mismatch (1000 vs 1024) here is intentional.
// it helps avoiding horrors like 1023 -> "1e+03B"
float number=bytes;
while( number>1000 )
{
number /= 1024;
unit++;
}
snprintf(result,7,"%.3g%s",number,units[unit]);
return result;
}

double benchmark(int64_t N,int64_t R)
{
	srandom(clock());
	int64_t * tab=(int64_t *)malloc(sizeof(int64_t)*N);
	assert(tab!=NULL);
	int64_t i=0;
	for(i=0;i<N;i++)
	{
		tab[i]=i;
	}
	for (i = N-1; i>0; i--) 
    {
          int64_t j = rand()%(i);
          int64_t t = tab[j];
          tab[j] = tab[i];
          tab[i] = t;
       
   }
//   int64_t indiceCourant=0;

   double temps=clock();
   
   for(i=0;i<R;i++)
   {
	    int64_t indiceCourant=0;
		while(tab[indiceCourant]!=0){

				indiceCourant=  tab[indiceCourant];
		 
			}
	}
	

 //   printf("%ld %g ns\n",N*8,((1000000000*(clock()-temps))/CLOCKS_PER_SEC)/(N*R));//Calcul temps moyen 
 free(tab);
 return ((1000000000*(clock()-temps))/CLOCKS_PER_SEC)/(N*R);
}

int main()
{
	
	double tab[1000];
	int i=0;
	int64_t N=1000;
	int64_t R=10000;
	for(i=0;i<1000;i++)
	{
		int64_t temps=clock();
		tab[i]=benchmark( N,R);
		printf("%s %ld %g\r\n",hsize(N*8),N*8,tab[i]);
		if((((clock()-temps))/CLOCKS_PER_SEC)>1)
		{
			if(R>4)
			{
			R/=2;
			}
		}
		N=N*1.1;
		//printf("%g\r\n",tab[i]);
		
		
	}
		/*for(i=0;i<50;i++)
	{
		printf("%g\r\n",tab[i]);
		
	}*/
	
	
    return 0;
}

