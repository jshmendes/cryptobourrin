#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

#define BOUND 10000


int main(int argc, char *argv[])
{
	mpz_t tabm[BOUND][2];
	
	mpz_t min,a,b,var,tmp,N;
	int ite_min,i,j,k,upper;
	
	int base;
	
	//Init variables
	i = 0 ;
	j = 0 ;
	k = 0 ;
	upper = 100000000;
	mpz_init(min);
	mpz_init(N);
	mpz_init(a);
	mpz_init(b);
	mpz_init_set_str(var,"8",10);
	mpz_init_set_str(tmp,"1",10);
	
	for (i=0 ; i < BOUND ; i++)
	{
		mpz_init_set_str(tabm[i][0],"0",10);
		mpz_init_set_str(tabm[i][1],"0",10);
	}

	
	if(argc != 4)
	{
			fprintf(stderr, "usage:\n\tloopDetection hex/dec e N\n\n");
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
			fprintf(stderr, "usage:\n\tloopDetection hex/dec e N\n\n");
	}

	
	
    mpz_set_str(a,argv[2],base);
    mpz_set_str(N,argv[3],base);

	
	i = 0;
	mpz_set(min,N);
	mpz_set(tmp,var);
	//Searching for cycling value
		
	while( j < BOUND )
	{
		mpz_mul(tmp,tmp,var);
		mpz_mod(tmp,tmp,N);
		
		if(mpz_cmp(tmp,min) < 0)
		{
			mpz_set(min,tmp);
			ite_min = i+2;

			if(mpz_cmp_ui(tmp,1) == 0)
			{
				gmp_printf("Find an inverse:\n%Zd inverses itself in %d (%Zd)\n", var, ite_min,tmp);
				mpz_powm_ui(tmp,var,ite_min,N);
                                gmp_printf("%Zd ^ %d mod N = %Zd (should be ONE)\n", var,ite_min,tmp);
				return 0;
				
			}
			for(k=0; k<j ; k++)
				if(mpz_cmp(min, tabm[k][0]) == 0)
				{
					gmp_printf("Find a loop\n %Zd loops in", tabm[k][0]);
					mpz_set_ui(tmp,ite_min);
					for(i=k+1;i<j;i++)
						mpz_mul(tmp,tmp,tabm[i][1]);
					gmp_printf(" %Zd iterations (%d)\nAnd we can prove it : \n", tmp,k);
					
					mpz_powm(var,tabm[k][0],tmp,N);
					gmp_printf("\t%Zd ^ %Zd mod N = %Zd \n", tabm[k][0],tmp,var);
					mpz_sub_ui(tmp,tmp,1);
					mpz_powm(var,tabm[k][0],tmp,N);
					gmp_printf("\t%Zd ^ %Zd mod N = %Zd (should be ONE)\n", tabm[k][0],tmp,var);	
					return 0 ;
				}
		
		}
		
		i++;
		if(i == upper )
		{
			mpz_set(tabm[j][0],min);
			mpz_set_ui(tabm[j][1],ite_min);
		//	gmp_printf("Round %d:\n\t%Zd\n\t%d\n",j,min,ite_min);
			i=0; j++;
			mpz_set(var,min);
			mpz_set(min,N);
			mpz_set(tmp,var);
		}
	
	
	}

gmp_printf("No loop found \n");
return 0;
}
