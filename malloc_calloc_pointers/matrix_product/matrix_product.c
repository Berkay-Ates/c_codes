#include<stdio.h>
#include<stdlib.h>

int** malloc2ndOrder(int row);
void malloc1thOrder(int** allocated2ndOrder, int row,int column);
void setMatrixValues(int row, int column, int **secondOrderArray);
void printMatrixValues(int row,int column,int **secondOrderMatrix);
void freeFirstOrderMatrix(int** firstOrderMatrix,int row);
void freeSecondOrderMatrix(int** secondOrderMatrix);
 
int main(){

    int **firstMatrix;
    int **secondMatrix;
    int **thirdMatrix;

    int frow;
    int fcolumn;
    int srow;
    int scolumn;

    printf("first matrix row:");
    scanf("%d",&frow);
    printf("first matrix column:");
    scanf("%d",&fcolumn);
    printf("second matrix row:");
    scanf("%d",&srow);
    printf("first matrix row:");
    scanf("%d",&scolumn);


    firstMatrix = malloc2ndOrder(frow);
    malloc1thOrder(firstMatrix,frow,fcolumn);
    secondMatrix = malloc2ndOrder(srow);
    malloc1thOrder(secondMatrix,srow,scolumn);
    setMatrixValues(frow,fcolumn,firstMatrix);
    setMatrixValues(srow,scolumn,secondMatrix);
    printMatrixValues(frow,fcolumn,firstMatrix);
    printMatrixValues(srow,scolumn,secondMatrix);
    freeFirstOrderMatrix(firstMatrix,frow);
    freeFirstOrderMatrix(secondMatrix,srow);
    freeSecondOrderMatrix(firstMatrix);
    freeSecondOrderMatrix(secondMatrix);
    
}

int** malloc2ndOrder(int row){
    int **tmp = (int**) malloc(sizeof(int*)*row);
    int **result;
    if(tmp != NULL){
        result = tmp;
    }else{
        return 0;
    }
    return result;
}

void malloc1thOrder(int** allocated2ndOrder, int row,int column){
    int i = 0;
    for(i = 0;i<row;i++){
        allocated2ndOrder[i] = (int*) malloc(column*sizeof(int));
    }
}

void setMatrixValues(int row, int column, int **secondOrderArray){
    int i=0;
    int j=0;
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            printf("enter %dth row and %dth column element:",i,j);
            //scanf("%d",(*(secondOrderArray+i)+j));
            *(*(secondOrderArray+i)+j) = 5;
        }
    }
}

void printMatrixValues(int row,int column,int **secondOrderMatrix){

    int i=0;
    int j=0;
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            printf("array[%d][%d]:%d",i,j,*(secondOrderMatrix[i]+j));
        }
        printf("\n");
    }
        
}

void freeFirstOrderMatrix(int** firstOrderMatrix,int row){
    int i = 0;
    for(i=0;i<row;i++){
        free(firstOrderMatrix[i]);
    }
}

void freeSecondOrderMatrix(int** secondOrderMatrix){
    free(secondOrderMatrix);
}