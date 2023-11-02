#include "../userlist/userlist.h"

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
