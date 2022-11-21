#include<stdio.h>
#include<stdlib.h>
 
void pointerSwap(int **pointer1, int **pointer2);
void basicAddressSwap(int* int1,int* int2);

int main(){
    int value1 = 1;
    int value2 = 2;
    int* pointer1 ;
    int* pointer2;

    pointer1 = &value1;
    pointer2 = &value2;
    printf("initial condition");

    printf("address of value1= %p\n",&value1);
    printf("value of value1= %d\n",value1);
    printf("value of pointer1 = %d\n",*pointer1);
    printf("address referred by pointer1 = %p\n",pointer1);
    printf("address of pointer1 = %p\n\n",&pointer1);


    printf("address of value2= %p\n",&value2);
    printf("value of value2= %d\n",value2);
    printf("value of pointer2 = %d\n",*pointer2);
    printf("address referred by pointer2 = %p\n",pointer2);
    printf("address of pointer2 = %p\n",&pointer2);


    pointerSwap(&pointer1,&pointer2);
    printf("\nfirst swap\n");


    printf("address of value1= %p\n",&value1);
    printf("value of value1= %d\n",value1);
    printf("value of pointer1 = %d\n",*pointer1);
    printf("address referred by pointer1 = %p\n",pointer1);
    printf("address of pointer1 = %p\n\n",&pointer1);


    printf("address of value2= %p\n",&value2);
    printf("value of value2= %d\n",value2);
    printf("value of pointer2 = %d\n",*pointer2);
    printf("address referred by pointer2 = %p\n",pointer2);
    printf("address of pointer2 = %p\n",&pointer2);


    int **ppointer1 = &pointer1;
    int **ppointer2 = &pointer2;
    pointerSwap(ppointer1,ppointer2);

    printf("\nsecond swap\n");

    printf("address of value1= %p\n",&value1);
    printf("value of value1= %d\n",value1);
    printf("value of pointer1 = %d\n",*pointer1);
    printf("address referred by pointer1 = %p\n",pointer1);
    printf("address of pointer1 = %p\n\n",&pointer1);


    printf("address of value2= %p\n",&value2);
    printf("value of value2= %d\n",value2);
    printf("value of pointer2 = %d\n",*pointer2);
    printf("address referred by pointer2 = %p\n",pointer2);
    printf("address of pointer2 = %p\n",&pointer2);


    int a = 5;
    int b = 3;

    printf("a: %d, b: %d\n",a,b);
    basicAddressSwap(&a,&b);
    printf("a: %d, b: %d\n",a,b);
    //* addressleri uzerinden degisiklik yaptık
    
}


void pointerSwap(int **pointer1, int **pointer2){

    int* tmp = *pointer1;
    *pointer1 = *pointer2;
    *pointer2 = tmp; 
}

void basicAddressSwap(int* int1,int* int2){

    //* suan int degerlerin addresleri bizim elimizde dolayısıyla addresler uzerinden elemanlara istedigimiz degisikligi 
    //* yapabiliriz bu sayede elemanların degeerleri de degismis olacaktır. 
    int tmp = *int1;
    *int1 = *int2;
    *int2 = tmp;

}