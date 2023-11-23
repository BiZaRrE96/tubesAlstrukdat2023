#ifndef _USERLIST_H_
#define _USERLIST_H_

#include "../user/user.h"
#include "../liststatik/liststatik.h"
#include "../photo/photo.h"
#include "../boolean/boolean.h"
#include "../commandmachine/commandmachine.h"
#include "../friendship/friendship.h"

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
#define ElmtFriendRequest(U, i) (U).TabUser[(i)].friendRequest
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


// void displayFriendship(Friendship friendship, int count) {
//     int i, j;
//     for (i = 0; i < count; i++) {
//         for (j = 0; j < count; j++) {
//             printf("%d", FriendshipStatus(friendship, i, j));
//             if (j != count - 1) {
//                 printf(" ");
//             }
//         }
//         if (i != count - 1) {
//             printf("\n");
//         }
//     }
//     printf("\n");
// }


void daftarTeman(User currentUser, UserList userList, Friendship friendship) {
    int UserId = indexOfUser(userList, currentUser.username);
    printf("\n\n");
    
    int count = 0;
    for (int i = 0; i < userList.Neff; i++) {
        if (FriendshipStatus(friendship, UserId, i) == 1 && i != UserId) {
            if (count == 0) {
                printf("Daftar teman %s:\n", wordToStr(currentUser.username));
            }
            count++;


            printf("%d. %s\n", count, wordToStr(ElmtUsername(userList, i)));
            
        }
    }

    if (count == 0) {
        printf("%s belum mempunyai teman\n", wordToStr(currentUser.username));
    }

    printf("\n\n");
}

void hapusTeman(User currentUser, UserList *usersList, Friendship *friendship) {
    // int idxUser = indexOfUser(*usersList, currentUser.username);
    // if (isEmptyFriend(*friendship, idxUser)) {
    //     printf("%s belum mempunyai teman\n", currentUser.username);
    //     return;
    // }

    // printf("\nMasukan nama teman yang ingin dihapus.\n");
    // STARTCOMMAND();
    // int idxFriend = indexOfUser(*usersList, currentWord);

    // if ((FriendshipStatus(*friendship, idxUser, idxFriend) == 1) && (idxFriend != idxUser)) 
    // {
    //     printf("Apakah anda ingin benar-benar menghapus pertemanan ? (YA/TIDAK)\n");
    //     STARTCOMMAND();
    //     if (isWordStrEqual(currentWord.TabWord, "YA", 2)) 
    //     {
    //         FriendshipStatus(*friendship, idxUser, idxFriend) = 0;
    //         FriendshipStatus(*friendship, idxFriend, idxUser) = 0;
    //         printf("Teman berhasil dihapuskan.\n\n");
    //     } else {
    //         printf("Teman batal dihapuskan.\n\n");
    //     }
    //     return;
    // }

    // printf("Teman tidak ditemukan.\n\n");

    
}

void LIHAT_PROFIL(UserList users, Word username, User currentUser, Friendship friendship)
{
    int idxUser = indexOfUser(users, username);
    if (idxUser == -1) {
        printf("\nTidak dapat menemukan pengguna bernama %s.\n", wordToStr(username));
        return;
    } 
    
    User user = Pengguna(users, idxUser);
    if ((Privacy(user) == PRIVATE) && FriendshipStatus(friendship, indexOfUser(users, currentUser.username), idxUser) == 0) {
        printf("\nWah, akun %s diprivat nih. Ikuti dulu yuk untuk bisa melihat profil Tuan Prim!\n", wordToStr(username));
        return;
    }

    printf("\n| Nama: %s\n", wordToStr(ElmtUsername(users, idxUser)));
    printf("| Bio Akun: %s\n", wordToStr(ElmtBio(users, idxUser)));
    printf("| No HP: %s\n", wordToStr(ElmtPhoneNumber(users, idxUser)));
    printf("| Weton: %s\n", wordToStr(ElmtWeton(users, idxUser)));

    printf("| Foto: \n");
    displayPhoto(Photo(user));


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

    Pengguna(*U, listLengthUserlist(*U)-1) = user;

}
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */

void printListUser(UserList U) {
    for (int i = 0; i < U.Neff; i++) {
        printf("%s\n", wordToStr(ElmtUsername(U, i)));
    }
}


/* ********** ADT USERLIST ********** */
void DAFTAR(UserList *users, Friendship *friendship)
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
        DAFTAR(users, friendship);
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
    int idx = indexOfUser(*users, name);
    friendship->friends.rowEff++;
    friendship->friends.colEff++;
    for (int i = 0; i < MAX_USERS; i++)
    {
        FriendshipStatus(*friendship, idx, i) = 0;
        FriendshipStatus(*friendship, i, idx) = 0;
        if (i == idx) FriendshipStatus(*friendship, idx, i) = 1;
        createPhoto(&Photo(Pengguna(*users, idx)));
    }


}

void MASUK(UserList users, User *currentUser, boolean *isLogin)
{
        printf("\n\nMasukkan Nama:\n");
        STARTCOMMAND();

        Word nama = currentWord;
        int IndexUser = indexOfUser(users, nama);

        if (IndexUser == -1)
        {
            printf("Wah, nama yang Anda cari tidak ada. Masukkan nama lain!");
            MASUK(users, currentUser, isLogin);
            return;
        }

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
        printf(". Mari menjelajahi BurBir bersama Ande-Ande Lumut!\n");
        *currentUser = terdaftar;
        *isLogin = true;
        

}

void KELUAR(boolean *isLogin)
{
    *isLogin = false;
    
    printf("\nAnda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
}


void tambahteman (User akunlogin, UserList* listakun, Friendship friendship) {
    prioqueue Q = akunlogin.friendRequest;

    if (!IsEmptyPrioQueue(Q))
    {
        printf("\n\nTerdapat permintaan pertemanan yang belum Anda setujui. Silakan kosongkan daftar permintaan pertemanan untuk Anda terlebih dahulu.\n\n");
        return;
    }

    printf("\n\nMasukan nama pengguna :\n");
    STARTCOMMAND();
    Word namaTeman = currentWord;
    int idxUser = indexOfUser(*listakun, akunlogin.username);
    int idxReceived = indexOfUser(*listakun, currentWord);

    if (idxReceived == -1)
    {
        printf("Pengguna bernama %s tidak ditemukan.\n", wordToStr(currentWord));
        return;
    }

    User calonTeman = Pengguna(*listakun, idxReceived);

    if (idxUser == idxReceived)
    {
        printf("Anda tidak bisa berteman dengan diri anda sendiri.\n");
        return;
    }

    if (FriendshipStatus(friendship, idxUser, idxReceived) == 1)
    {
        printf("Kalian sudah berteman.\n");
        return;
    }

    if (isHaveSentRequest(FriendRequest(calonTeman), idxUser))
    {
        printf("Permintaan pertemanan sudah pernah dilakukan, tunggu hingga permintaan Anda disetujui.\n");
        return;
    }


    // Kirim permintaan pertemanan
    friend sender = {idxUser, countFriend(friendship, idxUser)};
    EnqueuePrioQueue(&listakun->TabUser[idxReceived].friendRequest, sender);
    printf("Permintaan pertemanan kepada %s telah dikirim. Tunggu beberapa saat hingga permintaan Anda disetujui.\n\n\n", wordToStr(ElmtUsername(*listakun, idxReceived)));

    
    // if (isWordEqual(namaTeman, akunlogin.username)) {
    //     printf("Anda tidak bisa berteman dengan diri anda sendiri.\n");
    // } else 
    // if (FriendshipStatus(friendship, i, k) == 1) 
    // {
    //     printf("Kalian sudah berteman.");
    // } else 
    // if (isHaveSentRequest(FriendRequest(Pengguna(list)) , i)) 
    // {
    //     printf("Permintaan pertemanan sudah pernah dilakukan, tunggu hingga permintaan Anda disetujui.\n");
    // } else 
    // {
    //     boolean found = false;
    //     for (int j = 0;j < FRIENDSHIPCAPACITY;j++) {
    //         if (isWordEqual(namaTeman,ElmtUsername(listpengguna,j))) {
    //             printf("Permintaan pertemanan kepada");
    //             printf("%s ", namaTeman);
    //             printf("telah dikirim. Tunggu beberapa saat hingga permintaan Anda disetujui.\n");
    //             EnqueuePrioQueue(&Q, Teman);
    //             found = true;
    //         } else
    //         {
    //             found = false;
    //         }
    //     }
    //     if (!found) {
    //         printf("Pengguna bernama ");
    //         printf("%s ", namaTeman);
    //         printf("tidak ditemukan.\n");
    //     }
    // }
    
}

void daftarpermintaanteman (User akunlogin, UserList* listakun) {
    // UserList listpengguna;
    // prioqueue qteman, qpending;

    // int userID = indexOfUser(listpengguna, akunlogin.username);

    // Enqueueuserprio(*Q, userID, &qteman, &qpending);
    // PrintPrioQueue(qteman, listakun);
    // concatenationprio(qteman, qpending, Q);
}

void setujuipermintaanteman (User akunlogin, UserList* listakun, friend* Teman, prioqueue* Q) {
    // prioqueue qteman, qpending;
    // UserList listpengguna;
    // Friendship friendship;
    
    //     int userID = indexOfUser(listpengguna, akunlogin.username);
    //     int friendID;
    //     Word namaTeman;
    //     EnqueueUserPrioQueue(*Q, userID, &qteman, &qpending);
    //     printf("%s\n", namaTeman);
    //     printf("Apakah anda ingin menyetujui permintaan pertemanan ini ? (ya/tidak)\n");
    //     STARTWORD();
    //     if (IsWordEqual(currentWord, 'tidak')) 
    //     {
    //         DequeuePrioQueue(&qpending, &Teman);
    //         printf("Berhasil menolak permintaan pertemanan dari ");
    //         printf("%s.\n", namaTeman);
    //     } else if (IsWordEqual(currentWord, 'ya')) 
    //     {
    //         DequeuePrioQueue(&qpending, &Teman);
    //         FriendshipStatus(friendship, userID, friendID) = 1;
    //         FriendshipStatus(friendship, friendID, userID) = 1;
    //         printf("%s ", namaTeman);
    //         printf("telah menjadi temanmu.\n");
    //     } else
    //     {
    //         printf("Command tidak sesuai.\n");
    //     }
    
} 

#endif