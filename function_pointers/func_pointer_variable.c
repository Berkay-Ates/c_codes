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

void is_freezing( bool (*freeze_check)(int) ){
//* freezing fonksiyonu icerisine aldıgımız fonksiyon pointerları sayesinde freezingin islemlerini degistirebiliyoruz
    int temperature = 0;
    printf("temperature:");
    scanf("%d",&temperature);
    if(freeze_check(temperature)){
        printf("it is freezing");
    }else{
        printf("it is not freezing");
    }
}

int main(){

    is_freezing(&freeze_c);
    is_freezing(&freeze_f);

}


//* sıralamak icin en tepede bir fonksiyon var icerisine aldıgı fonksiyon pointer ile dizileri sıralıyor 
//* istersek bu fonksiyon ile bubble sort yaptırırız istersek de selection sort 
//* genericlik zehri alındı
//* ama tam degil sanki 

