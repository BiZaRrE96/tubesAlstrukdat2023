#include <stdio.h>
#include <stdlib.h>

#include "prioqueuechar.h"
#include "friendship.h"

boolean IsEmptyPrioQueue (prioqueue Q)
{
    return (HeadQ(Q) == Nil && TailQ(Q) == Nil);
}

boolean IsFullPrioQueue (prioqueue Q)
{
    return (MaxElQ(Q) == NBElmtPrio(Q));
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

void tambahteman (boolean isLogin, User akunlogin, UserList* listakun, friend Teman, prioqueue* Q) {
    UserList listpengguna;
    Friendship friendship;
    if (!isLogin) 
    {
        printf("Anda belum login !\n");
        printf("Silahkan Login terlebih dahulu sebelum menggunakan fungsi ini.\n");
    } else if (!IsEmptyPrioQueue(*Q))
    {
        printf("Terdapat permintaan pertemanan yang belum Anda setujui. Silakan kosongkan daftar permintaan pertemanan untuk Anda terlebih dahulu.");
    } else 
    {
        printf("Masukan nama pengguna :\n");
        STARTWORD();
        Word namaTeman = currentWord;
        int i = indexOfUser(listpengguna, akunlogin.username);
        int k = indexOfUser(listpengguna, currentWord);
        if (isWordEqual(namaTeman,ElmtUsername(listpengguna,i))) {
            printf("Anda tidak bisa berteman dengan diri anda sendiri.\n");
        } else if (FriendshipStatus(friendship, i, k) == 1) 
        {
            printf("Kalian sudah berteman.");
        } else if (Q->T->IDrecieve == k) 
        {
            printf("Permintaan pertemanan sudah pernah dilakukan, tunggu hingga permintaan Anda disetujui.\n");
        } else 
        {
            boolean found = false;
            for (int j = 0;j < FRIENDSHIPCAPACITY;j++) {
                if (isWordEqual(namaTeman,ElmtUsername(listpengguna,j))) {
                    printf("Permintaan pertemanan kepada");
                    printf("%s ", namaTeman);
                    printf("telah dikirim. Tunggu beberapa saat hingga permintaan Anda disetujui.\n");
                    EnqueuePrioQueue(&Q, Teman);
                    found = true;
                } else
                {
                    found = false;
                }
            }
            if (!found) {
                printf("Pengguna bernama ");
                printf("%s ", namaTeman);
                printf("tidak ditemukan.\n");
            }
        }
    }
}

void daftarpermintaanteman (boolean islogin, User akunlogin, UserList* listakun, prioqueue* Q) {
    UserList listpengguna;
    prioqueue qteman, qpending;
    if (!islogin) 
    {
        printf("Anda belum login !\n");
        printf("Silahkan Login terlebih dahulu sebelum menggunakan fungsi ini.\n");
    } else 
    {
        int userID = indexOfUser(listpengguna, akunlogin.username);
        Enqueueuserprio(*Q, userID, &qteman, &qpending);
        PrintPrioQueue(qteman, listakun);
        concatenationprio(qteman, qpending, Q);
    }
}

void setujuipermintaanteman (boolean islogin, User akunlogin, UserList* listakun, friend* Teman, prioqueue* Q) {
    prioqueue qteman, qpending;
    UserList listpengguna;
    Friendship friendship;
    if (!islogin) 
    {
        printf("Anda belum login !\n");
        printf("Silahkan Login terlebih dahulu sebelum menggunakan fungsi ini.\n");
    } else 
    {
        int userID = indexOfUser(listpengguna, akunlogin.username);
        int friendID;
        Word namaTeman;
        EnqueueUserPrioQueue(*Q, userID, &qteman, &qpending);
        printf("%s\n", namaTeman);
        printf("Apakah anda ingin menyetujui permintaan pertemanan ini ? (ya/tidak)\n");
        STARTWORD();
        if (IsWordEqual(currentWord, 'tidak')) 
        {
            DequeuePrioQueue(&qpending, &Teman);
            printf("Berhasil menolak permintaan pertemanan dari ");
            printf("%s.\n", namaTeman);
        } else if (IsWordEqual(currentWord, 'ya')) 
        {
            DequeuePrioQueue(&qpending, &Teman);
            FriendshipStatus(friendship, userID, friendID) = 1;
            FriendshipStatus(friendship, friendID, userID) = 1;
            printf("%s ", namaTeman);
            printf("telah menjadi temanmu.\n");
        } else
        {
            printf("Command tidak sesuai.\n");
        }
    }
}