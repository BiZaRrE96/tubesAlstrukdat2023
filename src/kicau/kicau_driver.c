#include "kicau.h"

int main(){

    KicauList KL;
    createKicauList(&KL, 10);

    Kicau(&KL, 69);
    Kicau(&KL, 69);
    
    //printKicauXasA(KL,1,69);
    viewRecentAsA(KL,69);
}