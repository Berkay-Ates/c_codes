#include<stdio.h>
#include<stdlib.h>


int* returnPointer(int);
void assignPointerValue(int* pointerInt,int intVariable);
 
int main(){

    //* const double pi = 3.14; 
    //* printf("%lf", pi);
    //* var names have to start with wheter chars or underscores otherwise wrong name error would be happen 

    //* int* myPointer;
    
    //* myPointer = returnPointer(2);
    //* printf("%p",myPointer);

    int testInt = 5;
    int* testPointer;
    testPointer = &testInt;
    
    //? pointer icerisinde sonuc olarak addressler bulunur biz bu addrsler uzerinden pointerin isaret ettiği degere ulasırız 
    //? pointerin degerini guncelledigimizde pointer yapılan degisikligi isaret ettigi elemana degisiklikler yansıtır. 
    //? zaten yaptıgımız degisiklik aslen pointerin adresini degistirmek degildir direk degiskenin degerini degistitmektir 

    printf("test pointer Address: %p\n",testPointer);
    printf("test pointer value: %d\n",*testPointer);

    printf("test int variable value: %d\n",testInt);
    printf("test intvariable address: %p\n", &testInt);

    assignPointerValue(testPointer,20);

    printf("test pointer Address: %p\n",testPointer);
    printf("test pointer value: %d\n",*testPointer);

    printf("test int variable value: %d\n",testInt);
    printf("test intvariable address: %p\n", &testInt);
}


int* returnPointer(int size){
    int* temp = (int*) malloc(sizeof(int)*size);
    if(temp == NULL){
        exit(-1);
    }
    printf("address of temp = %p\n",temp);
    return temp;
}


void assignPointerValue(int* pointerInt,int intVariable){
    printf("\npointer Variable Address any change func: %p\n",pointerInt);
    pointerInt = NULL;
    pointerInt = &intVariable;
    *pointerInt = intVariable;//* now pointer does not refer to int which is in main 

    printf("pointer Variable Address: %p\n",pointerInt);
    printf("pointer variable value: %d\n",*pointerInt);

    printf("int variable value: %d\n",intVariable);
    printf("int variable address: %p\n\n", &intVariable);
}

//! demekki pointerın da kendisi kopyalanıyor ama ponterin iceri de kopyalandıgı ve iccerikte address oldugundan dolayı 
//! pointerin iceriginde yapılan bir degisiklik direk addreslere yansıyacagı icin pointerin point ettigi degerler degisir


