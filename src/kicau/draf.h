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


typedef int address;

typedef struct {
    KICAU Kicau[MaxEl]; // memori penyimpanan Draf
    address TOP;
    Word Author;
} DrafStack;

typedef struct {
    DrafStack buffer[20];
    int length;
}DrafList;

/* ***** SELEKTOR DRAF ***** */
#define Top(DS) (DS).TOP
#define InfoTop(DS) (DS).Kicau[(DS).TOP]
#define Text(DS) (DS).Kicau[Top(DS)].Text
#define Author(DS) (DS).Author
#define Time(DS) (DS).Kicau[Top(DS)].Time
#define User(DL,i) (DL).buffer[i].Author
#define ELMT(DL,i) (DL).buffer[i]



void opsidraf(){
    printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n");
}

void CreateEmpty(DrafStack *DS, User user){
    Top(*DS) = Nil;
    Author(*DS) = Username(user);
}


boolean IsEmptyDraf(DrafStack DS){
    return Top(DS) == Nil;
}


void Push(DrafStack * DS, KICAU X){
    Top(*DS) += 1;
    InfoTop(*DS) = X;
}


void Pop(DrafStack *DS, KICAU *X){
    *X = InfoTop(*DS);
    Top(*DS) -= 1;
} 

void draf(DrafStack *DS){
    KICAU X;
    printf("Masukkan kicauan: ");
    STARTCOMMAND();
    Word input = currentWord;
    if (!isBlank(input)){
        X.Text = input;
        setToCurrentTime(&X.Time);
        Push(DS,X);
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

void terbit(KicauList *KL, DrafStack DS, id x, User user){
    Count(*KL)++;
        int i = Count(*KL);
        GetText(*KL,i) = Text(DS);
        GetLike(*KL,i) = 0;
        GetAuthor(*KL,i) = Username(user);
        setToCurrentTime(&GetTime(*KL,i));
        
        printf("Selamat! kicauan telah diterbitkan!\nDetil kicauan:\n");
        printKicauXasA(*KL, (i), Username(user));
        printf("\n");
}

void ubah(DrafStack *DS){
    printf("Masukkan kicauan: ");
    STARTCOMMAND();
    Word input = currentWord;
    if (!isBlank(input)){
        Text(*DS) = input;
        setToCurrentTime( &Time(*DS) );
    }else{
        printf("Kicauan tidak boleh hanya berisi spasi!\n");
    }
}
DrafStack searchDraf(DrafList DL, User user){
    int i =0;
    while (!isWordEqual(User(DL,i) , Username(user))){
        i++;
    }
    return ELMT(DL,i);
}
void viewDraf(DrafList DL, User user){
    DrafStack DS = searchDraf(DL, user);

    if(IsEmptyDraf(DS)){
        printf("Yah, anda belum memiliki draf apapun! Buat dulu ya :D");
    } else{
        printf("Ini draf terakhir anda:\n");
        printf("| %s\n",wordToStr(Text(DS)));
        printf("| ");
        TulisDATETIME(Time(DS));
        printf("\n");}
}
#endif