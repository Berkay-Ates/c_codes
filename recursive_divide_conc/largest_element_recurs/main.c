#include<stdio.h>
#include<stdlib.h>


int findLargest(int* a, int l, int r);
 
int main(){
    int a[10] = {9,4,1};
    int largest=0;

    largest = findLargest(a,0,3);
    printf("%d",largest);
    return 0 ;
}   

int findLargest(int* a, int l, int r){
     int tmp1=0,tmp2=0;
    if(l==r){
        return l;
    }else{
        tmp1 = findLargest(a,l,(l+r)/2);
        tmp2 = findLargest(a,((l+r)/2)+1,r);
         
        if(a[tmp1]>=a[tmp2])
            return tmp1;
        else
            return tmp2;

    }
}

