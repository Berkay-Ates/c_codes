#include<stdio.h>
#include<stdlib.h>

#define SIZE 10

void merge(int* values,int left, int middle, int right);
void mergeSort(int* values, int left,int right);
void printArray(int* arr,int size);


int main(){

    int values[10] = {1,5,10,2,6,9,8,7,3,4};

    printArray(values,SIZE);
    mergeSort(values,0,SIZE-1);
    printArray(values,SIZE);

 return 0; 
}

void printArray(int* array,int size){
    int i= 0;

    for(i=0;i<size;i++){
        printf(" %d ",array[i]);
    }
    printf("\n");
}

void merge(int* values,int left, int middle, int right){

    int* valcpy = (int*) malloc(sizeof(int)*SIZE);
    int i,j,k;
    i=left;
    j=middle+1;
    k=0;
    while (i<=middle && j<=right){
        
        if(values[i] <= values[j])
            valcpy[k] = values[i++];
        else
            valcpy[k] = values[j++];
        
        k++;
    }


    while(i<=middle)
        valcpy[k++] = values[i++];
    
    while(j<right)
        valcpy[k++] = values[j++];

    i=0;
    while(i<k){
        values[i+left] = valcpy[i];
        i++;
    }
}

void mergeSort(int* values, int left,int right){
    int middle = (left + right) / 2;
    if(left<right){
        
        mergeSort(values,left,middle);
        mergeSort(values,middle+1,right);
        merge(values,left,middle,right);
    }
}