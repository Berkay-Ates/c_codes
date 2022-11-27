#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum carModels {reno ,toyotac,mercedes,audi,ford} CarModelsEnum;
typedef enum menu {add,update,delete,print,terminate} MENUENUMS;

typedef struct carStruct {
    char model[30];
    int year;
    int price;
    int count;
} CAR;

typedef struct carStruct* CARPOINTER;

typedef struct cars{
    struct carStruct* carList;
    int carListSize;
}CARS;

void setMenuOptions(MENUENUMS* menuEnums);
void printCarList(CARS* cars);
void reallocCarList(CARS* cars);
void addNewCar(CARS* cars,int index);
void deleteCar(CARS* cars);
void updateCar(CARS* cars);

int main(){

    int i = 0;
    MENUENUMS menuEnums;

    CAR reno = {"reno model",2000,100000,12};
    CAR mercedes = {"mercedes model",2000,100000,12};
    CAR toyota = {"toyota model",2000,100000,12};

    CARS cars;

    cars.carList = (CAR*) malloc(sizeof(CAR)*3);
    cars.carListSize = 3;
    cars.carList[0] = reno;
    cars.carList[1] = toyota;
    cars.carList[2] = mercedes;

    printCarList(&cars);

    setMenuOptions(&menuEnums);

        while(menuEnums != terminate){
            switch (menuEnums){
        case add:
                printf("add selected\n");
                //* realloc the carlist then add new car to the carList 
                reallocCarList(&cars);
                addNewCar(&cars,cars.carListSize-1);
                printCarList(&cars);
            break;

        case update:
                printf("update selected\n");
                updateCar(&cars);

            break;

        case delete:
                printf("delete selected\n");
                //* delete selected element then decrease the size of carlist
                deleteCar(&cars);
            break;

        case print:
                printf("print selected\n");
                printCarList(&cars);
            break;
        case terminate:
                printf("program just terminating...\n");
            break;
        }
        setMenuOptions(&menuEnums);

    }
}

void deleteCar(CARS* cars){
    int deleteIndex = 0;
    do{
        printf("Enter index of car that you want to delete\n");
        scanf("%d",&deleteIndex);
    }while(deleteIndex >= cars->carListSize);

    strcpy(cars->carList[deleteIndex].model,cars->carList[cars->carListSize-1].model);
    cars->carList[deleteIndex].year = cars->carList[cars->carListSize-1].year;
    cars->carList[deleteIndex].price = cars->carList[cars->carListSize-1].price;
    cars->carList[deleteIndex].count = cars->carList[cars->carListSize-1].count;

    cars->carListSize = cars->carListSize-1;
}

void updateCar(CARS* cars){
    int updateIndex=0;
    do{
        printf("Enter index of car that you want to update\n");
        scanf("%d",&updateIndex);
    }while(updateIndex >= cars->carListSize);
    addNewCar(cars,updateIndex);
}

void addNewCar(CARS* cars,int index){
    printf("model:");
    scanf("%s",cars->carList[index].model);
    printf("year:");
    scanf("%d",&cars->carList[index].year);
    printf("price:");
    scanf("%d",&cars->carList[index].price);
    printf("count:");
    scanf("%d",&cars->carList[index].count);
}

void reallocCarList(CARS* cars){
    CAR* tmp = (CAR*) realloc(cars->carList,sizeof(CAR)*(cars->carListSize+1)); if(tmp == NULL) exit(-1);
    cars->carListSize = cars->carListSize+1;
    
    cars->carList = tmp;
    printf("car list have been expanded.. new size is: %d\n",(cars->carListSize));
    printf("Please answer following qustions\n");
}

void printCarList(CARS* cars){
    int i = 0;
     for(i = 0;i<cars->carListSize;i++){
        printf("%d - model: %s, year: %d, price: %d , count: %d",i,cars->carList[i].model, cars->carList[i].year, cars->carList[i].price, cars->carList[i].count);
        printf("\n");
    }
}

void setMenuOptions(MENUENUMS* menuEnums){
    printf("0-add\n1-update\n2-delete\n3-print\n4-terminate\nselection:");
    scanf("%d",menuEnums);
}