#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000000            //max size of heap
int MaxHeap[MAX_SIZE];              //for printing in descending order (biggest num at root)
int MinHeap[MAX_SIZE];              //for printing in ascending order  (smallest num at root)
int MaxHeapSize = 0;                //size of max heap (for printing)
int MinHeapSize = 0;                //size of min heap (for printing)

int processcommand(char buffer[], int *component);  //process command line and save it on commandtype
void InserttoMaxHeap(int component);                   //insert to max heap
void InserttoMinHeap(int component);                   //insert to min heap
void PrintMaxHeap(int size);                        //print max heap
void PrintMinHeap(int size);                        //print min heap
int main(int argc, char *argv[])
{
    FILE* fp;
    char buffer[9];                     //max size of buffer is sizeof("INSERT #")
    int commandtype;                    //saves what command should be performed 
                                        //(0 is insert to heap, 1 is print in ascend, 2 is print in descend, 3 is component)

    int component;                      //saves component for heap addition

    if (argc != 2){
        printf("usage: ./hw 2 input_filename\n");
        return 0;
    }
    else if(!(fp = fopen(argv[1], "r"))){
        printf("The input file does not exist.\n");
        return 0;
    }
    else {
        while (fscanf(fp,"%s", buffer) != EOF){
            commandtype = processcommand(buffer, &component);
            switch (commandtype){
                case 0:                            //insert
                    break;
                case 1:                            //print in ascending order
                    PrintMinHeap(MinHeapSize);
                    break;
                case 2:                            //print in descending order
                    PrintMaxHeap(MaxHeapSize);
                    break;
                default:                           //we got the component (insert)
                    InserttoMaxHeap(component);
                    InserttoMinHeap(component);
                    break;
            }
        }
    }
    return 0;
}
int processcommand(char buffer[], int *component)
{
    char insert[] = "INSERT";
    char ascend[] = "ASCEND";
    char descend[] = "DESCEND";                     //all command strings
    int num;                                        //saves component

    if (!strcmp(buffer, insert)){                      //if command is insert
        return 0;
    }
    else if (!strcmp(buffer, ascend)){                 //if command is ascend
        return 1;
    }
    else if (!strcmp(buffer, descend)){                //if command is descend
        return 2;
    }
    else *component = atoi(buffer);
    return 3;
}
void InserttoMaxHeap(int component){
    printf("insert %d to max heap\n", component);
}                  
void InserttoMinHeap(int component){
    printf("insert %d to min heap\n", component);
}
void PrintMaxHeap(int size){
    printf("printing descending order\n");
}
void PrintMinHeap(int size){
    printf("printing ascending order\n");
}