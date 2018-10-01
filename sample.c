#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

		

int main (int argc, char *argv[])
{
	// number of inputs has to be equal to 13, 
	char *app = (char*) malloc (20 * sizeof(char));
	char *impl = (char*) malloc (20 * sizeof(char));
	int numMaps = 0;
	int numReduce = 0;
	char *inFile = (char*) malloc (20 * sizeof(char));
	char *outFile = (char*) malloc (20 * sizeof(char));

	

	int i=0;
	int countDashArg = 0;
	if (argc != 13)
	{
		printf("Not enough arguments\n");
		exit(0);
	}

	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "--app") == 0)
		{
			strcpy(app, argv[i+1]);
			countDashArg++;
		}
		if (strcmp(argv[i], "--impl") == 0)
		{
			strcpy(impl, argv[i+1]);
			countDashArg++;
		}
		if (strcmp(argv[i], "--maps") == 0)
		{
			numMaps = atoi(argv[i+1]);
			countDashArg++;
		}
		if (strcmp(argv[i], "--reduces") == 0)
		{
			numReduce = atoi(argv[i+1]);
			countDashArg++;
		}
		if (strcmp(argv[i], "--input") == 0)
		{
			strcpy(inFile, argv[i+1]);
			countDashArg++;
		}
		if (strcmp(argv[i], "--output") == 0)
		{
			strcpy(outFile, argv[i+1]);
			countDashArg++;
		}
	}
	
	if (countDashArg != 6)
	{
		printf("Not enough key arguments\n");
		exit(0);
	}

	printf("--app %s --impl %s --maps %d --reduces %d --input %s --output %s\n", 
		app, impl, numMaps, numReduce, inFile, outFile);
	
	FILE *fileW = fopen(outFile, "w");
		if (fileW == NULL)
		{
 		   printf("Error opening file!\n");
 		   exit(1);
		}

	int c;
	FILE *fileR;
	fileR = fopen(inFile, "r");
	if (fileR) {
  	  while ((c = getc(fileR)) != EOF)
  	   {
		fprintf(fileW, "%c", c);	
	   }
 	   
           fclose(fileW);
	   fclose(fileR);
	}


}








