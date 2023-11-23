/* ADT Save and load Config */

#ifndef _SAVELOADCONFIG_H_
#define _SAVELOADCONFIG_H_

#include "../userlist/userlist.h"
#include "../friendship/friendship.h"
// #include "../pcolor/pcolor.h"
#include "../screen/screen.h"
#include "../kicau/kicau.h"

extern UserList users;
extern Friendship friendship;
extern KicauList kicauan;

Word Direc(Word foldername, char filename[], int lenFilename)
/*
    I.S. foldername dan filename terdefinisi
    F.S. Mengembalikan foldername + filename
*/
{
    Word result = foldername;
    // printf("%s\n", foldername.TabWord);

    result = insertStrToWord(result, "config/", 7, 0);
    result = insertStrToWord(result, "/", 1, result.Length);
    result = insertStrToWord(result, filename, lenFilename, result.Length);

    return result;
}

// Proses Mengambil Konfigurasi Pengguna
boolean readDataUsers(Word foldername)
// I.S. U sembarang
// F.S. U terisi data pengguna dari file
//      Kembalian merupakan pesan error (true atau false)
{
    // Membuka file `"../config/" + filename + "pengguna.config"`
    
    // Cek dahulu apakah foile ada   
    Word directory = Direc(foldername, "pengguna.config", 15); 
    if (fopen(wordToStr(directory), "r") == NULL) {
        return false;
    }

    STARTWORDFILE(wordToStr(directory));
    // printf("File ditemukan\n");
    (users).Neff = wordToInt(currentWord);
    // setSizeFriendship(F, wordToInt(currentWord));

    for (int i = 0; i < (users).Neff; i++) {
        // Username
        AdvSentence(); currentWord.Length--;
        // printf("ElmtUsername: %s\n", currentWord.TabWord);
        ElmtUsername(users, i) = currentWord;

        // Password
        AdvSentence(); currentWord.Length--;
        // printf("ElmtPassword: %s\n", currentWord.TabWord);
        ElmtPassword(users, i) = currentWord;

        // Bio
        AdvSentence(); currentWord.Length--;
        ElmtBio(users, i) = currentWord;
        // printf("ElmtBio: %s\n", currentWord.TabWord);

        // Nomor Telepon
        ADVWORD(); currentWord.Length--;
        ElmtPhoneNumber(users, i) = currentWord;
        // printf("Phone Number: %s\n", currentWord.TabWord);

        // Weton
        ADVWORD(); currentWord.Length--;
        ElmtWeton(users, i) = currentWord;
        // printf("ElmtWeton: %s\n", currentWord.TabWord);

        ADVWORD(); currentWord.Length--;
        // printf("ElmtPrivacy: %s\n", currentWord.TabWord);
        if (isWordStrEqual(currentWord, "Privat", 6)) {
            ElmtPrivacy(users, i) = PRIVATE;
        } else
        if (isWordStrEqual(currentWord, "Publik", 6)) {
            ElmtPrivacy(users, i) = PUBLIC;
        } else {
            return false;
        }


        // Gambar
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                ADVWORD(); currentWord.Length--;
                // printf("%c ", currentWord.TabWord[0]);
                PhotoColor(ElmtPhoto(users, i), j, k) = currentWord.TabWord[0];
                ADVWORD();
                // printf("%c ", currentWord.TabWord[0]);
                PhotoCharacter(ElmtPhoto(users, i), j, k) = currentWord.TabWord[0];
            }
        }


        MakeEmptyPrioQueue(&ElmtFriendRequest(users, i), 20);
    }
  
    // Friendship Matrix
    for (int j = 0; j < (users).Neff; j++) {
        for (int k = 0; k < (users).Neff; k++) {
            ADVWORD();
            FriendshipStatus(friendship, j, k) = currentWord.TabWord[0] - '0';
        }
    }

    // Untuk tiap permintaan pertemanan, disimpan ID permintaan pertemanan, 
    // dengan secara beturut-turut dari kiri adalah ID pengguna yang 
    // meminta pertemanan, ID pengguna yang diminta pertemanan, 
    // dan jumlah teman saat ID pengguna meminta pertemanan.
    

    ADVWORD();
    int Q = wordToInt(currentWord);
    while (Q--) {
        int idSender, idReceiver, numFriend;
        ADVWORD(); idSender = wordToInt(currentWord);
        ADVWORD(); idReceiver = wordToInt(currentWord);
        ADVWORD(); numFriend = wordToInt(currentWord);

        friend request = {idSender, numFriend};  
        EnqueuePrioQueue(&ElmtFriendRequest(users, idReceiver), request);
    }


    return true;
    // Permintaan Pertemanan
    // Cooming soon
}

boolean readDataKicauan(Word foldername) {
    Word directory = Direc(foldername, "kicauan.config", 15); 
    if (fopen(wordToStr(directory), "r") == NULL) {
        return false;
    }

    STARTWORDFILE(wordToStr(directory));

    createKicauList(&kicauan, 100);
    Count(kicauan) = wordToInt(currentWord);

    for (int i = Count(kicauan); i > 0; i--) {
        ADVWORD(); currentWord.Length--;
        int idKicau = wordToInt(currentWord);

        AdvSentence(); currentWord.Length--;
        GetText(kicauan, idKicau) = currentWord;

        ADVWORD(); currentWord.Length--;
        GetLike(kicauan, idKicau) = wordToInt(currentWord);

        AdvSentence(); currentWord.Length--;
        GetAuthor(kicauan, idKicau) = currentWord;

        AdvSentence(); currentWord.Length--;
        if (!parseWordToDatetime(currentWord, &GetTime(kicauan, idKicau))) {
            return false;
        }
    }

}

void errorLog(int lenFoldername)
/* Menampilkan pesan kesalahan */
{
    print_string_yellow("| ");
    print_string_red("Terjadi Kesalahan");
    
    for (int i = 0; i < ((40-19-1) + lenFoldername); i++) {
        printf(" ");
    }

    print_string_yellow("|\n");

    START_YELLOW;
    for (int i = 0; i < (40 + lenFoldername); i++) {
        printf("-");
    }
    printf("\n");
    STOP_COLOR;
}

boolean loadConfig(Word foldername)
/*
    I.S. Sembarang
    F.S. Konfigurasi pengguna, kicauan, balasan, dan draf berhasil dimuat
*/
{
    START_YELLOW;
    for (int i = 0; i < (40 + foldername.Length); i++) {
        printf("-");
    }

    // Memuat pengguna.config
    printf("\n| Memuat file `config/%s/pengguna.config |\n", wordToStr(foldername));
    
    if (!readDataUsers(foldername)) {
        errorLog(foldername.Length);
        return false;
    }

    // Memuat kicauan.config
    printf("| Memuat file `config/%s/kicauan.config  |\n", wordToStr(foldername));
    if (!readDataKicauan(foldername)) {
        errorLog(foldername.Length);
        return false;
    }

    // Memuat balasan.config
    printf("| Memuat file `config/%s/balasan.config  |\n", wordToStr(foldername));
    // if (!readDataReply(users, foldername)) {
    //     errorLog(foldername.Length);
    //     return false;
    // }

    // Memuat draf.config
    printf("| Memuat file `config/%s/draf.config     |\n", wordToStr(foldername));
    // if (!readDataDraft(users, foldername)) {
    //     errorLog(foldername.Length);
    //     return false;
    // }

    for (int i = 0; i < (40 + foldername.Length); i++) {
        printf("-");
    }
    printf("\n\n");

    STOP_COLOR;
    return true;
}


void Muat() {
    Word foldername;
    printf("Masukkan nama folder yang hendak dimuat: ");
    STARTCOMMAND();
    foldername = currentWord;
    printf("\n");
    if (!loadConfig(foldername)) {
        printf("Tidak ada folder yang dimaksud!\n");
    } else {
        printf("Pemuatan selesai!\n");
    }
    printf("\n\n");
    // loadConfig(foldername, users, friendship, kicauan);
}

#endif