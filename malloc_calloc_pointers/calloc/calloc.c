#include<stdio.h>
#include<stdlib.h>
 
int main(){

    int sizeOfarray = 0;
    int i = 0;
    int* arrayOfUser;
    printf("enter size of your array: ");
    scanf("%d",&sizeOfarray);
    arrayOfUser = (int*) calloc(sizeOfarray,sizeof(int));
    for ( i = 0; i < sizeOfarray; i++){
        printf("%d. element of array is : %d\n",i,*(arrayOfUser +i));
    } 
    free(arrayOfUser);
}