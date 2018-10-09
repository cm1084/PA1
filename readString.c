#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char **argv)
{
	char *inFile = (char*) malloc (20 * sizeof(char));

	strcpy(inFile, argv[1]);


	FILE *fileR;
    fileR = fopen(inFile, "r");     
   
    //char token[1024];
   
    int bigArrSize = 1000;        
   
    char **bigArr = (char**)malloc(bigArrSize*sizeof(char*));    
   
    char line[10000];
    char *sentence;
 
    char *wordsArray[10000];        
       
    if(fileR == NULL){
        printf("ERROR: Unable to open file \n");
        return 0;
    }
     
    int count = 1;  
   
    int wordsArrayIndex = 0;  
   
    while(fgets(line,sizeof(line),fileR)){
 
        //printf("Line: %d: ", count++);        
        //printf("%s\n", line);    
        line[strlen(line) - 1] = 0;
        sentence = strtok(line, " .,;:!-");
       
        while(sentence != NULL){

	   // check if its full of non-alpha and non-num

	   int y=0;
	   int check=0;
	   for (y=0; y<strlen(sentence); y++)
	   {
		 if (isalnum(sentence[y]) == 0)
			check++;
	   }
 
	   if (check == strlen(sentence))
		{
			sentence = strtok(NULL, " .,;:!-");
			continue;
		}

	   // skip
           
           bigArr[wordsArrayIndex] = (char*)malloc(sizeof(sentence));
           bigArr[wordsArrayIndex] = strdup(sentence);
           
           //printf("%s ", sentence);
           sentence = strtok(NULL, " .,;:!-");
               
           wordsArrayIndex++;        
           
           if(wordsArrayIndex == bigArrSize){
                bigArrSize = bigArrSize*2;
                bigArr = (char**)realloc(bigArr, bigArrSize*sizeof(char*));            
           }
           
        }                        
    }
   
     	
	int i=0;
	FILE *fileW = fopen("output.txt", "w");
		if (fileW == NULL)
		{
 		   printf("Error opening file!\n");
 		   exit(1);
		}
	
	for (i=0; i<wordsArrayIndex; i++)
	{
		fprintf(fileW, "%s\n", bigArr[i]);
	}

	printf ("%s\n", bigArr[79]);	

	return 0;
}








