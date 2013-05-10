#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>
	
int main(int argc, char *argv[]) 
{

	if(argc !=2)
	{
		fprintf(stdout,"usage:\n\t./bruteforceD N\n\n");
		return 0;
	}

	mpz_t x,N, pow,tmp, min, minRef ;
	mpz_init_set_str(x,"2", 16);	
	mpz_init_set_str(tmp,"341510400", 10);	
	mpz_init_set_str(N,argv[1], 16);
	mpz_init_set_str(pow,"1",10);
	mpz_init_set_str(min,"100000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000",16);
	gmp_randstate_t rstate42;
	unsigned int i = 1;
	unsigned int j = 1;
	unsigned int count = 0;

	mpz_init_set(minRef,N);

	gmp_printf("N = %Z0x\n", N);
	gmp_randinit_default(rstate42);
	mpz_sub_ui(tmp,tmp,1);

	mpz_urandomb(tmp, rstate42,2000);
	gmp_printf("x = %Zd\n", tmp);
	mpz_init_set(min,tmp);
	while(count <5)
	{
		count++;
		mpz_set_str(pow,"0",10);
		mpz_init_set(tmp,min);
		gmp_printf("x = %Zd\n", tmp);
		mpz_init_set(min,minRef);
	
		mpz_set(x,tmp);
		i=0;
		j=0;
		while(mpz_cmp_ui(x,1) != 0)
		{

			mpz_add_ui(pow,pow,1);
			mpz_mul(x,x,tmp);
			mpz_mod(x,x,N);

			if(mpz_cmp(min,x) == 0)
			{
				gmp_printf("looping pow = %Zd\n", pow);
				break ;
			}
			
			if(mpz_cmp(min,x) > 0)
			{
				mpz_set(min, x);
				gmp_printf("Min = %Zd et ", min);				
				gmp_printf("pow = %Zd\n", pow);				
			}

			i++ ;		
			if (i == 10000000)
			{
				gmp_printf("On en est a pow = %Zd\n", pow);
				//gmp_printf("x = %Zd\n", x);
				i=0;
				j++;
				if(j >= 10)
				{
					gmp_printf("Jumping to next...\n");
					break ;
				}
			}
		}
		gmp_printf("... Ok pour x=%Zd et pow = %Zd\n\n", tmp, pow);
	}
	return 0;
}
