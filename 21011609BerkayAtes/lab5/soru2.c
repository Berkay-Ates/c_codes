#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct ogr{
	int  id;       
	char isim[10]; 
	char ders[10]; 
	int puan;	  
}OGR;

int main(){
	FILE *fp;
	OGR o1[4]={{1,"ali","mat1",100},{1,"veli","mat1",30},{1,"ayse","mat1",80},{1,"fatma","mat1",70}};
	int N = 4;
	OGR *ptr = (OGR*) malloc(N*sizeof(OGR));
	fp = fopen("input.txt","w+");
	fwrite(&N,sizeof(int),1,fp);
	fwrite(o1,sizeof(OGR)*N,1,fp);
	fclose(fp);
}

