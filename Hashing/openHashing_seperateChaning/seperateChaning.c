#include<stdio.h>
#include<stdlib.h>

#define TABLESIZE 37

typedef struct node{
	int key;
    struct node* next;
}NODE;

typedef struct hash{
    int count;
    struct node* head;
} HASH;

void printHashTable(HASH** hashTable);
NODE* createNewNode(int key);
void insertToTable(HASH** hashTable, int key);
HASH** initHashTable();
void searchHash(HASH** hashTable,int key);

int main(){
    HASH** hashTable = NULL;
    
    hashTable = initHashTable();

    insertToTable(hashTable,3);
    insertToTable(hashTable,4);
    insertToTable(hashTable,41);
    insertToTable(hashTable,78);
    insertToTable(hashTable,33);
    insertToTable(hashTable,70);
    insertToTable(hashTable,63);
    printHashTable(hashTable);

    searchHash(hashTable,41);
    searchHash(hashTable,91);
    searchHash(hashTable,63);


    while (1){printf("afdsf");}
    

 return 0; 
}


void printHashTable(HASH** hashTable){
    HASH* tmp = *hashTable;
    NODE* nodeTmp = tmp->head;

    int i = 0;
    for(i=0;i<TABLESIZE;i++){
        tmp = hashTable[i];
        printf("\n%d => ",i);
        if(tmp->head != NULL){
            nodeTmp = tmp->head;
            while(nodeTmp!= NULL){
                printf("%d ",nodeTmp->key);
                nodeTmp = nodeTmp->next;
            }
        }
    }
    printf("\n");
    
}

NODE* createNewNode(int key){
    NODE* newNode;

    newNode = (NODE*) malloc(sizeof(NODE));
    if(newNode == NULL){
        printf("new node could not allocated");
        exit(-1);
    }
    newNode->next = NULL;
    newNode->key = key;

    return newNode;
}

void insertToTable(HASH** hashTable, int key){
    int hashAddr;
    hashAddr = key%TABLESIZE;

    NODE* newNode;
    newNode = createNewNode(key);

    if(hashTable[hashAddr]->head == NULL){
        //* that means the index was null
        hashTable[hashAddr]->head=newNode;
        (hashTable[hashAddr]->count)+=1;
    }else{
        //* bakilan indis doluydu dolayisiyla headi guncellmek gerek 
        newNode->next = hashTable[hashAddr]->head;
        hashTable[hashAddr]->head = newNode;
        (hashTable[hashAddr]->count) +=1;
    }
}

void searchHash(HASH** hashTable,int key){
    int hashAddr = key%TABLESIZE;
    int i = 0;
    HASH* tmpHASH = hashTable[hashAddr];

    NODE* tmp = tmpHASH->head;
    
    while(tmp!=NULL && tmp->key != key ){
        tmp= tmp->next;
        i++;
    }

    if( tmp!= NULL && tmp->key == key){
        printf("mod degeri = %d, aranan eleman %d. indiste %d degeri olarak bulundu\n",hashAddr,i,tmp->key);
    }else{
        printf("%d aranan eleman dizide bulunamadi\n",key);
    }

}


HASH** initHashTable(){
    HASH** hashTable = NULL;
    int i = 0;
    hashTable = (HASH**) malloc(sizeof(HASH*)*TABLESIZE);
    if(hashTable == NULL){
        printf("Table did not allocated\n");
        exit(-1);
    }
    for(i=0;i<TABLESIZE;i++){
        hashTable[i] = (HASH*) malloc(sizeof(HASH));
        hashTable[i]->count=0;
        hashTable[i]->head = NULL;
    }
    return hashTable;
}