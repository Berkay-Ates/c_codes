#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int id;
    int v1;
    int v2;
    struct Node* next;
}NODE;

void printList(NODE* n); 
void insert(struct Node** head,int id,int v1, int v2);
NODE* intersection(NODE* start1,NODE* start2,int (*compare)(NODE*,NODE*));
int compare_by_value1(NODE* Node1,NODE* Node2);
int compare_by_value2(NODE* Node1,NODE* Node2);

int main(){
    printf("*************\n");
    NODE *start = NULL;
    insert(&start,1,10,15);
    insert(&start,2,20,15);
    insert(&start,4,20,15);
    insert(&start,7,30,20);
    insert(&start,10,30,40);
    printList(start);

    printf("*************\n");
    NODE *start2 = NULL;
    insert(&start2,1,10,15);
    insert(&start2,4,15,15);
    insert(&start2,7,25,20);
    insert(&start2,7,30,41);

    printList(start2);

    printf("------------------\n");
    NODE* start3 = intersection(start,start2,compare_by_value1);
    printList(start3);

    printf("------------------\n");
    NODE* start4 = intersection(start,start2,compare_by_value2);
    printList(start4);
}

NODE* intersection(NODE* start1,NODE* start2,int (*compare)(NODE*,NODE*)){
    NODE *head = NULL;
    while(start1->next!= NULL){
        if(compare(start1,start2) == 1){
            insert(&head,start1->id,start1->v1,start1->v2);
            insert(&head,start2->id,start2->v1,start2->v2);
            start1 = start1->next;
            start2 = start2->next;
        }else{
            start1 = start1->next;
        }
    }
    return head;
}

void insert(struct Node** head,int id,int v1, int v2){
    
    NODE *tmp = (NODE*)malloc(sizeof(NODE)*1); 
    NODE* tmp2 = *head;
        tmp->id = id;
        tmp->v1 = v1;
        tmp->v2 = v2;
        tmp->next = NULL;
    if(tmp == NULL) exit(-1);
    if(*head != NULL){
        while(tmp2->next != NULL){
            tmp2 = tmp2->next; 
        }
        tmp2->next = tmp;
    }else{
        *head = tmp;
    }  
    
}

void printList(NODE* n){
    NODE *tmp = n;
    while(tmp->next != NULL){
        printf("id: %d, v1: %d, v2: %d\n",tmp->id,tmp->v1,tmp->v2);
        tmp = tmp->next;
    }
    printf("id: %d, v1: %d, v2: %d\n",tmp->id,tmp->v1,tmp->v2);
}


int compare_by_value1(NODE* Node1,NODE* Node2){
    int result = 0;
    if(Node1->id == Node2->id && Node1->v1 == Node2->v1){
        result = 1;
    }
    return result;
}

int compare_by_value2(NODE* Node1,NODE* Node2){
    int result = 0;
    if(Node1->id == Node2->id && Node1->v2 == Node2->v2){
        result = 1;
    }
    return result;
}


