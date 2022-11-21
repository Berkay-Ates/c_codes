#include<stdio.h>
#include<stdlib.h>
 
int main(){
    int** matrix = mallocMatrix(6);

}

//* iceerisinde pointer gozu olan bir dizi acarak dizi icerisine de allocate ettigimiz dizilerin ilk elemanlarının
//* addresini veya da pointerlarını koyuyoruz 

int** mallocMatrix(int row){
    int** tmp = (int**) malloc(sizeof(int*)*row);
    if(tmp == NULL){
        exit(0);
    }

    return tmp;
}

void mallocArray(int row,int column,int** matrix){
    int i,j;
    for(i=0;i<row;i++){
        *(matrix+i)= (int*) malloc(sizeof(int)*column);
        //* matris icerisinde yer vardı row sayısı kadar simdi de bu baslangıc gozlerine 
        //* tutmak istedigimiz diziler icin yer ayırarak ayırdıgımız bu yerlerin addreslerini koyduk
    }
}

void freeMatrixArrays(int row,int** matrix){

    int i = 0;
    for(i = 0;i<row;i++){
        //free(matrix[i]);
        free(*(matrix+i));
    }
}


void freeArrayMatrix(int ** matrix){
    free(matrix);
}




