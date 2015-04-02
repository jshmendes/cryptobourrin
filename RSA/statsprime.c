#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, char * argv[])
{
	FILE *fp;
	char * line1 = NULL;
	char * line2 = NULL;
	size_t len = 0;
	ssize_t read;
	char *a, *b;
	unsigned long res;
	unsigned int array[10];
	int i = 0 ;
	int counter = 0;
	mpz_t p;
	mpz_t q;
	mpz_t n;
	mpf_t avr;
	mpf_t pf,qf,sqrt,min,max;
	mpf_t avrsqrt, minsqrt, maxsqrt;
	mpz_init(p);
	mpz_init(q);
	mpz_init(n);

	mpf_init(avr);
	mpf_init(pf);
	mpf_init(qf);
	mpf_init(max);
	mpf_init(min);
	mpf_init(sqrt);
	mpf_init(avrsqrt);
	mpf_init(minsqrt);
	mpf_init(maxsqrt);

	array[0] = 0;
	array[1] = 0;
	array[2] = 0;
	array[3] = 0;
	array[4] = 0;
	array[5] = 0;
	array[6] = 0;
	array[7] = 0;
	array[8] = 0;
	array[9] = 0;
	
	mpf_set_ui(min,2);
	mpf_set_ui(minsqrt,2);
	mpf_set_ui(avr,0);
	mpf_set_ui(avrsqrt,0);		

	//open file
	fp=fopen(argv[1], "r");
	if(fp== NULL)
	{
		return 1;
	}
	while ((read = getline(&line1, &len, fp)) != -1) 
	{
		if ((read = getline(&line2, &len, fp)) == -1){
			return 1;
		}
		counter++;
		//first get last char of lines
		mpz_set_str(p,line1,16);
		mpz_set_str(q,line2,16);
		mpz_sub_ui(q,q,1);
		mpz_sub_ui(p,p,1);
		mpz_mod_ui(q,q,1024);
		mpz_mod_ui(p,p,1024);
		mpz_mul(n,p,q);
		mpz_mod_ui(n,n,1024);
		res = mpz_get_ui(n);
		mpz_set_str(p,line1,16);
		mpz_set_str(q,line2,16);
		mpz_mul(n,q,p);
		mpf_set_z(qf,q);
		mpf_set_z(pf,p);

		if(mpf_cmp(qf,pf)<0)
			mpf_div(pf,pf,qf);
		else
			mpf_div(pf,qf,pf);

		if (mpf_cmp(min,pf)>0 )
				mpf_set(min,pf);
		else 
			if (mpf_cmp(pf,max)>0)
				mpf_set(max,pf);
		mpf_add(avr,avr,pf);
		
		mpf_set_z(pf,p);	
		mpz_sqrt(n,n);
		mpf_set_z(sqrt,n);
		if (mpf_cmp(qf,pf)<0)
			mpf_div(pf,qf,sqrt);
		else
			mpf_div(pf,pf,sqrt);
		
		mpf_add(avrsqrt,avrsqrt,pf);

		if (mpf_cmp(minsqrt,pf)>0 )
				mpf_set(minsqrt,pf);
		else 
			if (mpf_cmp(pf,maxsqrt)>0)
				mpf_set(maxsqrt,pf);

		gmp_printf("%.*Zf\n", 10, pf);
		
		if(res==0)
		{
			array[0]++;
			continue;
		}
	
		if((res%512)==0)
		{
			array[1]++;
			continue;
		}
		if((res%256)==0)
		{
			array[2]++;
			continue;
		}

		if((res%128)==0)
		{
			array[3]++;
			continue;
		}
		if((res%64)==0)
		{
			array[4]++;
			continue;
		}
		if((res%32)==0)
		{
			array[5]++;
			continue;
		}
		if((res%16)==0)
		{
			array[6]++;
			continue;
		}

		if((res%8)==0)
		{
			array[7]++;
			continue;
		}

		if((res%4)==0)
		{
			array[8]++;
			continue;
		}
	}

	for(i=0; i<10;i++)
		fprintf(stdout, "%8d ", array[i]);
	fprintf(stdout,"\n");
	mpf_div_ui(avr,avr,counter);
	mpf_div_ui(avrsqrt,avrsqrt,counter);
	gmp_printf("P/Q average ratio = %Ff (counter = %d)\n",  avr, counter);
	gmp_printf("P/Q min = %.*Ff max = %.*Ff\n", 20, min,20 , max);
	gmp_printf("Q/Sqrt(N) average ratio = %Ff \n", avrsqrt);
	gmp_printf("P/Sqrt(N) min = %.*Ff max = %.*Ff\n", 20, minsqrt,20 , maxsqrt);
	fclose(fp);
       if (line1)
           free(line1);
       if (line2)
	   free(line2);
       exit(EXIT_SUCCESS);

return 0;
}
