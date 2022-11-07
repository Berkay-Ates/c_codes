#include<stdio.h>
#include<stdlib.h>

void pointerArgument(int* anPointer);
 
int main(){

    int value;
    int* pvalue;
    pvalue = &value;

    printf("pointed address of pvalue:%p\n",pvalue);
    printf("address of pvalue:%p\n",&pvalue);
    printf("value of pvalue %d\n",*pvalue);
    printf("address of value:%p\n",&value);
    printf("value of value: %d\n",value);

    pointerArgument(&value);
    printf("pointed address of pvalue:%p\n",pvalue);
    printf("address of pvalue:%p\n",&pvalue);
    printf("value of pvalue %d\n",*pvalue);
    printf("address of value:%p\n",&value);
    printf("value of value: %d\n",value);

    pointerArgument(pvalue);
    printf("pointed address of pvalue:%p\n",pvalue);
    printf("address of pvalue:%p\n",&pvalue);
    printf("value of pvalue %d\n",*pvalue);
    printf("address of value:%p\n",&value);
    printf("value of value: %d\n",value);

    return 0;

}

void pointerArgument(int* anPointer){
    printf("enter a number to assign value: ");
    scanf("%d",anPointer);
    printf("\n");
}