/* ADT Senctence */

/*
    Note :  Perbedaan Sentence (kalimat) dengan Word (kata) adalah
            Sentence dapat memiliki spasi, sedangkan Word tidak.
*/

#ifndef __SENTENCEMACHINE_H__
#define __SENTENCEMACHINE_H__

#include "../wordmachine/wordmachine.h"
#define max_length 1000

void CopySentence() {
    // Akuisisi kalimat
    currentWord.Length = 0;
    while ((currentChar != ENTER) && (currentWord.Length < max_length) && (currentChar != MARK)) {
        currentWord.TabWord[currentWord.Length++] = currentChar;
        ADV();
    }
}

void StartSentence() {
    // Membaca kalimat pertama
    START();
    IgnoreBlanks();

    if (currentChar == ENTER) {
        EndWord = true;
    } else {
        EndWord = false;
        CopySentence();
    }
}

void AdvSentence() {
    // Membaca kalimat selanjutnya
    IgnoreBlanks();
    if (currentChar == ENTER) {
        EndWord = true;
    } else {
        CopySentence();
    }
}

Word SentenceToWord() {
    // Mengubah kalimat menjadi kata
    Word w;
    int i;
    for (i = 0; i < currentWord.Length; i++) {
        w.TabWord[i] = currentWord.TabWord[i];
    }
    w.Length = currentWord.Length;
    return w;
}

#endif
