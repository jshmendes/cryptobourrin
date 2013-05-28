/*************************************************************************
 *  Compilation:  gcc PollardRho.c -lgmp -o PollardRho
 *  Execution:    ./PollardRho N
 *  
 *  Factor N using the Pollard-Rho method.
 *
 *  % ./PollardRho 44343535354351600000003434353
 *  149
 *  329569479697
 *  903019357561501
 *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>
    

	int  rho(mpz_t *N, mpz_t *ret)
	{
		mpz_t div,c,x,xx,tmp,two,one;
		
		mpz_init_set_str(div, "1", 10);
		mpz_init_set_str(c, "10001", 16);
		mpz_init_set_str(x, "231234123417", 10);
		mpz_init_set_str(xx, "1", 10);
		
		mpz_init_set_str(tmp, "1", 10);
		mpz_init_set_str(one, "1", 10);
		mpz_init_set_str(two, "2", 10);
		
		mpz_set(xx,x);
		
		mpz_mod_ui(tmp,*N,2);
		if(mpz_cmp_ui(tmp,0) == 0)
		{
			mpz_set(*ret,two);
			return 1;
		}
		//gmp_printf("Before while div = %Zd, cmp = %d\n",div,mpz_cmp_ui(div,1));

			
		do {
			mpz_mul(x,x,x);
			mpz_mod(x,x,*N);
			mpz_add(x,x,c);
			mpz_mod(x,x,*N);
			
			mpz_mul(xx,xx,xx);
			mpz_mod(xx,xx,*N);
			mpz_add(xx,xx,c);
			mpz_mod(xx,xx,*N);
			mpz_mul(xx,xx,xx);
			mpz_mod(xx,xx,*N);
			mpz_add(xx,xx,c);
			mpz_mod(xx,xx,*N);
			
			mpz_sub(tmp,x,xx);
			
			mpz_gcd(div,tmp,*N);
			//gmp_printf("div = %Zd, cmp = %d\n",div,mpz_cmp_ui(div,1));
		} while(mpz_cmp_ui(div,1)==0);
		
		mpz_set(*ret,div);
		return 1;
	
	}
    
	int factor(mpz_t *N)
	{
		mpz_t div;
		mpz_t ret;
		mpz_init_set_str(div,"1",10);
		mpz_init_set_str(ret,"1",10);
		if(mpz_cmp_ui(*N,1) == 0 )
			return 0;
		if(mpz_probab_prime_p(*N,20))
		{	
			gmp_printf("%Zd\n",*N);
			return 1;
		}
		int i = rho(N,&ret);
		mpz_set(div,ret);
//		gmp_printf("ok factor bis %Zd\n",div);	
		factor(&div);
		mpz_div(*N,*N,div);
//		gmp_printf("ok factor ter %Zd\n",*N);	
		factor(N);
//		printf("out \n");
	}
	
    int main(int argc, char *argv[]) 
	{
		//N = new BigInteger(args[0]);
		//
		if(argc != 2)
		{
			printf("usage :\n\t <program> integer\n\n");
			return 0;
		}

		mpz_t N ;
		mpz_init(N);
		mpz_init_set_str(N,argv[1], 10);
		printf("Ok ready for factor\n");	
        	factor(&N);
    }
