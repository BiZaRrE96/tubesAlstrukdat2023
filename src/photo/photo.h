#ifndef _PHOTO_H_
#define _PHOTO_H_

#include "../wordmachine/wordmachine.h"
#include "../pcolor/pcolor.h"
#include <stdio.h>

#define MAX_PHOTO_SIZE 5

typedef struct
{
    char character;
    char color;
} Pixel;

typedef struct
{
    Pixel pixels[MAX_PHOTO_SIZE][MAX_PHOTO_SIZE];
} Photo;

#define PhotoColor(foto, i, j) (foto).pixels[(i)][(j)].color
#define PhotoCharacter(foto, i, j) (foto).pixels[(i)][(j)].character

// Tulis implementasi ADT Photo disini
void displayPhoto(Photo p)
{

    for (int i = 0; i < MAX_PHOTO_SIZE; i++)
    {
        for (int j = 0; j < MAX_PHOTO_SIZE; j++)
        {
            if (PhotoColor(p, i, j) == 'R')
            {
                print_red(PhotoCharacter(p, i, j));
            }
            else if (PhotoColor(p, i, j) == 'G')
            {
                print_green(PhotoCharacter(p, i, j));
            }
            else if (PhotoColor(p, i, j) == 'B')
            {
                print_blue(PhotoCharacter(p, i, j));
            }
            else
            {
                printf("%c", PhotoCharacter(p, i, j));
            }
            printf(" ");
        }
        printf("\n");
    }
}

void createPhoto(Photo *p)
{
    for (int i = 0; i < MAX_PHOTO_SIZE; i++)
    {
        for (int j = 0; j < MAX_PHOTO_SIZE; j++)
        {
            PhotoColor(*p, i, j) = ' ';
            PhotoCharacter(*p, i, j) = ' ';
        }
    }
}

void changePhoto(Photo *p)
{
    START();
    IgnoreBlanks();
    for (int i = 0; i < MAX_PHOTO_SIZE; i++)
    {
        for (int j = 0; j < MAX_PHOTO_SIZE; j++)
        {
            if (currentChar != ' ')
            {
                PhotoCharacter(*p, i, j) = currentChar;
                ADV();
                IgnoreBlanks();
                if (currentChar != ' ')
                {
                    PhotoColor(*p, i, j) = currentChar;
                }
            }
            ADV();
            IgnoreBlanks();
        }
    }
}

#endif