#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>
	
int main(int argc, char *argv[]) 
{

	if(argc !=3)
	{
		fprintf(stdout,"usage:\n\t./bruteforceD N E \n\n");
		return 0;
	}

	mpz_t E,N, two,tmp,D ;
	mpz_init_set_str(D,"3", 10);	
	mpz_init_set_str(tmp,"1", 16);	
	mpz_init_set_str(E,argv[2], 16);
	mpz_init_set_str(N,argv[1], 16);

	mpz_init_set_str(two,"2",10);
	mpz_powm(two,two,E,N);
	gmp_printf("\n%Zd\n\n",N);
	int i = 1;

	gmp_printf("E = %Z0x\n", E);
	gmp_printf("N = %Z0x\n", N);
	gmp_printf("D = %Z0x\n", D);
	gmp_printf("t = %Z0x\n", two);
	while(1)
	{
		
		mpz_powm(tmp,two,D,N);
		if(mpz_cmp_ui(tmp,2) == 0)
		{
			gmp_printf("\n\nD = %Zd\n\n", D);
//			return ;
		}
		i++;
		if (i == 1000000)
		{
			gmp_printf("\non en est a D = %Zd", D);
			i =0;
		}
		
		mpz_add_ui(D,D,2);
	}

}
