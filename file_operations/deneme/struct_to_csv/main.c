#include<stdio.h>
#include<stdlib.h>

typedef struct std {
    char type;
    char name[50];
    int age;
    double average;
}STUDENT;

int main(){

    STUDENT std1 = {'a',"berkay ates",33,29.09};
    STUDENT std2 = {'b',"berkay yagmurlu",55,44.09};
    STUDENT std3 = {'c',"berkay karli",77,52.09};
    STUDENT stds[3];
    stds[0] = std1;
    stds[1] = std2;
    stds[2] = std3;

    int i = 0;

    FILE *file;
    file = fopen("generated.csv","w");
    if(file==NULL) printf("file could not be opened");
  

    for(i = 0;i<3;i++){
        fprintf(file,"%c,%s,%d,%lf\n",stds[i].type,stds[i].name,stds[i].age,stds[i].average);
        if(ferror(file)) printf("there was an error about file opening");
    }


    fclose(file);

}