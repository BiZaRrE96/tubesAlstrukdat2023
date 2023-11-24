/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address_Linked dengan pointer */
/* ElType_Linked adalah integer */

#ifndef listlinier_H
#define listlinier_H

#include "../boolean/boolean.h"
#include <stdio.h>
#include <stdlib.h>

/* Definisi Node_Linked : */
typedef int ElType_Linked;
typedef struct node_Linked *Address_Linked;
typedef struct node_Linked
{
    ElType_Linked info_Linked;
    Address_Linked next_Linked;
} Node_Linked;

#define INFO_Linked(p) (p)->info_Linked
#define NEXT_Linked(p) (p)->next_Linked

Address_Linked newNode_Linked(ElType_Linked val)
{
    Address_Linked p = (Address_Linked)malloc(sizeof(Node_Linked));
    if (p != NULL)
    {
        INFO_Linked(p) = val;
        NEXT_Linked(p) = NULL;
    }
    return p;
}

typedef Address_Linked List;

#define IDX_UNDEF_Linked (-1)
#define FIRST_Linked(l) (l)

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateListLinked(List *l)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    FIRST_Linked(*l) = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isEmptyLinked(List l)
/* Mengirim true jika list kosong */
{
    return (FIRST_Linked(l) == NULL);
}

/****************** GETTER SETTER ******************/
ElType_Linked getElmtLinked(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..lengthLinked(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
    int i = 0;
    List p = l;

    // ALGORITMA
    while (i < idx)
    {
        p = NEXT_Linked(p);
        i++;
    }
    return INFO_Linked(p);
}

void setElmtLinked(List *l, int idx, ElType_Linked val)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..lengthLinked(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
{
    int i = 0;
    List p = *l;

    // ALGORITMA
    while (i < idx)
    {
        p = NEXT_Linked(p);
        i++;
    }
    INFO_Linked(p) = val;
}

int indexOfLinked(List l, ElType_Linked val)
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF_Linked jika tidak ditemukan */
{
    List p = l;
    int i = 0;
    boolean found = false;

    while (p != NULL && !found)
    {
        if (INFO_Linked(p) == val)
        {
            found = true;
        }
        else
        {
            p = NEXT_Linked(p);
            i++;
        }
    }

    if (found)
    {
        return i;
    }
    else
    {
        return IDX_UNDEF_Linked;
    }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst_Linked(List *l, ElType_Linked val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
    Address_Linked p;
    p = newNode_Linked(val);
    if (p == NULL)
    {
    }
    else
    {
        NEXT_Linked(p) = *l;
        *l = p;
    }
}

void insertLastLinked(List *l, ElType_Linked val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    Address_Linked q;
    Address_Linked p;
    q = *l;
    p = newNode_Linked(val);
    if (p == NULL)
    {
    }
    else
    {
        if (isEmptyLinked(*l))
        {
            insertFirst_Linked(l, val);
        }
        else
        {
            while (NEXT_Linked(q) != NULL)
            {
                q = NEXT_Linked(q);
            }
            NEXT_Linked(q) = p;
        }
    }
}

void insertAtLinked(List *l, ElType_Linked val, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..lengthLinked(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    Address_Linked q = *l;
    Address_Linked p = newNode_Linked(val);
    int i = 0;

    if (p == NULL)
    {
    }
    else
    {
        if (idx == 0)
        {
            insertFirst_Linked(l, val);
        }
        else
        {
            while (i < idx - 1)
            {
                i++;
                q = NEXT_Linked(q);
            }
            NEXT_Linked(p) = NEXT_Linked(q);
            NEXT_Linked(q) = p;
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst_Linked(List *l, ElType_Linked *val)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info_Linked disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
{
    Address_Linked p = *l;

    *val = INFO_Linked(p);
    if (NEXT_Linked(p) == NULL)
    {
        *l = NULL;
        free(*l);
        CreateListLinked(l);
    }
    else
    {
        *l = NEXT_Linked(p);
        free(p);
    }
}

void deleteLastLinked(List *l, ElType_Linked *val)
{
    /* I.S. list tidak kosong */
    /* F.S. Elemen terakhir list dihapus: nilai info_Linked disimpan pada x */
    /*      dan alamat elemen terakhir di-dealokasi */
    // KAMUS LOKAL
    Address_Linked p, q;

    // ALGORITMA
    if (NEXT_Linked(*l) == NULL)
    {
        deleteFirst_Linked(l, val);
    }
    else
    {
        p = *l;
        q = NULL;
        while (NEXT_Linked(p) != NULL)
        {
            q = p;
            p = NEXT_Linked(p);
        }
        if (q == NULL)
        {
            *l = NULL;
        }
        else
        {
            NEXT_Linked(q) = NULL;
        }
        *val = INFO_Linked(p);
        free(p);
    }
}

void deleteAtLinked(List *l, int idx, ElType_Linked *val)
{
    /* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..lengthLinked(l) */
    /* F.S. val diset dengan elemen l pada indeks ke-idx. */
    /*      Elemen l pada indeks ke-idx dihapus dari l */
    // KAMUS LOKAL
    Address_Linked p, q;
    int i = 0;

    // ALGORITMA
    if (NEXT_Linked(*l) == NULL)
    {
        deleteFirst_Linked(l, val);
    }
    else
    {
        if (idx == 0)
        {
            deleteFirst_Linked(l, val);
        }
        else
        {
            p = *l;
            while (i < idx)
            {
                q = p;
                p = NEXT_Linked(p);
                i++;
            }
            *val = INFO_Linked(p);
            NEXT_Linked(q) = NEXT_Linked(p);
            NEXT_Linked(p) = NULL;
            free(p);
        }
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayListLinked(List l)
{
    // void printInfo_Linked(List l);
    /* I.S. List mungkin kosong */
    /* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika list kosong : menulis [] */
    /* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
    // KAMUS LOKAL
    Address_Linked p;

    // ALGORITMA
    p = l;

    printf("[");

    if (!isEmptyLinked(l))
    {
        while (NEXT_Linked(p) != NULL)
        {
            printf("%d,", INFO_Linked(p));
            p = NEXT_Linked(p);
        }
        printf("%d", INFO_Linked(p));
    }

    printf("]");
}

int lengthLinked(List l)
{
    /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    // KAMUS LOKAL
    int count = 0;
    Address_Linked p;

    // ALGORITMA
    p = l;
    if (isEmptyLinked(l))
    {
        return count;
    }
    else
    {
        count = 1;
        while (NEXT_Linked(p) != NULL)
        {
            p = NEXT_Linked(p);
            count++;
        }
        return count;
    }
}

/****************** PROSES TERHADAP LIST ******************/
List concatLinked(List l1, List l2)
{
    /* I.S. l1 dan l2 sembarang */
    /* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
    /* Konkatenasi dua buah list : l1 dan l2    */
    /* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
    /* Tidak ada alokasi/dealokasi pada prosedur ini */
    // KAMUS LOKAL
    Address_Linked p;
    List l3;
    ElType_Linked val;

    CreateListLinked(&l3);
    p = l1;
    while (p != NULL)
    {
        insertLastLinked(&l3, INFO_Linked(p));
        p = NEXT_Linked(p);
    }
    p = l2;
    while (p != NULL)
    {
        insertLastLinked(&l3, INFO_Linked(p));
        p = NEXT_Linked(p);
    }

    return l3;
}

#endif