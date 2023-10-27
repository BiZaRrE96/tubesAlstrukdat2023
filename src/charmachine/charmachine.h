/* File: charmachine.h */
/* Definisi Mesin Karakter */

#ifndef __CHAR_MACHINE_H__
#define __CHAR_MACHINE_H__

#include <stdio.h>
#include "../Boolean/boolean.h"

#define MARK '.'
/* State Mesin */
extern char currentChar;
extern boolean EOP;

static FILE *pita;
static int retval;

char currentChar;
boolean EOP;

void ADV()
{
    /* Pita dimajukan satu karakter.
        I.S. : Karakter pada jendela =
                currentChar, currentChar != MARK
        F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
                currentChar mungkin = MARK.
                    Jika  currentChar = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    retval = fscanf(pita, "%c", &currentChar);
    EOP = (currentChar == MARK);
    if (EOP)
    {
        // printf("EOP\n");
        fclose(pita);
    }
}

void START()
{
    /* Mesin siap dioperasikan. Pita disiapkan untuk dibaca. Input dari keyboard.
        Karakter pertama yang ada pada pita posisinya adalah pada jendela.
        I.S. : sembarang
        F.S. : currentChar adalah karakter pertama pada pita. Jika currentChar != MARK maka EOP akan padam (false).
                Jika currentChar = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    

    pita = stdin;
    // Cek apakah pita close
    // printf("pita = stdin\n");
    ADV();
}

void STARTFILE(char filename[])
{
    /* Mesin siap dioperasikan. Pita disiapkan untuk dibaca. Input dari file.
        Karakter pertama yang ada pada pita posisinya adalah pada jendela.
        I.S. : sembarang
        F.S. : currentChar adalah karakter pertama pada pita. Jika currentChar != MARK maka EOP akan padam (false).
                Jika currentChar = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    pita = fopen(filename, "r");
    ADV();
}

#endif