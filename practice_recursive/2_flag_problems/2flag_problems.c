#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
 
// flag dizisindeki bayraklari kucukler asagida buyukler yukarida olacak sekilde siralayiniz


void arrangeFlags(char* flags, int size);
void printFlags(char* flags,int size);

int main(){

  char flags[SIZE] = {'a','b','a','b','a','a','b','a','b','b'};

  printFlags(flags,SIZE);
  printf("\n");
  arrangeFlags(flags,SIZE);
  printFlags(flags,SIZE);
  

}


void printFlags(char* flags,int size){
    int i = 0;

    for (i = 0; i < size; i++)
        printf("%c",flags[i]);
}


void arrangeFlags(char* flags, int size){
    int f1 = 0;
    int f2 = size;
    char tmp ;

    while(flags[f1 ]== 'a')
        f1++;

    while(flags[f2] == 'b'){
        f2--;
    }

    while(f1 <= f2){
        if(flags[f1] == 'a'){
           f1++;
        }else {
            tmp = flags[f2];
            flags[f2] = flags[f1];
            flags[f1] =tmp;
            f2--;
        }
    }
}



















