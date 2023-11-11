#include "balas.h"
#include <stdio.h>

int main(){
    BalasanList BL;
    createBalasanList(&BL);
    readBalasan(69,-1,&BL);
    readBalasan(69,1,&BL);
    printBalasanXasA(BL,1,69);
    printChildren(BL,1,69);
    
}