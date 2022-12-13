#include<stdio.h>
#include<stdlib.h>
 
typedef struct data{
	char name[20];
	char surname[20];
	char id[12];
}DATA;

typedef struct Employee{
	DATA *d;
	struct Employee *next;
}EMPLOYEE;

int main(){
    DATA data1 = {"james","kirk","12345"};
    DATA data2 = {"james1","kirk","12345"};
    DATA data3 = {"james2","kirk","12345"};
    EMPLOYEE emp3 = {&data3,NULL};
    EMPLOYEE emp2 = {&data2,&emp2};
    EMPLOYEE emp = {&data1,&emp2};
}