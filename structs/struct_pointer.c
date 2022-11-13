#include<stdio.h>
#include<stdlib.h>

typedef struct terim {
    int derece;
    int katsayi;
    char isim[30];
} TERIM;
 
int main(){

    TERIM *pt;
    TERIM t;

    printf("normal terim derecesi,katsayisi,ismi giriniz\n");
    scanf("%d",&t.derece);
    scanf("%d",&t.katsayi);
    scanf("%s",t.isim); //* isim zaten dizi oldugu icin bir pointer dolayısıyla kendisini verebiliriz scanf de pointer istiyor ki verileri stringi kaydetsin 

    printf("pointer terim derecesi,katsayisi,ismi giriniz\n");
    scanf("%d",&pt->derece);
    scanf("%d",&(*pt).katsayi);
    scanf("%s",pt->isim);

///*   pt->katsayisi === t.katsayi // pt'ye katsayı degiskeni atamak icin &(pt->katsayisi) veya da &pt->katsayisi veya da &(*pt).katsayi ifadesini kullanırız 
    
    printf("normal eleman degerleri katsayi:%d, derece:%d,isim:%s",t.katsayi,t.derece,t.isim);
    printf("pointer eleman degerleri katsayi:%d, derece:%d,isim:%s",pt->katsayi,(*pt).derece,pt->isim);


}