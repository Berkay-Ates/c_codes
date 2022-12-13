#include<stdio.h>
#include<stdlib.h>
 
int sum(int,int);
int divide(int,int);
int multiply(int,int);
int subtract(int,int); 

int main(){
    int (*funcArr[])(int,int) = {sum,divide,multiply,subtract};
    int product = funcArr[2](20,5); 
    //* int degiskenleri arr de tanımlamdıgıızda o an product icerisinde bulunan sacma bir deger gelmis oldu 
    printf("%d",product);
}


int sum(int a,int b){
    return a+b;
}

int divide(int a,int b){
    return a/b;
}
int multiply(int a,int b){
    return a*b;
}
int subtract(int a,int b){
    return a-b;
}