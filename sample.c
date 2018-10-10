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
            
            
    int c;

	FILE *fileR;
	//fileR = fopen(inFile, "r");	
    fileR = fopen(inFile,"r");     
    
    //char token[1024];
    
    int bigArrSize = 4000;        
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
        
        line[strlen(line) - 1] = '\0';
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
      
    int x;        

    /*
    printf("\n\nprinting from array\n");  
    
    for(x=0; x<wordsArrayIndex; x++){
    
        printf("%s,", wordsArray[x]);        
        printf("%d\n", x);      
    }
    */ 
 
    //printf("Total Count of Words %d", wordsArrayIndex);    
    
    int numOfWords = wordsArrayIndex;
    int numOfMaps = numMaps; 
   
    int numOfWordsPerMap = 0; 
    int numOfWordsInLastMap = 0;    

    int multiply = numOfWords*numOfMaps;     
    
    if((numOfWords%numOfMaps)!=0){
        numOfMaps--;     
    }

    numOfWordsPerMap = numOfWords/numOfMaps; 
    numOfWordsInLastMap = numOfWordsPerMap;     
        

    //means the number of words is not equally divided among the maps     
    if(multiply != numOfWords){
        numOfWordsInLastMap = numOfWords%numOfMaps; 
    }
    
    /*
    printf("\nNumber of maps: %d", numOfMaps+1); 
    printf("\nNumber of words per map: %d", numOfWordsPerMap); 
    printf("\nNumber of words in last map: %d", numOfWordsInLastMap); 
    */ 
    
    processesMap(numOfWords, numOfMaps, numOfWordsPerMap, numOfWordsInLastMap, bigArr); 
        
   	return 0; 
	
}

void processesMap(int numOfWords, int numOfMaps, int numOfWordsPerMap, int numOfWordsInLastMap, char **bigArr){

    printf("\nin Maps function\n"); 
    
    /*
    printf("\nIn method"); 
    printf("\nNumber of words in maps: %d", numOfWordsPerMap); 
    printf("\nNumber of words in last map: %d", numOfWordsInLastMap); 
    printf("\n\nprinting from array\n");  
    
    int x; 
    for(x=0; x<numOfWords; x++){
    
        printf("%s,", wordsArray[x]);        
        printf("%d\n", x);      
    }
    */ 
    
    int x; 
    int y=0; 
    
    int endIndex = numOfWordsPerMap; 
    
    //printf("%d\n\n", endIndex);    
    
    const char* message_0;    
  
    const int SIZE = 750000; 
  
    /* name of the shared memory object */
    const char* name = "OS"; 
  
    /* shared memory file descriptor */
    int shm_fd; 
  
    /* pointer to shared memory obect */
    void* ptr;     
        
    //separate data 
    for(x=0; x<numOfMaps; x++){
        
        if(x==0){
        /* create the shared memory object */
        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 
  
        /* configure the size of the shared memory object */
        ftruncate(shm_fd, SIZE); 
   
        /* memory map the shared memory object */
        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); 
        }
        else{
            shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 
  
            //configure the size of the shared memory object
            ftruncate(shm_fd, SIZE);             
        }        
        
        for(y; y<endIndex; y++){
            message_0 = strdup(bigArr[y]); 
          
            char *space = " "; 
            strcat(message_0,space);          
          
            sprintf(ptr, "%s", message_0); 
            ptr += strlen(message_0); 

            //printf("%d ",y); 
            //printf("%s", message_0);
          
        }
       
        y=endIndex; 
        endIndex += numOfWordsPerMap; 
    }
    
    endIndex = y + numOfWordsInLastMap; 
    
    //we have to fill the last map in differently
    if((numOfWordsInLastMap != numOfWordsPerMap) && numOfWordsInLastMap != 0){             
        for(y; y<endIndex; y++){
              message_0 = strdup(bigArr[y]); 
              
              char *space = " "; 
              strcat(message_0,space);          
          
              sprintf(ptr, "%s", message_0); 
              ptr += strlen(message_0);               
                  
        }
    }
    
    processesShuffle(numOfWords);     
   
    return;    
    
}

void processesShuffle(int numOfWords){
     
    printf("\nEntered shuffle\n");     
    
    /* shared memory file descriptor */
    int shm_fd; 
  
    /* pointer to shared memory obect */
    void *ptr;   
    
    /* name of the shared memory object */
    const char* name = "OS"; 
    
    const int SIZE = 750000;   
            
    //reading from new shared memory object 
    shm_fd = shm_open(name, O_RDONLY, 0666); 
   
  	//also in order to memory map the shared memory object
    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); 
  
    /* read from the shared memory object */
    //printf("%s", (char*)ptr); 
            
    char *readMessage = (char*)ptr; 
    //readMessage = (char*)ptr; 
    
    //printf("%s\n", readMessage); 
    //printf("%d\n", strlen(readMessage)); 
    //printf("%c\n", readMessage[0]);     
    
    int bigArrSize = strlen(readMessage);        
    char **bigArray = (char**)malloc(bigArrSize);     
    
      
    //printf("Reading from memory\nMessage:\n%s\n", readMessage); 
   
    //printf("before dup string"); 
    
    char *duplicateString = strdup(readMessage);
    
    //printf("Duplicate String:\n%s", duplicateString);     

    char *tokenize; 
    
    tokenize = strtok(duplicateString, " "); 
    
    int indexOfArr = 0;     

    printf("\n"); 
    while(tokenize!= NULL){
         
        //printf("Tokenize: %s\n", tokenize); 
        
        bigArray[indexOfArr] = (char*) malloc(sizeof(tokenize)); 
        bigArray[indexOfArr] = strdup(tokenize);
        
        indexOfArr++; 
        
        tokenize = strtok(NULL, " "); 
    
    }
    
    int x=0; 
    
    /*
    printf("\nPrinting out of bigArray\n"); 
    for(x; x<indexOfArr; x++){
        printf("%s\n", bigArray[x]);     
    }
    */ 
    
    int sizeWords=(indexOfArr/2)+1;
        
    mergeSort(bigArray, 0, indexOfArr-1, sizeWords);
    
    FILE *fileW = fopen("output.txt", "w");
    if (fileW == NULL)
    {
	   printf("Error opening file!\n");
	   exit(1);
	}        
   
    x=0; 
    //printf("\nPrinting out of bigArray\n"); 
    for(x; x<indexOfArr; x++){
        //printf("%s\n", bigArray[x]);  
        fprintf(fileW, "%s\n", bigArray[x]);   
    
    }
    
    reduce(bigArray); 
      
  
    /* remove the shared memory object */
    shm_unlink(name);

}

void reduce(char **bigArray){



}


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









