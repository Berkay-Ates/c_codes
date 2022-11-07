#include<stdio.h>
#include<time.h> 
#include<stdlib.h>
#include "bee_header.h"

int randomBeeValue(){
    int randomBeeCost = rand()%20 + rand()%5;
    return randomBeeCost;
}