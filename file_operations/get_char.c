#include<stdio.h>
#include<stdlib.h>
 
int main(){

    FILE *fileStr;

    fileStr = fopen("char_file.txt","r");
    char buffer[256];
    fgets(buffer,256,fileStr);
    printf("%s", buffer);

    fclose(fileStr);
}