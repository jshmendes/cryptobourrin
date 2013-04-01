#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>


int main(int argc, char *argv[])
{
	unsigned int i,j,k;
	mpz_t arr, tmp,temp;
	
	mpz_t tab[10];
	unsigned char   pow[10] ;
	
	if(argc >=10  && argc == 1)
	{
		printf("usage :\n\t ./arr nb1 nb2 nb3 .. nb9 (Pas plus de 9 elements) ");
		return 0 ;
	}
	
	k = argc-1;

	printf("k = %d, 1<<k = %d \n", k, 1<<k);
	
	mpz_init_set_ui(arr,1);
	mpz_init_set_ui(tmp,1);
	mpz_init_set_ui(temp,1);
	
	for(i = 0 ; i < k ; i++)
	{
		pow[i] = 1 ;
		mpz_init_set_str(tab[i],argv[i+1],10);
		gmp_printf(" tab[%d] = %Zd\n",i, tab[i]);
	}

	
	for(i = 0 ; i < 1<<k ; i++)
	{
	
		mpz_init_set_str(arr,"1",10);
		mpz_init_set_str(tmp,"1",10);
		for(j = 0 ; j < k ; j++)
		{
			if(i%(1<<(j)) == 0 )
				pow[j] = (((pow[j]^1)<<7)>>7);
			//gmp_printf(" tab[%d] = %Zd pow = %d \t ",j, tab[j], pow[j]);
			mpz_pow_ui(tmp,tab[j],pow[j]);
			mpz_mul(arr,arr,tmp);
		}	
		
		gmp_printf("%04d : arr = %Zd\n",i,arr);
	}
	
	return 0 ;

}
