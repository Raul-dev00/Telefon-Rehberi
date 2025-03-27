#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rehber {
    int numara;
    char isim[20];
    struct rehber* next;
};typedef struct rehber rbr;

void ilk_kisi_ekle(rbr** Head, int no, char* isim) {
    for (int i=0; i<isim[i]!='\0'; i++) {
        isim[i] = tolower(isim[i]);
    }
    rbr* new_head = (rbr*)malloc(sizeof(rbr));
    strcpy(new_head->isim, isim);
    new_head->numara = no;
    new_head->next=NULL;
    *Head = new_head;
}

void kisi_ekle(rbr* Head, int no, char* isim) {
    for (int i=0; i<isim[i]!='\0'; i++) {
        isim[i] = tolower(isim[i]);
    }
    rbr* iter = Head;
    while(iter->next!=NULL) {
        iter = iter->next;
    }
    iter->next=(rbr*)malloc(sizeof(rbr));
    strcpy(iter->next->isim, isim);
    iter->next->numara=no;
    iter->next->next=NULL;
}

rbr* kisi_sil(rbr* Head, char* isim) {
    for (int i=0; i<isim[i]!='\0'; i++) {
        isim[i] = tolower(isim[i]);
    }
    rbr* iter = Head;
    if (iter==NULL) {
        printf("Rehberde kayitli kisi bulunmamaktadir.\n");
        return Head;
    }
    else {
        //ilk eleman ama tek eleman degil silme
        if (strcmp(iter->isim,isim)==0 && iter->next!=NULL) {
            rbr* temp = Head;
            Head = Head->next;
            free(temp);
            printf("Silme islemi basarili.\n");
            return Head;
        }
        //ilk eleman ve tek eleman silme
        if (strcmp(iter->isim,isim)==0 && iter->next==NULL) {
            free(iter);
            rbr* new_head = NULL;
            Head = new_head;
            printf("Silme islemi basarili.\n");
            return Head;
        }
        while(iter->next != NULL) {
            //ne ilk ne som eleman silme
            if(strcmp(iter->next->isim, isim)==0 && iter->next!=NULL) {
                rbr* temp = iter->next;
                iter->next=iter->next->next;
                free(temp);
                printf("Silme islemi basarili.\n");
                return Head;
            }
            //son eleman silme
            if(strcmp(iter->next->isim, isim)==0 && iter->next->next==NULL) {
                rbr* temp = iter->next;
                free(temp);
                iter->next = NULL;
                printf("Silme islemi basarili.\n");
                return Head;
            }
            iter = iter->next;
        }
        printf("Aradiginiz isim bulunmamaktadir.\n");
    }
}

void kisi_arama(rbr* Head, char* isim) {
    for (int i=0; i<isim[i]!='\0'; i++) {
        isim[i] = tolower(isim[i]);
    }
    rbr* iter = Head;
    while (iter!=NULL) {
        if (strcmp(iter->isim,isim)==0) {
            printf("Isim: %s\n", iter->isim);
            printf("Numara: %d\n", iter->numara);
            return ;
        }
        iter=iter->next;
    }
    printf("Kisi bulunamadi.\n");
}

void rehberi_goruntule(rbr* Head) {
    rbr* iter = Head;
    printf("*****   REHBER  *****\n");
    if (iter==NULL) {
        printf("Rehberde goruntulenecek kisi yok.\n\n");
        return ;
    }
    while (iter!=NULL) {
        printf("Isim: %s\n", iter->isim);
        printf("Numara: %d\n", iter->numara);
        printf("_____________________________\n");
        iter=iter->next;
    }
}

void serbestBirak(rbr* Head) {
    rbr* temp = Head;
    while (Head!=NULL) {
        temp=Head;
        Head=Head->next;
        free(temp);
    }
}

int main(void)
{
    rbr* head = NULL;
    bool dongu = true;
    while(dongu) {
        int secim = 0;
        printf("Yapmak istediginiz islemi seciniz.\n");
        printf("[1] Kisi Ekle\n[2] Kisi Sil\n[3] Kisi Ara-Bul\n[4] Rehberi Goruntule\n[5] Kapat");
        scanf("%d", &secim);
        switch(secim) {
            case 1:
                char isim[20];
                int num;
                printf("Eklenecek kisinin bilgilerini giriniz:\n");
                getchar();
                printf("Isim: ");
                scanf("%[^\n]s", &isim);
                printf("Numara: ");
                scanf("%d", &num);
                if(head==NULL) {
                    ilk_kisi_ekle(&head,num,isim);
                    head->next=NULL;
                }
                else {
                    kisi_ekle(head,num,isim);
                }
                break;
            case 2:
                char silinecek_isim[10];
                getchar();
                printf("Silinecek kisinin adini giriniz: ");
                scanf("%[^\n]s", &silinecek_isim);
                head=kisi_sil(head,silinecek_isim);
                break;
            case 3:
                char aranan[20];
                getchar();
                printf("Aranan kisinin adini giriniz: ");
                scanf("%[^\n]s", &aranan);
                kisi_arama(head,aranan);
                break;
            case 4:
                rehberi_goruntule(head);
                break;
            case 5:
                printf("Cikis yapildi.");
                dongu=false;
                serbestBirak(head);
                break;
        }
    }
    return 0;
}
