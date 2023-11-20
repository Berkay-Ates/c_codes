#include<stdio.h>
#include<stdlib.h>

#define TABLESIZE 37
#define mm 31
#define C1 3
#define C2 5

void doubleHashing(int* hashTable,int key, int tableSize);
void quadraticProbingV2(int* hashTable, int key, int tableSize);
void quadraticProbingV1(int* hashTable, int key, int tableSize);
int searchHashTableLinearProbing(int* hashTable,int key,int tableSize);
void linearProbing(int* hashTable,int key,int tableSize);
void printHashTable(int* hashTable);
int* initHashTable(int tableSize);

int main(){
    //* open addressing yada closed addressing olayinda 3 farkli method vardir 
    //* linear probing ==> [h(k)+i] %m 
    //* quadratic probing ==> [h(k)+i^2] %m veya da [h(k)+ c1*i + c2*i^2] % m 
    //* double hashing ==> [h1(k)+i*h2(k)]%m  h1()= k % m  and h2()= 1 + (k % mm
    
    int* hashTable = NULL;
    hashTable = initHashTable(TABLESIZE);
    // printHashTable(hashTable);
    
    linearProbing(hashTable,4,TABLESIZE);
    linearProbing(hashTable,3,TABLESIZE);
    linearProbing(hashTable,40,TABLESIZE);
    linearProbing(hashTable,77,TABLESIZE);
    linearProbing(hashTable,77,TABLESIZE);
    searchHashTableLinearProbing(hashTable,40,TABLESIZE);
    searchHashTableLinearProbing(hashTable,77,TABLESIZE);
    searchHashTableLinearProbing(hashTable,12,TABLESIZE);
    searchHashTableLinearProbing(hashTable,3,TABLESIZE);
    searchHashTableLinearProbing(hashTable,14,TABLESIZE);
    printHashTable(hashTable);

    free(hashTable);

 return 0; 
}

int searchHashTableLinearProbing(int* hashTable,int key,int tableSize){
        int hash = key % TABLESIZE;
    int i = 0;

    while(hashTable[hash] != -1 && hashTable[hash] != key && i < tableSize){
        i++;
        hash = (hash+1)%TABLESIZE;
    }
     if(hashTable[hash] == -1)
        printf("Aranan key degeri tabloda bulunmuyor\n");
    else if(hashTable[hash] == key){
        printf("%d degeri tablonun %d. indexinde\n",key,hash);
        return hash;
    }else if(i>= tableSize)
        printf("tablo dolu %d degeri arandi fakat bulunamadi\n",key);

    return -1;
}

int* initHashTable(int tableSize){
    int i = 0;
    int* table = (int*) malloc(sizeof(int)*tableSize);
    if(table == NULL){
        printf("table was null");
        exit(-1);
}
    for(i=0;i<tableSize;i++)
        table[i] = -1;

    return table;
}

void printHashTable(int* hashTable){
    int i = 0;
    printf("\n");
    for(i = 0; i<TABLESIZE ;i++){
        printf("%d => %d \n", i , hashTable[i]);
    }
}


void doubleHashing(int* hashTable,int key, int tableSize){
    int i = 0;
    int hash = ((key%TABLESIZE) + i*(1+(key%mm)))%TABLESIZE;

    while(hashTable[hash] != -1 && hashTable[hash] != key && i*i < tableSize){
        i++;
        hash = (hash + i*(1+(key%mm)));
    }

    if(hashTable[hash] == -1)
        hashTable[hash] = key;
    else if(hashTable[hash] == key)
        printf("%d key degeri zaten tabloda var\n",key);
    else if(i>= tableSize)
        printf("tablo dolu %d degeri yerlestirilemedi\n",key);
}


void quadraticProbingV2(int* hashTable, int key, int tableSize){
    int i = 0;
    int hash = ((key%TABLESIZE) + C1*1 + C2*i*i)%TABLESIZE;
    
    while(hashTable[hash] != -1 && hashTable[hash] != key && i*i < tableSize){
        i++;
        hash = (hash+C1*i + C2*i*i)%TABLESIZE;
    }

    if(hashTable[hash] == -1)
        hashTable[hash] = key;
    else if(hashTable[hash] == key)
        printf("%d key degeri zaten tabloda var\n",key);
    else if(i>= tableSize)
        printf("tablo dolu %d degeri yerlestirilemedi\n",key);
}




void quadraticProbingV1(int* hashTable, int key, int tableSize){
    int i = 0;
    int hash = ((key%TABLESIZE) + i*i)%TABLESIZE;
    
    while(hashTable[hash] != -1 && hashTable[hash] != key && i*i < tableSize){
        i++;
        hash = (hash+i*i)%TABLESIZE;
    }

    if(hashTable[hash] == -1)
        hashTable[hash] = key;
    else if(hashTable[hash] == key)
        printf("%d key degeri zaten tabloda var\n",key);
    else if(i>= tableSize)
        printf("tablo dolu %d degeri yerlestirilemedi\n",key);
}



void linearProbing(int* hashTable,int key,int tableSize){
    int hash = key % TABLESIZE;
    int i = 0;

    while(hashTable[hash] != -1 && hashTable[hash] != key && i < tableSize){
        i++;
        hash = (hash+1)%TABLESIZE;
    }

    if(hashTable[hash] == -1)
        hashTable[hash] = key;
    else if(hashTable[hash] == key)
        printf("%d key degeri zaten tabloda var\n",key);
    else if(i>= tableSize)
        printf("tablo dolu %d degeri yerlestirilemedi\n",key);
}



