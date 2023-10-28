#include "kicau.h"

int main(){

    KicauList KL;
    createKicauList (&KL, 10);

    Kicau(&KL, 69);
    
    printf("aaa\n");
    printf("test: %s\n ",wordToStr(KL.Kicau[0].Text));
    printf("Author ID : %d\n",GetAuthor(KL,0));
}