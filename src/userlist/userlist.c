#include "userlist.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateUserList(UserList *U)
/* I.S. U sembarang */
/* F.S. U terdefinisi dengan Neff(U) = 0 */
{
    Neff(*U) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLengthUserlist(UserList U)
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list U kosong */
{
    return Neff(U);
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfUser(UserList U, Word nama)
/* Search apakah ada elemen List U yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(u,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */
{
    int i = 0;
    boolean found = false;
    while (!found && i < Neff(U))
    {
        if (CompareWord(ElmtUsername(U, i), nama))
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    if (found)
    {
        return i;
    }
    else
    {
        return IDX_UNDEF;
    }
}

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLastUser(UserList *U, User user)
/* Proses: Menambahkan user sebagai elemen terakhir List */
/* I.S. List U boleh kosong, tetapi tidak penuh */
/* F.S. user adalah elemen terakhir u yang baru */
{
    Neff(*U)++;
    User(*U, listLengthUserlist(*U)) = user;
}

void DAFTAR()
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

        int index = indexOfUser(users, name);
        Word pass;
        boolean PassCheck = false;

        if (index != IDX_UNDEF)
        {
            printf("Wah, sayang sekali nama tersebut telah diambil.");
            DAFTAR();
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
        insertLastUser(&users, NewUser);
    }

    else
    {
        printf("\nAnda sudah masuk, keluar terlebih dahulu untuk mendaftar\n");
    }
}

void MASUK()
{
    if (!isLogin)
    {
        printf("\n\nMasukkan Nama:\n");
        STARTCOMMAND();

        Word nama = currentWord;
        int IndexUser = indexOfUser(users, nama);

        if (IndexUser == IDX_UNDEF)
        {
            printf("Wah, nama yang Anda cari tidak ada. Masukkan nama lain!");
            MASUK();
        }
        else
        {
            User terdaftar = Pengguna(users, IndexUser);
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
