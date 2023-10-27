#ifndef __SCREEN_H__
#define __SCREEN_H__

#include<stdio.h>
#include<stdlib.h>

#define cls printf("\033[2J\033[H")

void displaySplashScreen() {
    FILE *fptr;
    

    fptr=fopen("bin/burbir.txt", "r");
    if (fptr == NULL)
    {
        system("pwd");
        printf("Cannot open file (splash)\n");
        exit(0);
    }
    char c;

    // Membaca data dari file
    c = fgetc(fptr);
    while (c != EOF)
    {
        print_green(c);
        c = fgetc(fptr);
    }

    fclose(fptr);
}

#endif