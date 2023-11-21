#ifndef _USERLIST_H_
#define _USERLIST_H_

#include "../user/user.h"
#include "../liststatik/liststatik.h"
#include "../photo/photo.h"
#include "../boolean/boolean.h"
#include "../commandmachine/commandmachine.h"

#define MAX_USERS 20

typedef struct
{
    User TabUser[MAX_USERS];
    int Neff;
} UserList;

#define Pengguna(U, i) (U).TabUser[(i)]
#define Neff(U) (U).Neff
#define ElmtUsername(U, i) (U).TabUser[(i)].username
#define ElmtPassword(U, i) (U).TabUser[(i)].password
#define ElmtBio(U, i) (U).TabUser[(i)].bio
#define ElmtPhoneNumber(U, i) (U).TabUser[(i)].phoneNumber
#define ElmtWeton(U, i) (U).TabUser[(i)].weton
#define ElmtPhoto(U, i) (U).TabUser[(i)].photo
#define ElmtPrivacy(U, i) (U).TabUser[(i)].privacy

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateUserList(UserList *U){
    Neff(*U) = 0;
};
/* I.S. U sembarang */
/* F.S. U terdefinisi dengan Neff(U) = 0 */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLengthUserlist(UserList U){
    return Neff(U);
};
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */

/* ********** OUTPUT ********** */
/* Hanya untuk keperluan debugging */
void displayUserList(UserList U) {
    for (int i = 0; i < U.Neff; i++) {
        printf("| Password: %s\n", wordToStr(ElmtPassword(U, i)));
        LIHAT_PROFIL(Pengguna(U, i));
    }
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfUser(UserList U, Word nama) {
    int i = 0;
    while (i < U.Neff && !isWordEqual(ElmtUsername(U, i), nama)) {
        i++;
    }
    if (i == U.Neff) {
        return -1;
    } else {
        return i;
    }
}
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLastUser(UserList *U, User user){
    Neff(*U)++;
    Pengguna(*U, listLengthUserlist(*U)) = user;
}
;
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */

#endif