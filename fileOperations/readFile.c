#include<stdio.h>
#include<stdlib.h>
 
int main(){
    FILE *textFile;
    char content[10000];
    textFile = fopen("text.txt","r");//* dosya okunma modunda acılmıs olundu 
    if(textFile == NULL){
        printf("specified file does not exists");
        exit(-1);
    }
    printf("file opened successfully\n");
    fgets(content,10000,textFile);
    printf("%s",content);

    fclose(textFile); 
}