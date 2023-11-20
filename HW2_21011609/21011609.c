#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 10

void printArray(char* arrName,int arr[]);
int partition(int arr[], int low, int high, int pivot);
void matchPairs(int keys[], int locks[], int low, int high);
void swap(int *x,int *y);

int main(){

    srand(time(NULL));
    
    int locks[SIZE] = {93, 24, 71, 68, 56, 42, 39, 31, 86, 2};
    int keys[SIZE] = {2, 24, 31, 93, 42, 56, 68, 71, 86, 39};

    printf("Keys and Locks before matching them : \n");

    printArray("Locks:", locks);
    printArray("Keys:", keys);

    matchPairs(keys, locks, 0, SIZE-1);

    printf("\nMatched keys and locks are : \n");

    printArray("Locks:",locks);
    printArray("Keys:",keys);
}

void swap(int* x , int* y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void printArray(char* arrName, int arr[]){
    printf("%s ",arrName);
    int i = 0;
    for ( i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    
    printf("\n");
}

int partition(int arr[], int low, int high, int pivot){
    int i = low;
    int j = 0;
    //* bizim dizimizde pivotun nerede oldugu belli degil 

    for (j = low; j < high; j++){

        if (arr[j] < pivot){ //* kucuk elemanlari sol tarafa tasimamizi saglar 
            swap(&arr[i],&arr[j]);
            i++;
        }
        else if (arr[j] == pivot) { //* pivotu partitioning yapilirken isleri karistirmamasi icin en sona aliyoruz 
            //* partitioning islemi sonlandiktan sonra pivot degerini olmasi gereken noktaya getiriyoruz
            swap(&arr[j],&arr[high]);
            j--; //* burada fazladan bir pivot islemi yaptik dolayisiyla dongu degiskeninin artmamasini saglamamiz gerek
        }
    }
    //* pivottan en son buyuk olan eleman i de oldugu icin yeni pivot yeri i nin yeri olmak zorunda 
    //* dolayisiyle eski pivotu i nin yerine getirelim

    swap(&arr[i],&arr[high]);

    return i;
}


void matchPairs(int locks[], int keys[], int low, int high){

    if (low < high){
        //* partition yaparken normalde pivot noktasi kod tarafindan bize dondurulur 
        //* fakat burada ayni dizideki elemanlari birbirleri ile karsilastiramayacagimiz icin 
        //* algoritmanin akisina gore random bir indis secip bu indisteki elemanla locks dizisini siraliyoruz.
        //* Sonra yine ayni elamana gore bu defa keys dizisini partition ediyoruz bu sayede her iki dizi de ayni 
        //* seviyede partition edilmis oluyor. 

        //* yaptigimiz islem temelde bir siralama oldugu icin siralamanin karmasikligi nlogn oldugundan 
        //* her adimda temelde kesin olarak 1 anahtar ile 1 key yerlesmis olmasina ragmen toplam islem 
        //* nlogn de bitmis oluyor

        int random_number = rand() % (high-low) + low; 

        //* keys partition
        int pivot = partition(keys, low, high, locks[random_number]);

        //* locks partition
        partition(locks, low, high, keys[pivot]);

        matchPairs(locks, keys, low, pivot - 1);
        matchPairs(locks, keys, pivot + 1, high);
    }
}


