#ifndef _BALAS_H_
#define _BALAS_H_

#include "../boolean/boolean.h"
#include "../userlist/userlist.h"
#include "../sentencemachine/sentencemachine.h"
#include "../commandmachine/commandmachine.h"
#include "../datetime/datetime.h"

//Notes untuk merger balasan:
// jalankan createBalasanList
// untuk print semua balasan printBalasanComplete(BL, -1, user)
// printBalasanComplete(BL, id, user) akan mengeprint balasan id ID dan semua child nya
// readBalasan untuk membuat balasan dan memasukkan ke BL

//DATA TYPE USED : ADT Tree dengan struktur data berkait
//Kenapa Tree? biar kalau delete cascading
//Kenapa struktur data berkait? tidak perlu alokasi banyak2
// belum tentu suatu kicau ada balasan

typedef int id;

typedef struct BALASAN* AddressBalas;

typedef struct BALASAN{
    Word Text;
    Word Author;
    DATETIME Time;
    int indexLevel;
    id IdBalas;
    AddressBalas Next;
    AddressBalas Prev;
    id parentID;
} BALASAN;

typedef struct {
    BALASAN* First;
    BALASAN* Last;
    int countEvo;
    int realCount;
} BalasanList;

extern Friendship friendship;
extern UserList users;

/* ***** SELEKTOR BALASAN ***** */
#define BalasanText(b) (b).Text
#define BalasanAuthor(b) (b).Author
#define BalasanTime(b) (b).Time
//#define IDX_UNDEF -1
// bruh moment
boolean AcanSeeB(Word A, Word B) {
    int readerID = indexOfUser(users,A);
    int readeeID = indexOfUser(users,B);
    //Remove // to make verbose
    //printf("A to B: %d\n",(FriendshipStatus(friendship,readerID,readeeID)));
    //printf("B to A: %d\n",(FriendshipStatus(friendship,readeeID,readerID)));
    if(isWordEqual(A,B)){
        printf("is self\n");
        return true;
    }
    else if(ElmtPrivacy(users,readeeID) == true){
        printf("readee public\n");
        return true;
    }
    
    else if((FriendshipStatus(friendship,readerID,readeeID)) == 1 && (FriendshipStatus(friendship,readeeID,readerID)) == 1){
        printf("is friends\n");
        return true;
    }
    else{
        return false;
    }
}


/*TEMPORARY FUNCTION*/
boolean balasAcanSeeB(Word A, Word B){
    //return true;
    return AcanSeeB(A,B);
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

void readBalasan(Word author,id parent, BalasanList *BL){
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

//debug helper
void printBalasan(BALASAN*B){
    printf("| ID = %d\n",B->IdBalas);
    printf("| %s\n",wordToStr(B->Author));
    printf("| ");
    TulisDATETIME(B->Time);
    printf("\n");
    printf("| %s\n",wordToStr(B->Text));   
}
//Print singular balasan
void printBalasanXasA(BalasanList BL, id x, Word user, int indexLevel){
    if (getBalasan(BL,x) == NULL){
        printf("Balasan tidak ada bro!\n");
    }
    else{
        BALASAN* b = getBalasan(BL,x);
        int space = b->indexLevel - indexLevel;
        if (space < 0){
            space = 0;
        }
        if (balasAcanSeeB(user,b->Author) == true){
            printSpaces(space);
            printf("| ID = %d\n",x);
            printSpaces(space);
            printf("| %s\n",wordToStr(b->Author));
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

//Print balasan dalam BalasanList berID x, dan semua children nya
//Tidak mengeprint host balasan
void printChildren(BalasanList BL, id x, Word user, int indexLevel){
    BALASAN * p = getBalasan(BL,x);
    boolean stop = false;
    while (!stop){
        if (p->parentID == x){
            printBalasanXasA(BL,p->IdBalas,user,indexLevel);
            printChildren(BL, p->IdBalas,user,p->indexLevel);
        };

        if (p->Next == NULL){
            stop = true;
        }
        else{
            p = p->Next;
        }
    }
}

//Delete suatu balasan dan semua childrennya (cascading)
//id -1 akan memprint semua balasan
void printBalasanComplete(BalasanList BL, id x, Word user){
    if (x == -1){
        BALASAN * p = BL.First;
        boolean stop = false;
        while (!stop){
            if (p->parentID == -1){
                printBalasanXasA(BL, p->IdBalas,user,0);
                printChildren(BL, p->IdBalas,user,0);
            };

            if (p->Next == NULL){
                stop = true;
            }
            else{
                p = p->Next;
            }
        }
    }
    else{
        int indexLevel = getBalasan(BL,x)->indexLevel;
        printBalasanXasA(BL,x,user,indexLevel);
        printChildren(BL,x,user,indexLevel);
    }
};

void deleteSingularBalasan(BalasanList *BL,id ID){
    BALASAN* B = getBalasan(*BL,ID);
    if (B->Prev != NULL){
        (B->Prev)->Next = B->Next;
    }
    else{//artinya ini pertama harusnya
        //printf("Moved head of BL\n");
        BL->First = B->Next;
    }
    if (B->Next != NULL){
        (B->Next)->Prev = B->Prev;
    }
    else{//artinya ini last
        //printf("Moved tail of BL\n");
        BL->Last = B->Prev;
    }
    free(B);
}

void deleteBalasan(BalasanList*BL, id x, Word user){
    BALASAN* B = (getBalasan(*BL,x));
    if (B == NULL){
        printf("Balasan tidak ada!");
    }
    else if (!isWordEqual(B->Author,user)){
        printf("Balasan bukan milik anda!");
    }
    else{
        deleteChildren(BL,x);
    }   
}
//fungsi pembantu
void deleteChildren(BalasanList* BL,id ID){
    BALASAN* P = getBalasan(*BL,ID);
    boolean done = false; 
    while(!done){
        if(P->Next == NULL){
            done = true;
        }
        else{
            P = P->Next;
        }
        if(P->parentID == ID){
            if (P->Next == NULL){
                deleteSingularBalasan(BL,P);
            }
            else{
                deleteChildren(BL,P->IdBalas);
            }
        }
    }
    deleteSingularBalasan(BL,ID);
}

#endif
