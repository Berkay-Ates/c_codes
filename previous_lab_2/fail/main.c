#include<stdio.h>
#include<stdlib.h>
#include<time.h>
 
int main(){

    srand(time(NULL));

    int row;
    int column;
    int** matrix;
    int i,j;
    int randomValue;
    int horizontalSum=0;
    int verticalSum=0;

    printf("matrix row:");
    scanf("%d",&row);
    printf("matrix column:");
    scanf("%d",&column);

    matrix = (int**) malloc(sizeof(int*)*(row+1));

    for(i=0;i<row;i++){
        matrix[i] = (int*) malloc(sizeof(int)*(column+1));
    }

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            randomValue = rand()%10;
            *(*(matrix+i)+j) = randomValue;
        }
    }

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            printf("[%d][%d]:%d \n",i,j,matrix[i][j]);
        }
        printf("\n");
    }
    printf("pure matrix reallocating\n");


    //   matrix = (int**) realloc(matrix,(row+1)*sizeof(int*));
    
    // for(i=0;i<row;i++){
    //     matrix[i] = (int*) realloc(matrix[i],(column+1)*sizeof(int));
    // }

    //* matrix reallocated

      for(i=0;i<row+1;i++){
        printf("%d: ",i);
        for(j=0;j<column+1;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }

    printf("reallocated\n");

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
           horizontalSum += matrix[i][j];
        }
        matrix[i][column] = horizontalSum;
        horizontalSum = 0;
    }

     for(i=0;i<row+1;i++){
        printf("%d: ",i);
        for(j=0;j<column+1;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }

    for(i=0;i<column;i++){
        for(j=0;j<row;j++){
           verticalSum += matrix[j][i];
        }
        matrix[row][i] = verticalSum;
        verticalSum = 0;
    }

    for(i=0;i<row+1;i++){
        printf("%d: ",i);
        for(j=0;j<column+1;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }

    //***--------

    verticalSum = 0;
    for(i=0;i<row;i++){
        verticalSum += matrix[i][column+1];
    }

    matrix[row+1][column+1] += verticalSum;

    horizontalSum = 0;
    for(i=0;i<column;i++){
        horizontalSum += matrix[row+1][i];
    }

    matrix[row+1][column+1] += horizontalSum;

    for(i=0;i<row+1;i++){
        for(j=0;j<column+1;j++){
            printf("[%d][%d]:%d \n",i,j,matrix[i][j]);
        }
        printf("\n");
    }

    for(i=0;i<row+1;i++){
        free(matrix[i]);
    }
    free(matrix);

}

