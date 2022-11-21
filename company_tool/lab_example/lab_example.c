#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum menuOptions{add,search,list,delete,exitProg} MENUOPTIONS;

typedef struct employee{
    char name[30];
    int age;
    int salary;
} EMPLOYEE;

void printOperationsMenu();
EMPLOYEE* reallocEmployees(int newSize,EMPLOYEE* currentEmployees);
void listEmployees(EMPLOYEE* employee,int emplooyeCount);
void searchEmploye(EMPLOYEE* emplooyees,int emplooyeCount,char* searching);
void deleteEmploye(EMPLOYEE* emplooyees,int* emplooyeCount,char* searching);

int main(){

    int flag = 1;
    MENUOPTIONS options;
    EMPLOYEE *employees = (EMPLOYEE*) malloc(sizeof(EMPLOYEE)*2); //* if current size == employee Count then double the array
    int currentSize = 2;
    int employeeCount = 0;
    char searchKeyword[30];

    do{
        printOperationsMenu();
        printf("desired operations:");
        scanf("%d",&options);
        
        switch (options){
        case add:
                printf("add selected\n");
                if(currentSize == employeeCount){
                    employees = reallocEmployees(currentSize*2,employees);
                    currentSize = currentSize*2;
                }
                printf("name:"); scanf("%s",(employees+employeeCount)->name);//* char da bulunan dizi oldugu icin zaten pointer gitti 
                printf("age:"); scanf("%d",&employees[employeeCount].age);
                printf("salary:"); scanf("%d",&(employees+employeeCount)->salary);             
                employeeCount++;
            break;
        case search:
                printf("search selected\n");
                printf("searched person name:");
                scanf("%s",searchKeyword);
                searchEmploye(employees,employeeCount,searchKeyword);
            break;
        case list:
                printf("list selected\n");
                listEmployees(employees,employeeCount);
            break;
        case delete:
                printf("delete selected\n");
                printf("person name to be deleted:");
                scanf("%s",searchKeyword);
                deleteEmploye(employees,&employeeCount,searchKeyword);
            break;
        case exitProg:
                printf("exitting..\n");
                flag=0;
            break;

        default:
            flag = 0;
            printf("you selected an unknown options, which causes terminating the program\n");
            break;
        }

    }while(flag == 1);
    free(employees);
}


void deleteEmploye(EMPLOYEE* emplooyees,int* emplooyeCount,char* searching){
    int i = 0;
   
    while(strcmp(emplooyees[i].name,searching) != 0 && i<*emplooyeCount){
        i++;
    }
    
    if(i == *emplooyeCount-1){
        *emplooyeCount = *emplooyeCount-1;
    }else if(strcmp(emplooyees[i].name,searching) == 0){
        printf("This guy deleted -> %s, %d, %d\n",emplooyees[i].name,emplooyees[i].age,emplooyees[i].salary);
        strcpy(emplooyees[i].name,emplooyees[*emplooyeCount-1].name);
        emplooyees[i].age = emplooyees[*emplooyeCount-1].age;
        emplooyees[i].salary = emplooyees[*emplooyeCount-1].salary;
        (*emplooyeCount)--;
       
    }else{
        printf("searching emplooye did not exist in the database to be deleted\n");
    }
}

void searchEmploye(EMPLOYEE* emplooyees,int emplooyeCount,char* searching){
    int i = 0;
    while(strcmp(emplooyees[i].name,searching) != 0 && i<emplooyeCount){
        i++;
    }
    if(strcmp(emplooyees[i].name,searching) == 0){
        printf("%s, %d, %d\n",emplooyees[i].name,emplooyees[i].age,emplooyees[i].salary);
    }else{
        printf("searching emplooye did not exist in the database\n");
    }
}


void listEmployees(EMPLOYEE* employee,int emplooyeCount){
    int i = 0;
    for(i=0;i<emplooyeCount;i++){
        printf("%s, %d, %d\n",employee[i].name,employee[i].age,employee[i].salary);
    }

}

void printOperationsMenu(){
    printf("0-ADD\n1-SEARCH\n2-LIST\n3-DELETE\n4-EXIT\n");
}

EMPLOYEE* reallocEmployees(int newSize,EMPLOYEE* currentEmployees){
    EMPLOYEE* tmp = (EMPLOYEE*) realloc(currentEmployees,sizeof(EMPLOYEE)*newSize);
    if(tmp != NULL){
        printf("reached to arrays bound, array expanded to %d\n",newSize);
    }else{
        printf("array could not be expanded so program terminating\n");
        exit(-1);
    }
    return tmp;
}