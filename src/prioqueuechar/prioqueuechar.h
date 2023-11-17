#ifndef prioqueue_H
#define prioqueue_H

#include "../src/boolean/boolean.h"
#include "../src/friendship/friendship.h"

#define Nil -1

typedef struct
{
    int IDsend;
    int IDrecieve;
    int Friendcount;
}friend;

typedef int addressPrioqueue;

typedef struct 
{
    friend *T;
    addressPrioqueue HEADQ;
    addressPrioqueue TAILQ;
    int MaxElQ;
}prioqueue;

#define HeadQ(Q)     (Q).HEADQ
#define TailQ(Q)     (Q).TAILQ
#define InfoHeadQ(Q) (Q).T[(Q).HEADQ]
#define InfoTailQ(Q) (Q).T[(Q).TAILQ]
#define MaxElQ(Q)    (Q).MaxElQ
#define ElmtQ(Q,i)   (Q).T[(i)]

boolean IsEmptyPrioQueue (prioqueue Q);

boolean IsFullPrioQueue (prioqueue Q);

int PrioQueueLength (prioqueue Q);

void MakeEmptyPrioQueue (prioqueue* Q, int Max);

void DeAlokasiPrioQueue (prioqueue* Q);

void EnqueuePrioQueue (prioqueue* Q, friend t);

void DequeuePrioQueue (prioqueue* Q, friend* t);

void EnqueueUserPrioQueue (prioqueue Q, int IDuser,prioqueue* Quser, prioqueue *Qsisa);

void ConcatenationPrioQueue (prioqueue Quser, prioqueue Qsisa, prioqueue *Q);

void tambahteman (boolean isLogin, User akunlogin, UserList* listakun, friend Teman, prioqueue* Q);

void daftarpermintaanteman (boolean islogin, User akunlogin, UserList* listakun, prioqueue* Q);

 

#endif