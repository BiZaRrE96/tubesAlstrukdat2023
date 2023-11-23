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
    if((isWordEqual(A,B)) || (ElmtPrivacy(users,readeeID) == true)){
        return true;
    }
    if ((FriendshipStatus(friendship,readerID,readeeID)) == 1 && (FriendshipStatus(friendship,readeeID,readerID)) == 1){
        return true;
    }
    return false;
    
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
    // printf("ID = %d\n",ID);

    if (p == NULL){
        return NULL;
    }

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
    

void printSpaces(int x){
    for (int i = 0; i < x; i++){
        printf("   ");
    }
};

void printBalasanXasA(BalasanList BL, id x, Word user){
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

void readBalasan(Word author,id parent, BalasanList *BL, Word kicauAuthor) {
    printf("\n");
    if (parent == -1 || getBalasan(*BL, parent) != NULL) {
        // Cek apakah author tidak berteman dengan user dan privat
        if (parent == -1) {
            if (balasAcanSeeB(author,kicauAuthor) == false) {
                printf("Wah, akun tersebut merupakan akun privat dan anda belum berteman akun tersebut!\n");
                return;
            }
        }
        else 
        if (balasAcanSeeB(author,getBalasan(*BL,parent)->Author) == false) {
            printf("Wah, akun tersebut merupakan akun privat dan anda belum berteman akun tersebut!\n");
            return;
        }
        

        BL->countEvo++;
        BL->realCount++;
        BALASAN *b = (BALASAN*) malloc (sizeof(BALASAN));
        printf("\nMasukkan balasan: ");
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

        printf("\nSelamat!, balasan telah diterbitkan!\nDetil balasan:\n");
        printBalasanXasA(*BL,b->IdBalas,author);
        printf("\n");
        return;
    } 

    printf("\nWah, kicau tidak ditemukan!\n");

};


void printBalasan(BalasanList BL, id x, Word user) {
    if (getBalasan(BL,x) == NULL){
        printf("\nBalasan tidak ada bro!\n\n");
        return;
    }

    BALASAN* b = getBalasan(BL,x);
    int space = b->indexLevel;
    while (b != NULL){
        printf("\n");
        printBalasanXasA(BL,b->IdBalas,user);  
        printf("\n");
        b = b->Next;
    }
}

void deleteBalasanId(BalasanList* BL, id x, id idDelete, Word user) {
    if (getBalasan(*BL,x) == NULL){
        printf("Balasan tidak ditemukan!\n");
        return;
    }

    BALASAN* b = getBalasan(*BL,x);
    while (b != NULL){
        if (b->IdBalas == idDelete) {
            if (!isWordEqual(user, b->Author)) {
                printf("Hei, ini balasan punya siapa? Jangan dihapus ya!\n");
                return;
            }

            if (b->Prev == NULL) {
                BL->First = b->Next;
            }
            else{
                b->Prev->Next = b->Next;
            }
            if (b->Next == NULL){
                BL->Last = b->Prev;
            }
            else{
                b->Next->Prev = b->Prev;
            }
            free(b);

            printf("Balasan berhasil dihapus!\n");          
            

            return;
        }
        b = b->Next;
    }

    printf("Balasan tidak ditemukan!\n");
}

#endif