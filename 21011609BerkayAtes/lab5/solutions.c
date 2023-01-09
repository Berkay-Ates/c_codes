#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
typedef struct ogr{
	int  id;       
	char isim[10]; 
	char ders[10]; 
	int puan;	  
}OGR;

int main(){

    int N,i=0;
    int not,mod;
    int length = 0; 
    OGR data[20];
    FILE *dataFile;
    FILE *mailFile;
    char *fileName;
    char message[100] = "";
    char message2[100] = "";
    char notSTR[3] = "";

    dataFile = fopen("input.txt","r");
    if(dataFile == NULL) exit(-1);
    fread(&N,sizeof(int),1,dataFile);
    
    for(i=0;i<N;i++){  
        fread((data+i),sizeof(OGR),1,dataFile);
        printf("%d, %s, %s, %d\n",data[i].id,data[i].isim,data[i].ders,data[i].puan);
    }

    fclose(dataFile);

    for(i=0;i<N;i++){
        not = data[i].puan;

        itoa(data[i].puan, notSTR, 10);

        length = strlen(data[i].isim);
        printf("%d\n", length);
        fileName = (char*) malloc(sizeof(char)*(length+4));
        strcpy(fileName,data[i].isim);
        strcat(fileName,".txt"); 

        mailFile = fopen(fileName,"w");
        strcpy(message,"merhaba ");
        strcat(message,data[i].isim);
        strcat(message," mat vizesinden aldiginiz not ");
        strcat(message,notSTR);
        strcat(message," lutfen bu maile cevap vermeyiniz.");
        fwrite(message,sizeof(message),1,mailFile);
        free(fileName);
        fclose(mailFile);
        mailFile = fopen(fileName,"r");
        fread(message2,sizeof(char)*100,1,mailFile);
        fclose(mailFile);
        printf(" %s ", message2);
    }

} 