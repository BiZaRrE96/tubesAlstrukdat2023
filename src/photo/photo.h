#ifndef _PHOTO_H_
#define _PHOTO_H_

#include "../wordmachine/wordmachine.h"

#define MAX_PHOTO_SIZE 5

typedef struct {
    char character;
    char color;
} Pixel;

typedef struct {
    Pixel pixels[MAX_PHOTO_SIZE][MAX_PHOTO_SIZE];
} Photo;

#define PhotoColor(photo, i, j) (photo).pixels[(i)][(j)].color
#define PhotoCharacter(photo, i, j) (photo).pixels[(i)][(j)].character

// Tulis implementasi ADT Photo disini


#endif