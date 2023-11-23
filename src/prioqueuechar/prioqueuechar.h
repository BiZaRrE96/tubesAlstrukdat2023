#ifndef prioqueue_H
#define prioqueue_H

#include "../boolean/boolean.h"

#define Nil -1

typedef struct
{
    int IDrecieve;
    int Friendcount;
} friend;

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

boolean IsEmptyPrioQueue (prioqueue Q)
{
    return (HeadQ(Q) == Nil && TailQ(Q) == Nil);
}

boolean IsFullPrioQueue (prioqueue Q)
{
    return (PrioQueueLength(Q) == MaxElQ(Q));

}
int PrioQueueLength (prioqueue Q)
{
    if (IsEmptyPrioQueue(Q))
    {
        return 0;
    } else 
    {
        if ((TailQ(Q) - HeadQ(Q)) >= 0)
        {
            return TailQ(Q) - HeadQ(Q) + 1;
        } else 
        {
            return MaxElQ(Q) - (HeadQ(Q) - (TailQ(Q) + 1));
        }
    }
}

void MakeEmptyPrioQueue (prioqueue* Q, int Max)
{
    (*Q).T = (friend *) malloc((Max) * sizeof(friend));
    if ((*Q).T == NULL) 
    {
        MaxElQ(*Q) = 0;
    } else 
    {
        HeadQ(*Q) = Nil;
        TailQ(*Q) = Nil;
        MaxElQ(*Q) = Max;
    }
}

void DeAlokasiPrioQueue (prioqueue* Q)
{
    HeadQ(*Q) = Nil;
    TailQ(*Q) = Nil;
    MaxElQ(*Q) = 0;
    free((*Q).T);
}

void EnqueuePrioQueue (prioqueue* Q, friend t)
{
    boolean found;
    int idx;
    int i, j;
    friend temp;

    if (IsEmptyPrioQueue(*Q))
    {
        HeadQ(*Q) = 0;
        TailQ(*Q) = 0;
        InfoHeadQ(*Q) = t;
    } else if (IsFullPrioQueue(*Q))
    {
        printf("Queue is full\n");
    } else 
    {
        TailQ(*Q) = TailQ(*Q) == MaxElQ(*Q) - 1 ? 0 : TailQ(*Q) + 1;
        InfoTailQ(*Q) = t;
        i = TailQ(*Q);
        j = (i == 0) ? MaxElQ(*Q) - 1 : i - 1;
        while (i != HeadQ(*Q) && ElmtQ(*Q, i).Friendcount > ElmtQ(*Q, j).Friendcount)
        {
            temp = ElmtQ(*Q, i);
            ElmtQ(*Q, i) = ElmtQ(*Q, j);
            ElmtQ(*Q, j) = temp;
            i = j;
            j = (i == 0) ? MaxElQ(*Q) - 1 : i - 1;
        }
    }
}

void DequeuePrioQueue (prioqueue* Q, friend* t)
{
    if (PrioQueueLength(*Q) == 1) 
    {
        *t = InfoHeadQ(*Q);
        HeadQ(*Q) = Nil;
        TailQ(*Q) = Nil;
    } else 
    {
        *t = InfoHeadQ(*Q);
        HeadQ(*Q) = (HeadQ(*Q) == MaxElQ(*Q) - 1) ? 0 : HeadQ(*Q) + 1;
    }   
}

void EnqueueUserPrioQueue (prioqueue Q, int IDuser, prioqueue* Quser, prioqueue *Qsisa)
{
    friend temp;
    MakeEmptyPrioQueue(Quser, 20);
    MakeEmptyPrioQueue(Qsisa, 100);
    while(!IsEmptyPrioQueue(Q))
    {
        DequeuePrioQueue(&Q, &temp);
        if(temp.IDrecieve == IDuser)
        {
            EnqueuePrioQueue(Quser,temp);
        } else
        {
            EnqueuePrioQueue(Qsisa, temp);
        }
    }    
}

void ConcatenationPrioQueue (prioqueue Quser, prioqueue Qsisa, prioqueue* Q)
{
    while (!IsEmptyPrioQueue(Quser))
    {
        friend temp;
        DequeuePrioQueue(&Quser, &temp);
        EnqueuePrioQueue(Q, temp);
    }
    while (!IsEmptyPrioQueue(Qsisa))
    {
        friend temp;
        DequeuePrioQueue(&Qsisa, &temp);
        EnqueuePrioQueue(Q, temp);
    }
}

boolean isHaveSentRequest(prioqueue Q, int IDuser)
{
    boolean found = false;
    int i = HeadQ(Q);
    while (i != TailQ(Q) && !found)
    {
        if (ElmtQ(Q, i).IDrecieve == IDuser)
        {
            found = true;
        } else 
        {
            i = (i == MaxElQ(Q) - 1) ? 0 : i + 1;
        }
    }
    return found;
}

#endif