#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
typedef struct data {
    char name[20];
    char surname[20];
    char id[12];
}DATA;

typedef struct employee{
    DATA* data;
    struct employee* next;
} EMPLOYEE;

typedef enum menu_options {addEmp,removeEmp,printIdFirst,printSurnameFirst,printNameFirst,quit} MENU;

void print(char* strToPrint);
void addEmployee(EMPLOYEE **head,EMPLOYEE **newEmp);
void setStr(char *def,char * location);
EMPLOYEE* getEmployee();
void printEmpList(EMPLOYEE *head, int empCount);
void printNodeData(DATA* data);
void removeNode(EMPLOYEE **head,int *userCount);

int main(){
    MENU menuOptions;
    EMPLOYEE* head = NULL;
    int totalEmployee = 0;
    do{
        print("-----------------------------------------------------------");
        print("0-Add\n1-Remove\n2-Print Id First\n3-Print Surname First\n4-Print Name First\n5-Quit");
        scanf("%d",&menuOptions);
        print("-----------------------------------------------------------");

        switch (menuOptions){
            case addEmp:
                print("add selected");
                EMPLOYEE* data = getEmployee();
                addEmployee(&head,&data);
                totalEmployee++;
                printEmpList(head,totalEmployee);
                break;
            case removeEmp:
                    removeNode(&head,&totalEmployee);
                break;
            case printIdFirst:
                break;
            case printSurnameFirst:
                break;
            case printNameFirst:

                break;
            case quit:
                menuOptions = quit;
                break;
        }

    }while(menuOptions != quit);
}

void removeNode(EMPLOYEE **head,int *userCount){
    int count = *userCount;
    char id[12];
    printf("Id to be deleted:");
    scanf("%s",id);
    int found = 0;
    EMPLOYEE *tmp = *head;
    EMPLOYEE *prev = NULL;
    while(found == 0 && tmp != NULL && count > 0){
        count --;
        if(strcmp(tmp->data->id,id) == 0){
            found = 1;
            if(prev == NULL){
                //* head silinecek 
                *head = tmp->next;
                (*userCount)--;
            }else{
                //* arad bir deger silinecek 
                //* silinecek olan bu deger cakma head olacagı icin 
                //* cakma head e isaret eden yer artık cakma headin isaret ettig noktaya isaret etmeye baslayacak 
                //* boylece artık cakma head ortadan cıktı koptu gitti 
                //* artık kimse ona isaret etmiyor 
                prev->next = tmp->next;
                (*userCount)--;
            }
            //? cakma headi freeleyelim 
            free(tmp);
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void printEmpList(EMPLOYEE *head, int empCount){
    int i = 0;
    EMPLOYEE* tmp = head;
    print("-----------------------------*** starts List ***-----------------------------");
    for (i = 0; i < empCount; i++){
        //printf("ID:%d\n",i);
        printNodeData(tmp->data);
        tmp = tmp->next;
    }
    print("-----------------------------***  End  List  ***-----------------------------");
}

void addEmployee(EMPLOYEE **head,EMPLOYEE **newEmp){
    (*newEmp)->next = *head;
    *head = *newEmp;
}

EMPLOYEE* getEmployee(){
    DATA *data = (DATA*) malloc(sizeof(DATA)*1);
    EMPLOYEE *emp = (EMPLOYEE*) malloc(sizeof(EMPLOYEE)*1);
    if(data == NULL || emp == NULL) print("could not allocated memeory for new employee");
    setStr("id:",data->id);
    setStr("name:",data->name);
    setStr("surname:",data->surname);
    emp->next = NULL;
    emp->data = data;
    return emp;
}

void setStr(char *def,char * location){
    printf("%s",def);
    scanf("%s",location);
}

void printNodeData(DATA* data){
    printf("id:%s ,name:%s, surname:%s\n",data->id,data->name,data->surname);
}

void print(char* strToPrint){
    printf("%s\n",strToPrint);
}
