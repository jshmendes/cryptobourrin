mpz_t farr[100000];
mpz_t karr[10000],darr[10000];
mpz_t phi;

/*
 cfrac : 
 Decomposing a/b in continued fraction
*/
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