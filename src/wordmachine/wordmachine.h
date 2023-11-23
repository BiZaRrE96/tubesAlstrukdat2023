/* ADT Word Machine */
/* Definisi Mesin Word: Model Akuisisi Versi I */

#ifndef __WORDMACHINE_H__
#define __WORDMACHINE_H__

#include "../CharMachine/charmachine.h"
#include <stdlib.h>

#define NMax 280
#define BLANK ' '
#define ENTER '\n'


typedef struct
{
   char TabWord[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
   int Length;
} Word;

/* State Mesin Word */
static boolean EndWord;
static Word currentWord;

/* ********* AKUISISI ********* */
void IgnoreBlanks()
{
    /* Mengabaikan satu atau beberapa BLANK
       I.S. : currentChar sembarang
       F.S. : currentChar ≠ BLANK,currentChar = MARK, atau currentChar = ENTER */
    while ((currentChar == BLANK) || (currentChar == ENTER))
    {
        ADV();
    }
}

void CopyWord()
{
    /* Mengakuisisi kata, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari kata
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = BLANK atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
              Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
    currentWord.Length = 0;
    while (currentChar != BLANK && currentChar != MARK && currentChar != ENTER)
    {
        if (currentWord.Length < NMax)
        { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        }
        else
            break;
    }
}

void STARTWORD()
{
    /* I.S. : currentChar sembarang
       F.S. : EndWord = true, dan currentChar = MARK;
              atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
              currentChar karakter pertama sesudah karakter terakhir kata */
    START();
    IgnoreBlanks();
    EndWord = false;
    if (currentChar == MARK)
    {
        EndWord = true;
    }
    else
    {
        EndWord = false;
        CopyWord();
    }
}

void STARTWORDFILE(char filename[])
{
    /* I.S. : currentChar sembarang
       F.S. : EndWord = true, dan currentChar = MARK;
              atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
              currentChar karakter pertama sesudah karakter terakhir kata */
    STARTFILE(filename);
    IgnoreBlanks();
    EndWord = false;
    if (currentChar == MARK)
    {
        EndWord = true;
    }
    else
    {
        EndWord = false;
        CopyWord();
    }
}

void ADVWORD()
{
    /* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
       F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
              currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
              Jika currentChar = MARK, EndWord = true.
       Proses : Akuisisi kata menggunakan procedure CopyWord */
    IgnoreBlanks();
    if (currentChar == MARK)
    {
        EndWord = true;
    }
    else
    {
        // EndWord = false;
        CopyWord();
        IgnoreBlanks();
    }
}

/* ********* KELOMPOK OPERASI WORD ********* */
int wordToInt(Word w)
/*
    I.S. w terdefinisi sebagai string angka
    F.S. Mengembalikan nilai integer dari hasil konversi w
*/
{
    int i, result = 0;
    for (i = 0; i < w.Length; i++)
    {
        if (w.TabWord[i] >= '0' && w.TabWord[i] <= '9')
            result = result * 10 + (w.TabWord[i] - '0');
    }

    if (w.TabWord[0] == '-')
        result *= -1;
    return result;
}

boolean isWordEqual(Word w1, Word w2) {
/*
    I.S. w1 dan w2 terdefinisi
    F.S. Mengembalikan true jika w1 dan w2 sama, false jika tidak
*/
    if (w1.Length != w2.Length) {
        return false;
    }

    for (int i = 0; i < w1.Length; i++) {
        if (w1.TabWord[i] != w2.TabWord[i]) {
            return false;
        }
    }

    return true;

}

boolean isWordInt(Word w) {
/*
    I.S. w sembarang
    F.S. Mengembalikan true jika w adalah string angka, false jika tidak
*/
    for (int i = 0; i < w.Length; i++) {
        if (i == 0 && w.TabWord[i] == '-') {
            continue;
        }
        if (w.TabWord[i] < '0' || w.TabWord[i] > '9') {
            return false;
        }
    }

    return true;
}  

boolean isWordStrEqual(Word W, char s[], int len) 
/*
    I.S. W dan s terdefinisi
    F.S. Mengembalikan true jika W.TabWord dan s sama, false jika tidak
*/
{
    // Jika panjangnya berbeda, maka pasti tidak sama
    if (W.Length != len) {
        return false;
    }

    // Cek satu per satu setiap karakter pada W.TabWord dan s
    for (int i = 0; i < W.Length; i++) {
        if (W.TabWord[i] != s[i]) {
            return false;
        }
    }

    return true;
}

char* wordToStr(Word W)
/*
    I.S. W terdefinisi
    F.S. Mengembalikan string yang berisi W.TabWord
*/
{
    char* result = (char*) malloc((W.Length+1) * sizeof(char));
    for (int i = 0; i < W.Length; i++) {
        result[i] = W.TabWord[i];
    }
    result[W.Length] = '\0';

    return result;
}

Word insertStrToWord(Word W, char str[], int lenStr, int idx)
/*
    I.S. W dan str terdefinisi
    F.S. Mengembalikan Word yang merupakan hasil penyisipan str pada W pada indeks idx
*/
{
    Word result;
    result.Length = W.Length + lenStr;

    for (int i = 0; i < idx; i++) {
        result.TabWord[i] = W.TabWord[i];
    }

    for (int i = 0; i < lenStr; i++) {
        result.TabWord[i + idx] = str[i];
    }

    for (int i = idx; i < W.Length; i++) {
        result.TabWord[i + lenStr] = W.TabWord[i];
    }

    return result;
}

Word mergeWord(Word wLeft, Word wRight)
/*
    I.S. wLeft dan wRight terdefinisi
    F.S. Mengembalikan Word yang merupakan hasil penggabungan wLeft dan wRight
*/
{
    Word result;
    result.Length = wLeft.Length + wRight.Length;

    for (int i = 0; i < wLeft.Length; i++) {
        result.TabWord[i] = wLeft.TabWord[i];
    }

    for (int i = 0; i < wRight.Length; i++) {
        result.TabWord[i + wLeft.Length] = wRight.TabWord[i];
    }

    return result;
}



#endif