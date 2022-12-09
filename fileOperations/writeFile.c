#include<stdio.h>
#include<stdlib.h>
 
int main(){
    FILE *newFile;
    newFile = fopen("newfile.txt","a");
    fputs("hello world this is first line of text we are going to add right now\n",newFile);
    fputs("this is second line of text we are going to add right now\n",newFile);
    fclose(newFile);
}