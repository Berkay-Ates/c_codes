#include<stdio.h>
#include<stdlib.h>
 
int sum(int,int);
int divide(int,int);
int multiply(int,int);
int subtract(int,int); 

int (*selectOperation())(int a ,int b){ 
    //* fonksiyon pointeri donduren bir fonksiyon
    
    int option = 0;
    printf("1-sum\n");
    printf("2-mul\n");
    printf("3-div\n");
    printf("4-sub\n");
    scanf("%d",&option);
 
    if(option == 1) return sum;
    else if(option == 2) return multiply;
    else if(option == 3) return divide;
    else return subtract;

}

int main(){

    int (*operation)(int,int) =  selectOperation();//* icerisine 2 degisken alan bir fonksiyonun pointerini donduren bir fonksiyon
    printf("answer: %d\n",operation(20,4)); 

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