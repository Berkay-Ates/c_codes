#include<stdio.h>
#include<stdlib.h>
 
int main(){
    // FILE *fh_output ;
    // fh_output = fopen("io.txt","r");
    // fclose(fh_output);

    FILE *fh_input;
    fh_input = fopen("number_file.txt","r");

    int finput = 0;
    char *file_txt;
    while(fscanf(fh_input,"%d",&finput) != EOF){
        printf("the number just read from the file is : %d\n",finput);
    }


    fclose(fh_input);
}