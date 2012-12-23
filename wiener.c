#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>


mpz_t farr[100000];
int cfrac(mpz_t a,mpz_t b)
{
	mpz_t q,tmp,r,dum0;int i;
	mpz_init(q);
	mpz_init(tmp);
	mpz_init(r);
	mpz_init_set_str(dum0,"0",10);
	
	for(i=0;i<100000;i++)
	  mpz_init(farr[i]);
    i=-1;
	while(mpz_cmp(b,dum0)>0)
	{
	  i++;
	  mpz_fdiv_q(q,a,b);
	  mpz_set(farr[i],q);
	  mpz_mul(tmp,q,b);
	  mpz_sub(r,a,tmp);
	  mpz_set(a,b);
	  mpz_set(b,r);

	 }
//     fprintf(stdout, "coucou c'est moi : %d\n",i);
	 return i;
 }

mpz_t karr[10000],darr[10000];
void find_k_d(mpz_t a,mpz_t b,int j)
{
	mpz_t x,y,z,tmp;int k,i;int m=1;
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
}


mpz_t phi;
void find_phi(mpz_t e,int n)
{
	  mpz_t tmp,tmp2,dum1,dum0;int i;
	  mpz_init(tmp);
	  mpz_init(tmp2);
	  mpz_init_set_str(dum0,"0",10);
	  mpz_init_set_str(dum1,"1",10);
	  for(i=1;i<=n;i++)
	  {
		  mpz_mul(tmp,e,darr[i]);
		  mpz_sub(tmp,tmp,dum1);
		  mpz_mod(tmp2,tmp,karr[i]);
		  if(mpz_cmp(tmp2,dum0)==0)
			{
				  mpz_fdiv_q(phi,tmp,karr[i]);
				  break;
			}	  
	  }   
}
mpz_t p,q;
void fact(mpz_t n)
{
	mpz_t dum0,dum1,md,dum2,tmp,tmp2,tmp3,dum4;
	mpz_init_set_str(dum1,"1",10);
	mpz_init_set_str(dum2,"2",10);
	mpz_init_set_str(dum4,"4",10);
	mpz_init_set_str(dum0,"0",10);
	mpz_init(tmp);
	mpz_init(tmp2);
	mpz_init(tmp3);
	mpz_init(md);
	mpz_add(tmp,dum1,n);
	mpz_sub(tmp,tmp,phi);
	mpz_mul(tmp2,tmp,tmp);
	mpz_mul(tmp3,n,dum4);
	mpz_sub(tmp3,tmp2,tmp3);
	if(mpz_perfect_square_p(tmp3)!=0)
	 {
		  mpz_sqrt(tmp3,tmp3);
		  mpz_add(p,tmp3,tmp);
		  mpz_mod(md,p,dum2);
		  if(mpz_cmp(md,dum0)==0)
			  mpz_fdiv_q(p,p,dum2);  
		  mpz_sub(q,tmp3,tmp);
		   mpz_mod(md,q,dum2);	
	      if(mpz_cmp(md,dum0)==0)
	          mpz_fdiv_q(q,q,dum2);
	      if(mpz_cmp(p,dum0)>0)
			  mpz_fdiv_q(q,n,p);
		  else if(mpz_cmp(q,dum0)>0)
		      mpz_fdiv_q(p,n,q);
	  }
}






int main()
{
	mpz_t a,b;int j,i,iteration;mpz_t f,tmp,tmpb,dum0,dum1,dum2,dum4,r1,r2,x;
	mpz_t tab[10];
	mpz_t arr[256];
	mpz_t k,l,m,t,delta,B;
	mpz_init(k);mpz_init(l);mpz_init(f);
	mpz_init(m);mpz_init(t);
	mpz_init(r1);mpz_init(r2);
	mpz_init(delta);mpz_init(B);
	mpz_init(a);mpz_init(b);mpz_init(tmp);mpz_init(tmpb);
	mpz_init_set_str(dum0,"0",10);
	mpz_init_set_str(dum1,"1",10);
	mpz_init_set_str(dum2,"2",10);
	mpz_init_set_str(dum4,"4",10);
/*	printf("\nEnter the value of encryption key e ");
	gmp_scanf("%Zd",&a);
	printf("\nEnter the value of modulus N ");
	gmp_scanf("%Zd",&b);
*/

//mpz_set_str(a,"25411171",10);
//mpz_set_str(b,"27962863",10);
//mpz_set_str(a, "60728973",10);
//mpz_set_str(b, "160523347",10);
//mpz_set_str(a, "1908717316858446782674807627631",10);
//mpz_set_str(b, "2746482122383906972393557363644983749146398460239422282612197",10);
mpz_set_str(a,"3594320245477",10);
mpz_set_str(b,"7978886869909",10); 
mpz_set_str(b,"C836AC35487C4DF89786C40E6F708777679DCC8D3AA3E1D33AC420D5B30531E478E6FD137B26D5AAF22A0701561281AC010DC3CFBFCFD5573CCA5FFAB2BFD4CF",16);
mpz_set_str(a,"802EF8CC586F35606E6B1B04FEF635D50DE2EABE9507ADA29662517F60517821E3C764AF09C2D7CD9DF0467250F83437443EA2BEA2BC719333351F280CE9E4F9",16);
//mpz_set_str(a,"4603830998027",10); 
//mpz_set_str(b,"7978886869909",10); 
/*
mpz_set_str(a,"921318991",10); 
mpz_set_str(b,"7978886869909",10); 
mpz_set_str(a,"263",10); 
mpz_set_str(b,"7978886869909",10); 
*/
	gmp_printf("gcd(N,e) is  %Zd\n",tmp);

	gmp_randstate_t state;	
	gmp_randinit_default (state);

	mpz_init_set(arr[1],a);
	mpz_sqrt(arr[0],arr[1]);

	mpz_init_set(x,a);
	i=1;
	while(i)
	{	
/*	
		mpz_urandomm (x, state, arr[0]);
		mpz_mul_ui(x,x,2);
		mpz_add_ui(x,x,1);
		mpz_set(a, x);
*/
		mpz_set(tmp,a);
		mpz_set(tmpb,b);
	
		mpz_sqrt(k,b);
		mpz_mul_ui(l,k,2);
		mpz_add_ui(k,b,1);
		mpz_sub(f,k,l);

		j=cfrac(a,f);
	   	find_k_d(a,b,j);
	   	mpz_set(a,tmp);				
		find_phi(a,j);  
		mpz_set(b,tmpb);

		mpz_set(b,tmpb);
		mpz_set(a,tmp);

		mpz_sqrt(tmpb,b);
		mpz_sqrt(tmp,tmpb);

		mpz_fdiv_q_ui(r1,tmp,3);

	/*	gmp_printf("1/3*N^{1/4} = %Zd \n\n",r1); 
		gmp_printf("N is  %Zd \n",b); 
		gmp_printf("e is  %Zd \n\n",a); */
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
		i=0;
	}
	fprintf(stdout, "Wiener's attack failed\n");
}
