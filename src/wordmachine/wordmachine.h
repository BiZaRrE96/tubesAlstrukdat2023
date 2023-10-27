/* File: wordmachine.h */
/* Definisi Mesin Word: Model Akuisisi Versi I */

#ifndef __WORDMACHINE_H__
#define __WORDMACHINE_H__

#include "../CharMachine/charmachine.h"
#include <stdlib.h>

#define NMax 50
#define BLANK ' '
#define ENTER '\n'
#define MARKCOMMAND ';'

typedef struct
{
   char TabWord[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
   int Length;
} Word;

/* State Mesin Word */
static boolean EndWord;
static Word currentWord;

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

int strToInt(Word w)
{
    // printf("Length: %d\n", w.Length);
    int i, result = 0;
    for (i = w.Length-1; i >= 0; i--)
    {
        // printf("w.TabWord[%d]: %c\n", i, w.TabWord[i]);
        if (w.TabWord[i] >= '0' && w.TabWord[i] <= '9')
            result = result * 10 + (w.TabWord[i] - '0');
    }
    return result;
}



// Fungsi apakah value dari TabWord adalah string s
boolean isWordStrEqual(Word W, char s[]) 
{
    for (int i = 0; i < W.Length; i++) {
        if (W.TabWord[i] != s[i]) {
            return false;
        }
    }

    return true;
}

// Membuat fungsi untuk mengkonvert word ke char[]
char* wordToStr(Word W) {
    char* result = (char*) malloc(W.Length * sizeof(char));
    for (int i = 0; i < W.Length; i++) {
        result[i] = W.TabWord[i];
    }

    return result;
}

Word insertStrToWord(Word W, char str[], int lenStr, int idx) {
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

Word mergeWord(Word wLeft, Word wRight) {
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

// -------------------- COMMAND --------------------
void CopyCommand() {
    /* Mengakuisisi kata, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari kata
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = BLANK atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
              Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
    currentWord.Length = 0;
    while (currentChar != MARKCOMMAND)
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

void STARTCOMMAND() {
    START();
    IgnoreBlanks();

    if (currentChar == MARKCOMMAND) {
        EndWord = true;
    } else {
        EndWord = false;
        CopyCommand();
    }
}

boolean isCommandExit() {
    // Command = "TUTUP_PROGRAM"
    char exitCommandStr[] = "TUTUP_PROGRAM";

    if (currentWord.Length != 13) {
        return false;
    }

    for (int i = 0; i < 13; i++) {
        if (currentWord.TabWord[i] != exitCommandStr[i]) {
            return false;
        }
    }

    return true;
}

#endif