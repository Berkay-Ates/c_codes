#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void printMatrix(int** matrix,int row, int column);
 
int main(){
    srand(time(NULL));

    int** matrix; 
    int row;
    int column;
    int i,j;
    int verticalSum=0,horizontalSum = 0;
    int rnd = 0;

    printf("matrix row size:");
    scanf("%d",&row);
    printf("matrix column size:");
    scanf("%d",&column);

    matrix = (int**) malloc(sizeof(int*)*row);
    if(matrix == NULL){
        printf("matrix does not allocated\n ");
        return -1;
    }

    for(i=0;i<row;i++){
        matrix[i] = (int*) malloc(sizeof(int)*column);
    }

    printMatrix(matrix,row,column);

    //TODO assign Random values;
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            rnd = random()%15;
            matrix[i][j] = rnd;
        }
    }

    printMatrix(matrix,row,column);

    //TODO reallocate matrix 
    int **pointer = (int**) realloc(matrix,(row+1)*sizeof(int*));
    if(pointer != NULL){
        matrix=pointer;
    }else{
        printf("matrix does not allocated");
        return -1;
    }

    for(i=0;i<row+1;i++){
        matrix[i] = (int*) realloc(matrix[i],(column+1)*sizeof(int));
    }

    printf("\nreallocated matrix is:\n");
    printMatrix(matrix,row+1,column+1);

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            horizontalSum += matrix[i][j];
        }
        matrix[i][column] = horizontalSum;
        horizontalSum = 0;
    }

    printf("\nhorizontally summed matrix is:\n");
    printMatrix(matrix,row+1,column+1);

    for(i=0;i<column;i++){
        for(j=0;j<row;j++){
            verticalSum += matrix[j][i];
        }
        matrix[row][i] = verticalSum;
        verticalSum = 0;
    }

    printf("\nvertically summed matrix is:\n");
    printMatrix(matrix,row+1,column+1);

    for(i=0;i<row;i++){
       verticalSum += matrix[i][column];
    }

    matrix[row][column] += verticalSum;

    for(i=0;i<column;i++){
        horizontalSum += matrix[row][i];
    }

    matrix[row][column] += horizontalSum;
    
    printf("\nall operations done matrix is:\n");
    printMatrix(matrix,row+1,column+1);

    //TODO free matrix
    for(i=0;i<row;i++){
       free(matrix[i]);
    }
    
    free(matrix);
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