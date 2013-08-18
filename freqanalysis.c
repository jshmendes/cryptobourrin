#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void anagramme(unsigned char *ligne)
{


}


int compareInt(const void *a, const void *b)
{
	int i = *(int *) a;
	int j = *(int *) b;
	if( i> j) return 1;
	if( i< j) return -1;
	if( i==j) return 0;
}

int main(int argc, char * argv[])
{
	unsigned char buffer[1000000];
	unsigned char buf[1000000];
	unsigned int freqAnalysis[0xFF];
	unsigned int i,j,tmp,ref,k,l,m,n;
	unsigned char rc;
	double pc = 0;

	if(argc != 2)
	{
		fprintf(stderr, "usage : \n\t\tfreq <filepath>\n\n");
		return ;
	}
	FILE *fp = NULL;
	fp = fopen(&argv[1][0],"r");
//	fp = fopen("../sstic/sstic.tar.gz-chiffree","b");
//	FILE *fp = fopen("../anssi/anssi.santo.fr/04-blue-block.txt","r");

	if(fp==NULL)
	{
		fprintf(stderr, "Erreur à l'ouverture du fichier\n");
		return EXIT_FAILURE;
	}	
	
	for(i=0; i<0x80;i++)
	{
		freqAnalysis[i]=0;
	}
	j=0;
    
	fprintf(stderr, "Top\n");

	for(i=0; (i<212 && (rc = getc(fp))!=0x00); i++)
	{
		fprintf(stderr, " j = %d \n", j);
		buffer[i] = rc ;	
		freqAnalysis[rc]++;
		j++;
	}

	for(i=0; i<0xFF;i++)
	{
		if(freqAnalysis[i])		
			fprintf(stdout, "freqAnalysis[%02x/%c] = %d\n", i, (i>0x1f)?(char)i:0x20, freqAnalysis[i]);
	}


	fprintf(stdout, "\n");
	tmp = 0;
	for(i=0x30; i<0x3a; i++)
	{
		tmp+=freqAnalysis[i];
	}
	fprintf(stdout, "freqAnalysis[CHIFFRE] = %d\n",tmp);

	tmp = 0;
	for(i=0x41; i<0x5b;i++)
	{
		tmp+=freqAnalysis[i];
	}
	fprintf(stdout, "freqAnalysis[MAJUSCULE] = %d\n",tmp);
	fprintf(stdout, "\n");
	for(i=0x61; i<0x7b;i++)
	{
		if(freqAnalysis[i]+freqAnalysis[i-0x20])		
		fprintf(stdout, "freqAnalysis[%02x/%c] = %d\n", i, (i>0x1f)?(char)i:0x20, freqAnalysis[i]+freqAnalysis[i-0x20]);
	}

	fprintf(stdout, "freqAnalysis[0x20] = %d\n", freqAnalysis[i]+freqAnalysis[0x20]);
	fprintf(stdout, "freqAnalysis[0x0A] = %d\n", freqAnalysis[i]+freqAnalysis[0x0A]);

	fprintf(stdout, "\n");
	fprintf(stdout, "\n");

	for(i=0x61; i<0x7b;i++)
	{
		fprintf(stdout, "freqAnalysis[%02x/%c] = %d\n", i, (i>0x1f)?(char)i:0x20, freqAnalysis[i]);
	}
/*	fprintf(stdout, "\n");
 	qsort(&freqAnalysis[0x61], 0x19, sizeof(unsigned int),compareInt);

	for(i=0x00; i<0x80;i++)
	{
		fprintf(stdout, "freqAnalysis[%02x/%c] = %d\n", i, (i>0x1f)?(char)i:0x20, freqAnalysis[i]);
	}
*/
	if(0)
	{
		//bigramme
		for(i=0; i<672;i++)
		{}


		//q & u
		int q[40][200];
		k=0;
		for(i=0; (i<674); i++)
		{
			if('q' == buffer[i] || 'Q' == buffer[i])
			{
				fprintf(stderr, "find q at %d \n", i);
				q[k][0]=i;
				m = 1 ;
				for(l=0; l<674; l++)
					if('u' == buffer[l] || 'U' == buffer[l]) 
							q[k][m++]= i-l;
				k++;
			}	
		}

	/*
		for(i = 0 ; i < 7 ; i++)
		{
			fprintf(stdout, "q[%3d] : ", q[i][0]);	
			for(l = 1 ; l < 31 ; l++)
				fprintf(stdout, "%4d,", q[i][l]);
			fprintf(stdout, "\n");	
		}
	*/
		fprintf(stdout, "\n");	
		for(i = 0 ; i < 7 ; i++)
		{
			for(l = 1 ; l < 31 ; l++)
			{
				j=q[i][l];
				tmp = 0 ;
				for(k = 0 ; k < 7 ; k++)
				{
					for(m = 1 ; m< 31 ; m++)
						if(j == q[k][m]) tmp++;
				}
				if (tmp > 1) fprintf(stdout, "%4d [%d],",j,tmp); 
			}
		}
		fprintf(stdout, "\n");	


		// Ponctuation et espace

		k=0;
		for(i=0; (i<674); i++)
		{
			if(',' == buffer[i] || '.' == buffer[i] || ';' == buffer[i] || ':' == buffer[i] || '-' == buffer[i])
			{
				fprintf(stderr, "find Ponctuation at %d \n", i);
				q[k][0]=i;
				m = 1 ;
				for(l=0; l<674; l++)
					if(' ' == buffer[l] || 0x0a == buffer[l]) 
							q[k][m++]= i-l;
				k++;
			}	
		}

		fprintf(stdout, "\n");	
		for(i = 0 ; i < 7 ; i++)
		{
			for(l = 1 ; l < 31 ; l++)
			{
				j=q[i][l];
				tmp = 0 ;
				for(k = 0 ; k < 7 ; k++)
				{
					for(m = 1 ; m< 31 ; m++)
						if(j == q[k][m]) tmp++;
				}
				if (tmp > 1) fprintf(stdout, "%4d [%d],",j,tmp); 
			}
		}
		fprintf(stdout, "\n");	
	}
	return 0;
}
