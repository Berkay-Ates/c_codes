#include<stdio.h>
#include<stdlib.h>
 
int main(){

    int a = 55;
    printf("%c",a);

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