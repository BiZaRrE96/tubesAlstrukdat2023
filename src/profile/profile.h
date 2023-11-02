#ifndef _PROFILE_H_
#define _PROFILE_H_

#include "../commandmachine/commandmachine.h"
#include "../boolean/boolean.h"
#include "../photo/photo.h"
#include "../user/user.h"
#include "../userlist/userlist.h"

#define PRIVATE false
#define PUBLIC true

typedef struct
{
    Word bio;
    Word phoneNumber;
    Word weton; // Weton lahir (Pahing, Kliwon, Wage, Pon, dan Legi (case insensitive))
    Photo photo;
    boolean privacy; // false = privat, true = public
} Profile;

#define Bio(P) (P).bio
#define PhoneNumber(P) (P).phoneNumber
#define Weton(P) (P).weton
#define Photo(P) (P).photo
#define Privacy(P) (P).privacy

void GANTI_PROFIL(Profile *P, User CurrentUser);

void LIHAT_PROFIL(Profile *P);

void ATUR_JENIS_AKUN(Profile *P);

void UBAH_FOTO_PROFIL(Profile *P);

void PRINT_PROFIL (Profile P, User user);

#endif