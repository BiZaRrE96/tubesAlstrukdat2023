#ifndef _PROFILE_H_
#define _PROFILE_H_

#include "../sentencemachine/sentencemachine.h"
#include "../boolean/boolean.h"
#include "../photo/photo.h"

#define PRIVAT 0
#define PUBLIC 1

// Maksimal ukuran photo 5x5
#define MAX_ROW_PHOTO 5
#define MAX_COL_PHOTO 5

typedef struct {
    Sentence bio;
    Word phoneNumber;
    Word weton;         // Weton lahir (Pahing, Kliwon, Wage, Pon, dan Legi (case insensitive))
    Photo photo;
    boolean privacy;
} Profile;



#endif