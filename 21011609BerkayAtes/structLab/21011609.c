#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct user{
    int id;
    char name[16];
    char type;
} USER;

void addUser(USER *users,int index);
USER* orderUsers(USER *users,int userCount);

int main(){

    int userCount = 0;
    int i;

    printf("userCount: ");
    scanf("%d",&userCount);
    USER* users = (USER*) malloc(sizeof(USER)*userCount);
    if(users == NULL){
        exit(-1);
    }

    USER user1 = {1996,"name1",'A'};
    USER user2 = {1992,"name2",'B'};
    USER user3 = {1998,"name3",'B'};
    USER user4 = {19915,"name4",'B'};
    USER user5 = {19912,"name5",'B'};
    USER user6 = {19919,"name6",'B'};
    USER user7 = {1991,"name7",'B'};
    USER user8 = {1993,"name8",'A'};
    USER user9 = {1990,"name9",'A'};
    USER user10 = {1997,"name10",'A'};
    USER user11 = {19910,"name11",'A'};
    USER user12 = {19917,"name12",'A'};
    USER user13 = {19925,"name13",'A'};

    users[0] = user1;
    users[1] = user2;
    users[2] = user3;
    users[3] = user3;
    users[4] = user5;
    users[5] = user6;
    users[6] = user7;
    users[7] = user8;
    users[8] = user9;
    users[9] = user10;
    users[10] = user11;
    users[11] = user12;
    users[12] = user13;



    // for(i = 0;i<userCount;i++){
    //     addUser(users,i);
    // } //* for client assign

    for(i=0;i<userCount;i++){
        printf("id:%d, name:%s, type:%c\n",users[i].id,users[i].name,users[i].type);
    }
    users = orderUsers(users,userCount);
    for(i=0;i<userCount;i++){
        printf("id:%d, name:%s, type:%c\n",users[i].id,users[i].name,users[i].type);
    }

    free(users);
}


USER* orderUsers(USER *users,int userCount){
    int i = 0;
    int j=0;
    int btype = 0;
    int atype=0;
    USER *newUsers = (USER*) malloc(sizeof(USER)*userCount);

    for(i=0;i<userCount;i++){
        if(users[i].type == 'A'){
            j=atype;
            while(0<j && newUsers[j-1].id>users[i].id){
                newUsers[j].id = newUsers[j-1].id;
                strcpy(newUsers[j].name,newUsers[j-1].name);
                newUsers[j].type = newUsers[j-1].type;
                j--;
            }
            newUsers[j].id = users[i].id;
            strcpy(newUsers[j].name,users[i].name);
            newUsers[j].type = users[i].type;
            atype++;
        }
    }

    for(i=0;i<userCount;i++){
        if(users[i].type == 'B'){
            j=btype;
            while(0<j && newUsers[atype+j-1].id >users[i].id){
                newUsers[j+atype].id = newUsers[j+atype-1].id;
                strcpy(newUsers[j+atype].name,newUsers[j+atype-1].name);
                newUsers[j+atype].type = newUsers[j+atype-1].type;
                j--;
            }
            newUsers[j+atype].id = users[i].id;
            strcpy(newUsers[j+atype].name,users[i].name);
            newUsers[j+atype].type = users[i].type;
            btype++;
        }
    }

    free(users);
    return newUsers;
}

void addUser(USER *users,int index){
    USER newUser;
    int id;
    char name[15];
    char type;

    printf("id:");
    scanf("%d",&id);
    printf("name:");
    scanf("%s",name);
    printf("type:");
    scanf(" %c",&type);
    users[index].id = newUser.id = id;
    strcpy(users[index].name,name);
    users[index].type = type;
}


int find(int id,USER *user,int userCount){
    int i = 0;
    while(id<user[i].id && i<userCount){
        i++;
    }
    return i;
}