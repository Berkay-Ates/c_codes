#include<stdio.h>
#include<stdlib.h>
#define SIZE 15
 
// flag dizisindeki bayraklari kucukler asagida buyukler yukarida olacak sekilde siralayiniz


void arrangeFlags(char* flags, int size);
void printFlags(char* flags,int size);

int main(){

  char flags[SIZE] = {'a','b','b','a','c','b','a','a','b','b','c','a','b','c','c'};

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
    int f3 = size-1;
    int f2 ;
    char tmp ;

    while(flags[f1]== 'a')
        f1++;

    f2=f1;
    while(flags[f2] != 'b')
        f2++;
    
    while(flags[f2] == 'b')
        f2++;

    while(flags[f3] == 'c'){
        f3--;
    }

    printf("\nf1:%d f2:%d f3:%d \n",f1,f2,f3);

    while(f2 <= f3){
        if(flags[f2] == 'a'){
          tmp=flags[f1];
          flags[f1]=flags[f2];
          flags[f2]=tmp;
          f1++;
        }else if(flags[f2]=='b'){
            f2++;
        }else { // flags[f2] = c 
            tmp = flags[f2];
            flags[f2] = flags[f3];
            flags[f3] = tmp;
            f3--;
        }
    }
}



















