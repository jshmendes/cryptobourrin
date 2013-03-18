#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>


int main(int argc, char *argv[])
{
	int i,j,k;
	mpz_t arr, tmp,temp;
	
	mpz_t tab[10];
	byte   pow[10];
	
	if(argc >=10  && argc == 1)
	{
		printf("usage :\n\t ./arr nb1 nb2 nb3 .. nb9 (Pas plus de 9 elements) ");
		return 0 ;
	}
	
	
	k = argc-1;
	
	mpz_init_set(arr,"1",10);
	mpz_init_set(tmp,"1",10);
	mpz_init_set(temp,"1",10);
	
	for(i = 0 ; i < 10 ; i++)
	{
		pow[i] = 0 ;
		mpz_init_set(tab[i],argv[i+1],10);
	}

	
	for(i = 0 ; i < 2**k ; i++)
	{
	
		mpz_set(arr,"1",10);
		for(j = 0 ; j < k ; j++)
		{
			mpz_pow_ui(tmp,tab[j],(j<i)?(((pow[j]^1)h<<7)>>7):0);
			mpz_mul(arr,arr,tmp);
		}	
		
		gmp_printf("%04d : arr = %Zd\n",i,arr);
	}
	
	return 0 ;

}
