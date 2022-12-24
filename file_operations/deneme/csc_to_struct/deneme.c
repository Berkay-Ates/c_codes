#include<stdio.h>
#include<stdlib.h>
 
typedef struct std {
    char type;
    char name[50];
    int age;
    double average;
}STUDENT;

int main(){

    FILE *csvFile;
    csvFile = fopen("deneme.csv","r");
    if(csvFile == NULL) exit(-1);

    STUDENT students[100];
    int read = 0;
    int records = 0;

    do{
        read = fscanf(csvFile,"%c,%49[^,],%d,%lf\n",
                &students[records].type,
                students[records].name,
                &students[records].age,
                &students[records].average);
                if(read == 4) records++;
                if(read != 4 && !feof(csvFile)){
                    //* feof varsa dosyanın sonuna gelmisizdir demektir 
                    //? dosyanın sonuna gelmedik ve okudugumuz deger sayısı 4 degilse sorun var demektir 
                    printf("error while reading file. maybe file format is incorrect \n");
                    exit(-1);  
                }

                if(ferror(csvFile)){
                    printf("error while reading file\n");
                    exit(-1);
                }
    }while(!feof(csvFile));

    fclose(csvFile);

    int i = 0;

    for(i = 0;i<records;i++){
        printf("%c, %s, %d, %lf\n",students[i].type,students[i].name,students[i].age,students[i].average);
    }

}