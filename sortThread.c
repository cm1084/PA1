#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 

    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  

    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 

    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 

        int m = l+(r-l)/2; 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 
struct map_struct {
	int *given;
	int *result;
};


// Thread function to generate sum of 0 to N
void* sum_runner(void* arg)
{
	struct map_struct *arg_struct =
			(struct map_struct*) arg;
	
	arg_struct->result=(int*)malloc(10*sizeof(int));
  	int i = 0;
  	for( i = 0; i < 10; i++){
		arg_struct->result[i] = arg_struct->given[i];
		//printf("%d\n", arg_struct->result[i]);
  	}
	
  	mergeSort(arg_struct->result, 0, 9);

	pthread_exit(0);
}

void* reduce_runner(void* arg)
{
	struct map_struct *arg_struct =
			(struct map_struct*) arg;
	
	arg_struct->result=(int*)malloc(10*sizeof(int));
  	int i = 0;
  	for( i = 0; i < 10; i++){
		arg_struct->result[i] = arg_struct->given[i];
		//printf("%d\n", arg_struct->result[i]);
  	}

	pthread_exit(0);
}

int main(int argc, char **argv)
{
	int *bigArr=(int*)malloc(40*sizeof(int));
  	int i = 0;
  	for(i = 0; i < 50 ; i++){
    		bigArr[i] = rand() % 100;
  	}

	// assume number of maps is 4
	struct map_struct mapper[4];
	// Thread ID:
	pthread_t tids[4];

	int start=0;
	int end=10;
	int j=0;
	for (i = 0; i < 4; i++) {
		mapper[i].given=(int*)malloc(10*sizeof(int));
		for (j=0; j<end; j++)
		{
			mapper[i].given[j] = bigArr[start];
			start++;
			//printf("%d\n", mapper[i].given[j]);
		}

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, sum_runner, &mapper[i]);
	}

	// Wait until thread is done its work
	for (i = 0; i < 4; i++) {
		pthread_join(tids[i], NULL);	
	}

	/*---- map phase ends here */

	// Shuffle Phase, where the sorting is done, 
	int *resultArr=(int*)malloc(40*sizeof(int));
	int index=0;
	for (i = 0; i < 4; i++) {

		for (j=0; j<end; j++)
		{
			resultArr[index] = mapper[i].result[j];
			index++;
		}	
	}

	printf("After map returns\n");


	for (i=0; i<40; i++)
	{
		printf("%d ", resultArr[i]);
	}

	printf("\n\nAfter the shufftle\n");
	// sort the array here

	mergeSort(resultArr, 0, 39);

	// sort the array ends
	
	for (i=0; i<40; i++)
	{
		printf("%d ", resultArr[i]);
	}
       
	printf("\n");

	/*---- reduce phase starts ----*/
	// assume number of reduce is 4
	
	// assume number of maps is 4
	struct map_struct reducer[4];
	// Thread ID:
	pthread_t redutids[4];
	start = 0;
	for (i = 0; i < 4; i++) {
		reducer[i].given=(int*)malloc(10*sizeof(int));
		for (j=0; j<end; j++)
		{
			reducer[i].given[j] = resultArr[start];
			start++;
			//printf("%d\n", mapper[i].given[j]);
		}

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&redutids[i], &attr, reduce_runner, &reducer[i]);
	}

	// Wait until thread is done its work
	for (i = 0; i < 4; i++) {
		pthread_join(redutids[i], NULL);	
	}


	int *finalCombine=(int*)malloc(40*sizeof(int));

	index=0;
	for (i = 0; i < 4; i++) {

		for (j=0; j<end; j++)
		{
			finalCombine[index] = reducer[i].result[j];
			index++;
		}	
	}


	printf("\n\nAfter the reduce\n");
	
	for (i=0; i<40; i++)
	{
		printf("%d ", finalCombine[i]);
	}

	printf("\n");
	
	return 0;
}








