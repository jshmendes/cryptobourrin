#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>
	
int main(int argc, char *argv[]) 
{

	if(argc !=2)
	{
		fprintf(stdout,"usage:\n\t./hextodec number\n\n");
		return 0;
	}

	mpz_t N ;
	mpz_init(N);
	mpz_init_set_str(N,argv[1], 16);


	gmp_printf("\n%Zd\n\n",N);

}
