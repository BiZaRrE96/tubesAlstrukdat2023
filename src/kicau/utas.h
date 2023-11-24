#ifndef _Utas_H_
#define _Utas_H_

#include <stdio.h>
#include <stdlib.h>
#include "../boolean/boolean.h"
#include "../commandmachine/commandmachine.h"
#include "../datetime/datetime.h"
#include "kicau.h"

// Utas dibuat dengan ADT LinkedList

typedef struct node *AddressUtas;
typedef struct node{
    KICAU info;
    AddressUtas next;
} Node;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

typedef struct{
    AddressUtas p;
    int IDUtas;
    int IDKicau;
} Utas;

typedef struct {
    Utas Utas[100];
    int length;
} ListUtas;

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

AddressUtas newNode(KICAU val) {
/* Definisi Utas : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */
    AddressUtas p = (AddressUtas) malloc(sizeof(Node));
    if (p!=NULL) {
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}

void createListUtas(ListUtas *LU){
    len(*LU) = 0;
}

void createEmptyUtas(Utas *U) {
    First(*U) = NULL;
}

boolean isEmptyListUtas(ListUtas LU){
    return len(LU) == 0;
}

boolean isEmptyUtas(Utas U){
    return First(U) == NULL;
}

int lengthUtas(Utas U) {
    int count = 0;
    AddressUtas p = First(U);
    while (p != NULL) {
        count++;
        p = NEXT(p);
    }
    return count;
}

void insertFirstUtas(Utas *U, KICAU val) {
    AddressUtas p = newNode(val);
    if (p!= NULL) {
        NEXT(p) = First(*U);
        First(*U) = p;
    }
}

void insertLastUtas(Utas *U, KICAU val) {
    AddressUtas p = newNode(val);
    if (p!= NULL) {
        if (isEmptyUtas(*U)) {
            insertFirstUtas(U, val);
        } else {
            AddressUtas last = First(*U);
            while (NEXT(last) != NULL) {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

void insertAtUtas(Utas *U, KICAU val, int index) {
    if (index == 0) {
        insertFirstUtas(U, val);
        return;
    } 
    AddressUtas p = newNode(val);
    if (p!= NULL) {
        AddressUtas last = First(*U);
        int i = 0;
        while (i < index-1) {
            last = NEXT(last);
            i++;
        }
        NEXT(p) = NEXT(last);
        NEXT(last) = p;
    }
}

void deleteFirstUtas(Utas *U) {
    if (!isEmptyUtas(*U)) {
        AddressUtas p = First(*U);
        First(*U) = NEXT(p);
        NEXT(p) = NULL;
        free(p);
    }
}

void deleteLastUtas(Utas *U) {
    if (!isEmptyUtas(*U)) {
        AddressUtas last = First(*U);
        AddressUtas prev = NULL;
        while (NEXT(last) != NULL) {
            prev = last;
            last = NEXT(last);
        }
        if (prev == NULL) {
            deleteFirstUtas(U);
        } else {
            NEXT(prev) = NULL;
            free(last);
        }
    }
}

void deleteAtUtas(Utas *U, int index) {
    if (index == 0) {
        deleteFirstUtas(U);
        return;
    }
    if (!isEmptyUtas(*U)) {
        AddressUtas last = First(*U);
        AddressUtas prev = NULL;
        int i = 0;
        while (i < index) {
            prev = last;
            last = NEXT(last);
            i++;
        }
        NEXT(prev) = NEXT(last);
        NEXT(last) = NULL;
        free(last);
    }
}

boolean isKicauUsedOnUtas(ListUtas LU, int IDKicau) {
    int i = 0;
    while (i < len(LU)) {
        if (IDKicau(GetUtas(LU, i)) == IDKicau) {
            return true;
        }
        i++;
    }
    return false;
}

boolean isUtasExist(ListUtas LU, int IDUtas) {
    return (IDUtas < len(LU) && IDUtas >= 0);
}

void insertUtas(ListUtas *LU, Utas U) {
    GetUtas(*LU, len(*LU)) = U;
    len(*LU)++;
}

void UTAS(ListUtas *listutas, int idxKicau, KicauList kicaulist, User user) {
    if (isKicauUsedOnUtas(*listutas, idxKicau)) {
        printf("Kicauan ini telah digunakan sebagai Utas\n");
        return;
    }

    if (!isWordEqual(Username(user), GetAuthor(kicaulist, idxKicau))) {
        printf("Utas ini bukan milik anda!\n");
        return;
    }

    // Apakah idxKicau valid?
    if (idxKicau > Count(kicaulist) || idxKicau < 1) {
        printf("Utas tidak ditemukan!\n");
        return;
    }

    Utas utas;

    utas.IDKicau = idxKicau;
    utas.IDUtas = len(*listutas);
    createEmptyUtas(&utas);

    insertFirstUtas(&utas, GetKicauan(kicaulist, idxKicau));

    printf("\nUtas berhasil dimuat!\n");

    while (true) {
        printf("\nMasukkan kicauan:\n"); STARTCOMMAND();

        KICAU Element;
        Element.Author = Username(user);
        Element.Text = currentWord;
        setToCurrentTime(&Element.Time);

        insertLastUtas(&utas, Element);

        printf("\nApakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
        STARTCOMMAND();

        if (!isWordStrEqual(currentWord, "YA", 2)) {
            break;
        }

        printf("\n");
    }
    
    insertUtas(listutas, utas);

    printf("\nUtas selesai!\n");
}

void SAMBUNG_UTAS(ListUtas *listutas, int idxUtas, int indeks, User user) {
    idxUtas--;
    if (!isUtasExist(*listutas, idxUtas)) {
        printf("Utas tidak ditemukan!\n");
        return;
    }

    Utas utas = GetUtas(*listutas, idxUtas);

    if (idxUtas >= lengthUtas(utas) || idxUtas < 0) {
        printf("Index tidak valid!\n");
        return;
    }

    if (!isWordEqual(Username(user), Author(utas))) {
        printf("Anda tidak bisa menyambung utas ini!\n");
        return;
    }

    printf("Masukkan kicauan: "); STARTCOMMAND();

    KICAU Element;
    Element.Author = Username(user);
    Element.Text = currentWord;
    setToCurrentTime(&Element.Time);

    insertAtUtas(&utas, Element, indeks);

    GetUtas(*listutas, idxUtas) = utas;

    printf("\nKicauan berhasil disambung\n");
}

void HAPUS_UTAS(ListUtas *listutas, int idxUtas, int indeks, User user) {
    idxUtas--;
    
    if (!isUtasExist(*listutas, idxUtas)) {
        printf("Utas tidak ditemukan!\n");
        return;
    }

    Utas utas = GetUtas(*listutas, idxUtas);

    if (indeks > lengthUtas(utas) || indeks < 1) {
        printf("Kicauan dengan index %d tidak ditemukan pada utas ini!\n", indeks);
        return;
    }

    if (!isWordEqual(Username(user), Author(utas))) {
        printf("Anda tidak bisa menghapus kicauan dalam utas ini!\n");
        return;
    }

    if (indeks == 0) {
        printf("Anda tidak bisa menghapus kicauan utama!\n");
        return;
    }

    deleteAtUtas(&utas, indeks);

    printf("\nKicauan berhasil dihapus!\n\n");
}

void CETAK_UTAS(ListUtas listutas, int idxUtas, User user) {
    idxUtas--;
    if (!isUtasExist(listutas, idxUtas)) {
        printf("Utas tidak ditemukan!\n");
        return;
    }

    Utas utas = GetUtas(listutas, idxUtas);

    if (!AcanSeeB(Username(user), Author(utas))) {
        printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!\n");
        return;
    }

    AddressUtas p = First(utas);
    int i = 1;

    KICAU kicau = INFO(p);
    printf("| ID = %d\n", IDKicau(utas));
    printf("| %s \n", wordToStr(Author(utas)));
    printf("| ");
    TulisDATETIME(kicau.Time);
    printf("\n");
    printf("| %s\n", wordToStr(kicau.Text));
    p = NEXT(p);

    while (p != NULL) {
        KICAU kicau = INFO(p);
        printf("\n");
        printf("    | INDEX = %d\n", i);
        printf("    | %s\n", wordToStr(Author(utas)));
        printf("    ");
        TulisDATETIME(kicau.Time);
        printf("\n");
        printf("    | %s\n", wordToStr(kicau.Text));
        p = NEXT(p);
    }
}
// boolean KicauUsed(int IDKicau, ListUtas LU){
//     for (int i = 0; i < len(LU); i++){
//         if (IDKicau(GetUtas(LU,i)) == IDKicau){
//             return true;
//         }
//     }
//     return false;
// }

// void UTAS(int IDKicau, KicauList KL, User user, ListUtas *LU) 
// {
//     if (!KicauUsed(IDKicau, *LU)){
//         if (isWordEqual(Username(user),GetAuthor(KL,IDKicau))){
//             Utas utas;
//             createUtas(&LU, KL, &utas, IDKicau);
//             AddressUtas p = First(utas);
//             opsi();
//             STARTCOMMAND();
//             Word input = currentWord;
//             printf("\n");
//             while (isWordStrEqual(input,"YA",2)){
//                 KICAU kicau;
//                 printf("Masukkan Kicauan:\n");
//                 STARTCOMMAND();
//                 input = currentWord;
//                 kicau.Text = input;
//                 setToCurrentTime(&kicau.Time);
//                 AddressUtas Node = newNode(kicau);
//                 NEXT(p)=Node;
//                 p=NEXT(p);
//                 opsi();
//                 STARTCOMMAND();
//                 input = currentWord;
//             }
//             printf("Utas selesai!\n");
//         } else {
//             printf("Utas ini bukan milik anda!\n");
//         }
//     } else {
//         printf("Kicauan ini telah digunakan sebagai Utas\n");
//     }
// }

// void createUtas(ListUtas *LU, KicauList KL, Utas *U, int IDKicau){
//     GetUtas(*LU,len(*LU)) =*U;
//     AddressUtas p = newNode(GetKicauan(KL,IDKicau));
//     First(*U) = p;
//     IDUtas(*U) = len(*LU);
//     printf("idUtas = %d\n",IDUtas(*U));
//     IDKicau(*U) = IDKicau;
//     len(*LU)++;
// }
// boolean UtasExist(int IDUtas, ListUtas LU){
//     if (IDUtas<len(LU)){
//         return true;
//     } else {
//         return false;
//     }
// }

// void cetakUtas(ListUtas LU,int IDUtas, User user){
//     if (UtasExist(IDUtas, LU)){
//         Utas utas=GetUtas(LU,IDUtas);
//         AddressUtas p = First(utas);
//         int i = 1;
//         if ((AcanSeeB(Username(user),Author(utas))) == true){
//             KICAU kicau = INFO(p);
//             printf("| ID = %d\n",IDKicau(utas));
//             printf("| %s \n",wordToStr(Author(utas)));
//             printf("| ");
//             TulisDATETIME(kicau.Time);
//             printf("\n");
//             printf("| %s\n",wordToStr(kicau.Text));
//             p = NEXT(p);
//             while (p != NULL){
//                 KICAU kicau = INFO(p);
//                 printf("\n");
//                 printf("    | INDEX = %d\n",i);
//                 printf("    | %s\n",wordToStr(Author(utas)));
//                 printf("    ");
//                 TulisDATETIME(kicau.Time);
//                 printf("\n");
//                 printf("    | %s\n",wordToStr(kicau.Text));
//                 p = NEXT(p);
//             }
//         } else {
//             printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!\n");
//         }
//     } else {
//         printf("Utas tidak ditemukan!\n");
//     }
// }

// void Delete(Utas utas, int index){
//     AddressUtas temp,p = First(utas);
//     while(p != NULL){
//         temp = p;
//         p = NEXT(p);
//         index--;
//     NEXT(temp) = NEXT(p);
//     free(p);
//     }
// }

// void HapusUtas(ListUtas *LU, int IDUtas, int index,  User user){
//     if (UtasExist(IDUtas, *LU)){  
//         if(index == 0){
//             printf("Anda tidak bisa menghapus kicauan utama!\n  ");
//         } else {
//             Utas utas = GetUtas(*LU, IDUtas);
//             int i = index;
//             AddressUtas p = First(utas);
//             if (isWordEqual(INFO(p).Author, Username(user))){
//                 while(i != 0){
//                     p=NEXT(p);
//                     i--;
//                 }
//                 if (p==NULL){
//                     printf("Kicauan sambungan dengan index %d tidak ditemukan pada Utas!\n", index);
//                 } else {
//                     Delete(utas, index);
//                 }
//             } else {
//                 printf("Anda tidak bisa menghapus kicauan dalam Utas ini!\n");
//             }
//         }
//     } else {
//         printf("Utas tidak ditemukan!\n");
//     }
// }
// void sambungUtas(ListUtas *LU,int IDUtas, int index, User user){
//     if (UtasExist(IDUtas, *LU)){
//         Utas utas = GetUtas(*LU, IDUtas);
//             int i = index-1;
//             AddressUtas p = First(utas);
//             if (isWordEqual(INFO(p).Author, Username(user))){
//                 while(i != 0){
//                     p=NEXT(p);
//                     i--;
//                 }
//                 if (p==NULL){
//                     printf("Index terlalu tinggi!\n");
//                 } else {
//                     KICAU kicau;
//                     printf("Masukkan kicauan: ");
//                     STARTCOMMAND();
//                     Word input = currentWord;
//                     if (!isBlank(input)){
//                         kicau.Text = input;
//                         setToCurrentTime(&kicau.Time);
//                         NEXT(p) = newNode(kicau);
//                         p = NEXT(p);
//                     }
//                     else{
//                         printf("Kicauan tidak boleh hanya berisi spasi!\n");
//                     }
//                 }
//             } else {
//                 printf("Anda tidak bisa menghapus kicauan dalam Utas ini!\n");
//             }
//     } else {
//         printf("Utas tidak ditemukan!\n");
//     }
// }
#endif 
