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

	mpz_t x,N, pow,tmp, min ;
	mpz_init_set_str(x,"2", 16);	
	mpz_init_set_str(tmp,"100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 16);	
	mpz_init_set_str(N,argv[1], 16);
	mpz_init_set_str(pow,"1",10);
	mpz_init_set_str(min,"10000000000",10);
	unsigned int i = 1;
	unsigned int j = 1;

	gmp_printf("N = %Z0x\n", N);

	mpz_sub_ui(tmp,tmp,1);

	while(1)
	{
		mpz_add_ui(tmp,tmp,1);
		gmp_printf("x = %Zd\n", tmp);
		mpz_mul(x,tmp,tmp);
		i=0;
		j=0;
		while(mpz_cmp_ui(x,1) != 0)
		{
			mpz_add_ui(pow,pow,1);
			mpz_mul(x,x,tmp);
			mpz_mod(x,x,N);

			if(mpz_cmp(min,x) > 0)
			{
				mpz_set(min, x);
				gmp_printf("Min = %Zd et ", min);				
				gmp_printf("pow = %Zd\n", pow);				
			}

			if(mpz_cmp(min,x) == 0)
			{
				gmp_printf("looping pow = %Zd\n", pow);
				break ;
			}

			i++ ;		
			if (i == 10000000)
			{
				gmp_printf("On en est a pow = %Zd\n", pow);
				i=0;
				j++;
				if(j >= 1000)
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
