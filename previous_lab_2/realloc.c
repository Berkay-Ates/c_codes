#include<stdio.h>
#include<stdlib.h>
void printMatrix(int** matrix,int row, int column);

int main(){

    int row = 0;
    int column = 0;
    int **matrix; 
    int i,j;

    printf("row:");
    scanf("%d",&row);
    printf("column:");
    scanf("%d",&column);

    matrix = (int**) malloc(sizeof(int*)*row);

    if(matrix == NULL){
        printf("matrix does not allocated");
        return -1;
    }

    for(i=0;i<row;i++){
        matrix[i] = (int*) malloc(column*sizeof(int));
    }

    printMatrix(matrix,row,column);

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
           matrix[i][j] = 55;
        }
    }
    printMatrix(matrix,row,column);


    //* realloc the matrix

    int** tmp = (int**) realloc(matrix,sizeof(int*)*row*2);
    if(tmp != NULL){
        matrix = tmp;
    }else{
        printf("matrix does not reallocated");
        return -1;
    }

    for(i=0;i<row*2;i++){
        matrix[i] = (int*) realloc(matrix[i],sizeof(int)*2*column);
    }

    for(i=0;i<2*row;i++){
        for(j=0;j<2*column;j++){
           matrix[i][j] = 66;
        }
    }
    printMatrix(matrix,2*row,2*column);



}


void printMatrix(int** matrix,int row, int column){
    int i = 0;
    int j=0;
    for(i=0;i<row;i++){
        printf("%d: ",i);
        for(j=0;j<column;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}