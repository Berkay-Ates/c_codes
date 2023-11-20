#include<stdio.h>
#include<stdlib.h>
 
#define SIZE 10

void printArray(int* arr,int size);
void quickSort(int* array,int left, int right);
int partitionRightMost(int* array,int left, int right);
int partitionLeftMost(int* arr, int low, int high);
void swap(int *a, int *b);

int partitionMYSELF(int* arr,int left, int right);
int partitionMYSELF2(int* arr,int left, int right);
int partitionMYSELF3(int* arr,int left, int right);
int partitionMYSELF4(int* arr,int left, int right);

int main(){

    int values[10] = {4,10,1,9,2,5,6,7,8,3};

    printArray(values,SIZE);

    // printf("%d\n",partition(values,0,9));
    quickSort(values,0,SIZE-1);
    
    printArray(values,SIZE);

    return 0; 
}


void quickSort(int* array,int left, int right){

    int pivot = 0;
    if(left<right){
        pivot = partitionMYSELF4(array,left,right);
        quickSort(array,left,pivot-1);
        quickSort(array,pivot+1,right);

    }
}

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}


int partitionMYSELF4(int* arr,int left, int right){

    //* pivotun olmadigi taraftan baslamak lazim 

  int pivot = arr[left];
  
  int i;
  int j = left+1;

  for(i=right;left<i;i--){
    if(pivot<arr[i]){
      swap(&arr[i], &arr[right--]);
    }
  }

  swap(&arr[left], &arr[right]);
  return right;
} 


int partitionMYSELF3(int* arr,int left, int right){

    //* pivotun olmadigi taraftan baslamak lazim 

  int pivot = arr[left];
  
  int i;
  int j = left+1;

  for(i=left;i<right;i++){
    if(arr[i] < pivot){
      swap(&arr[i], &arr[j++]);
    }
  }

  swap(&arr[left], &arr[j-1]);
  return j-1;
} 


int partitionMYSELF2(int* arr,int left, int right){

    //* pivotun olmadigi taraftan baslamak lazim 

  int pivot = arr[left];
  
  int i;

  for(i=right;left<i;i--){
    if(arr[i] > pivot){
      swap(&arr[i], &arr[right--]);
    }
  }
  swap(&arr[left], &arr[right]);
  return right;
} 

void printArray(int* array,int size){
    int i= 0;

    for(i=0;i<size;i++){
        printf(" %d ",array[i]);
    }
    printf("\n");
}


int partitionMYSELF(int* arr, int left, int right) {
    int pivot = arr[left];
    int i = left + 1;
    int j = right;

    while (i <= j) {
        while (i <= j && arr[i] <= pivot)
            i++;
        while (i <= j && arr[j] > pivot)
            j--;
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[left], &arr[j]);
    return j;
}

int partitionLeftMost(int* arr, int low, int high){
 
    // First element as pivot
    int pivot = arr[low];
    // int st = low; // st points to the starting of array
    // int end = high; // end points to the ending of the array
    int i = 0;

    for (i = high; i > low; i--) {
        if (arr[i] > pivot)
            swap(&arr[i], &arr[high--]); //* high eger pivottan buyukse bu sekilde emin olmus olucagiz 
    }

    swap(&arr[low], &arr[high]);

    return high;
}

int partitionRightMost(int array[], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}





// int partition(int* array ,int left, int right){

//     int p = array[left];

//     int i = left+1;
//     int j = right;

//     while(i>=j){
//         while(p>=array[i]) i++;
//         while(p<=array[j]) j--;
//         swap(&array[i],&array[j]);
//     }

//     // swap(&array[i],&array[j]);
//     swap(&array[left],&array[j]);
//     return j;
// }

// int partition(int* array ,int left, int right){

//     int pivot = 0;
//     int high = right;
//     int low = left+1;
//     while(high >= low){
//         if(array[low] > array[pivot]){
//             while(array[high] >= array[pivot])
//                 high--;

//             if(high > low){
//                 swap(&array[low],&array[high]);
//                 low++;
//                 high--;
//             }

//         }else{
//             low++;
//         }
//     }
//     swap(&array[high],&array[pivot]);
//     // printArray(d,right);printf("\n");
//     return high;
// }








