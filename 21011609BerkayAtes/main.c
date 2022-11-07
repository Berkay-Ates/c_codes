#include<stdio.h>
#include<stdlib.h>
#include"compare.h"
 
// #define COMPAPE_MIN_FUNC(a,b) ( (a) < (b) ? (a) : (b))
// #define COMPAPE_MAX_FUNC(a,b) ( (a) < (b) ? (b) : (a))

int main(){
   //int numbers[ARRAY_LENGTH] = {10,9,8,7,6,5,4,3,2,1};
    int numbers[ARRAY_LENGTH] = {1,2,3,4,5,6,7,8,9,10};
    int minValuesSUM;
    int maxValuesSUM;
    int min = 9999;
    int max = 0;
    int firstMIN=999;
    int secondMIN=999;
    int firstMAX=0;
    int secondMAX=0;
    int i,j;

    for(i=0;i<ARRAY_LENGTH;i++){
        max = numbers[i];
        printf("max : %d\n",max);
        if(COMPARE_MAX_FUNC(max,secondMAX) == max){
            firstMAX = secondMAX;
            secondMAX = max;
        }else {
            if(COMPARE_MAX_FUNC(max,firstMAX) == max){
                firstMAX = max;
            }  
        }

        min = numbers[i];
        printf("min : %d\n",min);
        if(COMPARE_MIN_FUNC(min,firstMIN) == min){
            secondMIN = firstMIN;
            firstMIN = min;
        }else{
            if(COMPARE_MIN_FUNC(min,secondMIN) == min){
                secondMIN = min;
            }   
        }
    }

    printf("first min: %d\n",firstMIN);
    printf("first max: %d\n",firstMAX);
    printf("second max: %d\n",secondMAX);
    printf("second min: %d\n",secondMIN);
    printf("sums of elements: %d\n",firstMIN+firstMAX+secondMIN+secondMAX);

}