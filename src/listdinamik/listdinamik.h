// NAMA PEMBUAT : Christian Justin Hendrawan
// NIM : 13522135
// TOPIK : ADT LIST DINAMIK

/* MODUL INTEGER DYNAMIC LIST */
/* Berisi definisi dan semua primitif pemrosesan list integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori list dinamik */
#ifndef LISTDIN_H
#define LISTDIN_H

#include "../boolean/boolean.h"
#include <stdio.h>
#include <stdlib.h>

/*  Kamus Umum */
#define IDX_MIN_LIST_DINAMIK 0
/* Indeks minimum list */
#define IDX_UNDEF_LIST_DINAMIK -1
/* Indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef int DinElType; /* type elemen list */
typedef int IdxType_ListDin;
typedef struct
{
    DinElType *buffer_DINAMIS; /* memori tempat penyimpan elemen (container) */
    int nEff_DINAMIS;       /* >=0, banyaknya elemen efektif */
    int LISTDIN_CAPACITY;   /* ukuran elemen */
} ListDin;
/* Indeks yang digunakan [0..LISTDIN_CAPACITY-1] */
/* Jika l adalah : ListDin, cara deklarasi dan akses: */
/* Deklarasi : l : ListDin */
/* Maka cara akses:
   l.nEff_DINAMIS      untuk mengetahui banyaknya elemen
   l.buffer_DINAMIS    untuk mengakses seluruh nilai elemen list
   l.buffer_DINAMIS[i] untuk mengakses elemen ke-i */
/* Definisi :
  list kosong: l.nEff_DINAMIS = 0
  Definisi elemen pertama : l.buffer_DINAMIS[i] dengan i=0
  Definisi elemen terakhir yang terdefinisi: l.buffer_DINAMIS[i] dengan i=l.LISTDIN_CAPACITY */

/* ********** SELEKTOR ********** */
#define NEFF_DINAMIS(l) (l).nEff_DINAMIS
#define BUFFER_DINAMIS(l) (l).buffer_DINAMIS
#define ELMT_LIST_DINAMIS(l, i) (l).buffer_DINAMIS[i]
#define LISTDIN_CAPACITY(l) (l).LISTDIN_CAPACITY

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int LISTDIN_CAPACITY)
/* I.S. l sembarang, LISTDIN_CAPACITY > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas LISTDIN_CAPACITY */
{
    BUFFER_DINAMIS(*l) = (DinElType *)malloc(LISTDIN_CAPACITY * sizeof(DinElType));
    NEFF_DINAMIS(*l) = 0;
    LISTDIN_CAPACITY(*l) = LISTDIN_CAPACITY;
}

void dealocateListDin(ListDin *l)
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, LISTDIN_CAPACITY(l)=0; NEFF_DINAMIS(l)=0 */
{
    NEFF_DINAMIS(*l) = 0;
    LISTDIN_CAPACITY(*l) = 0;
    free(BUFFER_DINAMIS(*l));
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLengthDin(ListDin l)
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
/* *** Daya tampung container *** */
{
    return (NEFF_DINAMIS(l));
}

/* *** Selektor INDEKS *** */
IdxType_ListDin getFirstIdxDin(ListDin l)
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
{
    return IDX_MIN_LIST_DINAMIK;
}
IdxType_ListDin getLastIdxDin(ListDin l)
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
{
    return (listLengthDin(l) - 1);
}
/* ********** Test Indeks yang valid ********** */
boolean isIdxValidDin(ListDin l, IdxType_ListDin i)
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return (i >= IDX_MIN_LIST_DINAMIK && i <= LISTDIN_CAPACITY(l));
}
boolean isIdxEffDin(ListDin l, IdxType_ListDin i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF_DINAMIS(l) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
{
    return (i >= 0 && i < NEFF_DINAMIS(l));
}
boolean isEmptyDin(ListDin l)
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
/* *** Test list penuh *** */
{
    return (NEFF_DINAMIS(l) == 0);
}
boolean isFullDin(ListDin l)
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
{
    return (NEFF_DINAMIS(l) == LISTDIN_CAPACITY(l));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readListDin(ListDin *l)
/* I.S. l sembarang dan sudah dialokasikan sebelumnya */
/* F.S. List l terdefinisi */
/* Proses : membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= LISTDIN_CAPACITY(l) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= LISTDIN_CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
      0 satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk l kosong */
{
    int n, i;
    scanf("%d", &n);
    while (n < 0 || n > LISTDIN_CAPACITY(*l))
    {
        scanf("%d\n", &n);
    }

    NEFF_DINAMIS(*l) = n;

    if (n > 0)
    {
        for (i = 0; i <= n - 1; i++)
        {
            scanf("%d", &ELMT_LIST_DINAMIS(*l, i));
        }
    }
}
void printListDin(ListDin l)
/* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
{
    int i;

    printf("[");

    if (NEFF_DINAMIS(l) > 0)
    {
        for (i = 0; i <= NEFF_DINAMIS(l) - 1; i++)
        {
            printf("%d", ELMT_LIST_DINAMIS(l, i));
            if (i != NEFF_DINAMIS(l) - 1)
            {
                printf(",");
            }
        }
    }
    printf("]");
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
ListDin plusMinusListDin(ListDin l1, ListDin l2, boolean plus)
/* Prekondisi : l1 dan l2 memiliki Neff_DINAMIS sama dan tidak kosong */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */
{
    int i;
    ListDin Hasil;
    CreateListDin(&Hasil, LISTDIN_CAPACITY(l1));
    NEFF_DINAMIS(Hasil) = NEFF_DINAMIS(l1);
    if (plus == true)
    {
        for (i = 0; i <= NEFF_DINAMIS(l1) - 1; i++)
        {
            ELMT_LIST_DINAMIS(Hasil, i) = ELMT_LIST_DINAMIS(l1, i) + ELMT_LIST_DINAMIS(l2, i);
        }
    }
    else
    {
        for (i = 0; i <= NEFF_DINAMIS(l1) - 1; i++)
        {
            ELMT_LIST_DINAMIS(Hasil, i) = ELMT_LIST_DINAMIS(l1, i) - ELMT_LIST_DINAMIS(l2, i);
        }
    }
    return Hasil;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListEqualDin(ListDin l1, ListDin l2)
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff_DINAMIS l1 = l2 dan semua elemennya sama */
{
    boolean sama = true;
    int i = 0;
    if (NEFF_DINAMIS(l1) == NEFF_DINAMIS(l2))
    {
        while (sama == true && i <= NEFF_DINAMIS(l1) - 1)
        {
            if (ELMT_LIST_DINAMIS(l1, i) != ELMT_LIST_DINAMIS(l2, i))
            {
                sama = false;
            }
            i++;
        }
    }
    else
    {
        sama = false;
    }
    return sama;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType_ListDin indexOfDin(ListDin l, DinElType val)
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan IDX_UNDEF_LIST_DINAMIK */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF_LIST_DINAMIK) jika List l kosong */
/* Skema Searching yang digunakan bebas */
{
    boolean found = false;
    int index = IDX_UNDEF_LIST_DINAMIK;
    int i = 0;
    if (NEFF_DINAMIS(l) > 0)
    {
        while (found != true && i <= NEFF_DINAMIS(l) - 1)
        {
            if (ELMT_LIST_DINAMIS(l, i) == val)
            {
                found = true;
                index = i;
            }
            i++;
        }
    }
    return index;
}

/* ********** NILAI EKSTREM ********** */
void extremeValuesDin(ListDin l, DinElType *max, DinElType *min)
/* I.S. List l tidak kosong */
/* F.S. max berisi nilai maksimum l;
        min berisi nilai minimum l */
{
    int maximum, minimum, i;
    maximum = ELMT_LIST_DINAMIS(l, 0);
    minimum = ELMT_LIST_DINAMIS(l, 0);

    for (i = 0; i <= NEFF_DINAMIS(l) - 1; i++)
    {
        if (ELMT_LIST_DINAMIS(l, i) > maximum)
        {
            maximum = ELMT_LIST_DINAMIS(l, i);
        }
        if (ELMT_LIST_DINAMIS(l, i) < minimum)
        {
            minimum = ELMT_LIST_DINAMIS(l, i);
        }
    }
    *max = maximum;
    *min = minimum;
}

/* ********** OPERASI LAIN ********** */
void copyListDin(ListDin lIn, ListDin *lOut)
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff_DINAMIS dan LISTDIN_CAPACITY sama) */
/* Proses : Menyalin isi lIn ke lOut */
{
    int i;
    CreateListDin(lOut, LISTDIN_CAPACITY(lIn));

    for (i = 0; i <= NEFF_DINAMIS(lIn) - 1; i++)
    {
        ELMT_LIST_DINAMIS(*lOut, i) = ELMT_LIST_DINAMIS(lIn, i);
    }
    NEFF_DINAMIS(*lOut) = NEFF_DINAMIS(lIn);
}

DinElType sumListDin(ListDin l)
/* Menghasilkan hasil penjumlahan semua elemen l */
/* Jika l kosong menghasilkan 0 */
{
    int sum = 0;
    int i;

    for (i = 0; i <= NEFF_DINAMIS(l) - 1; i++)
    {
        sum += ELMT_LIST_DINAMIS(l, i);
    }
    return sum;
}
int countValDin(ListDin l, DinElType val)
/* Menghasilkan berapa banyak kemunculan val di l */
/* Jika l kosong menghasilkan 0 */
{
    int counter = 0;
    int i;

    for (i = 0; i <= NEFF_DINAMIS(l) - 1; i++)
    {
        if (ELMT_LIST_DINAMIS(l, i) == val)
        {
            counter += 1;
        }
    }
    return counter;
}

/* ********** SORTING ********** */
void sortDin(ListDin *l, boolean asc)
{
    /* I.S. l boleh kosong */
    /* F.S. Jika asc = true, l terurut membesar */
    /*      Jika asc = false, l terurut mengecil */
    /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
       algoritma bebas */
    int i,
        j;
    DinElType temp;
    IdxType_ListDin idx;
    if (asc == true)
    {
        for (i = 1; i < NEFF_DINAMIS(*l); i++)
        {
            temp = ELMT_LIST_DINAMIS(*l, i);
            idx = i - 1;
            while ((temp < ELMT_LIST_DINAMIS(*l, idx)) && (idx > 0))
            {
                ELMT_LIST_DINAMIS(*l, idx + 1) = ELMT_LIST_DINAMIS(*l, idx);
                idx--;
            }
            if (temp >= ELMT_LIST_DINAMIS(*l, idx))
            {
                ELMT_LIST_DINAMIS(*l, idx + 1) = temp;
            }
            else
            {
                ELMT_LIST_DINAMIS(*l, idx + 1) = ELMT_LIST_DINAMIS(*l, idx);
                ELMT_LIST_DINAMIS(*l, idx) = temp;
            }
        }
    }
    else
    {
        for (i = 1; i < NEFF_DINAMIS(*l); i++)
        {
            temp = ELMT_LIST_DINAMIS(*l, i);
            idx = i - 1;
            while ((temp > ELMT_LIST_DINAMIS(*l, idx)) && (idx > 0))
            {
                ELMT_LIST_DINAMIS(*l, idx + 1) = ELMT_LIST_DINAMIS(*l, idx);
                idx--;
            }
            if (temp <= ELMT_LIST_DINAMIS(*l, idx))
            {
                ELMT_LIST_DINAMIS(*l, idx + 1) = temp;
            }
            else
            {
                ELMT_LIST_DINAMIS(*l, idx + 1) = ELMT_LIST_DINAMIS(*l, idx);
                ELMT_LIST_DINAMIS(*l, idx) = temp;
            }
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLastDin(ListDin *l, DinElType val)
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
/* ********** MENGHAPUS ELEMEN ********** */
{
    if (isFullDin(*l) != true)
    {
        ELMT_LIST_DINAMIS(*l, NEFF_DINAMIS(*l)) = val;
        NEFF_DINAMIS(*l)
        ++;
    }
}

void deleteLastDin(ListDin *l, DinElType *val)
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
{
    if (isEmptyDin(*l) != true)
    {
        *val = ELMT_LIST_DINAMIS(*l, getLastIdxDin(*l));
        NEFF_DINAMIS(*l)
        --;
    }
}



#endif