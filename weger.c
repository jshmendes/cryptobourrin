#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>

#include "tools.h"

int main(int argc, char *argv[])
{
	int j,i,iteration, base;
	mpz_t a,b, a_orig;
	mpz_t f,tmp,tmpb,r1,r2,x;
	mpz_t tab[10];
	mpz_t arr[256];
	mpz_t k,l,m,t,delta,B;
	mpz_init(k);mpz_init(l);mpz_init(f);
	mpz_init(m);mpz_init(t);
	mpz_init(r1);mpz_init(r2);
	mpz_init(delta);mpz_init(B);
	mpz_init(a);mpz_init(a_orig);mpz_init(b);mpz_init(tmp);mpz_init(tmpb);

	unsigned long int factor = 1000000000000000;

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

	mpz_set_str(a,"6055258312152372605476785266317750951108834153931",10);
	mpz_set_str(b,"8133876630876764379064472085871019680113623317877",10);

	mpz_set(tmp,a);
	mpz_set(a_orig,a);
	mpz_set(tmpb,b);

	mpz_sqrt(k,b);
/* 
    mpz_mul_ui(l,k,2);
	mpz_add_ui(k,b,1);
	mpz_sub(f,k,l);
*/
	int num;
	int den;
	double num_x,den_x;
	mpf_t tri,ter;
	mpf_t f_x;
	mpf_init2(f_x, 4096);	mpf_init2(ter, 4096);	mpf_init2(tri,4096);

	for(num = 100; num < 254 ; num++)
	{
		fprintf(stderr,"num = %3d\n",num);
		for(den = 270; den <= 280 ; den++)
		{
			mpf_set_z(f_x,b);
			num_x = (double) 2 + ((double)num/(double)den);
			den_x = num_x/sqrt(1+(double)num/(double)den);
	//		fprintf(stdout," num_x = %f den_x = %f\n", num_x, den_x);
	//		fprintf(stdout," num_x = %f den_x = %f\n", num_x, den_x);
	//		fprintf(stdout,"den_x = %f\n", den_x);
			mpf_set_d(tri,den_x);
	//		gmp_printf("Tri = %.*Ff\n",10,tri);
	//		gmp_printf("f_x = %.*Ff\n",10,f_x);
			mpf_sqrt(f_x,f_x);	
	//		gmp_printf("f_x = %.*Ff\n",10,f_x);
	//		gmp_printf("k   = %Zd\n",k);
			mpf_mul(tri,tri,f_x);
	//		gmp_printf("Tri = %.*Ff\n",10, tri);
			mpf_sub_ui(tri,tri,1);
	//		gmp_printf("Tri = %.*Ff\n",10,tri);
			mpf_set_z(ter,b);
			mpf_sub(ter,ter,tri);
	//		gmp_printf("Ter = %.*Ff\n",10,ter);
			mpf_mul_ui(ter,ter,factor);
			mpz_set_f(f,ter);
	//		mpz_add_ui(f,f,1);
	//		gmp_printf("f   = %Zd\n",f);
	//		gmp_printf("a   = %Zd\n",a);
			mpz_mul_ui(a,a_orig,factor);
			j=cfrac(a,f);
			find_k_d(a,f,j);
			mpz_set(a,a_orig);
			for(i=0; i < j+1; i++)
			{
	//			gmp_printf("i=%d\tkarr[i] = %Zd,\n\tdarr[i] = %Zd\n",i,karr[i],darr[i]);
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
						fprintf(stderr, "attack worked\n");
						gmp_printf("P   is %Zd \n",r1);
						gmp_printf("Q   is %Zd\n",r2);

						mpz_sub_ui(r1,r1,1);
						mpz_sub_ui(r2,r2,1);		

						mpz_mul(r1,r1,r2);
						gmp_printf("Phi is %Zd\n",r1);
						mpz_invert(r2,a_orig,r1);
						gmp_printf("d   is %Zd\n",r2);
						gmp_printf("e   is %Zd\n",a);
						gmp_printf("N   is %Zd\n",b);
						return ;
					}
				}
			}
		}
	}

	fprintf(stderr, "attack failed\n");
    
    mpz_sqrt(tmpb,b);
	mpz_sqrt(tmp,tmpb);

	mpz_fdiv_q_ui(r1,tmp,3);

	gmp_printf("\td > 1/3*N^{1/4} = %Zd \n\n",r1); 

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
