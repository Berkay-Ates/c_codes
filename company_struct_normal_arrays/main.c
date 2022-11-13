#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum ENUMROLES {manager, CEO, IC, CTO} ROLES;
typedef enum ENUMLISTROLES {HEADNODE,TAILNODE,INNERNODE} LISTROLES;
//* enum ENUMROLES {manager,contentCreator,IC,SEO,CTO};
//* typedef enum ENUMROLES EnumRoles;

typedef struct employee* EMP_POINTER;
typedef struct employee{
    char name[100];
    int age;
    ROLES companyRole;
    LISTROLES listRole;
}EMPLOYEE;

void printEmployees(int empNumber,EMPLOYEE* employees);
char* getNodeRole(EMPLOYEE emp);
char* getCompanyRole(EMPLOYEE emp);
EMPLOYEE* reallocateEmp(EMPLOYEE* emp,int newSize);
void registerEmp(EMPLOYEE* node);
int main(){

    EMPLOYEE node;
    EMPLOYEE HEAD;
    HEAD.age = 21;
    strcpy(HEAD.name,"HEAD node");
    HEAD.companyRole = CEO;
    HEAD.listRole = 0;
    EMPLOYEE employees[10];
    employees[0] = HEAD;
    int i = 1;

    int flag=0;
    
    do{
        registerEmp(&node);
        employees[i] = node;
        printf("more employee?: ");
        scanf("%d",&flag); 
        i++;
    }while(flag == 1);

    printEmployees( i,employees);
}


void registerEmp(EMPLOYEE* node){
    int roles;
    int age;
    printf("name:");
    scanf("%s",node->name);
    printf("age:");
    scanf("%d",&age);
    node->age = age;
    printf("0-manager \n1-CEO \n2-IC,\n3-CTO\n");
    printf("emp. role:");
    scanf("%d",&roles);
    node->companyRole = roles;
    //manager, CEO, IC, CTO
    node->listRole = INNERNODE;
}


EMPLOYEE* reallocateEmp(EMPLOYEE* empLIST,int newSize){
    EMPLOYEE* emp;
    emp = (EMPLOYEE*) realloc(empLIST,sizeof(EMPLOYEE)*newSize);
    if(emp != NULL){
        return emp;
    }
    exit(-1);
}

void printEmployees(int empNumber,EMPLOYEE* employees){
    int i;
    for(i=0;i<empNumber;i++){
        printf("%d: name:%s, age:%d, listRole:%s, companyRole:%s",i,employees[i].name, employees[i].age,getNodeRole(employees[i]),getCompanyRole(employees[i]));  
        printf("\n");
    }
}

char* getNodeRole(EMPLOYEE emp){
    char msg[50];
    if(emp.listRole == HEADNODE){
        return "head node";

    }else if(emp.listRole == INNERNODE){
       return "inner node";

    }else{
       return "tail node";
    }
}


char* getCompanyRole(EMPLOYEE emp){
    char msg[50];
    if(emp.companyRole == manager){
        return "manager";

    }else if(emp.companyRole == CEO){
       return "CEO";

    }else{
       return "NOT IMPLEMENTED ROLE IN ELSE-IF";
    }
}






