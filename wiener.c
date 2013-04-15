#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>

#include "tools.h"



int main(int argc, char *argv[])
{
	int base;
	mpz_t a,b,tmp;
	mpz_t tab;
	mpz_init(a);mpz_init(b);mpz_init(tmp);mpz_init(tab);

	if(argc != 4)
	{		
		fprintf(stderr, "usage:\n\twiener hex/dec e N\n\n");
		return 0;
	}
	if(strcmp(argv[1],"hex")==0)
	{
		base = 16 ;
	}
	else if(strcmp(argv[1],"dec")==0)
	{
		base = 10 ;
	} 
	else 
	{
		fprintf(stderr, "usage:\n\twiener hex/dec e N\n\n");
	}

	mpz_set_str(a,argv[2],base);	
	mpz_set_str(b,argv[3],base);

	mpz_set_str(tab,"3",10);		

	basic(a,b);

	int j,i=0;

	for(j = 1 ; j < 3 ; j++)
	{
		mpz_set(tmp, tab);
		
		for(i=1; i<1000; i++)
		{
			mpz_mul(tmp,tmp,tab);
			fprintf(stdout, " i = %d, j=%d \n",i,j);
			if(mpz_cmp(tmp,b)>0)
				break ;

			gmp_printf("tmp = %Zd\n", tmp);
			wiener(tmp,b);
			gmp_printf("tmp = %Zd\n", tmp);
		}
		mpz_add_ui(tab, tab, 2);
	}

	wiener(a,b);

	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(tmp);

	return 0;
}
