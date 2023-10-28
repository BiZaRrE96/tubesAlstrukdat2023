#ifndef _KICAU_H_
#define _KICAU_H_

//ADT kicau(?)
#include <time.h>

#include "../boolean/boolean.h"
#include "../userlist/userlist.h"
#include "../sentencemachine/sentencemachine.h"
//#include "../time/time.h"

//Suatu kicauan minimal terdiri dari 
/*id
text (isi kicauan)
like (jumlah like)
author (pembuat kicauan)
datetime (waktu kicauan).
*/

typedef int id;

//extern int globalKicauCount;

typedef struct {
    //id KicauID; tidak perlu, cukup lihat index kicau list + 1
    Word Text;
    int Like;
    id Author;
    struct tm Time;
} KICAU;

typedef struct {
    int KicauCount; //jumlah kicau
    int capacity; //>= 0
    KICAU *Kicau; // memori penyimpanan kicau
} KicauList;

/* ***** SELEKTOR KICAU ***** */

/* ***** SELEKTOR KicauList ***** */
#define CAPACITY(KL) (KL).capacity
#define Count(KL) (KL).KicauCount
#define GetKicauan(KL,i) (KL).Kicau[i]
#define Buffer(KL) (KL).Kicau

#define GetText(KL,i) (KL).Kicau[i].Text
#define GetLike(KL,i) (KL).Kicau[i].Like
#define GetAuthor(KL,i) (KL).Kicau[i].Author
#define GetTime(KL,i) (KL).Kicau[i].Time

/* ****** TEMPORARY FUNCTIONS, SUBJECT TO CHANGE WITH UPDATES*/
void setToCurrentTime(struct tm * t){
    time_t currentTime;

    time(&currentTime);
    t = localtime(&currentTime);

};

void createKicauList (KicauList* KL, int cap){
    
    Buffer(*KL) = (KICAU*) malloc (cap * sizeof(KICAU));
    
    if(Buffer(*KL) != NULL){
        CAPACITY(*KL) = cap;
        Count(*KL) = 0;
    }
    else{
        CAPACITY(*KL) = 0;
        printf("ALOKASI KICAULIST GAGAL!\n");
    }

}
/*
    I.S. : Sembarang
    F.S. : KicauList terdefinisi dengan capacity cap
            atau gagal terdefinisi dengan cap  = 0
*/

void Kicau(KicauList *KL, id author){
    printf("Masukkan kicauan: ");

    int i = Count(*KL);
    StartSentence();
    GetText(*KL,i) = SentenceToWord();
    GetLike(*KL,i) = 0;
    GetAuthor(*KL,i) = author;
    setToCurrentTime(&GetTime(*KL,i));
    Count(*KL)++;
}

/* ***** MENGUBAH UKURAN ARRAY ***** */

void expandList(KicauList *kl, int num);
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

void shrinkList(KicauList *kl, int num);
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */

#endif