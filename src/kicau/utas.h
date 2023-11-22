#ifndef _Utas_H_
#define _Utas_H_

#include <stdio.h>
#include <stdlib.h>
#include "../boolean/boolean.h"
#include "../sentencemachine/sentencemachine.h"
#include "../commandmachine/commandmachine.h"
#include "../datetime/datetime.h"
#include "kicau.h"
// Utas dibuat dengan ADT List Statik

typedef struct node *Address;
typedef struct node{
    KICAU info;
    Address next;
} Node;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

typedef struct{
    Address p;
    int IDUtas;
    int IDKicau;
} Utas;

typedef struct {
    Utas Utas[100];
    int length;
}ListUtas;

#define GetUtas(LU,i) (LU).Utas[(i)]
#define First(U) (U).p
#define IDUtas(U) (U).IDUtas
#define IDKicau(U) (U).IDKicau
#define IdKicau(l) INFO(First(l)).id
#define Author(U)  INFO((U).p).Author
#define len(LU) (LU).length

void opsi(){
    printf("\n");
    printf("Apakah Anda ingin melanjutkan Utas ini? (YA/TIDAK)");
}
Address newNode(KICAU val){
    Address p = (Address) malloc(sizeof(Node));
    if (p!=NULL) {
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}

boolean KicauUsed(int IDKicau, ListUtas LU){
    for (int i = 0; i < len(LU); i++){
        if (IDKicau(GetUtas(LU,i)) == IDKicau){
            return true;
        }
    }
    return false;
}

void UTAS(int IDKicau, KicauList KL, User user, ListUtas LU){
    if (!KicauUsed(IDKicau, LU)){
        if (isWordEqual(Username(user),GetAuthor(KL,IDKicau))){
            Utas utas;
            createUtas(&LU, KL, &utas, IDKicau);
            Address p = First(utas);
            opsi();
            STARTCOMMAND();
            Word input = currentWord;
            printf("\n");
            while (isWordStrEqual(input,"YA",2)){
                p= NEXT(p);
                KICAU kicau = INFO(p);
                printf("Masukkan Kicauan:\n");
                STARTCOMMAND();
                input = currentWord;
                kicau.Text = input;
                setToCurrentTime(&kicau.Time);
                opsi();
                STARTCOMMAND();
                input = currentWord;
            }
        } else {
            printf("Utas ini bukan milik anda!\n");
        }
    } else {
        printf("Kicauan ini telah digunakan sebagai Utas\n");
    }
}

void createUtas(ListUtas *LU, KicauList KL, Utas *U, int IDKicau){
    GetUtas(*LU,len(*LU)) =*U;
    Address p = newNode(GetKicauan(KL,IDKicau));
    First(*U) = p;
    IDUtas(*U) = len(*LU);
    IDKicau(*U) = IDKicau;
    len(*LU)++;
}
boolean UtasExist(int IDUtas, ListUtas LU){
    if (IDUtas<len(LU)){
        return true;
    } else {
        return false;
    }
}

void cetakUtas(ListUtas LU,int IDUtas, User user){
    if (UtasExist(IDUtas, LU)){
        Utas utas=GetUtas(LU,IDUtas);
        Address p = First(utas);
        int i = 1;
        if ((AcanSeeB(user,Author(utas))) == true){
            KICAU kicau = INFO(p);
            printf("| ID = %d\n",IDKicau(utas));
            printf("| %s \n",wordToStr(Author(utas)));
            printf("| ");
            TulisDATETIME(kicau.Time);
            printf("\n");
            printf("| %s\n",wordToStr(kicau.Text));
            p = NEXT(p);
            while (p != NULL){
                KICAU kicau = INFO(p);
                printf("\n");
                printf("    | INDEX = %d\n",i);
                printf("    | %s\n",wordToStr(Author(utas)));
                printf("    ");
                TulisDATETIME(kicau.Time);
                printf("\n");
                printf("    | %s\n",wordToStr(kicau.Text));
                p = NEXT(p);
            }
        } else {
            printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!\n");
        }
    } else {
        printf("Utas tidak ditemukan!\n");
    }
}

void Delete(Utas utas, int index){
    Address temp,p = First(utas);
    while(p != NULL){
        temp = p;
        p = NEXT(p);
        index--;
    NEXT(temp) = NEXT(p);
    free(p);
    }
}

void HapusUtas(ListUtas LU, int IDUtas, int index,  User user){
    if (UtasExist(IDUtas, LU)){  
        if(index == 0){
            printf("Anda tidak bisa menghapus kicauan utama!\n  ");
        } else {
            Utas utas = GetUtas(LU, IDUtas);
            int i = index;
            Address p = First(utas);
            if (isWordEqual(INFO(p).Author, Username(user))){
                while(i != 0){
                    p=NEXT(p);
                    i--;
                }
                if (p==NULL){
                    printf("Kicauan sambungan dengan index %d tidak ditemukan pada Utas!\n", index);
                } else {
                    Delete(utas, index);
                }
            } else {
                printf("Anda tidak bisa menghapus kicauan dalam Utas ini!\n");
            }
        }
    } else {
        printf("Utas tidak ditemukan!\n");
    }
}
void sambungUtas(ListUtas LU,int IDUtas, int index, User user){
    if (UtasExist(IDUtas, LU)){
        Utas utas = GetUtas(LU, IDUtas);
            int i = index-1;
            Address p = First(utas);
            if (isWordEqual(INFO(p).Author, Username(user))){
                while(i != 0){
                    p=NEXT(p);
                    i--;
                }
                if (p==NULL){
                    printf("Index terlalu tinggi!\n");
                } else {
                    p=NEXT(p);
                    KICAU kicau = INFO(p);
                    printf("Masukkan kicauan: ");
                    STARTCOMMAND();
                    Word input = currentWord;
                    if (!isBlank(input)){
                        kicau.Text = input;
                        setToCurrentTime(&kicau.Time);
                    }
                    else{
                        printf("Kicauan tidak boleh hanya berisi spasi!\n");
                    }
                }
            } else {
                printf("Anda tidak bisa menghapus kicauan dalam Utas ini!\n");
            }
    } else {
        printf("Utas tidak ditemukan!\n");
    }
}
#endif 