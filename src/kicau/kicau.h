#ifndef _KICAU_H_
#define _KICAU_H_

//ADT kicau(?)
//MENGGUNAKAN : ADT LST DINAMIK
#include "../boolean/boolean.h"
#include "../userlist/userlist.h"
#include "../sentencemachine/sentencemachine.h"
#include "../commandmachine/commandmachine.h"
#include "../datetime/datetime.h"
#include "balas.h"
#include "../friendship/friendship.h"
#include "../user/user.h"
//#include "../time/time.h"

extern UserList users;

typedef int id;

//extern int globalKicauCount;

typedef struct {
    //id KicauID; tidak perlu, cukup lihat index kicau list + 1
    Word Text;
    int Like;
    Word Author;
    DATETIME Time;
    BalasanList BL;

    //membantu memberi spasi sebelum tulisan
} KICAU;

typedef struct {
    int KicauCount; //jumlah kicau
    int capacity; //>= 0
    KICAU *Kicau; // memori penyimpanan kicau
} KicauList;

/* ***** SELEKTOR KICAU ***** */
#define GetText(KL,i) (KL).Kicau[i].Text
#define GetLike(KL,i) (KL).Kicau[i].Like
#define GetAuthor(KL,i) (KL).Kicau[i].Author
#define GetTime(KL,i) (KL).Kicau[i].Time

/* ***** SELEKTOR KicauList ***** */
#define CAPACITYKICAU(KL) (KL).capacity
#define Count(KL) (KL).KicauCount
#define GetKicauan(KL,i) (KL).Kicau[i]
#define Buffer(KL) (KL).Kicau

//#define GetParent(K) (K).parent

//extern variable diluar kicau yang konsisten


/* ****** TEMPORARY FUNCTIONS, SUBJECT TO CHANGE WITH UPDATES*/


/* UNUSED< DEFINED IN BALAS
//akan digunakan untuk nanti balasan
void printSpaces(int x){
    for (int i = 0; i < x; i++){
        printf(" ");
    }
};
*/

/* ***** MAIN FUNCTIONS ***** */
boolean isIdxKicauValid(KicauList KL, id i){
    return ((i > 0) && (i <= Count(KL)));
};


void createKicauList (KicauList* KL, int cap){
    Buffer(*KL) = (KICAU*) malloc (cap * sizeof(KICAU));
    if(Buffer(*KL) != NULL){
        CAPACITYKICAU(*KL) = cap;
        Count(*KL) = 0;
    }
    else{
        CAPACITYKICAU(*KL) = 0;
        printf("ALOKASI KICAULIST GAGAL!\n");
    }
}
/*
    I.S. : Sembarang
    F.S. : KicauList terdefinisi dengan capacity cap
            atau gagal terdefinisi dengan cap  = 0
*/

boolean isBlank(Word word){
    int i = word.Length;
    int j = 0;
    boolean retval = true;
    while(j < i && retval){
        if(word.TabWord[j] != ' '){
            retval = false;
        }
        j++;
    }

    return retval;

};

/* ***** MENGUBAH UKURAN ARRAY ***** */


void copyList(KicauList host, KicauList *target){
    //max
    if (CAPACITYKICAU(*target) > Count(host)){ //if a can contain all kicau
        Count(*target) = Count(host);
    }
    else{
        Count(*target) = CAPACITYKICAU(*target);
    }

    for (int i = 0; i < Count(*target); i++){
        target->Kicau[i].Author = host.Kicau[i].Author;
        target->Kicau[i].Like = host.Kicau[i].Like;
        target->Kicau[i].Text = host.Kicau[i].Text;
        target->Kicau[i].Time = host.Kicau[i].Time;
    }
};
/* Proses : Menyalin semua isi host ke target */
/* I.S. List sudah terdefinisi */
/* F.S. isi host tercopy ke target semua atau sampai penuh */

void expandList(KicauList *kl, int num){
    KicauList newKl;
    int newcap = num + CAPACITYKICAU(*kl);
    createKicauList(&newKl,CAPACITYKICAU(*kl));
    copyList(*kl,&newKl);
    free(kl->Kicau);
    createKicauList(kl,newcap);
    copyList(newKl,kl);
};
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

void shrinkList(KicauList *kl, int num){
    KicauList newKl;
    int newcap = CAPACITYKICAU(*kl) - num;
    createKicauList(&newKl,CAPACITYKICAU(*kl));
    copyList(*kl,&newKl);
    free(kl->Kicau);
    createKicauList(kl,newcap);
    copyList(newKl,kl);
}
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */

//void compressList(KicauList *kl);

/* ***** MAIN KICAU FUNCTIONS ***** */



//view kicauan with id X (real id from 1) as user with id user
void printKicauXasA(KicauList KL, id x, Word user){
    if (AcanSeeB(user,GetAuthor(KL,x)) == true){
        printf("| ID = %d\n",x);
        printf("| %s \n",wordToStr(GetAuthor(KL,x)));
        printf("| ");
        TulisDATETIME(GetTime(KL,x));
        printf("\n");
        printf("| %s\n",wordToStr(GetText(KL,x)));
        printf("| Disukai: %d\n",GetLike(KL,x));
    }
    else{
        printf("OMMITED/PRIVATE\n");
    }
    //printBalasan
};

void Kicau(KicauList *KL, Word author){
    printf("Masukkan kicauan: ");
    STARTCOMMAND();
    Word input = currentWord;

    if (!isBlank(input)){
        Count(*KL)++;
        int i = Count(*KL);
        GetText(*KL,i) = input;
        GetLike(*KL,i) = 0;
        GetAuthor(*KL,i) = author;
        setToCurrentTime(&GetTime(*KL,i));
        

        printf("Selamat! kicauan telah diterbitkan!\nDetil kicauan:\n");
        printKicauXasA(*KL, (i), author);
        printf("\n");
    }
    else{
        printf("Kicauan tidak boleh hanya berisi spasi!\n");
    }

}

void viewRecentAsA(KicauList KL,Word A){
    printf("\n");
    for (int i = Count(KL); i > 0; i--){
        printKicauXasA(KL, i, A);
        printf("\n");
    }
    printf("\n");
}

void likeKicau(KicauList *KL,id postID, Word user){
    // Cek dahulu apakah postID valid
    id userId = indexOfUser(users, user);

    printf("\n");
    if (!isIdxKicauValid(*KL,postID)){
        printf("Tidak dapat ditemukan dengan ID = %d\n\n",postID);
        return;
    }

    id author = indexOfUser(users, GetAuthor(*KL,postID));
    // Cek dahulu apakah author dari kicau privat dan tidak berteman
    if (ElmtPrivacy(users, author) == PRIVATE && !FriendshipStatus(friendship, author, userId)) {
        printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya\n\n");
    }

    GetLike(*KL,postID)++;

    printf("Selamat! kicauan telah disukai!\nDetil kicauan:\n");
    printKicauXasA(*KL, postID, user);
    printf("\n");
    
    
}


/*Balas utilities*//*
void balasBasA(id user, KicauList KL, id IDKicauan, id IDBalas){
    if (getBalasan());
}
*/
#endif