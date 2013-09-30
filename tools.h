

int isprime(mpz_t x)
{
	return mpz_probab_prime_p(x,20);
}


int gcd(mpz_t e, mpz_t N)
{
	mpz_t gcd;
	mpz_init(gcd);	

	mpz_gcd(gcd,e,N);
	int ret = mpz_cmp_ui(gcd,1)?1:0;
	
	mpz_clear(gcd);

	return ret;
}


int isperfectsquare(mpz_t N)
{
	mpz_t tmp;
	mpz_init(tmp);	

	mpz_sqrt(tmp,N);
	mpz_mul(tmp,tmp,tmp);

	int ret = 	mpz_cmp(tmp,N)?0:1;

	mpz_clear(tmp);

	return ret;
}


void basic(mpz_t a, mpz_t b)
{
	mpz_t tmp,temp;
	mpz_init(tmp);mpz_init(temp);

	if (isprime(a) == 2) 
		fprintf(stdout, "e is prime\n");
	else
		fprintf(stdout, "e is not prime\n");


	if (isprime(b) == 2) 
	{
		fprintf(stdout, "N is prime... FAIL !\n");
	}
	else
		fprintf(stdout, "N is not prime\n");

	mpz_mod_ui(tmp,b,2);
	if(0==mpz_cmp_ui(tmp,1))
		fprintf(stdout, "Phi(N) is a multiple of 4\n");

	mpz_mod_ui(tmp,b,6);
	if(0==mpz_cmp_ui(tmp,5))
		fprintf(stdout, "Phi(N) is a multiple of 12\n");

	mpz_mod_ui(tmp,b,4);
	if(0==mpz_cmp_ui(tmp,3))
		fprintf(stdout, "Phi(N) is a multiple of 8\n");

	mpz_mod_ui(tmp,b,12);
	if(0==mpz_cmp_ui(tmp,11))
		fprintf(stdout, "Phi(N) is a multiple of 12\n");

	mpz_mod_ui(tmp,b,24);
	if(0==mpz_cmp_ui(tmp,11))
		fprintf(stdout, "Phi(N) is a multiple of 24\n");

	mpz_mod_ui(tmp,b,24);
	if(0==mpz_cmp_ui(tmp,23))
		fprintf(stdout, "Phi(N) is a multiple of 24\n");

/*	mpz_mod_ui(tmp,b,65537);
	gmp_printf("N = %Zd mod 65537\n",tmp);

	mpz_mod_ui(tmp,b,1901);
	gmp_printf("N = %Zd mod 65537\n",tmp);
*/

//431 809 2621 7829 209785669799 150794606190194112168401 417467109300720063964829

	mpz_set_str(temp,"209785669799",10);
	 mpz_mod(tmp, b,temp);
gmp_printf(" N mod %2Zd = %Zd \n", temp, tmp);


	mpz_set_str(temp,"150794606190194112168401",10);
	 mpz_mod(tmp, b,temp);
gmp_printf(" N mod %2Zd = %Zd \n", temp, tmp);

	mpz_set_str(temp,"417467109300720063964829",10);
	 mpz_mod(tmp, b,temp);
gmp_printf(" N mod %2Zd = %Zd \n", temp, tmp);
	mpz_set_str(temp,"2",10);	
	int i = 0;
	int j = 0;
	fprintf(stdout, "000 ");
	for(i = 0 ; i < 20 ; i++)
		fprintf(stdout, "%3d,",i);
	i = 0 ;
	while(i < 400)
	{
		if(i%20 == 0)
			fprintf(stdout,"\n%03d ",j++);	
		mpz_mod(tmp, b,temp);
//		if (!mpz_cmp_ui(tmp,9))
			gmp_printf("%3Zd,",tmp);
		
                //if (!mpz_cmp_ui(tmp, 697))
                //        gmp_printf(" N mod %2Zd = %Zd \n", temp, tmp);
		i++;
		mpz_add_ui(temp,temp,1);
	}

	mpz_mod_ui(tmp,b, 431);
	gmp_printf(" N mod 431 = %Zd \n", tmp);	

       mpz_mod_ui(tmp,b, 809);
        gmp_printf(" N mod 809 = %Zd \n", tmp);
       mpz_mod_ui(tmp,b, 2621);
        gmp_printf(" N mod 2621 = %Zd \n", tmp);
       mpz_mod_ui(tmp,b, 7829);
        gmp_printf(" N mod 7829 = %Zd \n", tmp);


	if (isperfectsquare(b) == 1) 
	{
		fprintf(stdout, "N is a perfect square... FAIL !\n");
	}

	if(gcd(a,b))
		fprintf(stdout, "e and N are relatively prime\n");

	mpz_sub(tmp,b,a);
	mpz_sqrt(temp,b);
	gmp_printf(" sqrt(N) = %Zd \n", temp);
//	mpz_div(temp,tmp,temp);
//	gmp_printf(" (N-e)/sqrt(N) = %Zd \n", temp);

	mpz_clear(tmp);mpz_clear(temp);

}

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


int find_k_d(mpz_t a,mpz_t b,int j)
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

  /*Dujella Formula*/

  mpz_sqrt(y,b);
  mpz_mul(y,y,b);
  mpz_mul_ui(y,y,1000);
  mpz_mul_ui(x,a,4244);
  mpz_div(y,y,x);
  m=0;
  for(i=1; i<j;i+=2)
  {
    mpz_mul(z,karr[i],karr[i+1]);
    if(mpz_cmp(z,y)>0)
    {
	m = i;
	break;
    }
  }
//  if(0!=m)
  	//printf("should be %d / %d\n", m,j); 
  
  mpz_clear (y);
  mpz_clear (z);
  mpz_clear (tmp);
  mpz_clear (x);
  return m;
}


int wiener(mpz_t a, mpz_t b)
{
	int bound,j,i,iteration,iter,den;
	mpz_t f,tmp,tmpb,r1,r2,x;
	mpz_t tab[10];
	mpz_t arr[256];
	mpz_t k,l,m,t,delta,B;
	mpz_init(k);mpz_init(l);mpz_init(f);
	mpz_init(m);mpz_init(t);
	mpz_init(r1);mpz_init(r2);
	mpz_init(delta);mpz_init(B);
	mpz_init(tmp);mpz_init(tmpb);

	//gmp_printf("e   is %Zd\n",a);
	//gmp_printf("N   is %Zd\n",b);

	mpz_set(tmp,a);
	mpz_set(tmpb,b);

	//f = N + 1 - 2sqrt(N)
	mpz_sqrt(k,tmpb);
	mpz_mul_ui(l,k,2);
	mpz_add_ui(k,tmpb,1);
	mpz_sub(f,k,l);
	

	j=cfrac(tmp,f);
   	bound=find_k_d(tmp,tmpb,j);
   	mpz_set(tmp,a);				
	mpz_set(tmpb,b);

        //Dujella Formula
	//k = \frac{N\sqrt{N}}{4.244*E}
	mpz_sqrt(k,tmpb);
	mpz_mul(k,k,tmpb);
	mpz_mul_ui(k,k,1000);
	mpz_div(k,k,tmp);
	mpz_div_ui(k,k,4244);

	//gmp_printf("k = %Zd\n", k);
	//if darr
	for(i=1; i < j; i+=2)
	{
		mpz_mul(l,karr[i],karr[i+1]);
		if(mpz_cmp(l,k) > 0)		
		{
			break;
		}
	}
	
	
	//fprintf(stdout,"Bound = %d, i = %d \n",bound,i);
	{
		if(mpz_cmp_ui(karr[i],0) != 0)		
		{
			//gmp_printf("X / Y  = %Zd / %Zd \n", karr[i], darr[i]);
			mpz_mul(k,darr[i],a);
			mpz_sub_ui(l,k,1);
			mpz_fdiv_q(t,l,karr[i]);

			//delta	= (b-t+1)^2-4*b
			mpz_sub(k, tmpb,t);
			mpz_add_ui(B, k,1);
			mpz_mul(k,B,B);
			mpz_mul_ui(l,tmpb, 4);
			mpz_sub(delta, k,l);
		
			if(mpz_cmp_ui(delta, 0) > 0)
			{		
				mpz_sqrt(k,delta);

				mpz_sub(l,B,k);
				mpz_fdiv_q_ui(r1,l,2); 

				mpz_add(l,k,B);
				mpz_fdiv_q_ui(r2,l,2); 

				mpz_mul(k, r1,r2);

				if(mpz_cmp(tmpb,k) ==0)
				{
					fprintf(stdout, "Wiener's attack worked for i = %d\n", i);
					gmp_printf("P   is %Zd \n",r1);
					gmp_printf("Q   is %Zd\n",r2);

					mpz_sub_ui(r1,r1,1);
					mpz_sub_ui(r2,r2,1);		

					mpz_mul(r1,r1,r2);
					gmp_printf("Phi is %Zd\n",r1);
					mpz_invert(r2,a,r1);
					gmp_printf("d   is %Zd\n",r2);

					mpz_clear (tmp);
					mpz_clear (tmpb);
					mpz_clear (r1);
					mpz_clear (r2);
					mpz_clear (k);
					mpz_clear (l);
					mpz_clear (f);

					exit(0);
				}
			}
		}
	}

//	} /*EO Iteration sur iter */
/*
	//fprintf(stdout, "Wiener's attack failed !\n");
	mpz_sqrt(tmpb,b);
	mpz_sqrt(tmp,tmpb);

	mpz_fdiv_q_ui(r1,tmp,3);

	//gmp_printf("\td > 1/3*N^{1/4} = %Zd \n",r1); 
*/
	mpz_clear (tmp);
	mpz_clear (tmpb);
	mpz_clear (r1);
	mpz_clear (r2);
	mpz_clear (k);
	mpz_clear (l);
	mpz_clear (f);

	return 1;
}

