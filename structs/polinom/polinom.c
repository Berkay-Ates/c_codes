#include<stdio.h>
#include<stdlib.h>


typedef struct{
    int age;
    int salary;
} DATA;

 typedef struct emp* EMP_POINTER;

typedef struct emp {
    DATA empData;
    EMP_POINTER employee;
}EMPLOYEE;


int main(){

   
    DATA dataOfB = {22,10};
    EMPLOYEE employeeB = {dataOfB,NULL};
    EMP_POINTER BPointer = &employeeB;


    DATA dataOfA = {21,90};
    EMPLOYEE employeeA = {dataOfA,&employeeB};
    EMP_POINTER APointer = &employeeA;


    printf("address of the B : %p \n",&employeeB);
    printf("age of B:%d , salary of B:%d \n",employeeB.empData.age,((&employeeB)->empData).salary);
    printf("B is referring to = %p\n",employeeB.employee);
    printf("Bpointer  value is : %p\n",BPointer);


    printf("address of the A : %p\n",&employeeA);
    printf("age of A:%d , salary of A:%d \n",employeeA.empData.age,((&employeeA)->empData).salary);
    printf("A is referring to = %p\n",employeeA.employee);
     printf("Apointer  value is : %p\n",APointer);
}