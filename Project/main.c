#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//* struct definitions
typedef struct Ogrenci{
    char ogrID[9];
    char ad[30];
    char soyad[30];
    int puan;
    struct Ogrenci*next;
    struct Ogrenci*prev;
} OGRENCI;

typedef struct Yazar{
    int yazarID;
    char yazarAd[30];
    char yazarSoyad[30];
    struct Yazar*next;
} YAZAR;
  
typedef struct kitapOrnek { 
    char EtiketNo[20]; 
    char Durum[8]; 
    struct KitapOrnek *next;
} KITAPORNEK;

typedef struct Kitap {
    char kitapAdi[30]; 
    char ISBN[14]; 
    int adet; 
    struct Kitap *next; 
    struct KitapOrnek *head;
} KITAP;

typedef struct KitapYazar{
    char ISBN[14]; 
    int YazarID;
} KITAPYAZAR;

typedef struct Tarih{
    int gun:5; 
    int ay:4; 
    int yil:12;
} TARIH;

typedef struct KitapOdunc{
    char EtiketNo[20]; 
    char ogrID[8]; 
    int islemTipi:1; 
    struct Tarih islemTarihi;
}KITAPODUNC;

//* enum definitions
typedef enum mainMenu {student,book,writers,exitMainMenu} MAINMENU;
typedef enum writerOptions {addWriter,removeWriter,listWriters,updateWriter,writerInfo,exitWriters} WRITERMENU;
typedef enum studentOptions {addStd,removeStd,updateStd,listStd,stdInfo,uSubmittedStd,banedStd,submitBook,barrowBook,exitStd} STUDENTMENU; 

//* writer func macros 
void print(char *msg);
void printDiv();
char* addWriterToList(YAZAR** head,char* writerName,char* writerSurname);
void readWriterFile(FILE* file,YAZAR **head );
void printWriters(YAZAR *head);
char* removeWriterFromList(YAZAR **head, int id);
char* updateWriterFromList(YAZAR** head,int writerID,char* writerName,char* writerSurname);
void writeListToWriterFile(FILE *file,YAZAR *head);

//* student funcs macros
void readStdFromFile(FILE* stdFile,OGRENCI** stdHead);


int readBookWriterFileToList(FILE *file, KITAPYAZAR** bookWriter);
void printWriterInfo(YAZAR *head,char* writerName,KITAPYAZAR *bookWriter,int totalBook);

int main(){
    MAINMENU mainmenuOpt;
    WRITERMENU writerOpt;
    STUDENTMENU stdMenu;

    KITAPYAZAR *bookWriterList;
    FILE *writerBookFile;

    YAZAR *writerHead = NULL;
    FILE *writerFile;
    int totalBook =0;

    OGRENCI *stdHead;
    FILE *stdFile;


    writerBookFile = fopen("KitapYazar.csv","r");
    if(writerBookFile == NULL) exit(-1);
    totalBook = readBookWriterFileToList(writerBookFile,&bookWriterList);
   
    do{

        printDiv();
        print("Choose one of them to proceed your work\n0-Student\n1-Book\n2-Writers\n3-Exit Main Menu");
        printf("selection:");
        scanf("%d",&mainmenuOpt);
        printDiv();

        switch(mainmenuOpt){
            case student:

                stdFile = fopen("Ogrenciler.csv","r");
                if(stdFile == NULL) exit(-1);
                readStdFromFile(stdFile,&stdHead);
                fclose(stdFile);

               do{
                    printDiv();
                    print("Choose one of them to proceed your work\n0-add std\n1-remove std\n2-update std\n3-list std\n4-std Info\n5-Unsubmitted Stds\n \
                            \n6-banned std\n7-submit book\n8-barrow book\n9-exit std");
                    printf("selection:");
                    scanf("%d",&stdMenu);
                    printDiv();
                    switch(stdMenu){

                        case addStd:

                            break;
                        case removeStd:

                            break;
                        case updateStd:

                            break;
                        case listStd:

                            break;
                        case stdInfo:

                            break;
                        case uSubmittedStd:
                        
                            break;
                        case banedStd:

                            break;
                        case submitBook:

                            break;
                        case barrowBook:

                            break;
                        case exitStd:
                            print("std menu exitted");
                            break;
                        default:
                            print("wrong selection please select options included above");
                        break;  
                    }
               }while(stdMenu != exitStd);

            break;
            case book:
                print("book Selected");    
            break;    
            case writers:
                writerHead = NULL;
                writerFile = fopen("Yazarlar.csv","r");
                if(writerFile == NULL) exit(-1);
                readWriterFile(writerFile,&writerHead);
                fclose(writerFile);
                fclose(writerBookFile);
                YAZAR newWriter;

                //* dosyadan okuyup yazarları bir linked list icerisine ekleyelim
                //* devamında linked list icerisinde istenildigi kadar islem yapıp break yaparken de dosyayı guncel linkli liste ile 
                //* guncelleyebiliriz 

                do{
                    printDiv();
                    print("Choose one of them to proceed your work\n0-add writer\n1-remove writer\n2-list writers\n3-update\n4-writer Info\n5-exit Writer menu");
                    printf("selection:");
                    scanf("%d",&writerOpt);
                    printDiv();

                    switch(writerOpt){
                        case addWriter:
                            // printf("writer id:"); 
                            // scanf("%d",&newWriter.yazarID);
                            printf("writer name:");
                            scanf("%s",newWriter.yazarAd);
                            printf("writer surname:");
                            scanf("%s",newWriter.yazarSoyad);
                            print(addWriterToList(&writerHead,newWriter.yazarAd,newWriter.yazarSoyad));
                            break;
                        case removeWriter:
                            print("writer ID to be deleted");
                            printf("id:");
                            scanf("%d",&newWriter.yazarID);
                            print(removeWriterFromList(&writerHead, newWriter.yazarID));
                            break;
                        case listWriters:
                            printWriters(writerHead);
                            break;
                        case updateWriter:
                            //* update any writer
                            printf("writer id(for detection):");
                            scanf("%d",&newWriter.yazarID);
                            printf("writer name:");
                            scanf("%s",newWriter.yazarAd);
                            printf("writer surname:");
                            scanf("%s",newWriter.yazarSoyad);
                            print(updateWriterFromList(&writerHead,newWriter.yazarID,newWriter.yazarAd,newWriter.yazarSoyad));
                        break;
                        case writerInfo:
                            //* show writer all info by its name
                            printf("writer name:");
                            scanf("%s",newWriter.yazarAd);
                            printWriterInfo(writerHead,newWriter.yazarAd,bookWriterList,totalBook);
                            break;
                        case exitWriters:
                            print("writers exitted");
                        break;
                        default:
                            print("wrong selection please select options included above");
                        break;  
                    }
                }while(writerOpt != exitWriters);
                //* writer all of the structs to writer files and close the file end of writer operations 
                writerFile = fopen("YAZARLAR.csv","w");
                if(writerFile == NULL) exit(-1);
                writeListToWriterFile(writerFile,writerHead);
                fclose(writerFile);
            
            break;
            case exitMainMenu:
                print("Main Menu Exitted");    
            break; 
            default:
                print("wrong selection please select options included above");
            break;  
        }
        
    } while(mainmenuOpt != exitMainMenu);
}


void readStdFromFile(FILE* stdFile,OGRENCI** stdHead){
    printf("read func called\n");
    int read = 0;
     char number[9];
    char name[30];
    char surname[30];
    int point;
    //*17011015,Trevor,Hastie,100
    while(!feof(stdFile)){
        read = fscanf(stdFile,"%9[^,],%30[^,],%30[^,],%d\n",number,name,surname,&point);
        if(read != 4 && !feof(stdFile)){
            print("there was an error while reading the file");
        }else if(read == 4 ){
            addStdToList(stdHead,number,name,surname,point);
        }

        if(ferror(stdFile)){
            print("there was an error while reading Kitap-Yazar file ");
            exit(-1);
        }
    }
}

void addStdToList(OGRENCI** stdHead,char* number,char* name,char* surname,int point){
    OGRENCI *tmp = (OGRENCI*) malloc(sizeof(OGRENCI));

}

void printWriterInfo(YAZAR *head,char* writerName,KITAPYAZAR *bookWriter,int totalBook){
    YAZAR *tmp = head;
    int found = 0;
    int i = 0;
    while(tmp!= NULL){
        if(strcmp(tmp->yazarAd,writerName) == 0){
            
            printf("Id:%d\nName:%s\nSurname:%s\n",tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
            for(i=0;i<totalBook;i++){
                if(bookWriter[i].YazarID == tmp->yazarID){
                    found = 1;
                    printf("ISBN: %s, writerId: %d\n",bookWriter[i].ISBN ,bookWriter[i].YazarID );
                }
            }
        }
        tmp = tmp->next;
    }
    if(found == 0){
        print("there are no book written by given author");
    }
}

int readBookWriterFileToList(FILE *file, KITAPYAZAR** bookWriter){
    //* book writer file just a array, we don't need linked list so just assign all elements to a list 
    int read = 0;
    int count = 0;
    int size = 1;
    char ISBN[14]; 
    int yazarID;
    KITAPYAZAR *tmpBookWriter = (KITAPYAZAR*) malloc(sizeof(KITAPYAZAR)*1);
    
    do{
        read = fscanf(file,"%13[^,],%d\n",ISBN,&yazarID);
        if(read != 2 && !feof(file)){
            print("there was an error while reading Kitap-Yazar file");
            exit(-1);
        }else if(read == 2){
            if(size == count){
                tmpBookWriter = (KITAPYAZAR*) realloc(tmpBookWriter,sizeof(KITAPYAZAR)*size*2);
                size = size*2;
            }
            int i = 0;
            while(i<13){
                tmpBookWriter[count].ISBN[i] = ISBN[i];
                i++;
            }
            tmpBookWriter[count].ISBN[i] = '\0';
            tmpBookWriter[count].YazarID = yazarID;
            count++;
        }
        if(ferror(file)){
            print("there was an error while reading Kitap-Yazar file ");
            exit(-1);
        }
    }while(!feof(file));
    *bookWriter = tmpBookWriter;
    return count;
}


void writeListToWriterFile(FILE *file,YAZAR *head){
    YAZAR *tmp = head;
    YAZAR *prev;

    do{
        fprintf(file,"%d,%s,%s\n",tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
        if(ferror(file)) print("there was an error while writing writers to file");
        prev = tmp;
        tmp = tmp->next;
        free(prev);
    }while(tmp != NULL);
}

char* updateWriterFromList(YAZAR** head,int writerID,char* writerName,char* writerSurname){
    int updated = 0;
    YAZAR *tmp = *head;

    while(tmp != NULL && updated == 0){
        if(tmp->yazarID == writerID){
            updated = 1;
            strcpy(tmp->yazarAd,writerName);
            strcpy(tmp->yazarSoyad,writerSurname);
        }
        tmp = tmp->next;
    }
    return updated == 1 ? "desired writer updated" : "writer does not found to be updated";
}

char* removeWriterFromList(YAZAR **head, int id){
    int found = 0;
    YAZAR *tmp = *head;
    YAZAR *prev=NULL;
    while(tmp != NULL && found == 0){
        if(tmp->yazarID == id){
            found = 1;
            if(prev == NULL){
                //* asil head silinecek 
                *head = tmp->next; //* *head = (*head)->next; 
            }else{
                //* ic nodelardan biri silinecek bu da tmp ye denk geliyor 
                //* buradan tmp ye isaret eden node artık tmp nin onundeki yada tmp nin isaret ettigi node a isaret etmeli
                prev->next = tmp->next;
                //* we also need delete the writer id or make -1 the writer id from the book writer list 
            }
            free(tmp);
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return found == 1 ? "desired writer deleted" : "writer does not found to be deleted";
}

void printWriters(YAZAR *head){
    YAZAR *tmp = head;
    while(tmp != NULL){
        printf("%d , %s , %s\n", tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
        tmp = tmp->next;
    }

}

void readWriterFile(FILE* file,YAZAR **head){
    int read = 0;
    //* 8, Jorge, Nocedal

    int id;
    char n1[30];
    char n2[30];

    do{
        read = fscanf(file,"%d,%29[^,],%29[^\n]",&id,n1,n2);
        
        if(read != 3 && !feof(file)){
            print("there was an error while reading the Writer file");
            exit(-1);
        }else if(read == 3){
            addWriterToList(head,n1,n2);
            printf(" read value is :%d\n",read);
            printWriters(*head);
        }
        if(ferror(file)){
            print("there was an error while reading the Writer file");
            exit(-1);
        }
    }while(!feof(file));
}

char* addWriterToList(YAZAR** head,char* writerName,char* writerSurname){
    YAZAR *tmp = (YAZAR*) malloc(sizeof(YAZAR)*1);
    YAZAR *tmp2 = *head;
    // tmp->yazarID = writerID;
    strcpy(tmp->yazarAd,writerName);
    strcpy(tmp->yazarSoyad,writerSurname);

    if(*head == NULL){
        tmp->yazarID = 1;
        *head = tmp;
    }else{
        while(tmp2->next != NULL){
             tmp2 = tmp2->next;
             if(tmp->yazarID == tmp2->yazarID){
                 return "there are duplicated writer id Wheater in the file or given values. Please check the \ngiven values or the file values of writer id";
            }
        }
        tmp->yazarID = (tmp2->yazarID) +1;
        //printf("%d\n",tmp2->yazarID);
        tmp2->next = tmp;
    }
    return "writer added to list";
}

void print(char *msg){
    printf("%s\n",msg);
}

void printDiv(){
    print("-----------------------------------------------------------");
}