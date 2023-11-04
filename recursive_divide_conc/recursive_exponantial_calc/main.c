#include<stdio.h>
#include<stdlib.h>
 

int calcPow(int bottom,int power);

int main(){

    int res = calcPow(2,5);

    printf("%d",res);
 return 0; 
}


int calcPow(int bottom,int power){
    int res1 = 0;

    if(power == 1 )
        return bottom;
    if(power % 2 == 0){
        res1 = calcPow(bottom,power/2);
        return  res1 *  res1;
    }else{
        res1 = calcPow(bottom,power/2);
        return res1 *  res1 * bottom;
    }
}