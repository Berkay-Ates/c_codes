#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <time.h>

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
    char Durum[9]; 
    struct kitapOrnek *next;
} KITAPORNEK;

typedef struct Kitap {
    char kitapAdi[30]; 
    char ISBN[14]; 
    int adet; 
    struct Kitap *next; 
    struct kitapOrnek *head;
} KITAP;

typedef struct KitapYazar{
    char ISBN[14]; 
    int YazarID;
} KITAPYAZAR;

typedef struct Tarih{
    unsigned int gun:5; 
    unsigned int ay:4; 
    unsigned int yil:12;
} TARIH;

typedef struct KitapOdunc{
    char EtiketNo[20]; 
    char ogrID[9]; 
    unsigned int islemTipi:1; //* odunc alma veya teslim etme -0 odunc alma -1 teslim etme
    struct Tarih islemTarihi;
}KITAPODUNC;

//* enum definitions
typedef enum mainMenu {student,book,writers,exitMainMenu} MAINMENU;
typedef enum writerOptions {addWriter,removeWriter,listWriters,updateWriter,writerInfo,exitWriters} WRITERMENU;
typedef enum studentOptions {addStd,removeStd,updateStd,listStd,stdInfo,unSubmittedStd,bannedStd,submitBook,barrowBook,exitStd} STUDENTMENU; 
typedef enum bookOptions {addBook,removeBook,updateBook,BookInfo,lateBooks,shelfBook,matchBWrt,updataBWrt,listBooks,listBookHistory,exitBook} BOOKMENU;

//* writer func macros 
void print(char *msg);
void printDiv();
char* addWriterToList(YAZAR** head,char* writerName,char* writerSurname);
void readWriterFile(FILE* file,YAZAR **head );
void printWriters(YAZAR *head);
char* removeWriterFromList(YAZAR **head, int id);
char* updateWriterFromList(YAZAR** head,int writerID,char* writerName,char* writerSurname);
void writeWriterListToWriterFile(FILE *file,YAZAR *head);
void printWriterNode(int id,char* name,char* surname);

//* student funcs macros
void readStdFromFile(FILE* stdFile,OGRENCI** stdHead);
void writeStdFileFromList(FILE* stdFile,OGRENCI *stdHead);
char* addStdToList(OGRENCI** stdHead,char* number,char* name,char* surname,int point);
void printStdList(OGRENCI* head);
char* removeStdFromList(OGRENCI **stdHead,char* name);
char* updateStdFromList(OGRENCI **stdHead,char* stdId,char* stdName,char* stdSurname);
void printStdInfo(OGRENCI* stdHead,char* stdName,KITAP * booksHead,int totalBookOpr, KITAPODUNC* bookHistory);
void printStdNode(OGRENCI* tmp);
void printUnsubmittedStd(KITAPODUNC* bookHist,int totalOpr,OGRENCI* std);
void printBannedStd(KITAPODUNC* bookHist,int totalOpr,OGRENCI* std);
int chekStdDetail(OGRENCI* stdHead,char* stdID);


//* book funcs macros 
void readBooksFileToList(FILE* bookFile,KITAP** booksHead,int totalOperations,KITAPODUNC* bookOperationHistory);
void writeBookBorrowFileFromList(FILE* bookBorrowFile,KITAPODUNC* bookBorrowList,int* totalBookOperations);
void writeBookFileFromBookList(FILE *file, KITAP* bookHead);
void addBookToList(KITAP** booksHead,char* bookName,char* ISBN, int bookCount,int totalOperations,KITAPODUNC* history);
void readBookBorrowFileToList(FILE* bookProcessFile,KITAPODUNC** bookBorrowList,int* totalBookOperations);
void printBOOKS(KITAP* books);
void printBookNode(KITAP* book);
void printBookNameNode(char* bookName,KITAP* books);
void addBookToChildList(KITAPORNEK** head,char* label,char* state);
void printBookHistoryItem(KITAPODUNC bookBorrow);
int checkBookState(KITAP** booksHead,char * ISBN);
void proceedBookBorrowing(KITAP **booksHead, char* ISBN ,int* totalBookOperations,KITAPODUNC** bookHistory,char* stdId);
void proceedBookSubmitting(OGRENCI** std ,KITAP **booksHead,char* stdID, int totalBookOperations,KITAPODUNC** bookBorrowList);
int getDateAsDays(TARIH date);
char* removeBookFromList(int totalBookOperations,KITAPODUNC* bookBorrowList,KITAP** booksHead,char* ISBN,int *totalBookWriter,KITAPYAZAR** bookWriter);
int proceedAddNewBookToLib(KITAP** booksHead,YAZAR** writerHead,KITAP newBOOK, int totalBookOperations, KITAPODUNC* bookBorrowList,int *totalBookWriter,KITAPYAZAR** bookWriter);
void printSelfBook(KITAP *head);
void printLateBooks(int totalBookOperations,KITAPODUNC* bookBorrowList);


void readBookWriterFileToList(FILE *file, KITAPYAZAR** bookWriter,int* totalWriter);
void writeBookWriterFileFromList(FILE *file, KITAPYAZAR* bookWriter,int* totalBookWriter);
void printWriterBookList( KITAPYAZAR* bookWriter,int totalBookWriter);
void printWriterInfo(YAZAR *head,char* writerName,KITAPYAZAR *bookWriter,int totalBookWriter);

int main(){                                                                                                                            
    char* mainMenuInfo = "Choose one of them to proceed your work\n0-Student\n1-Book\n2-Writers\n3-Exit Main Menu";
    char* bookMenuInfo = "Choose one of them to proceed your work\n0-add book\n1-remove book\n2-update book\n3-Book Info \n4-late books\n5-books on self\n6-match book with writers\n7-update Book Writer\n8-List Books\n9-listBookHistory\n10-exit Book Menu";
    char* stdMenuInfo = "Choose one of them to proceed your work\n0-add std\n1-remove std\n2-update std\n3-list std\n4-std Info\n5-Unsubmitted Stds\n6-banned std\n7-submit book\n8-barrow book\n9-exit std";
    char* writerMenuInfo = "Choose one of them to proceed your work\n0-add writer\n1-remove writer\n2-list writers\n3-update\n4-writer Info\n5-exit Writer menu";

    MAINMENU mainmenuOpt;
    WRITERMENU writerOpt;
    BOOKMENU bookMenu;
    STUDENTMENU stdMenu;

    KITAP bookOBJ;
    OGRENCI stdOBJ;

    KITAP* booksHead = NULL;
    FILE* bookFile;

    KITAPODUNC *bookBorrowList;
    
    FILE* bookBorrowFile;
    int totalBookOperations;

    KITAPYAZAR *bookWriterList;
    FILE *writerBookFile;

    YAZAR *writerHead = NULL;
    YAZAR newWriter;
    FILE *writerFile;
    int totalBookWriter =0;

    OGRENCI *stdHead = NULL;
    FILE *stdFile;

    writerBookFile = fopen("KitapYazar.csv","r");
    if(writerBookFile == NULL) exit(-1);
    readBookWriterFileToList(writerBookFile,&bookWriterList,&totalBookWriter);
    printWriterBookList(bookWriterList,totalBookWriter);
    fclose(writerBookFile);

    bookBorrowFile = fopen("KitapOdunc.csv","r");
    if(bookBorrowFile == NULL) exit(-1);
    readBookBorrowFileToList(bookBorrowFile,&bookBorrowList,&totalBookOperations);
    fclose(bookBorrowFile);

    bookFile = fopen("Kitaplar.csv","r");
    if(bookFile == NULL) exit(-1);
    readBooksFileToList(bookFile,&booksHead,totalBookOperations,bookBorrowList);
    fclose(bookFile);

    writerHead = NULL;
    writerFile = fopen("Yazarlar.csv","r");
    if(writerFile == NULL) exit(-1);
    readWriterFile(writerFile,&writerHead);
    fclose(writerFile);

    stdHead = NULL;
    stdFile = fopen("Ogrenciler.csv","r");
    if(stdFile == NULL) exit(-1);
    readStdFromFile(stdFile,&stdHead);
    fclose(stdFile);


    do{
        printDiv();
        print(mainMenuInfo);
        printf("selection:");
        scanf("%d",&mainmenuOpt);
        printDiv();

        switch(mainmenuOpt){
            case student:
               do{
                    printDiv();
                    print(stdMenuInfo);
                    printf("selection:");
                    scanf("%d",&stdMenu);
                    printDiv();
                    OGRENCI newStd;
                    switch(stdMenu){
                        case addStd:
                            printf("number:");
                            scanf("%s",newStd.ogrID);
                            printf("name:");
                            scanf("%s",newStd.ad);
                            printf("surname:");
                            scanf("%s",newStd.soyad);
                            print(addStdToList(&stdHead,newStd.ogrID,newStd.ad,newStd.soyad,100));
                            break;
                        case removeStd:
                            printf("std Name(deletion):");
                            scanf("%s",newStd.ad);
                            print(removeStdFromList(&stdHead,newStd.ad));
                            //TODO teslim edilmemis kitaplar varsa sildirtmemeliyiz 
                            break;
                        case updateStd:
                            //TODO we have to loop through other elements and update all of them 
                            printf("number(for detection):");
                            scanf("%s",newStd.ogrID);
                            printf("name(new):");
                            scanf("%s",newStd.ad);
                            printf("surname(new):");
                            scanf("%s",newStd.soyad);
                            print(updateStdFromList(&stdHead,newStd.ogrID,newStd.ad,newStd.soyad));
                            break;
                        case listStd:
                            printStdList(stdHead);
                            break;
                        case stdInfo:
                            printf("std Name(ForInfo):");
                            scanf("%s",newStd.ad);
                            //TODO have to update this func because we need std book info also (borrow something elses)
                            //* ID bilgisi veya Ad-Soyad bilgisi alınan öğrencinin kişisel bilgileri (Ad, Soyad, ID, Puan
                            //* vb) ve tüm kitap hareketleri listelenmelidir.
                            printStdInfo(stdHead,newStd.ad,booksHead,totalBookOperations,bookBorrowList);
                            break;
                        case unSubmittedStd:
                            printUnsubmittedStd(bookBorrowList,totalBookOperations,stdHead);
                            break;
                        case bannedStd:
                            printBannedStd(bookBorrowList,totalBookOperations,stdHead);
                            //TODO ogr puanı negatifse direk yazdıralım teslim etmedigi kitaplardan dolayı eksiye dusecekse de yazalım
                            break;
                        case submitBook:
                            //* id alalım 
                            //* kitaplar uzerinde dolanarak adamın alıp teslim etmedigi labeli id kontrolu ile yazdıralım
                            //* teslim etmek isdedigi kitabın labelini yazsın 
                            //* sonra o labele ait kitaplar ve odunc listesinde guncellemelerimizi yapalım
                            printf("std ID:");
                            scanf("%s",stdOBJ.ogrID);
                            proceedBookSubmitting(&stdHead,&booksHead,stdOBJ.ogrID,totalBookOperations,&bookBorrowList);
                            
                            break;
                        case barrowBook:
                            printf("BOOK ISBN:");
                            scanf("%s",bookOBJ.ISBN);
                            int bookDetail = checkBookState(&booksHead,bookOBJ.ISBN);
                            // -1 - yok
                            //  0 - var ama musait degil 
                            //  1 var ve musait
                            if(bookDetail == -1){
                                printf("%s does not belog to any book\n",bookOBJ.ISBN);
                            }else if (bookDetail == 1){
                                printf("STD ID:");
                                scanf("%s",stdOBJ.ogrID);
                                int stdDetail = chekStdDetail(stdHead,stdOBJ.ogrID);
                                if(stdDetail == 0){
                                    printf("%s does not belong to any student\n",stdOBJ.ogrID);
                                }else if(stdDetail == 1){
                                    print("Given std Id enamble to barrow book"); 
                                    proceedBookBorrowing(&booksHead,bookOBJ.ISBN,&totalBookOperations,&bookBorrowList,stdOBJ.ogrID);
                                }
                            }
                            break;
                        case exitStd:
                            print("std menu exitted");
                            break;
                        default:
                            print("wrong selection please select options included above");
                        break;  
                    }
               }while(stdMenu != exitStd);

                    bookBorrowFile = fopen("KitapOdunc.csv","w");
                    if(bookBorrowFile == NULL) exit(-1);
                    print("book history file writing");
                    writeBookBorrowFileFromList(bookBorrowFile,bookBorrowList,&totalBookOperations); 
                    fclose(bookBorrowFile);

                    print("std file writing");
                    stdFile = fopen("Ogrenciler.csv","w");
                    if(stdFile == NULL) exit(-1);
                    print("std file writing");
                    writeStdFileFromList(stdFile,stdHead);
                    fclose(stdFile);

            break;
            case book:
                //* kitap verlieri alınıp otomatik olarak ilgili yerlere atanmıs vaziyette yazarların ve ogrencilerin 
                //* ortak noktası oldugu icin kitaplar file'i programın basında okunacak ve ilgili yerlere atanacak 
                do{
                    printDiv();
                    print(bookMenuInfo);
                    printf("selection:");
                    scanf("%d",&bookMenu);
                    printDiv();
                    int i = 0;
                    int Result; 
                    KITAP newBOOK;
                    YAZAR newWriter;

                    switch(bookMenu){
                        case addBook:
                            printf("Book Name:");
                            scanf(" %[^\n]s",newBOOK.kitapAdi);
                            printf("Book ISBN:");
                            scanf("%s",newBOOK.ISBN);
                            printf("Book Count:");
                            scanf("%d",&newBOOK.adet);
                            Result = proceedAddNewBookToLib(&booksHead,&writerHead,newBOOK,totalBookOperations,bookBorrowList,&totalBookWriter,&bookWriterList);
                            if(Result == -1){
                                printf("%s ISBN already exists in the library",newBOOK.ISBN);
                            }else{
                                print("book added to writerBookList,bookList,and writers also updated");
                            }
                            break;
                        case removeBook:
                            printf("Enter BOOK ISBN: ");
                            scanf("%s",newBOOK.ISBN);
                            print(removeBookFromList(totalBookOperations,bookBorrowList,&booksHead,newBOOK.ISBN,&totalBookWriter,&bookWriterList));
                            break;
                        case updateBook:
                            //* we could add new books or delete some books child also
                            //* change booklist and books name, book count thats it
                            break;
                        case listBookHistory:
                            for(i=0 ;i<totalBookOperations;i++){
                                printBookHistoryItem(bookBorrowList[i]);
                            }
                            break; 
                        case listBooks:
                            printBOOKS(booksHead);
                            break;
                        case BookInfo:
                            printf("enter book Name:");
                            //gets(newBOOK.kitapAdi);
                            scanf(" %[^\n]s",newBOOK.kitapAdi);
                            printBookNameNode(newBOOK.kitapAdi,booksHead);
                            break;
                        case lateBooks:
                            printLateBooks(totalBookOperations,bookBorrowList);
                            break;
                        case shelfBook:
                            printSelfBook(booksHead); 
                            break;
                        case matchBWrt:
                                //* listeler guncel bir halde sadece dosyaları acarak bastan yazmamız yeterli olacaktır
                            break;
                        case updataBWrt:
                            //* listeler guncel bir halde sadece dosyayı acarek bastan yazmamız yeterli olacaktır
                            break;
                        case exitBook:
                            print("Book menu exited");
                            break;
                        default:
                             print("wrong selection please select options included above");
                            break;
                    }
                }while(bookMenu != exitBook);

                
                bookFile = fopen("Kitaplar.csv","w");
                if(bookFile == NULL) exit(-1);
                writeBookFileFromBookList(bookFile,booksHead);
                fclose(bookFile);


            break;    
            case writers:

                //* dosyadan okuyup yazarları bir linked list icerisine ekleyelim
                //* devamında linked list icerisinde istenildigi kadar islem yapıp break yaparken de dosyayı guncel linkli liste ile 
                //* guncelleyebiliriz 

                do{
                    printDiv();
                    print(writerMenuInfo);
                    printf("selection:");
                    scanf("%d",&writerOpt);
                    printDiv();

                    switch(writerOpt){
                        case addWriter:
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
                            //TODO we have to update book writer array as -1 for deleted wrtier
                            break;
                        case listWriters:
                            printWriters(writerHead);
                            break;
                        case updateWriter:
                            //TODO we have to loop through other files and update writer infos such as on bookwriter file 
                            //* update any writer
                            printf("writer id(for detection):");
                            scanf("%d",&newWriter.yazarID);
                            printf("writer name(new):");
                            scanf("%s",newWriter.yazarAd);
                            printf("writer surname(new):");
                            scanf("%s",newWriter.yazarSoyad);
                            print(updateWriterFromList(&writerHead,newWriter.yazarID,newWriter.yazarAd,newWriter.yazarSoyad));
                        break;
                        case writerInfo:
                            //*Kullanıcıdan alınan Yazar Adı bilgisine göre her bir yazarın bilgilerinin ve bu yazara ait
                            //* kitaplara ait tüm bilgilerin listelenmesi işlemleri yapılmalıdır.
                            //TODO update writer info funct interms of the instructions which are above
                            printf("writer name:");
                            scanf("%s",newWriter.yazarAd);
                            printWriterInfo(writerHead,newWriter.yazarAd,bookWriterList,totalBookWriter);
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
                writeWriterListToWriterFile(writerFile,writerHead);
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

void printLateBooks(int totalBookOperations,KITAPODUNC* bookBorrowList){
    int i = 0;    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    TARIH date; //* bugunun tarihi
    date.gun = tm.tm_mday;
    date.ay = tm.tm_mon;
    date.yil = tm.tm_year + 1900;
    int dayDifference = 0;
    print("LATE BOOKS ARE FOLLOWING:");
    for(i=0;i<totalBookOperations;i++){
        if(bookBorrowList[i].islemTipi == 0){ // kitap teslim edilmemis 
            dayDifference = getDateAsDays(date)-getDateAsDays(bookBorrowList[i].islemTarihi);
            if(dayDifference > 15){
                printBookHistoryItem(bookBorrowList[i]);
            }
        }
    }

}

void printSelfBook(KITAP *head){
    //* kitapların uzerinde dolanalım ve eger durumları rafta ise yazdıralım
    KITAP *tmp = head;
    KITAPORNEK *tmp2;
    while(tmp != NULL){
        tmp2 = tmp->head;
            printf("%s,%s,%d\n",tmp->kitapAdi,tmp->ISBN,tmp->adet);
            print("KITABA AIT RAFTA BULUNAN ORNEKLER:");
        while(tmp2 != NULL){
            if(strcmp(tmp2->Durum,"RAFTA") == 0){
                //* RAFTA olan bir kitap tespit edildi 
                printf("state: %s, label:%s \n",tmp2->Durum,tmp2->EtiketNo);
            }
            tmp2 = tmp2->next;
        print("");
        }
        tmp = tmp->next;
    }
}

void printBookNameNode(char* bookName,KITAP* books){
    KITAP* tmp = books;
    int found = 0;
    while(tmp != NULL && found == 0){
        if(strcmp(tmp->kitapAdi,bookName) == 0){
            found = 1;
            printBookNode(tmp);
            //* kitap yazar listesi uzerinde dolanarak ilgili yazarlarin id'sini toplayarak uyusan id'deki yazarları da yazdırmamız gerekli
        }
        tmp = tmp->next;
    }
    if(found == 0){
        print("bookd does not found");
    }
}

int proceedAddNewBookToLib(KITAP** booksHead,YAZAR** writerHead,KITAP newBOOK, int totalBookOperations, KITAPODUNC* bookBorrowList,int *totalBookWriter,KITAPYAZAR** bookWriter){
    //* -1 already exists ISBN
    //* 1 ısbn eklendi
    YAZAR* writerhead = *writerHead;
    KITAP* bookParent = *booksHead;
    YAZAR newWriter;
    int size = log2(*totalBookWriter)+1;
    size = pow(2,size);
    printf("size : %d, totalbookwriter: %d\n",size,*totalBookWriter);
    int isMoreWriter = 1;
    while(bookParent != NULL){
        if(strcmp(bookParent->ISBN,newBOOK.ISBN) == 0){
            return -1;
        }
        bookParent = bookParent->next;
    }

    while(isMoreWriter == 1){
        printf("writer Name:");
        scanf(" %[^\n]s",newWriter.yazarAd);
        printf("writer surname:");
        scanf(" %[^\n]s",newWriter.yazarSoyad);
        print(addWriterToList(writerHead,newWriter.yazarAd,newWriter.yazarSoyad));
        writerhead = *writerHead;
        while(writerhead->next != NULL){
            writerhead = writerhead->next;
        }
        printWriterNode(writerhead->yazarID,writerhead->yazarAd,writerhead->yazarSoyad);
        printf("%s, %s\n",writerhead->yazarAd,newWriter.yazarAd);

        if(strcmp(writerhead->yazarAd,newWriter.yazarAd) == 0 ){
            //* yani girilen yazar listeye eklenebilmisse
            print("book writer list updating");
            if(*totalBookWriter == size){
                *bookWriter = (KITAPYAZAR*) realloc(*bookWriter,sizeof(KITAPYAZAR)*size*2);
                size = size*2;
            }
            strcpy((*bookWriter)[*totalBookWriter].ISBN,newBOOK.ISBN);
            (*bookWriter)[*totalBookWriter].YazarID = writerhead->yazarID;
            *totalBookWriter = *totalBookWriter+1;
        }
        printWriterBookList(*bookWriter,*totalBookWriter);
        printf("more writer(-1 exit)(1 continue):");
        scanf("%d",&isMoreWriter);
    }

    //* yazarlar eklendi 
    //* kitap yazar listesi de guncellendi

    addBookToList(booksHead,newBOOK.kitapAdi,newBOOK.ISBN, newBOOK.adet, totalBookOperations,bookBorrowList);
    return 1;
}

char* removeBookFromList(int totalBookOperations,KITAPODUNC* bookBorrowList,KITAP** booksHead,char* ISBN,int *totalBookWriter,KITAPYAZAR** bookWriter){

    KITAP* tmp = *booksHead;
    KITAP* prev = NULL;
    int i =0;
    int j = 0;
    int found = 0;
    char label[14];
    for(i=0;i<totalBookOperations;i++){
        for(j=0;j<13;j++){
            label[j] = bookBorrowList[i].EtiketNo[j];
        }
        if(strcmp(label,ISBN) == 0){
            if(bookBorrowList->islemTipi == 0){
                //* silinmek istenen kitabı bulduk ve bu kitabın tum kopyaları henuz teslim edilmemis 
                return "deletion operations failed because at least one copy of this book not submitted right now ";
            }
        }
    }

    for(i=0;i<*totalBookWriter;i++){

        if(strcmp((*bookWriter)[i].ISBN,ISBN) == 0){
            strcpy((*bookWriter)[i].ISBN,(*bookWriter)[*totalBookWriter].ISBN);
            (*bookWriter)[i].YazarID = (*bookWriter)[*totalBookWriter].YazarID;
            (*totalBookWriter) = (*totalBookWriter)-1;
        }
    }

    while(tmp != NULL && found == 0){
        if(strcmp(tmp->ISBN,ISBN) == 0){
            found = 1;
            if(prev == NULL){
                //* asil head silinecek
                (*booksHead) = (*booksHead)->next;
            }else{
                //* icerideki nodelardan biri silinecek
                prev->next = tmp->next;
            }
            free(tmp);
        }
        if(tmp != NULL){
            prev = tmp;
            tmp = tmp->next;
        }
    }
    return found == 1 ? "desired book deleted" : "book does not found to be deleted";
}

void writeStdFileFromList(FILE* stdFile,OGRENCI *stdHead){
    OGRENCI *tmp = stdHead;
    OGRENCI *tmp2 ;
    while(tmp != NULL){
        fprintf(stdFile,"%s,%s,%s,%d\n",tmp->ogrID,tmp->ad,tmp->soyad,tmp->puan);
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
        tmp2->prev = NULL;
        tmp2->next = NULL;
    }
}


void writeBookBorrowFileFromList(FILE* bookBorrowFile,KITAPODUNC* bookBorrowList,int* totalBookOperations){
    printf("%d \n",*totalBookOperations);
    int i = 0;
    KITAPODUNC crnt;
    TARIH* date;
    for(i = 0;i<*totalBookOperations;i++){
        crnt = bookBorrowList[i];
        date = &(bookBorrowList[i].islemTarihi);
        fprintf(bookBorrowFile,"%s,%s,%d,%d.%d.%d\n",crnt.EtiketNo,crnt.ogrID,crnt.islemTipi,date->gun,date->ay,date->yil);
        free(bookBorrowList+i);
    }
    *totalBookOperations = 0;
    free(totalBookOperations);
}

void writeBookFileFromBookList(FILE *file, KITAP* bookHead){
    KITAP *parent = bookHead;
    KITAP *parentTmp = bookHead;
    KITAPORNEK *child;
    KITAPORNEK *childTmp;

    while(parent != NULL){
        fprintf(file,"%s,%s,%d\n",parent->kitapAdi,parent->ISBN,parent->adet);
        if(ferror(file)) {
            print("there was an error while writing the book file");
            return;
        }
        child = parent->head;
        while(child != NULL){
            childTmp = child;
            child = child->next;
            free(childTmp);
            childTmp->next = NULL;
        }
        parent = parent->next;
    }

    print("child file writing done");
    //* simdi childleri null yaptıktan sonra parentleri de null yaparak cikmamiz gerekiyor
    parent = bookHead;
    while(parent != NULL){
        parentTmp = parent;
        parent = parent->next;
        free(parentTmp);
        parentTmp->next = NULL;
    }
}

void proceedBookSubmitting(OGRENCI** std ,KITAP **booksHead,char* stdID, int totalBookOperations,KITAPODUNC** bookBorrowList){

    OGRENCI* stdHead = *std;
    KITAP *parent = *booksHead;
    KITAPORNEK *child;
    char label[20];
    TARIH date;
    int day,month,year;
    int i = 0;
    int totalDay = 0;
    int decreased = 0;
    print("select one of the barrowed below:");
    while(parent != NULL){
        child = parent->head;
        while(child != NULL){
            if(strcmp(child->Durum,stdID) == 0){
                printf("state: %s , label: %s\n",child->Durum,child->EtiketNo);
                i = 1;
            }
            child = child->next;
        }
        parent = parent->next;
    }

    if(i == 0){
        print("There are no book to submit about given std ID");
        return;
    }

    parent = *booksHead;
    printf("label to submit: ");
    scanf("%s",label);
    printf("enter day.month.year:");
    scanf("%d.%d.%d",&day,&month,&year);
    date.gun = day;
    date.ay = month;
    date.yil = year;
    print("date assigned");
    for(i=0;i<totalBookOperations;i++){
        if(strcmp(((*bookBorrowList)[i]).EtiketNo,label) == 0){
            if(((*bookBorrowList)[i]).islemTipi == 0){
                ((*bookBorrowList)[i]).islemTipi = 1;

                totalDay = getDateAsDays(date) - getDateAsDays(((*bookBorrowList)[i]).islemTarihi);

                if(totalDay >15){
                    while(stdHead != NULL && decreased == 0){
                        if(strcmp(stdHead->ogrID,stdID) == 0){
                            stdHead->puan = stdHead->puan -10;
                            decreased = 1;
                        }
                        stdHead = stdHead->next;
                    }
                }

                while(parent != NULL){
                    child = parent->head;
                    while(child != NULL){
                        if(strcmp(child->EtiketNo,label) == 0){
                            if(strcmp(child->Durum,stdID) == 0){
                                memset(child->Durum,0,sizeof(char)*9);
                                strcpy(child->Durum,"RAFTA");
                            }
                        }
                        child = child->next;
                    }
                    parent = parent->next;
                }

            }
        }
    }
}


int getDateAsDays(TARIH date){
    return (date.ay*30 + date.gun + date.yil*365);
}


int chekStdDetail(OGRENCI* stdHead,char* stdID){
    OGRENCI* tmp = stdHead;
    int found = 0;
    while(tmp != NULL && found == 0){
        if(strcmp(tmp->ogrID,stdID) == 0){
            found = 1;
            if(tmp->puan < 0 ){
                print("Student with given Id has negative points");
                found = -1;
            }
        }
        tmp = tmp->next;
    }
    return found;
}


void proceedBookBorrowing(KITAP **booksHead, char* ISBN ,int* totalBookOperations,KITAPODUNC** bookHistory,char* stdID){
    KITAP *parent = *booksHead;
    KITAPORNEK *child;
    int a = log2((double)(*totalBookOperations)) + 1;
    int size = pow(2,a); //* b is allocated size of the book History
    char label[20];
    int day ; 
    int year;
    int month;
    //* gelen ISBN belli bir kitaba ait ve dahası ait olan kitapda odunc alınmamıs ornek oldugunu da biliyoruz
    while(parent != NULL){
        child = parent->head;
        if(strcmp(parent->ISBN,ISBN) == 0){
            while(child != NULL){
                if(strcmp(child->Durum,"RAFTA") == 0){
                    printf("state:%s, label: %s \n",child->Durum,child->EtiketNo);
                }
                child = child->next;
            }
        }
        parent = parent->next;
    }

    printf("enter one of the books label above to barrow:");
    scanf("%s",label);
    print("kitap labeli atandi");
    KITAP* parent2 = *booksHead;
    KITAPORNEK* child2;

     while(parent2 != NULL){
        child2 = parent2->head;
        if(strcmp(parent2->ISBN,ISBN) == 0){
            while(child2 != NULL){
                if(strcmp(child2->Durum,"RAFTA") == 0){
                    if(strcmp(child2->EtiketNo,label) == 0){
                        //* artık odunc alinacak olan kitap elimizde
                        print("book verileri ataniyor");
                        //* history'e odunc alinan kitabi ekleyelim 
                        //* kitap uzerindeki labela da ogrencinin numarasını verip ayrılalım
                        
                        if(size == *totalBookOperations){
                            *bookHistory = (KITAPODUNC*) realloc(*bookHistory,sizeof(KITAPODUNC)*2*size);
                            size = size*2;
                        }
                        print("1");
                        strcpy((*bookHistory)[*totalBookOperations].EtiketNo,child2->EtiketNo);
                         print("2");
                        ((*bookHistory)[*totalBookOperations]).islemTipi = 0;
                         print("3");
                        strcpy((*bookHistory)[*totalBookOperations].ogrID,stdID);
                        printf("enter day.month.year: ");
                        scanf("%d.%d.%d",&day,&month,&year);
                        ((*bookHistory)[*totalBookOperations]).islemTarihi.gun = day;
                        ((*bookHistory)[*totalBookOperations]).islemTarihi.ay = month;
                        ((*bookHistory)[*totalBookOperations]).islemTarihi.yil = year;
                        (*totalBookOperations)++;
                        strcpy(child2->Durum,stdID);
                        print("Borrowing done");

                    }
                }
                child2 = child2->next;
            }
        }
        parent2 = parent2->next;
    }

}



int checkBookState(KITAP** booksHead,char * ISBN){
    int isExist = -1;
    KITAP* parent = *booksHead;
    KITAPORNEK *child;
    KITAP** selected = NULL;
    char* raf = "RAFTA";

    while(parent != NULL && isExist == -1){
        child = parent->head;
        if(strcmp(parent->ISBN,ISBN) == 0){
            isExist = 0;
            while(child != NULL && isExist == 0){
                if(strcmp(child->Durum,raf) == 0){
                    isExist = 1;
                    print("There are at least one sample belongs to Given ISBN in the Library");
                }
                child = child->next;
            }
            if(isExist == 0 ){
                printf("%s isbn book all samples borrowed",ISBN);
            }
        }
        parent = parent->next;
    }

    return isExist;
}


void printBannedStd(KITAPODUNC* bookHist,int totalOpr,OGRENCI* std){

    OGRENCI* stdHead = std;
    while(stdHead!=NULL){   

        if(stdHead->puan < 0){
            printStdNode(stdHead);
            print("");
        }
        stdHead = stdHead->next;
    }

}


void printUnsubmittedStd(KITAPODUNC* bookHist,int totalOpr,OGRENCI* std){
    int i = 0;
    OGRENCI *stdHead;
    //* history uzerinde gezerek teslim edilmemis kitapları bulacagız 
    //* teslim edimeyen kitapların ogrenci mumaralarından ogrenci listesi uzerinde gezerek ilgili kisinin bilgilerini yazdıracagız

    for(i=0;i<totalOpr;i++){
        stdHead = std;
        if(bookHist[i].islemTipi == 0){
            //* we found an unsubmitted book
            while(stdHead != NULL){
                if(strcmp(stdHead->ogrID,bookHist[i].ogrID) == 0){
                    printStdNode(stdHead);
                    print("");
                }
                stdHead = stdHead->next;
            }

        }

    }

}


void readBookBorrowFileToList(FILE* bookProcessFile,KITAPODUNC** bookBorrowList,int* totalBookOperations){
    //* 1234567891012_2,17011020,0,28.12.2022
    print("read book process file func called");
    KITAPODUNC *tmp =(KITAPODUNC*) malloc(sizeof(KITAPODUNC)*1);
    int read = 0;
    int* count = totalBookOperations;
    int size = 1;

    char bookStcker[20];
    char stdId[14];
    int processType;
    int day;
    int month;
    int year;

    do{
        read = fscanf(bookProcessFile,"%19[^,],%13[^,],%d,%d.%d.%d\n",bookStcker,stdId,&processType,&day,&month,&year);

        if(read != 6 && !feof(bookProcessFile)){
             print("there was an error while reading the file");
        }else if(read == 6){
            printf("%s , %s , %d , %d , %d , %d \n",bookStcker,stdId,processType,day,month,year);
            if(size == *count){
                tmp = (KITAPODUNC*) realloc(tmp,sizeof(KITAPODUNC)*size*2);
                size = size*2;
            }
            tmp[*count].islemTipi = processType;
            strcpy(tmp[*count].EtiketNo,bookStcker);
            strcpy(tmp[*count].ogrID,stdId);
            tmp[*count].islemTarihi.gun = day;
            tmp[*count].islemTarihi.ay = month;
            tmp[*count].islemTarihi.yil = year;
            (*count)++;
        }
        if(ferror(bookProcessFile)){
            print("there was an error while reading Kitap file");
            exit(-1);
        }

    }while(!feof(bookProcessFile));

    *bookBorrowList = tmp;
}

void printBookHistoryItem(KITAPODUNC bookBorrow){
    printf("%s , %s , %d , %d.%d.%d \n",bookBorrow.EtiketNo,bookBorrow.ogrID,bookBorrow.islemTipi,bookBorrow.islemTarihi.gun,bookBorrow.islemTarihi.ay,bookBorrow.islemTarihi.yil);
}

void readBooksFileToList(FILE* bookFile,KITAP** booksHead,int totalOperations,KITAPODUNC* bookOperationHistory){
    //* read books to list and read books example to anotherher linked list and add books head to their parent place
    int read = 0;
    //* adet;
    //* ISBN;
    //* kitapAdi;

    int bookCount = 0;
    char ISBN[14];
    char bookName[30];

    do{
        read = fscanf(bookFile,"%29[^,],%13[^,],%d\n",bookName,ISBN,&bookCount);

        if(read!=3 && !feof(bookFile)){
            print("there was an error while reading the file");
        }else if(read == 3){
            addBookToList(booksHead,bookName,ISBN,bookCount,totalOperations,bookOperationHistory);
        }
        if(ferror(bookFile)){
            print("there was an error while reading Kitap file ");
            exit(-1);
        }
    }while(!feof(bookFile));

    printBOOKS(*booksHead);
}

void printBOOKS(KITAP* books){
    KITAP* tmp = books;
    KITAPORNEK *tmp2; 
    while(tmp != NULL){
        tmp2 = tmp->head; 
        printBookNode(tmp);
        tmp = tmp->next;
    }
    print(" ");
}

void printBookNode(KITAP* book){
    KITAP* tmp = book;
    KITAPORNEK *tmp2 = tmp->head; 
    printf("%s,%s,%d\n",tmp->kitapAdi,tmp->ISBN,tmp->adet);
        print("KITABA AIT ORNEKLER");
        while(tmp2 != NULL){
            printf("state: %s, label:%s \n",tmp2->Durum,tmp2->EtiketNo);
            tmp2 = tmp2->next;
    }
}

void addBookToList(KITAP** booksHead,char* bookName,char* ISBN, int bookCount,int totalOperations,KITAPODUNC* history){

    int bookC;
    int mod;
    int i,j = 0;
    KITAP *bookParent = (KITAP*) malloc(sizeof(KITAP)*1);
    bookParent->head = NULL;
    bookParent->next = NULL;
    KITAP *tmpParentBook = *booksHead;
    KITAPORNEK** bookChildHead = &(bookParent->head);

    bookParent->adet = bookCount;
    strcpy(bookParent->ISBN,ISBN);
    strcpy(bookParent->kitapAdi,bookName);
    char label[20];
    char state[9] = "RAFTA";
    
    for(i=0;i<bookCount;i++){

        memset(label,0,sizeof(label));
        strcpy(state,"RAFTA");
        j=0;
        strcpy(label,ISBN);
        label[13] = '_';
        bookC = i+1;
        while(bookC != 0){
            mod = bookC % 10;
            bookC = bookC/10;
            label[j+14] = (mod+'0');
            j++;
        }

        for(j=0;j<totalOperations;j++){
            if(strcmp(label,history[j].EtiketNo) == 0){
                if(history[j].islemTipi == 0){
                    strcpy(state,history[j].ogrID);
                }
            }
        }
        addBookToChildList(bookChildHead,label,state);
    }
    
    //* bookchildler olusturuldu ve set edilmis durumda artık paren book'u kendi linkli listesine ekleyebiliriz

    if(tmpParentBook == NULL){
        *booksHead = bookParent;
    }else{
        while(tmpParentBook->next != NULL){
            tmpParentBook = tmpParentBook->next;
        }
        tmpParentBook->next = bookParent;
    }
}

void addBookToChildList(KITAPORNEK** head,char* label,char* state){
    KITAPORNEK *tmp = (KITAPORNEK*) malloc(sizeof(KITAPORNEK)*1);
    KITAPORNEK *tmp2 = *head;
    
    strcpy(tmp->Durum,state);
    strcpy(tmp->EtiketNo,label);
    tmp->next = NULL;

    if(*head == NULL){
        *head = tmp;
    }else{
        while(tmp2->next != NULL){
            tmp2 = tmp2->next;
        }
        tmp2->next = tmp;
    }
}


void printStdInfo(OGRENCI* stdHead,char* stdName,KITAP* booksHead,int totalOpr, KITAPODUNC* history){
    OGRENCI *tmp = stdHead;
    KITAP *tmp2 = booksHead;
    KITAPORNEK *bookChild;
    int stdExists, i = 0;
    while(tmp!= NULL){
        if(strcmp(tmp->ad,stdName) == 0){
            stdExists = 1;
            printStdNode(tmp);
            print("\nUnsubmitted Books: ");
            while(tmp2!= NULL){
                bookChild = tmp2->head;
                while(bookChild != NULL){
                    if(strcmp(bookChild->Durum,tmp->ogrID) == 0){
                        printf("label: %s ,state: %s \n",bookChild->EtiketNo,bookChild->Durum);
                    }
                    bookChild = bookChild->next;
                }
                tmp2 = tmp2->next;
            }
            print("\nAll Book Operations:");
            for(i=0;i<totalOpr;i++){
                if(strcmp(history[i].ogrID,tmp->ogrID) == 0){
                    printBookHistoryItem(history[i]);
                }
            }
        }
        tmp = tmp->next;
    }
    if(stdExists == 0){
        print("student with given name does not exists");
    }
}

void printStdNode(OGRENCI* tmp){
    printf("number: %s\nname: %s,surname: %s\npoint: %d\n",tmp->ogrID,tmp->ad,tmp->soyad,tmp->puan);
    printf("prev: %p, next:%p\n",tmp->prev,tmp->next);
}
 

char* updateStdFromList(OGRENCI **stdHead,char* stdId,char*  stdName,char* stdSurname){
    OGRENCI *tmp = *stdHead;

    while(tmp!=NULL){
        if(strcmp(tmp->ogrID,stdId) == 0){
            strcpy(tmp->ad,stdName);
            strcpy(tmp->soyad,stdSurname);
            //* Sadece name ve surname degistigi icin ve history ile book listesinde id tutuldugu icin oralarda bir degisim yapmamız gerekmiyor
            return "desired std with given Id updated successfully";
        }
        tmp = tmp->next;
    }
    return "update failed, the given id does not belongs to any student";
}


char* removeStdFromList(OGRENCI **stdHead,char* name){
    OGRENCI *tmp = *stdHead;

    while(tmp != NULL){
        if(strcmp(tmp->ad,name) == 0){
            if(tmp->prev == NULL){
                //* head goes to be deleted 
                *stdHead = tmp->next;
                (*stdHead)->prev = NULL;//* heading previousu null olsun
            }else if(tmp->next == NULL){
                //* tail goes to be deleted
                tmp->prev->next = NULL;
            }else{
                //* one of the inner nodes goes to be deleted;
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
            }
            free(tmp);
            return  "desired student has been deleted";
        }
        tmp = tmp->next;
    }
    return "the student has not been found to be deleted try again later" ;
}

void printStdList(OGRENCI* head){
    OGRENCI* tmp = head;
    OGRENCI *tmp2;
    while(tmp != NULL){
        //print("ileri yon");
        printStdNode(tmp);
        printDiv();
        tmp2 = tmp->prev;
        tmp = tmp->next;
    }
    // tmp2 = tmp2->next;
    // while(tmp2 != NULL){
    //     print("geri yon");
    //     printf("number: %s\nname: %s,surname:%s\npoint:%d\n",tmp2->ogrID,tmp2->ad,tmp2->soyad,tmp2->puan);
    //     printf("prev: %p, next:%p\n",tmp2->prev,tmp2->next);
    //     printDiv();
    //     tmp2 = tmp2->prev;
    // }

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
            print("add to list calling");
            print(addStdToList(stdHead,number,name,surname,point));
        }

        if(ferror(stdFile)){
            print("there was an error while reading Kitap-Yazar file ");
            exit(-1);
        }
    }
}

char* addStdToList(OGRENCI** stdHead,char* number,char* name,char* surname,int point){
    OGRENCI *tmp = (OGRENCI*) malloc(sizeof(OGRENCI));
    OGRENCI *tmp2= *stdHead;
    strcpy(tmp->ogrID,number);
    strcpy(tmp->ad,name);
    strcpy(tmp->soyad,surname);
    tmp->puan = point;
    tmp->prev = NULL;
    tmp->next = NULL;

    if(tmp2 == NULL){
        *stdHead = tmp;
    }else{
        while(tmp2->next != NULL){
            tmp2 = tmp2->next;
            if(strcmp(tmp2->ogrID,tmp->ogrID) == 0){
                return "given student's id is already taken by another student please try again";
            } 
        }
        tmp2->next = tmp;
        tmp->prev = tmp2;
    }
    return "student has been added to double linked list succesfully";
}

void printWriterInfo(YAZAR *head,char* writerName,KITAPYAZAR *bookWriter,int totalBookWriter){
    YAZAR *tmp = head;
    int found = 0;
    int writerExists = 0;
    int i = 0;
    while(tmp!= NULL){
        if(strcmp(tmp->yazarAd,writerName) == 0){
            writerExists = 1;
            printWriterNode(tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
            for(i=0;i<totalBookWriter;i++){
                if(bookWriter[i].YazarID == tmp->yazarID){
                    found = 1;
                    printf("ISBN: %s, writerId: %d\n",bookWriter[i].ISBN ,bookWriter[i].YazarID );
                }
            }
        }
        tmp = tmp->next;
    }
    if(writerExists == 0){
        print("the writer given name does not exists");
    }else{
        if(found == 0){
            print("there are no book written by given author");
        }
    }
}

void writeBookWriterFileFromList(FILE *file, KITAPYAZAR* bookWriter,int* totalBookWriter){
    int i = 0;
    for(i=0;i<*totalBookWriter;i++){
        fprintf(file,"%s,%d\n",bookWriter[i].ISBN,bookWriter[i].YazarID);
        if(ferror(file)) print("there was an error while writing writers to file");
        free(bookWriter+i);
    }
    *totalBookWriter = 0;
    free(totalBookWriter);
}

void printWriterBookList( KITAPYAZAR* bookWriter,int totalBookWriter){
    int i = 0;
    print("Book Writer informations: ");
    for(i=0;i<totalBookWriter;i++){
        printf(" ISBN: %s, Writer ID: %d \n",bookWriter[i].ISBN,bookWriter[i].YazarID);
    }

}

void readBookWriterFileToList(FILE *file, KITAPYAZAR** bookWriter,int* totalWriter){
    //* book writer file just a array, we don't need linked list so just assign all elements to a list 
    int read = 0;
    int* count = totalWriter;
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
            if(size == *count){
                tmpBookWriter = (KITAPYAZAR*) realloc(tmpBookWriter,sizeof(KITAPYAZAR)*size*2);
                size = size*2;
            }
            int i = 0;
            while(i<13){
                tmpBookWriter[*count].ISBN[i] = ISBN[i];
                i++;
            }
            tmpBookWriter[*count].ISBN[i] = '\0';
            tmpBookWriter[*count].YazarID = yazarID;
            (*count)++;
        }
        if(ferror(file)){
            print("there was an error while reading Kitap-Yazar file ");
            exit(-1);
        }
    }while(!feof(file));
    *bookWriter = tmpBookWriter;
}


void writeWriterListToWriterFile(FILE *file,YAZAR *head){
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
        if(tmp!=NULL){
            prev = tmp;
            tmp = tmp->next;
            }
    }
    return found == 1 ? "desired writer deleted" : "writer does not found to be deleted";
}

void printWriters(YAZAR *head){
    YAZAR *tmp = head;
    while(tmp != NULL){
        printWriterNode(tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
        tmp = tmp->next;
    }

}

void printWriterNode(int id,char* name,char* surname){
    printf("%d , %s , %s\n", id,name,surname);
}

void readWriterFile(FILE* file,YAZAR **head){
    int read = 0;
    //* 8, Jorge, Nocedal

    int id;
    char n1[30];
    char n2[30];

    do{
        read = fscanf(file,"%d,%29[^,],%29[^\n]\n",&id,n1,n2);
        
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
    tmp->next = NULL;

    if(*head == NULL){
        tmp->yazarID = 1;
        *head = tmp;
    }else{
        while(tmp2->next != NULL){
             tmp2 = tmp2->next;
            //  if(tmp->yazarID == tmp2->yazarID){
            //      return "there are duplicated writer id Wheater in the file or given values. Please check the \ngiven values or the file values of writer id";
            // }
        }
        tmp->yazarID = (tmp2->yazarID) +1;
        //printf("%d\n",tmp2->yazarID);
        tmp2->next = tmp;
        printDiv();
    }
    return "writer added to list";
}

void print(char *msg){
    printf("%s\n",msg);
}

void printDiv(){
    print("-----------------------------------------------------------");
}