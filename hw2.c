#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1000000            //max size of heap
int MinHeap[MAX_SIZE];              //for printing in ascending order  (smallest num at root)
int MaxHeap[MAX_SIZE];              //for printing in descending order (biggest num at root)
int MinHeapSize = 0;                //size of min heap (for printing)
int MaxHeapSize = 0;                //size of max heap (for printing)
int fileflag = 0;                   //0 if creating new file, else 1

int ProcessCommand(char buffer[], int *component);                      //process command line and save it on commandtype
void InsertHeap(int heap[], int component, int size, int mode);        //insert to heap (mode 1 is min heapify, 2 is max heapify)
void PrintHeap(int heap[], int size, int mode);                         //print heap to hw2_result.txt (mode 1 is ascend, 2 is descend)
void swap(int* a, int* b);                                              //swap elements
void MinHeapify(int minheap[], int size, int root);
void MaxHeapify(int maxheap[], int size, int root);

int main(int argc, char *argv[])
{
    FILE* fp;
    char buffer[18];                     //max size of buffer is sizeof("INSERT 2^32")
    int commandtype;                    //saves what command should be performed 
                                        //(0 is insert to heap, 1 is print in ascend, 2 is print in descend, 3 is component)
    int component;                      //saves component for heap addition
    clock_t start, end;
    double duration;

    start = clock();
    if (argc != 2){
        printf("usage: ./hw 2 input_filename\n");
        return 0;
    }
    else if(!(fp = fopen(argv[1], "r"))){
        printf("The input file does not exist.\n");
        return 0;
    }
    else {
        while (fgets(buffer, 18, fp)){
            commandtype = ProcessCommand(buffer, &component);
            switch (commandtype){
                case 0:                            //insert
                    InsertHeap(MinHeap, component, MinHeapSize, 1);
                    InsertHeap(MaxHeap, component, MaxHeapSize, 2);
                    break;
                case 1:                            //print in ascending order
                    PrintHeap(MaxHeap, MaxHeapSize, 1);
                    fileflag = 1;
                    break;
                case 2:                            //print in descending order
                    PrintHeap(MinHeap, MinHeapSize, 2);
                    fileflag = 1;
                    break;
            }
        }
    }
    fclose(fp);
    end = clock();
    duration = (double)(end - start)/CLOCKS_PER_SEC;
    printf("output written to hw2_result.txt.\n");
    printf("running time : %f seconds\n", duration);
    return 0;
}
int ProcessCommand(char buffer[], int *component)
{
    char insert[] = "INSERT";
    char ascend[] = "ASCEND";
    char descend[] = "DESCEND";                     //all command strings
    char *ptr; 

    ptr = strtok(buffer, " \n");                    //tokenize command to check for insert
    if (!strcmp(ptr, insert)){                      //if command is insert
        ptr = strtok(NULL, "\n");
        *component = atoi(ptr);                     //save component
        return 0;
    }
    else if (!strcmp(ptr, ascend)){                 //if command is ascend
        return 1;
    }
    else if (!strcmp(ptr, descend)){                //if command is descend
        return 2;
    }
    return 3;
}
void InsertHeap(int heap[], int component, int size, int mode){
   int parent;
   int i = size;

   switch(mode){
        case 1:                                             //insert to min heap
            while(i > 0){
                parent = (i - 1)/2;
                if (component >= heap[parent]){
                    heap[i] = component;
                    MinHeapSize++;
                    return;
                }
                else {
                    heap[i] = heap[parent];
                    i = parent;
                }
            }
            heap[0] = component;                            //if inserting for the first time
            MinHeapSize++;
            break;
        case 2:                                             //insert to max heap
            while(i > 0){
                parent = (i - 1)/2;
                if (component <= heap[parent]){
                    heap[i] = component;
                    MaxHeapSize++;
                    return;
                }
                else {
                    heap[i] = heap[parent];
                    i = parent;
                }
            }
            heap[0] = component;                            //if inserting for the first time
            MaxHeapSize++;
            break;
   }
}                  

//  input : heap[] (array representing heap), size (heap size), mode (ascend or descend)
//  malloc a same size array, copy all elements in, heap sort and append to file, free array
void PrintHeap(int heap[], int size, int mode){
    int i;
    int* PrintArray = (int*)malloc(sizeof(int)*size);       //malloc to save space
    FILE* fp;

    if (!fileflag)
        fp = fopen("result.txt", "w");                      //if writing to file for the first time
    else fp = fopen("result.txt", "a");                     //otherwise append
    for(i = 0; i < size; i++)
        PrintArray[i] = heap[i];                            //copied heap into PrintArray
    switch (mode){
        case 1:                                             //heap sort on max heap
            for (i = size-1; i >= 0; i--){
                swap(&PrintArray[0], &PrintArray[i]);
                MaxHeapify(PrintArray, i, 0);
            }
            for (i = 0; i < size; i++){
                fprintf(fp, "%d ", PrintArray[i]);
            }
            fprintf(fp, "\n");
            break;
        case 2:                                             //heap sort on min heap
            for (i = size-1; i >= 0; i--){
                swap(&PrintArray[0], &PrintArray[i]);
                MinHeapify(PrintArray, i, 0);
            }
            for (i = 0; i < size; i++){
                fprintf(fp, "%d ", PrintArray[i]);
            }
            fprintf(fp, "\n");
            break;
    }
    fclose(fp);
    free(PrintArray);
}
void swap(int* a, int* b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void MinHeapify(int minheap[], int size, int i){
    int left = i*2+1;
    int right = i*2+2;
    int min = i;
    if (left < size && minheap[left] < minheap[min])
        min = left;
    if (right < size && minheap[right] < minheap[min])
        min = right;
    if (min != i){
        swap(&minheap[i], &minheap[min]);
        MinHeapify(minheap, size, min);
    }
}
void MaxHeapify(int maxheap[], int size, int i){
    int left = i*2+1;
    int right = i*2+2;
    int max = i;
    if (left < size && maxheap[left] > maxheap[max])
        max = left;
    if (right < size && maxheap[right] > maxheap[max])
        max = right;
    if (max != i){
        swap(&maxheap[i], &maxheap[max]);
        MaxHeapify(maxheap, size, max);
    }
}