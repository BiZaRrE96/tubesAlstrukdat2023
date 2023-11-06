/* File : prioqueuechar.h */
/* Definisi ADT Priority Queue Char dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */
/* Elemen queue terurut membesar berdasarkan elemen prio */

#ifndef prioqueuechar_H
#define prioqueuechar_H

#include "../src/boolean/boolean.h"
#include "../src/graf/graf.h"
#include "../src/wordmachine/wordmachine.h"


#define Nil -1
/* Konstanta untuk mendefinisikan address tak terdefinisi */

/* Definisi elemen dan address */
typedef struct {
    int prio;
    Word info;  /* elemen karakter */
} infotype_PQueue;
typedef int address;   /* indeks tabel */
/* Contoh deklarasi variabel bertype PrioQueueChar : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct {
    infotype_PQueue * T;   /* tabel penyimpan elemen */
    address HEAD;  /* alamat penghapusan */
    address TAIL;  /* alamat penambahan */
    int MaxEl;     /* Max elemen queue */
} PrioQueueChar;
/* Definisi PrioQueueChar kosong: HEAD=Nil; TAIL=Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika e adalah infotype dan Q adalah PrioQueueChar, maka akses elemen : */
#define Prio_PQueue(e)     (e).prio
#define Info_PQueue(e)     (e).info
#define Head_PQueue(Q)     (Q).HEAD
#define Tail_PQueue(Q)     (Q).TAIL
#define InfoHead_PQueue(Q) (Q).T[(Q).HEAD]
#define InfoTail_PQueue(Q) (Q).T[(Q).TAIL]
#define MaxEl_PQueue(Q)    (Q).MaxEl
#define Elmt_PQueue(Q,i)   (Q).T[(i)]

/* ********* Prototype ********* */
boolean IsEmpty_PQueue (PrioQueueChar Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFull_PQueue (PrioQueueChar Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NBElmt_PQueue (PrioQueueChar Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void MakeEmpty_PQueue (PrioQueueChar * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi_PQueue (PrioQueueChar * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void Enqueue_PQueue (PrioQueueChar * Q, infotype_PQueue X);
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut membesar berdasarkan prio */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */
void Dequeue_PQueue (PrioQueueChar * Q, infotype_PQueue * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */

/* Operasi Tambahan */
void PrintPrioQueueChar_PQueue (PrioQueueChar Q);
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<prio-1> <elemen-1>
...
<prio-n> <elemen-n>
#
*/

#endif