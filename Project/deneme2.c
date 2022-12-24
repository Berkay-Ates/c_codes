#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct kitapOrnek { 
    char EtiketNo[20]; 
    char Durum[9]; 
    struct kitapOrnek *next;
} KITAPORNEK;

typedef struct Kitap {
    char kitapAdi[30]; 
    char ISBN[14]; 
    int adet; 
    struct Kitap *next; 
    struct kitapOrnek *head;
} KITAP;

int main(){
    KITAP *kitap = (KITAP*) malloc(sizeof(KITAP)*1);
    KITAP *kitap2 = (KITAP*) malloc(sizeof(KITAP)*1);
    KITAPORNEK *kitapOrnek = (KITAPORNEK*) malloc(sizeof(KITAPORNEK)*1);
    char* name = "hello";
    char* surname = "world";
    strcpy(kitapOrnek->Durum,name);
    strcpy(kitapOrnek->EtiketNo,surname);

    kitap->next = kitap2;
    kitap->head = kitapOrnek;

}
