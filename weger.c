#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>

mpz_t farr[100000];
int cfrac(mpz_t a,mpz_t b)
{
	int i;
	mpz_t q,tmp,r;
	mpz_init(q);
	mpz_init(tmp);
	mpz_init(r);
		
	for(i=0;i<100000;i++)
	  mpz_init(farr[i]);
    i=-1;
	while(mpz_cmp_ui(b,0)>0)
	{
	  i++;
	  mpz_fdiv_q(q,a,b);
	  mpz_set(farr[i],q);
	  mpz_mul(tmp,q,b);
	  mpz_sub(r,a,tmp);
	  mpz_set(a,b);
	  mpz_set(b,r);
	}

	mpz_clear(q);
	mpz_clear(r);
	mpz_clear(tmp);

	return i;
}

mpz_t karr[10000],darr[10000];
void find_k_d(mpz_t a,mpz_t b,int j)
{
	int k,i,m=1;
	mpz_t x,y,z,tmp;
	mpz_init(y);
	mpz_init(z);
	mpz_init(tmp);
    mpz_set(karr[0],farr[0]);
    mpz_set_str(darr[0],"1",10);
	for(i=1;i<=j;i++)
	{
		mpz_set(z,farr[i-1]);
        mpz_set(y,farr[i]);
        mpz_init_set_str(x,"1",10);
		for(k=i;k>1;k--)
		{
			mpz_set(tmp,x);
	        mpz_set(x,y);
	        mpz_mul(z,z,y);
	        mpz_add(y,z,tmp);
	        mpz_set(z,farr[k-2]);
		}
	     mpz_set(karr[m],x);
	     mpz_set(darr[m],y);
	     m++;
	}

	mpz_clear (y);
	mpz_clear (z);
	mpz_clear (tmp);
	mpz_clear (x);

}


mpz_t phi;
void find_phi(mpz_t e,int n)
{
	int i;
	mpz_t tmp,tmp2;
	mpz_init(tmp);
	mpz_init(tmp2);
	for(i=1;i<=n;i++)
	{
		mpz_mul(tmp,e,darr[i]);
		mpz_sub_ui(tmp,tmp,1);
		mpz_mod(tmp2,tmp,karr[i]);
		if(mpz_cmp_ui(tmp2,0)==0)
		{
		  mpz_fdiv_q(phi,tmp,karr[i]);
		  break;
		}	  
	}   

	mpz_clear (tmp);
	mpz_clear (tmp2);
}

mpz_t p,q;
void fact(mpz_t n)
{
	mpz_t md,tmp,tmp2,tmp3;
	mpz_init(tmp);
	mpz_init(tmp2);
	mpz_init(tmp3);
	mpz_init(md);
	mpz_add_ui(tmp,n,1);
	mpz_sub(tmp,tmp,phi);
	mpz_mul(tmp2,tmp,tmp);
	mpz_mul_ui(tmp3,n,4);
	mpz_sub(tmp3,tmp2,tmp3);
	if(mpz_perfect_square_p(tmp3)!=0)
	 {
		  mpz_sqrt(tmp3,tmp3);
		  mpz_add(p,tmp3,tmp);
		  mpz_mod_ui(md,p,2);
		  if(mpz_cmp_ui(md,0)==0)
			  mpz_fdiv_q_ui(p,p,2);  
		  mpz_sub(q,tmp3,tmp);
		   mpz_mod_ui(md,q,2);	
	      if(mpz_cmp_ui(md,0)==0)
	          mpz_fdiv_q_ui(q,q,2);
	      if(mpz_cmp_ui(p,0)>0)
			  mpz_fdiv_q(q,n,p);
		  else if(mpz_cmp_ui(q,0)>0)
		      mpz_fdiv_q(p,n,q);
	  }
	mpz_clear (tmp);
	mpz_clear (tmp2);
	mpz_clear (tmp3);
	mpz_clear (md);

}




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

//mpz_set_str(a,"25411171",10);
//mpz_set_str(b,"27962863",10);
//mpz_set_str(a, "60728973",10);
//mpz_set_str(b, "160523347",10);
//mpz_set_str(a, "1908717316858446782674807627631",10);
//mpz_set_str(b, "2746482122383906972393557363644983749146398460239422282612197",10);
//mpz_set_str(a,"3594320245477",10);
//mpz_set_str(b,"7978886869909",10); 
//mpz_set_str(b,"C836AC35487C4DF89786C40E6F708777679DCC8D3AA3E1D33AC420D5B30531E478E6FD137B26D5AAF22A0701561281AC010DC3CFBFCFD5573CCA5FFAB2BFD4CF",16);
//mpz_set_str(a,"802EF8CC586F35606E6B1B04FEF635D50DE2EABE9507ADA29662517F60517821E3C764AF09C2D7CD9DF0467250F83437443EA2BEA2BC719333351F280CE9E4F9",16);
//mpz_set_str(a,"4603830998027",10); 
//mpz_set_str(b,"7978886869909",10); 
/*
mpz_set_str(a,"921318991",10); 
mpz_set_str(b,"7978886869909",10); 
mpz_set_str(a,"263",10); 
mpz_set_str(b,"7978886869909",10); 
*/

	mpz_set(tmp,a);
	mpz_set(a_orig,a);
	mpz_set(tmpb,b);

	mpz_sqrt(k,b);
/*	mpz_mul_ui(l,k,2);
	mpz_add_ui(k,b,1);
	mpz_sub(f,k,l);
*/
	int num;
	int den;
	double num_x,den_x;
	mpf_t tri,ter;
	mpf_t f_x;
	mpf_init2(f_x, 4096);	mpf_init2(ter, 4096);	mpf_init2(tri,4096);
	mpf_set_z(f_x,b);

/*
i=8	karr[i] = 136879,
	darr[i] = 176264
i=9	karr[i] = 137091,
	darr[i] = 176537
i=10	karr[i] = 273970,
	darr[i] = 352801
i=11	karr[i] = 685031,
	darr[i] = 882139
i=12	karr[i] = 7809311,
	darr[i] = 10056330
*/	

	for(num = 100; num < 150 ; num++)
	{
	fprintf(stderr,"num = %3d\n",num);
	for(den = num+1; den <= 150 ; den++)
	{
		mpz_set(b,tmpb);
		mpz_set(a,a_orig);
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

//		mpz_set_str(f, "2285786424189769091284159", 10); 
//		mpz_set_str(a, "3558458718976746753830603",10);

		mpz_mul_ui(  a,  a,factor);
		j=cfrac(a,f);
	    find_k_d(a,f,j);
	   	mpz_set(a,a_orig);				

//		find_phi(a,j);  

		mpz_set(b,tmpb);
//		gmp_printf("b   = %Zd\n",b);
//		gmp_printf("tmpb= %Zd\n",tmpb);
//		gmp_printf("a   = %Zd\n",a);

		//mpz_set_str(karr[0],"89468507233879006742852",10);
//		mpz_set_str(darr[0],"120180801986365356473843",10);
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
					fprintf(stderr, "Wiener's attack worked\n");
					gmp_printf("P   is %Zd \n",r1);
					gmp_printf("Q   is %Zd\n",r2);

					mpz_sub_ui(r1,r1,1);
					mpz_sub_ui(r2,r2,1);		

					mpz_mul(r1,r1,r2);
					gmp_printf("Phi is %Zd\n",r1);
					mpz_invert(r2,a,r1);
					gmp_printf("d   is %Zd\n",r2);
					gmp_printf("e   is %Zd\n",a);
					gmp_printf("N   is %Zd\n",b);
					return ;
				}
			}
		}

	}}

	fprintf(stderr, "Wiener's attack failed\n");
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																												mpz_sqrt(tmpb,b);
	mpz_sqrt(tmp,tmpb);

	mpz_fdiv_q_ui(r1,tmp,3);

	gmp_printf("\td > 1/3*N^{1/4} = %Zd \n\n",r1); 

}
