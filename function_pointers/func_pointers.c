#include<stdio.h>
#include<stdlib.h>

//* fonksiyon pointerlarında pointer arithmetigi yoktur

void function(int x){
    printf("X:%d\n",x);
}

double addDoubleValues(double x, double y){
    return x+y;
}

void printDoubleFunc(double x){
    printf("double x: %lf\n",x);
}

int main(){
    void (*func_pointer)(int);
    func_pointer = &function;
    (*func_pointer)(10);

    double (*double_func_pointer)(double,double);
    void(*print_double)(double);
    double_func_pointer = &addDoubleValues;
    print_double = &printDoubleFunc;
    double result = (*double_func_pointer)(12.0,23.0);
    print_double(result);

}