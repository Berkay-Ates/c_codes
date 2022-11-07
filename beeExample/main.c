#include<stdio.h>
#include<time.h> //* for random times
#include<stdlib.h>
#include "bee_macros.h"
#include "bee_header.h"

int main(){

    srand(time(NULL));
    
    int i = 0, j=0;
    int iterationNumber = 0;
    int numberOfBee=0;
    int min_bee_cost = 9999;

    printf("population size: ");
    scanf("%d",&numberOfBee);
    printf("iteration number: ");
    scanf("%d",&iterationNumber);

    #ifdef NUMBER_OF_BEE
    #undef NUMBER_OF_BEE
    #undef ITERATION_NUMBER
    #define NUMBER_OF_BEE numberOfBee
    #define ITERATION_NUMBER iterationNumber
    #endif

    int bee[NUMBER_OF_BEE];
    //* arıdegerlerinin tutulacagı dizinin boyutunu en basta bilmedigimiz icin diziyi boyutunu aldıktan sonra tanımlamak en iyisi 

    printf("\n\n");
    for(j=0;j<ITERATION_NUMBER;j++){

        for(i=0;i<NUMBER_OF_BEE;i++){
            bee[i] = randomBeeValue();
        }

        min_bee_cost=9999;
        printf("initial population:\n ");
        for(i=0;i<NUMBER_OF_BEE;i++){
            printf("%d ",bee[i]);
            if(BEE_COST_CALCULATOR(bee[i]) < min_bee_cost ){
                min_bee_cost = BEE_COST_CALCULATOR(bee[i]);
            }
        }
        printf("\ninitial best condition: %d \n\n",min_bee_cost);
    }

    return 0;

}