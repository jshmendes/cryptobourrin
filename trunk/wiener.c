#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>

#include "tools.h"


int main(int argc, char *argv[])
{
	int j,i,iteration, base;
	mpz_t a,b;
	mpz_t f,tmp,tmpb,r1,r2,x;
	mpz_t tab[10];
	mpz_t arr[256];
	mpz_t k,l,m,t,delta,B;
	mpz_init(k);mpz_init(l);mpz_init(f);
	mpz_init(m);mpz_init(t);
	mpz_init(r1);mpz_init(r2);
	mpz_init(delta);mpz_init(B);
	mpz_init(a);mpz_init(b);mpz_init(tmp);mpz_init(tmpb);

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

	gmp_printf("e   is %Zd\n",a);
	gmp_printf("N   is %Zd\n",b);

	mpz_set(tmp,a);
	mpz_set(tmpb,b);

	//f = N + 1 - 2sqrt(N)
	mpz_sqrt(k,b);
	mpz_mul_ui(l,k,2);
	mpz_add_ui(k,b,1);
	mpz_sub(f,k,l);

	j=cfrac(a,f);
   	find_k_d(a,b,j);
   	mpz_set(a,tmp);				
	mpz_set(b,tmpb);
	mpz_set(a,tmp);

	for(i=0; i < j+1; i++)
	{
		if(mpz_cmp_ui(karr[i],0) != 0)		
		{
			mpz_mul(k,darr[i],a);
			mpz_sub_ui(l,k,1);
			mpz_fdiv_q(t, l,karr[i]);

			//delta	= (b-t+1)^2-4*b
			mpz_sub(k, b,t);
			mpz_add_ui(B, k,1);
			mpz_mul(k,B,B);
			mpz_mul_ui(l,b, 4);
			mpz_sub(delta, k,l);
		
			if(mpz_cmp_ui(delta, 0) < 0)
				continue;	
			mpz_sqrt(k,delta);

			mpz_sub(l,B,k);
			mpz_fdiv_q_ui(r1,l,2); 

			mpz_add(l,k,B);
			mpz_fdiv_q_ui(r2,l,2); 

			mpz_mul(tmp, r1,r2);

			if(mpz_cmp(b,tmp) ==0)
			{
				fprintf(stdout, "Wiener's attack worked !\n");
				gmp_printf("P   is %Zd \n",r1);
				gmp_printf("Q   is %Zd\n",r2);

				mpz_sub_ui(r1,r1,1);
				mpz_sub_ui(r2,r2,1);		

				mpz_mul(r1,r1,r2);
				gmp_printf("Phi is %Zd\n",r1);
				mpz_invert(r2,a,r1);
				gmp_printf("d   is %Zd\n",r2);
				mpz_clear (b);
				mpz_clear (a);
				mpz_clear (tmp);
				mpz_clear (tmpb);
				mpz_clear (r1);
				mpz_clear (r2);
				mpz_clear (k);
				mpz_clear (l);
				mpz_clear (f);


				return ;
			}
		}
	}

	fprintf(stdout, "Wiener's attack failed !\n");
	mpz_sqrt(tmpb,b);
	mpz_sqrt(tmp,tmpb);

	mpz_fdiv_q_ui(r1,tmp,3);

	gmp_printf("\td > 1/3*N^{1/4} = %Zd \n",r1); 

	mpz_clear (b);
	mpz_clear (a);
	mpz_clear (tmp);
	mpz_clear (tmpb);
	mpz_clear (r1);
	mpz_clear (r2);
	mpz_clear (k);
	mpz_clear (l);
	mpz_clear (f);
}
