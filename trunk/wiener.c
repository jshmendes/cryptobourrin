#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>

#include "tools.h"



int main(int argc, char *argv[])
{
	int base;
	mpz_t a,b;
	mpz_init(a);mpz_init(b);

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

	if (isprime(a) == 2) 
		fprintf(stdout, "e is prime\n");
	else
		fprintf(stdout, "e is not prime\n");


	if (isprime(b) == 2) 
	{
		fprintf(stdout, "N is prime... FAIL !\n");
		return 0;
	}
	else
		fprintf(stdout, "N is not prime\n");

	if (isperfectsquare(b) == 1) 
	{
		fprintf(stdout, "N is a perfect square... FAIL !\n");
		return 0;
	}



	if(gcd(a,b))
		fprintf(stdout, "e and N are relatively prime\n");

	return wiener(a, b);

}
