#ifndef _Draf_H_
#define _Draf_H_
#define Nil -1
#define MaxEl 100

//ADT Draf(?)
//MENGGUNAKAN : ADT STACK
#include <stdio.h>
#include "../boolean/boolean.h"
#include "../sentencemachine/sentencemachine.h"
#include "../commandmachine/commandmachine.h"
#include "../datetime/datetime.h"
#include "kicau.h"

extern KicauList kicauan;

typedef int AddressDraf;

typedef struct {
    KICAU Kicau[MaxEl]; // memori penyimpanan Draf
    AddressDraf TOP;
} DrafStack;

typedef struct {
    DrafStack buffer[20];
    int length;
} DrafList;

/* ***** SELEKTOR DRAF ***** */
#define ElmtDrafList(DL,i) (DL).buffer[i]
#define Top(DS) (DS).TOP
#define InfoTop(DS) (DS).Kicau[(DS).TOP]
#define Text(DS) (DS).Kicau[Top(DS)].Text
#define Author(DS) (DS).Author
#define Time(DS) (DS).Kicau[Top(DS)].Time
#define User(DL,i) (DL).buffer[i].Author
#define ELMT(DL,i) (DL).buffer[i]

void CreateEmpty(DrafStack *DS){
    Top(*DS) = -1;
}

boolean IsEmptyDraf(DrafStack DS){
    return Top(DS) == -1;
}


void Push(DrafStack * DS, KICAU X){
    Top(*DS) += 1;
    InfoTop(*DS) = X;
}


void Pop(DrafStack *DS, KICAU *X){
    *X = InfoTop(*DS);
    Top(*DS) -= 1;
} 

void draf(DrafStack *DS, int idxUser, Word user){
    KICAU X;
    printf("Masukkan kicauan: ");
    STARTCOMMAND();
    Word input = currentWord;
    if (!isBlank(input)){
        X.Text = input;
        setToCurrentTime(&X.Time);
        X.Author = user;
        Push(DS,X);

        opsidraf(DS, idxUser);
    }
    else{
        printf("Kicauan tidak boleh hanya berisi spasi!\n");
    }
}

void hapus(DrafStack *DS){
    KICAU X;
    Pop(DS,&X);
    printf("Draf telah berhasil dihapus!");
}

void simpan(KICAU Draf, DrafStack *DS){
    Push(DS,Draf);
    printf("Draf telah berhasil disimpan!");
}

void terbit(DrafStack *DS, id x) {
    KICAU draft;
    Pop(DS,&draft);
    Count(kicauan)++;
    int i = Count(kicauan);
    GetText(kicauan,i) = draft.Text;
    GetLike(kicauan,i) = 0;
    GetAuthor(kicauan,i) = draft.Author;
    GetTime(kicauan,i) = draft.Time;
    
    printf("Selamat! kicauan telah diterbitkan!\nDetil kicauan:\n");
    printKicauXasA(kicauan, (i), draft.Author);
    printf("\n");
}

void viewDraf(DrafStack *DS, int idxUser, Word user){
    if (IsEmptyDraf(*DS)){
        printf("\nYah, anda belum memiliki draf apapun! Buat dulu ya :D\n");
        return 0;
    }

    printf("\nIni draf terakhir anda:\n");
    printf("| "); TulisDATETIME(Time(*DS)); 
    printf("\n| %s\n\n", wordToStr(Text(*DS)));

    printf("Apakah anda ingin menghapus, mengubah, atau menerbitkan draf ini? (UBAH/HAPUS/TERBIT)\n");
    STARTCOMMAND();
    if (isWordStrEqual(currentWord,"UBAH", 4)){
        draf(DS, idxUser, user);
    } else if (isWordStrEqual(currentWord,"HAPUS", 5)){
        hapus(DS);
    } else if (isWordStrEqual(currentWord,"TERBIT", 6)){
        terbit(DS, idxUser);
    } else {
        printf("Perintah tidak dikenali!\n");
    }
    
}

void opsidraf(DrafStack *DS, int idxUser) {
    printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini? (SIMPAN/HAPUS/TERBIT)\n");
    STARTCOMMAND();
    if (isWordStrEqual(currentWord,"SIMPAN", 6)){
        return;
    } else if (isWordStrEqual(currentWord,"HAPUS", 5)){
        hapus(DS);
    } else if (isWordStrEqual(currentWord,"TERBIT", 6)){
        terbit(DS, idxUser);
    } else {
        printf("Perintah tidak dikenali!\n");
        opsidraf(DS, idxUser);
    }
}
#endif