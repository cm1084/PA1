#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <stdbool.h>
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <sys/types.h>


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
    	
    char *wordcount = "wordcount"; 	
    char *sort = "sort"; 
    
    char *procs = "procs"; 
    char *threads = "threads";     
    	
    if(strcmp(app,wordcount) ==0){
        printf("app is wordcount "); 
        
        if(strcmp(impl,procs) ==0){
            printf("do wordcount with processes\n");         
        }
        
        else if(strcmp(impl,threads) ==0){
            printf("do wordcount with threads\n");         
        }   
    }	 
    
    else if(strcmp(app,sort) ==0){
        printf("app is sort ");
        
        if(strcmp(impl,procs) ==0){
            printf("do integer sort with processes\n");
        }
        
        else if(strcmp(impl,threads) ==0){
            printf("do integer sort with threads\n");        
        }    
    }
    
    else{
        printf("ERROR: incorrect input, please enter either wordcount or sort for --app");    
    }
            
            
	//reading from input file character by character and writing to output file
    int c;

	FILE *fileR;
	//fileR = fopen(inFile, "r");	
    fileR = fopen("word_input.txt","r");     
    
    //char token[1024];
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
        
        sentence = strtok(line, " .,;:!-"); 
        
        while(sentence != NULL){
          
           wordsArray[wordsArrayIndex] = malloc(sizeof(sentence)); 
           wordsArray[wordsArrayIndex] = strdup(sentence);        
           
           //printf("%s ", sentence); 
           sentence = strtok(NULL, " "); 
                
           ++wordsArrayIndex;         
            
            
        }                       
    }
    
    /*   
    int x;        

    printf("\n\nprinting from array\n");  
    
    for(x=0; x<wordsArrayIndex; x++){
    
        printf("%s ", wordsArray[x]);        
            
    }
    */
    
    
    //1) now add word to an index of wordsArray and malloc for each index to the size of sentence 

    //2) now do math to figure out how many words go per map
    
    //add a certain number of indices to each map depending on word count and num of maps 
    
    
        
   	return 0; 
	
	
    /*	
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
	*/ 


}








