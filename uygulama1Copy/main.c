#include<stdio.h>
#include "operationsEnum.h"
// #include "calculations.h"
#include "menu.h"
#include "calculations.h"
#include "func_bodies.c"

// did not worked #include "enum_bodies.h"

// #include "func_headers.h"
// #include "func_bodies.c"

enum OPERATIONS getSelected(int i);

int main(){
    int run = 1;
    int selectedAsNumber = 0;

    enum OPERATIONS selectedAsEnum;
    while(run){
        MENU;
        scanf("%d",&selectedAsNumber);
        selectedAsEnum = getSelected(selectedAsNumber);
        printf("selected num is %d \n",selectedAsNumber);
        switch (selectedAsEnum){
                case topla:
                    printf("topla\n");
                    break;
                case cikar:
                    printf("cikar\n");
                    break;
                case bol:
                    printf("bol\n");
                    break;
                case carp:
                    printf("carp\n");
                    break;
                case faktoriyel:
                    printf("factorial\n");
                    break;
                case bitir:
                    printf("bitiriliyor\n");
                    run = 0;
                    break;
                default:
                printf("there must be some error");
            }
    }
}

enum OPERATIONS getSelected(int i){
    enum OPERATIONS selected;
    switch (i){
        case 1:
            selected = topla;
            break;
        case 2:
            selected = cikar;
            break;
        case 3:
            selected = bol;
            break;
        case 4:
            selected = carp;
            break;
        case 5:
            selected = faktoriyel;
            break;
        case 6:   
            selected = bitir;
            break;
        default:
        selected = bitir;
            break;
    }
       return selected;
}