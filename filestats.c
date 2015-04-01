#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	FILE *fp;
	size_t len = 0;
	ssize_t read;
	int a;
	int i = 0 ;
	unsigned int array[256];
	
	for(i=0; i<256 ; i++)
		array[i] = 0;
	
	//open file
	fp=fopen(argv[1], "r");
	if(fp== NULL)
	{
		fprintf(stderr, "Cannot open file in argument\n");
		return 1;
	}
	
    do 
    {
      /*if (i%16==0)
      {
	i=0;
	fprintf(stdout, "\n");
      }*/
      a = fgetc(fp);
      printf("%X ", a);
      array[a]++;
      i++;

    } while(a != EOF);

    a=0;
	
    for(i=0; i<256 ; i++)
    {
	if (i%8==0) fprintf(stdout,"\n %3d :",i);	
	fprintf(stdout," %6d ", array[i]);
	a+=array[i];
    }
       fprintf(stdout,"\nNb total : %d\nOccurence Moyenne : %d\n",a,  a/256);
      
	fclose(fp);
       	exit(EXIT_SUCCESS);

return 0;
}
