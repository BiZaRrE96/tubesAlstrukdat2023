#ifndef _USERLIST_H_
#define _USERLIST_H_

#include "../user/user.h"

#define MAX_USERS 20
#define IDX_UNDEF -1

typedef User Eltypeuser;
typedef struct
{
    Eltypeuser TabUser[MAX_USERS];
    int Neff;
} UserList;

#define User(U, i) (U).TabUser[(i)]
#define Neff(U) (U).Neff
#define ElmtUsername(U, i) (U).TabUser[(i)].username
#define ElmtPassword(U, i) (U).TabUser[(i)].password
#define ElmtBio(U, i) (U).TabUser[(i)].bio
#define ElmtPhoneNumber(U, i) (U).TabUser[(i)].phoneNumber
#define ElmtWeton(U, i) (U).TabUser[(i)].weton
#define ElmtPhoto(U, i) (U).TabUser[(i)].photo
#define ElmtPrivacy(U, i) (U).TabUser[(i)].privacy

UserList users;          

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateUserList(UserList *U);
/* I.S. U sembarang */
/* F.S. U terdefinisi dengan Neff(U) = 0 */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLengthUserlist(UserList U);
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfUser(UserList U, Word nama);
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLastUser(UserList *U, User user);
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */

void DAFTAR();

void MASUK();

void KELUAR();

#endif