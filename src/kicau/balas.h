#ifndef _BALAS_H_
#define _BALAS_H_

#include "../boolean/boolean.h"
#include "../userlist/userlist.h"
#include "../sentencemachine/sentencemachine.h"
#include "../commandmachine/commandmachine.h"
#include "../datetime/datetime.h"

//DATA TYPE USED : ADT Tree dengan struktur data berkait
//Kenapa Tree? biar kalau delete cascading
//Kenapa struktur data berkait? tidak perlu alokasi banyak2
// belum tentu suatu kicau ada balasan

typedef int id;

typedef struct BALASAN* Address;

typedef struct BALASAN{
    Word Text;
    id Author;
    DATETIME Time;
    int indexLevel;
    id IdBalas;
    Address Next;
    Address Prev;
    id parentID;
} BALASAN;

typedef struct {
    BALASAN* First;
    BALASAN* Last;
    int countEvo;
    int realCount;
} BalasanList;

/* ***** SELEKTOR BALASAN ***** */
#define BalasanText(b) (b).Text
#define BalasanAuthor(b) (b).Author
#define BalasanTime(b) (b).Time
#define IDX_UNDEF -999
// bruh moment

/*TEMPORARY FUNCTION*/
static boolean balasAcanSeeB(id A, id B){
    //returns true if :
    // B is a public account
    // B is a private account and A is friends with B
    //check here
    return true;
}

boolean isBalasanBlank(BalasanList BL){
    return(BL.First == NULL);
}

void createBalasanList(BalasanList* BL){
    BL->First = NULL;
    BL->Last = NULL;
    BL->countEvo = 0;
    BL->realCount = 0;
}

BALASAN* getBalasan(BalasanList Bl, id ID){
    BALASAN* p = Bl.First;


    while(p != Bl.Last && p->IdBalas != ID){
        p = p->Next;
    }
    
    if (p->IdBalas == ID){
        return p;
    }
    else{
        return NULL;
    }
};

void insertBalasan(BalasanList* BL, BALASAN* b){
    if (isBalasanBlank(*BL)){
        BL->First = b;
        BL->Last = b;
    }
    else{
        BALASAN * blast = BL->Last;
        blast->Next = b;
        b->Prev = blast;
        BL->Last = b;
    }

};

void readBalasan(id author,id parent, BalasanList *BL){
    if(parent == -1 || getBalasan(*BL, parent) != NULL){
        BL->countEvo++;
        BL->realCount++;
        BALASAN *b = (BALASAN*) malloc (sizeof(BALASAN));
        printf("Masukkan balasan: ");
        STARTCOMMAND();
        b->Text = currentWord;
        b->Author = author;
        setToCurrentTime(&(b->Time));
        if (parent == -1){
            b->indexLevel = 0;
        }
        else{
            b->indexLevel = (getBalasan(*BL,parent)->indexLevel)+1;
        }
        b->IdBalas = BL->countEvo;
        b->Prev = BL->Last;
        b->Next = NULL;
        b->parentID = parent;
        insertBalasan(BL, b);   
    }
};
    

void printSpaces(int x){
    for (int i = 0; i < x; i++){
        printf("   ");
    }
};

void printBalasanXasA(BalasanList BL, id x, id user){
    if (getBalasan(BL,x) == NULL){
        printf("Balasan tidak ada bro!\n");
    }
    else{
        BALASAN* b = getBalasan(BL,x);
        int space = b->indexLevel;
        if (balasAcanSeeB(user,b->Author) == true){
            printSpaces(space);
            printf("| ID = %d\n",x);
            printSpaces(space);
            printf("| %d PLACEHOLDER UNTIL USERSYS\n",b->Author);
            printSpaces(space);
            printf("| ");
            TulisDATETIME(b->Time);
            printf("\n");
            printSpaces(space);
            printf("| %s\n",wordToStr(b->Text));
        }
        else{
            printSpaces(space);
            printf("| ID = %d\n",x);
            printSpaces(space);
            printf("| PRIVATE\n");
            printSpaces(space);
            printf("| PRIVATE");
            printf("\n");
            printSpaces(space);
            printf("| PRIVATE\n");
        }
    }
}

void printChildren(BalasanList BL, id x, id user){
    BALASAN * p = getBalasan(BL,x);
    boolean stop = false;
    while (!stop){
        if (p->parentID == x){
            printBalasanXasA(BL,p->IdBalas,user);
            printChildren(BL, p->IdBalas,user);
        };

        if (p->Next == NULL){
            stop = true;
        }
        else{
            p = p->Next;
        }
    }
}

#endif