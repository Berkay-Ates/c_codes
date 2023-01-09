#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* next;
} NODE;

NODE* createNode(int data);

//* adding to initial 
void addFront(NODE **head,int data);

//* adding to between 
void insertToMiddle(NODE **head,int data);

//* adding to end 
void addToEnd(NODE **head,int data);

//* delete Node 
void deleteNode(NODE** head,int data);

void traverseList(NODE *head);

int main(){
    NODE *head = NULL;

    addFront(&head,10);
    addFront(&head,20);
    addFront(&head,30);
    addToEnd(&head,56);
    addToEnd(&head,120);
    addFront(&head,45);
    insertToMiddle(&head,1);
    insertToMiddle(&head,23);
    insertToMiddle(&head,999);
    traverseList(head);
    
    printf("\n");
    deleteNode(&head,20);
    deleteNode(&head,111);
    deleteNode(&head,56);
    traverseList(head);
}

void deleteNode(NODE** head,int data){
    NODE *tmp = *head;
    NODE *tmp2;

    if((*head)->data == data){
        *head = (*head)->next;
        free(tmp);
    }else{
        while(tmp->next != NULL && tmp->data != data){
            tmp2 = tmp;
            tmp = tmp->next;
        }
        if(tmp->data == data){
            tmp2->next = tmp->next;
            free(tmp);
        }
    }
}

void insertToMiddle(NODE **head,int data){
    NODE *tmp = createNode(data);
    NODE *tmp2 = *head;
    tmp->data = data;
    tmp->next = NULL;

    if(head == NULL){
        *head = tmp;
    }else{
        while( tmp2->next != NULL &&  tmp2->next->data < data ){
            tmp2 = tmp2->next;
        }
        tmp->next = tmp2->next;
        tmp2->next = tmp; 
    }

}


void addToEnd(NODE **head,int data){
    NODE *tmp = createNode(data);
    NODE *tmp2 = *head;
    tmp->data = data;
    tmp->next = NULL;

    if(head == NULL){
        *head = tmp;
    }else{
        while(tmp2->next != NULL){
            tmp2 = tmp2->next;
        }

        tmp2->next = tmp;
    }
}


void traverseList(NODE *head){
    while(head!=NULL){
        printf("%d ",head->data);
        head = head->next;
    }
}

void addFront(NODE **head,int data){
    NODE *newNode = createNode(data);
    newNode->next = (*head);
    (*head) = newNode;

}

NODE* createNode(int data){
    NODE* tmp = (NODE*) malloc(sizeof(createNode));
    tmp->data = data;
    tmp->next = NULL;

    return tmp;
}


