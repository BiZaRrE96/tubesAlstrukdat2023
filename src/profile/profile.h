#ifndef _PROFILE_H_
#define _PROFILE_H_

#include "../sentencemachine/sentencemachine.h"
#include "../boolean/boolean.h"
#include "../photo/photo.h"

#define PRIVATE false
#define PUBLIC true

typedef struct {
    Word bio;
    Word phoneNumber;
    Word weton;         // Weton lahir (Pahing, Kliwon, Wage, Pon, dan Legi (case insensitive))
    Photo photo;
    boolean privacy;    // false = privat, true = public
} Profile;

#define Bio(P) (P).bio
#define PhoneNumber(P) (P).phoneNumber
#define Weton(P) (P).weton
#define Photo(P) (P).photo
#define Privacy(P) (P).privacy

#endif