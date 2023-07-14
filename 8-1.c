#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void heapify(int arr[], int n, int i){


int biggest = i;
int left = (2*i) +1;
int right = (2*i) +2;
int parent = (i-1)/2;

if(arr[biggest]<arr[left] && left<n){
	biggest = left;
}

if(arr[biggest]<arr[right] && right<n){
	biggest = right;
}

if(biggest!=i){
	swap(&arr[i],&arr[biggest]);
    heapify(arr, n, biggest);
}
	

}


void heapSort(int arr[], int n)
{

for (int i = (n/2)-1; i >= 0; i--){
	heapify(arr,n,i);
}

for (int i = n-1; i >=0; i--){
	swap(&arr[0],&arr[1]);

	heapify(arr, i, 0);
}

}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
int m = (l+r)/2;
int arr1[] = {};
int arr2[] = {};

for (int i=0; i<m; i++){
	arr1[i] = pData[i];
	arr2[i] = pData[(m+1)+i];
}


int arr3[] = {};

int index = 0;
int half = (l+r)/2;
int left = 0;
int right = 0;

int arr1size = sizeof(arr1)/sizeof(arr1[0]);
int arr2size = sizeof(arr2)/sizeof(arr2[0]);

while ((left<half)&&(right<half)){
    if(arr1[left]<arr2[right]){

        arr3[index] = arr1[left];
        index++;
        left++;
	}

    else{
        arr3[index] = arr2[right];
        index++;
        right++;
	}
}


    if(left<half){
        for (int i = left; i<half; i++){
            arr3[index] = arr1[i];
            index++;
        }
    }

    if(right<half){
        for(int i = right; i<half; i++){
            arr3[index] = arr2[i];
            index++;
        }
    }

 extraMemoryAllocated += ((arr1size * sizeof(int))+(arr2size * sizeof(int)));

}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}