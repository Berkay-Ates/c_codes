#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
 
bool freeze_c(int a ){
    if(a<0) return true;
    else return false;   
}

bool freeze_f(int a ){
    if(a<32 ) return true;
    else return false;
}

void genericFunc(bool (*func)(int)){
    int temperature;
    printf("ener the tempreature outside right now: ");
    scanf("%d",&temperature);
    if(func(temperature)){
        printf("it is freezing\n");
        return;
    }
    printf("it is not freezing\n");
}


int main(){
    printf("celcius func worked\n");
    genericFunc(freeze_c);//* icerisine intager alan ve boolean donduren bir fonksiyon istiyor
                          //* icerisine alacak oldugu int degeri generic function icerisinden saglanacak
    
    printf("fahrenheit func worked\n");
    genericFunc(freeze_f);
    
}


