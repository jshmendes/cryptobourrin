#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	unsigned int i,j,k,end;
	unsigned char buf[672];
	unsigned char tabbigramme[255][255][100];  
	unsigned char rc;


	fprintf(stderr, "hello world !\n");

	for(i=0; i<255 ; i++)
		for(j=0; j<255 ; j++)
			for(k=0; k<100 ; k++)
				tabbigramme[i][j][k]=0;

	fprintf(stderr, "init passed\n");

	FILE *fp = fopen("04-blue-block.txt","r");
	
	if(fp==NULL)
	{
		fprintf(stderr, "Erreur à l'ouverture du fichier\n");
		return EXIT_FAILURE;
	}	
	
	for(i=0; (i<672&&(rc = getc(fp))!=0x00); i++)
	{
		buf[i] = rc ;	
	}
	end = i;
	
	for(i=0; i<end; i++)
	{		
		tabbigramme[buf[i]][buf[i+1]][0]++;
	}

	for(i=0; i<0x80;i++)
	{
		for(j=0; j<0x80;j++)
		{
			if(	0!=tabbigramme[i][j][0] )		
				fprintf(stdout, "tabbigramme[%c][%c] = %d\n", (i>0x1f)?(char)i:0x20,(j>0x1f)?(char)j:0x20, tabbigramme[i][j][0]);
		}	
	}

	return 0;
}
