#include<stdio.h>
#include<stdlib.h>
 
void function(int x){
    printf("X:%d\n",x);
}

double addDoubleFunc(double x, double y){
    return x+y;
}

void printDoubleFunc(double x){
    printf("double x: %lf\n",x);
}

int main(){
    // void (*printfunc)(int);
    // printfunc = &function;
    // (*printfunc)(10);

    double (*addDoubles)(double,double);
    void (*printDouble)(double);
    addDoubles = &addDoubleFunc;
    printDouble = &printDoubleFunc;

    double result = (*addDoubleFunc)(12.0,34.0);
    (*printDouble)(result);
}