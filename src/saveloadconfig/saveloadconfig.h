/* ADT Save and load Config */

#ifndef _SAVELOADCONFIG_H_
#define _SAVELOADCONFIG_H_

#include "../userlist/userlist.h"
#include "../friendship/friendship.h"
#include "../pcolor/pcolor.h"
#include "../screen/screen.h"

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
boolean readDataUsers(UserList *U, Word foldername, Friendship *F)
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
    (*U).Neff = wordToInt(currentWord);

    for (int i = 0; i < (*U).Neff; i++) {
        // Username
        AdvSentence(); currentWord.Length--;
        // printf("ElmtUsername: %s\n", currentWord.TabWord);
        ElmtUsername(*U, i) = currentWord;

        // Password
        AdvSentence(); currentWord.Length--;
        // printf("ElmtPassword: %s\n", currentWord.TabWord);
        ElmtPassword(*U, i) = currentWord;

        // Bio
        AdvSentence(); currentWord.Length--;
        ElmtBio(*U, i) = currentWord;
        // printf("ElmtBio: %s\n", currentWord.TabWord);

        // Nomor Telepon
        ADVWORD(); currentWord.Length--;
        ElmtPhoneNumber(*U, i) = currentWord;
        // printf("Phone Number: %s\n", currentWord.TabWord);

        // Weton
        ADVWORD(); currentWord.Length--;
        ElmtWeton(*U, i) = currentWord;
        // printf("ElmtWeton: %s\n", currentWord.TabWord);

        ADVWORD(); currentWord.Length--;
        // printf("ElmtPrivacy: %s\n", currentWord.TabWord);
        if (isWordStrEqual(currentWord, "Privat", 6)) {
            ElmtPrivacy(*U, i) = PRIVATE;
        } else
        if (isWordStrEqual(currentWord, "Publik", 6)) {
            ElmtPrivacy(*U, i) = PUBLIC;
        } else {
            return false;
        }


        // Gambar
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                ADVWORD(); currentWord.Length--;
                // printf("%c ", currentWord.TabWord[0]);
                PhotoColor(ElmtPhoto(*U, i), j, k) = currentWord.TabWord[0];
                ADVWORD();
                // printf("%c ", currentWord.TabWord[0]);
                PhotoCharacter(ElmtPhoto(*U, i), j, k) = currentWord.TabWord[0];
            }
        }

        
    }
  
    // Friendship Matrix
    for (int j = 0; j < (*U).Neff; j++) {
        for (int k = 0; k < (*U).Neff; k++) {
            ADVWORD();
            FriendshipStatus(*F, j, k) = currentWord.TabWord[0];
        }
    }

    return true;
    // Permintaan Pertemanan
    // Cooming soon
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

boolean loadConfig(Word foldername, UserList *users, Friendship *friendship)
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
    
    if (!readDataUsers(users, foldername, friendship)) {
        errorLog(foldername.Length);
        return false;
    }

    // Memuat kicauan.config
    printf("| Memuat file `config/%s/kicauan.config  |\n", wordToStr(foldername));
    // if (!readDataTweet(users, foldername)) {
    //     errorLog(foldername.Length);
    //     return false;
    // }

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

#endif