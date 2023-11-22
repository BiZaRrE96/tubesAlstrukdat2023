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


/* ********** ADT USERLIST ********** */
void DAFTAR(UserList *users)
{
    if (!isLogin)
    {
        boolean NameCheck = false;
        Word name;

        while (!NameCheck)
        {
            printf("\n\nMasukkan nama:\n");
            STARTCOMMAND();

            if (currentWord.Length <= 20)
            {
                name = currentWord;
                NameCheck = true;
            }
            else
            {
                NameCheck = false;
                printf("Username tidak valid karena kepanjangan. Masukkan lagi yuk!");
            }
        }

        int index = indexOfUser(*users, name);
        Word pass;
        boolean PassCheck = false;

        if (index != -1)
        {
            printf("Wah, sayang sekali nama tersebut telah diambil.");
            DAFTAR(users);
        }

        else
        {
            while (!PassCheck)
            {
                printf("\n\nMasukkan kata sandi:\n");
                STARTCOMMAND();

                if (currentWord.Length <= 20)
                {
                    pass = currentWord;
                    PassCheck = true;
                }

                else
                {
                    printf("Password tidak valid karena kepanjangan. Masukkan lagi yuk!");
                    PassCheck = false;
                }
            }
        }
        User NewUser = {name, pass};
        printf("\nPengguna telah berhasil terdaftar. Masuk untuk menikmati fitur-fitur BurBir.\n");
        insertLastUser(users, NewUser);
    }

    else
    {
        printf("\nAnda sudah masuk, keluar terlebih dahulu untuk mendaftar\n");
    }
}

void MASUK(UserList *users)
{
    if (!isLogin)
    {
        printf("\n\nMasukkan Nama:\n");
        STARTCOMMAND();

        Word nama = currentWord;
        int IndexUser = indexOfUser(*users, nama);

        if (IndexUser == -1)
        {
            printf("Wah, nama yang Anda cari tidak ada. Masukkan nama lain!");
            MASUK(users);
        }
        else
        {
            User terdaftar = Pengguna(*users, IndexUser);
            Word CorrectPass = terdaftar.password;
            boolean PassCheck = false;

            while (!PassCheck)
            {
                printf("\n\nMasukkan kata sandi:\n");
                STARTCOMMAND();

                Word Inputpass = currentWord;
                if (compareWord(CorrectPass, Inputpass))
                {
                    PassCheck = true;
                }
                else
                {
                    PassCheck = false;
                    printf("Wah, kata sandi yang Anda masukkan belum tepat. Periksa kembali kata sandi Anda!");
                }
            }
            printf("Anda telah berhasil masuk dengan nama pengguna ");
            PrintWord(terdaftar.username);
            printf(". Mari menjelajahi BurBir bersama Ande-Ande Lumut!");
            currentUser = terdaftar;
        }
    }

    else
    {
        printf("\nAnda sudah masuk, keluar terlebih dahulu untuk mendaftar\n");
    }
}

void KELUAR()
{
    if (!isLogin)
    {
        printf("\nAnda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
    }
    else
    {
        isLogin = false;
        printf("\nAnda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
    }
}


#endif