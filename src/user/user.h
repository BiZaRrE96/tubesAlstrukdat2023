// ADT User

#ifndef USER_H_
#define USER_H_

#include "../commandmachine/commandmachine.h"
#include "../boolean/boolean.h"
#include "../photo/photo.h"
#include "../userlist/userlist.h"
#include "../matrix/matrixchar.h"

#define PRIVATE false
#define PUBLIC true

#define MAX_LENGTH_USERNAME 20
#define MAX_LENGTH_PASSWORD 20

typedef struct
{
    Word username;
    Word password;
    Word bio;
    Word phoneNumber;
    Word weton; // Weton lahir (Pahing, Kliwon, Wage, Pon, dan Legi (case insensitive))
    Matrixchar photo;
    boolean privacy; // false = privat, true = public;
} User;

#define Username(U) (U).username
#define Password(U) (U).password
#define Bio(U) (U).bio
#define PhoneNumber(U) (U).phoneNumber
#define Weton(U) (U).weton
#define Photo(U) (U).photo
#define Privacy(U) (U).privacy

boolean isLogin = false; // Global Variabel yang di main
User currentUser;        // Global Variabel yang di main
UserList users;          // Global Variabel yang di main

void DAFTAR();

void MASUK();

void KELUAR();

void GANTI_PROFIL(User *currentUser);

void LIHAT_PROFIL(User currentUser);

void ATUR_JENIS_AKUN(User *currentUser);

void UBAH_FOTO_PROFIL(User *currentUser);

void PRINT_PROFIL(User currentUser);

void PRINT_FOTO(User currentUser);

#endif