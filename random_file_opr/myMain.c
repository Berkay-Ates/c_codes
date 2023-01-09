#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>

typedef struct data{
	int id;
	char name[50];
	char department[20];
	struct DATA *next;
}DATA;


int main(){

    DATA d[20];
    FILE* dataSet; 
    int i=0,j = 0;

    dataSet = fopen("Dataset.txt","r");
    while(!feof(dataSet)){
        fread(&d[j].id,sizeof(DATA),1,dataSet);
        printf("okundu\n");
        j++;
    }
    fclose(dataSet);

    for(i=0;i<j;i++){
        printf("%d, %s, %s\n",d[i].id,d[i].name,d[i].department);
    }

}