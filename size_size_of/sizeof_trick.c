#include<stdio.h>
#include<stdlib.h>
 
int main(){

    int arraySize ;
    int i =0;
    int* array;

    printf("printf size of your array: ");
    scanf("%d",&arraySize);
    array =(int*) malloc(sizeof(int)*arraySize);

    printf("given size of array: %d\n",arraySize);
    printf(" size of array by sizeof: %d\n",sizeof(array[0]));
    printf("array size by sizeof:%d\n",(sizeof(array)/(sizeof(array[0]))));
 

    while(i<arraySize){

        scanf("%d",(array+i));
        i++;
    }

    while(i>0){
        printf("%d. element of array : %d\n",i, array[i-1]);
        i--;
    }
    free(array);
    return 0;
}