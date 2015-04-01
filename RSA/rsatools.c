#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>

int main(int argc, char *argv[])
{
	mpz_t a,b,c;
	int base = 0 ;
	mpz_t tmpb;
	mpz_init(a);mpz_init(b);mpz_init(c);mpz_init(tmpb);

	if(argc != 5)
	{		
		fprintf(stderr, "usage:\n\trsatools hex/dec e P Q\n\n");
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
		fprintf(stderr, "usage:\n\trsatools hex/dec e P Q\n\n");
	}

	mpz_set_str(a,argv[2],base);	
	mpz_set_str(b,argv[3],base);	
	mpz_set_str(c,argv[4],base);	

	gmp_printf("e   is %Zd\n",a);
	gmp_printf("P   is %Zd\n",b);
	gmp_printf("Q   is %Zd\n",c);

	mpz_mul(tmpb,b,c);
	gmp_printf("N   is %Zd\n",tmpb);

	mpz_sub_ui(c,c,1);
	mpz_sub_ui(b,b,1);		

	mpz_mul(b,b,c);
	gmp_printf("Phi is %Zd\n",b);
	mpz_invert(c,a,b);
	gmp_printf("d   is %Zd\n",c);
	mpz_clear (b);
	mpz_clear (a);
	mpz_clear (c);
	mpz_clear (tmpb);
	return ;
}
