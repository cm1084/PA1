#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void merge(char** input, int l, int m, int r, int size)
{
   	int i, j, k;
   	int n1 = m - l + 1;
	int n2 =  r - m;
    
	char **L = (char**)malloc(size*sizeof(char*));
	char **R = (char**)malloc(size*sizeof(char*));
 
 
    	for (i = 0; i < n1; i++)
        	L[i] = input[l + i];
    	for (j = 0; j < n2; j++)
        	R[j] = input[m + 1+ j];
 
 
    	i = 0; 
    	j = 0; 
    	k = l; 
    
    	while (i < n1 && j < n2)
    	{
		if ( isdigit(L[i][0]) > 0 && isdigit(R[j][0]) == 0)
		{
			input[k] = L[i];
       			i++;
			k++;
			continue;
		}
		else if ( isdigit(R[j][0]) > 0 && isdigit(L[i][0]) == 0)
		{
			input[k] = R[j];
        	   	j++;
			k++;
			continue;
		}		
		

		if (isalnum(L[i][0]) == 0 && isalnum(R[j][0]) > 0)
		{
			input[k] = L[i];
       			i++;
			k++;
			continue;
		}
		else if ( isalnum(R[j][0]) == 0 && isalnum(L[i][0]) > 0)
		{
			input[k] = R[j];
        	   	j++;
			k++;
			continue;
		}


	 
		if (strcmp(L[i], R[j]) < 0)
       		{
        		input[k] = L[i];
       			i++;
      		}
        	else
        	{
       		       	input[k] = R[j];
        	   	j++;
       		}
            		
                	k++;
	
	}
 
   	 
   	 while (i < n1)
   	 {
   	     input[k] = L[i];
   	     i++;
   	     k++;
   	 }
 	
   	
   	 while (j < n2)
   	 {
   	     input[k] = R[j];
   	     j++;
   	     k++;
   	 }
}

void mergeSort(char** input, int l, int r, int size)
{
    if (l < r)
    {

        int m = l+(r-l)/2;
 
        mergeSort(input, l, m, size);
        mergeSort(input, m+1, r, size);
 
        merge(input, l, m, r, size);
    }
}

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
	   y=0;
	   while( sentence[y]) {
    		  sentence[y]=tolower(sentence[y]);
    		  y++;
   		}
           
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
	
	int sizeWords=(wordsArrayIndex/2)+1;
	mergeSort(bigArr, 0, wordsArrayIndex-1, sizeWords);
	
	for (i=0; i<wordsArrayIndex; i++)
	{
		fprintf(fileW, "%s\n", bigArr[i]);
	}

	//printf ("%s\n", bigArr[79]);	

	return 0;
}








