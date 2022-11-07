#include <stdio.h>
#include <stdlib.h>
#include "func_headers.h"

// int sum(int x,int y);
// int subtract(int x,int y);
// int multiply(int x, int y);
// int divide(int x, int y);
// int factorial(int x);

int sum(int x, int y){
    return x+y;
}

int subtract(int x,int y){
    return x-y;
}

int multiply(int x, int y){
    return x*y;
}

int divide(int x,int y){
    return x/y;
}

int factorial(int x){
    int i = x;
    int result = 1;

    while(x>1){
        result *= x--;
    }

    for(i=x;i>=0;i--){
        if(i==1){
            printf("%d = %d \n",i,result);

        }else if(i>1){
            printf("%d * ", i);

        }else{
            printf("%d \n", result);
        }
    }
    return result;
}
