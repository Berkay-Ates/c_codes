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
    int islemTipi:1; //* odunc alma veya teslim etme -0 odunc alma -1 teslim etme
    struct Tarih islemTarihi;
}KITAPODUNC;

//* enum definitions
typedef enum mainMenu {student,book,writers,exitMainMenu} MAINMENU;
typedef enum writerOptions {addWriter,removeWriter,listWriters,updateWriter,writerInfo,exitWriters} WRITERMENU;
typedef enum studentOptions {addStd,removeStd,updateStd,listStd,stdInfo,unSubmittedStd,bannedStd,submitBook,barrowBook,exitStd} STUDENTMENU; 
typedef enum bookOptions {addBook,removeBook,updateBook,BookInfo,lateBooks,shelfBook,matchBWrt,updataBWrt,exitBook} BOOKMENU;


//* writer func macros 
void print(char *msg);
void printDiv();
char* addWriterToList(YAZAR** head,char* writerName,char* writerSurname);
void readWriterFile(FILE* file,YAZAR **head );
void printWriters(YAZAR *head);
char* removeWriterFromList(YAZAR **head, int id);
char* updateWriterFromList(YAZAR** head,int writerID,char* writerName,char* writerSurname);
void writeListToWriterFile(FILE *file,YAZAR *head);
void printWriterNode(int id,char* name,char* surname);

//* student funcs macros
void readStdFromFile(FILE* stdFile,OGRENCI** stdHead);
char* addStdToList(OGRENCI** stdHead,char* number,char* name,char* surname,int point);
void printStdList(OGRENCI* head);
char* removeStdFromList(OGRENCI **stdHead,char* name);
char* updateStdFromList(OGRENCI **stdHead,char* stdId,char* stdName,char* stdSurname);
void printStdInfo(OGRENCI* stdHead,char* stdName);
void printStdNode(OGRENCI* tmp);

//* book funcs macros 
void readBooksFileToList(FILE* bookFile,KITAP** booksHead,int totalOperations,KITAPODUNC* bookOperationHistory);
void addBookToList(KITAP** booksHead,char* bookName,char* ISBN, int bookCount,int totalOperations,KITAPODUNC* history);
int readBookBorrowFileToList(FILE* bookProcessFile,KITAPODUNC** bookBorrowList);
void printBOOKS(KITAP* books);
void addBookToChildList(KITAPORNEK** head,char* label,char* state);



int readBookWriterFileToList(FILE *file, KITAPYAZAR** bookWriter);
void printWriterInfo(YAZAR *head,char* writerName,KITAPYAZAR *bookWriter,int totalBook);

int main(){
    char* mainMenuInfo = "Choose one of them to proceed your work\n0-Student\n1-Book\n2-Writers\n3-Exit Main Menu";
    char* bookMenuInfo = "Choose one of them to proceed your work\n0-add book\n1-remove book\n2-book info\n3-update book\n4-late books\n5-books on self\n6-match book with writers\n7-update Book Writer\n8-exit Book Menu";
    char* stdMenuInfo = "Choose one of them to proceed your work\n0-add std\n1-remove std\n2-update std\n3-list std\n4-std Info\n5-Unsubmitted Stds\n6-banned std\n7-submit book\n8-barrow book\n9-exit std";
    char* writerMenuInfo = "Choose one of them to proceed your work\n0-add writer\n1-remove writer\n2-list writers\n3-update\n4-writer Info\n5-exit Writer menu";

    MAINMENU mainmenuOpt;
    WRITERMENU writerOpt;
    BOOKMENU bookMenu;
    STUDENTMENU stdMenu;

    KITAP* booksHead = NULL;
    FILE* bookFile;

    KITAPODUNC *bookBorrowList;
    
    FILE* bookBorrowFile;
    int totalBookOperations;


    KITAPYAZAR *bookWriterList;
    FILE *writerBookFile;

    YAZAR *writerHead = NULL;
    FILE *writerFile;
    int totalBook =0;

    OGRENCI *stdHead = NULL;
    FILE *stdFile;

    writerBookFile = fopen("KitapYazar.csv","r");
    if(writerBookFile == NULL) exit(-1);
    totalBook = readBookWriterFileToList(writerBookFile,&bookWriterList);
    fclose(writerBookFile);


    bookBorrowFile = fopen("KitapOdunc.csv","r");
    if(bookBorrowFile == NULL) exit(-1);
    totalBookOperations = readBookBorrowFileToList(bookBorrowFile,&bookBorrowList);

    //* bu islem sonucunde book borrow file elemanları bookborrowlist uzerinden erisilebilir olmalıdır
    fclose(bookBorrowFile);

    bookFile = fopen("Kitaplar.csv","r");
    if(bookFile == NULL) exit(-1);
    readBooksFileToList(bookFile,&booksHead,totalBookOperations,bookBorrowList);
    fclose(bookFile);


    do{
        printDiv();
        print(mainMenuInfo);
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

                            printStdInfo(stdHead,newStd.ad);
                            break;
                        case unSubmittedStd:

                            break;
                        case bannedStd:

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
                //* kitap verlieri alınıp otomatik olarak ilgili yerlere atanmıs vaziyette yazarların ve ogrencilerin 
                //* ortak noktası oldugu icin kitaplar file'i programın basında okunacak ve ilgili yerlere atanacak 
                do{
                    printDiv();
                    print(bookMenuInfo);
                    printf("selection:");
                    scanf("%d",&bookMenu);
                    printDiv();

                    switch(bookMenu){
                        case addBook:
                            break;
                        case removeBook:
                            break;
                        case updateBook:
                            break;
                        case BookInfo:
                            break;
                        case lateBooks:
                            break;
                        case shelfBook:
                            break;
                        case matchBWrt:
                            break;
                        case updataBWrt:
                            break;
                        case exitBook:
                            print("Book menu exited");
                            break;
                        default:
                             print("wrong selection please select options included above");
                            break;
                    }
                }while(bookMenu != exitBook);


            break;    
            case writers:
                writerHead = NULL;
                writerFile = fopen("Yazarlar.csv","r");
                if(writerFile == NULL) exit(-1);
                readWriterFile(writerFile,&writerHead);
                fclose(writerFile);
               
                YAZAR newWriter;

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


int readBookBorrowFileToList(FILE* bookProcessFile,KITAPODUNC** bookBorrowList){
    //* 1234567891012_2,17011020,0,28.12.2022
    print("read book process file func called");
    KITAPODUNC *tmp =(KITAPODUNC*) malloc(sizeof(KITAPODUNC)*1);
    int read = 0;
    int count = 0;
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
            if(size == count){
                tmp = (KITAPODUNC*) realloc(tmp,sizeof(KITAPODUNC)*size*2);
                size = size*2;
            }
            tmp[count].islemTipi = processType;
            strcpy(tmp[count].EtiketNo,bookStcker);
            strcpy(tmp[count].ogrID,stdId);
            tmp[count].islemTarihi.gun = day;
            tmp[count].islemTarihi.ay = month;
            tmp[count].islemTarihi.yil = year;
            count++;
        }
        if(ferror(bookProcessFile)){
            print("there was an error while reading Kitap file");
            exit(-1);
        }

    }while(!feof(bookProcessFile));

    *bookBorrowList = tmp;
    return count;
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
    KITAP* tmo = books;
    KITAPORNEK *tmo2 = tmo->head; 
    while(tmo != NULL){
        printDiv();
        printf("%s,%s,%d\n",tmo->kitapAdi,tmo->ISBN,tmo->adet);
        print("KITABA AIT ORNEKLER");
        while(tmo2 != NULL){
            printf("state: %s, label:%s \n",tmo2->Durum,tmo2->EtiketNo);
            tmo2 = tmo2->next;
        }
        tmo = tmo->next;
        if(tmo != NULL) tmo2 = tmo->head;
        
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
        
        //* SUANDA LABEL ELIMIZDE, KITAP HISTORYSI UZERINDE GEZEREK LABELIMIZLE ESLESEN KITAP VARSA VE HALA TESLIM EDILMEMISSE ILGILI OGRENCI 
        //* NUMARASINI KITABIN DURUM KISMINA KOPYALAYALIM

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


void printStdInfo(OGRENCI* stdHead,char* stdName){
    OGRENCI *tmp = stdHead;
    int stdExists = 0;
    while(tmp!= NULL){
        if(strcmp(tmp->ad,stdName) == 0){
            stdExists = 1;
            printStdNode(tmp);
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

void printWriterInfo(YAZAR *head,char* writerName,KITAPYAZAR *bookWriter,int totalBook){
    YAZAR *tmp = head;
    int found = 0;
    int writerExists = 0;
    int i = 0;
    while(tmp!= NULL){
        if(strcmp(tmp->yazarAd,writerName) == 0){
            writerExists = 1;
            printWriterNode(tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
            for(i=0;i<totalBook;i++){
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
        print("free");
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