#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct DATA{
	int ID;
	char Name[50];
	char department[20];
	struct DATA *next;
}data;

int Sort_Ascending(int first,int second);
int Sort_Descending(int first,int second);
void Split_Data(data* holder,char buff[255],char delimiter[2]);
data* File_Read(char *File_Name,char delimiter[2]);
void File_Write(data* head, char *File_Name,char delimiter );
void File_Write_wfprintf(data* head, char *File_Name,char delimiter );
data* Sort_Data(data* head,int (*Sort_Condition)(int,int));
void Print_List(data* head);


int main(){
    data* head;
	head=File_Read("Dataset.txt",",\0");
	Print_List(head);
	head=Sort_Data(head,Sort_Descending);
	printf("Descending\n");
	Print_List(head);
	File_Write(head,"New_dataset.txt",',');
	
	head=Sort_Data(head,Sort_Ascending);
	printf("Ascending\n");
	Print_List(head);
    File_Write_wfprintf(head,"New_dataset_v3.txt",',');
	
    

}

void Split_Data(data* holder,char buff[255],char delimiter[2]){
    char *token;
    token = strtok(buff,delimiter); //* buff icerisindeki \0 indexleri 
    holder->ID = atoi(token); //* str yi inte cevirir
    token = strtok(NULL,delimiter);
    strcpy(holder->Name,token);
    token = strtok(NULL,delimiter);
    token[strlen(token)-1] = '\0';
    strcpy(holder->department,token);
}

data* File_Read(char *File_Name,char delimiter[2]){
    FILE* fp = fopen(File_Name,"r");
    char buf[255];
    data* head = (data*) malloc(sizeof(data)*1);
    data* curr_data; 
    data* prev_data;

    if(fgets(buf,255,fp) != NULL){
        printf("%s",buf);
        Split_Data(head,buf,delimiter);
    }else{
        return NULL;
    }

    //* yukarıdaki head yapısında headi set ettik 
    prev_data = head;
    while(fgets(buf,255,fp) != NULL){
        printf("%s",buf);
        curr_data = (data*) malloc(sizeof(data)*1);
        prev_data->next = curr_data;
        Split_Data(curr_data,buf,delimiter);
        prev_data = curr_data;
    }

    prev_data->next = NULL;
    fclose(fp);
    return head;

}

void File_Write(data* head, char *File_Name,char delimiter ){
    FILE *fp = fopen(File_Name,"w");
    char tmp[20];

    while(head != NULL){
       // itoa(head->ID,tmp,10); //* convert int data to string data 
        head->ID = '0' + tmp ;
        fputs(tmp,fp);
        fputc(delimiter,fp);
        fputs(head->Name,fp);
        fputc(delimiter,fp);
        fputs(head->department,fp);
        fputc('\0',fp);
        head = head->next;
    }
    fclose(fp);
    return ;
}

void File_Write_wfprintf(data* head, char *File_Name,char delimiter ){
    FILE *fp = fopen(File_Name,"w");
    char tmp[20];
    while(head != NULL){
        fprintf(fp,"%d,%s,%s\n",head->ID,head->Name,head->department);
        head = head->next;
    }
    fclose(fp);
    return;
}

data* Sort_Data(data* head,int (*Sort_Condition)(int,int)){
    if(head == NULL || head->next == NULL){
        return head;
    }
    
    int max = head->ID;
    data *prev = head;
    data* to_move = NULL;
    data *tmp = head->next;

    //* find maximum value in rest(head->next)
    while(tmp != NULL){
        if(Sort_Condition(tmp->ID,max)){
            max = tmp->ID;
            to_move = prev;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    if(to_move == NULL){
        head->next = Sort_Data(head->next,Sort_Condition);
        return head;
    }

    prev = to_move;
    to_move = prev->next;
    prev->next = prev->next->next;
    to_move->next = Sort_Data(head,Sort_Condition);
    return to_move;

}



int Sort_Ascending(int first,int second){
	return first<second;
}

int Sort_Descending(int first,int second){
	return first>second;
}

void Print_List(data* head){
    while(head != NULL){
		printf("ID: %d, Name: %s, Department: %s\n",head->ID,head->Name,head->department);
        head = head->next;
    }
}

 
