#ifndef __SENTENCEMACHINE_H__
#define __SENTENCEMACHINE_H__

#include "../wordmachine/wordmachine.h"
#define max_length 1000

typedef struct
{
    char TabSentence[max_length];
    int Length;
} Sentence;

static boolean endSentence;
static Sentence currentSentence;

void CopySentence() {
    // Akuisisi kalimat
    currentSentence.Length = 0;
    while ((currentChar != ENTER) && (currentSentence.Length < max_length) && (currentChar != MARK)) {
        currentSentence.TabSentence[currentSentence.Length++] = currentChar;
        ADV();
    }
}

void StartSentence() {
    // Membaca kalimat pertama
    START();
    IgnoreBlanks();

    if (currentChar == ENTER) {
        endSentence = true;
    } else {
        endSentence = false;
        CopySentence();
    }
}

void AdvSentence() {
    // Membaca kalimat selanjutnya
    IgnoreBlanks();
    if (currentChar == ENTER) {
        endSentence = true;
    } else {
        CopySentence();
    }
}

#endif
