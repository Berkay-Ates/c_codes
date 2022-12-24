#include<stdio.h>
#include<stdlib.h>
 
int main(){
    FILE *fh_output ;
    fh_output = fopen("io.txt","a"); 

    fputs("abc",fh_output);
    fputs("123",fh_output);
    fputs("hello this is an string\n",fh_output);

    fprintf(fh_output,"data: %d\n",10);
    
    fclose(fh_output);
}