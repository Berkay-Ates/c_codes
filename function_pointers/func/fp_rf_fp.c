#include<stdio.h>
#include<stdlib.h>

int sum(int,int);
int divide(int,int);
int mul(int,int);
int sub(int,int); 

int (*selectedFunc())(int a ,int b){
    
    int option = 0;

    printf("1:sum\n");
    printf("2:divide\n");
    printf("3:multply\n");
    printf("4:sub\n");
    scanf("%d",&option);

    switch (option){
        case 1: return sum;
        case 2: return divide;
        case 3: return mul;
        case 4: return sub;
    }

}
 
int main(){

    int (*genericFunc)(int,int) = selectedFunc();
    int result = (*genericFunc)(20,4);
    printf("%d",result);

}

int sum(int a,int b){
    return a+b;
}

int divide(int a,int b){
    return a/b;
}
int mul(int a,int b){
    return a*b;
}
int sub(int a,int b){
    return a-b;
}