#ifndef _SAVELOADCONFIG_H_
#define _SAVELOADCONFIG_H_

#include "../userlist/userlist.h"
#include "../friendship/friendship.h"
#include "../pcolor/pcolor.h"
#include "../screen/screen.h"

Word Direc(Word foldername, char filename[], int lenFilename) {
    Word result = foldername;
    // printf("%s\n", foldername.TabWord);

    result = insertStrToWord(result, "../config/", 10, 0);
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
    // printf("Folder = %s\n", foldername.TabWord);
    // printf("Memulai membuka file %s {%d}\n", wordToStr(Direc(foldername, "pengguna.config", 15)), Direc(foldername, "pengguna.config", 15).Length);
    
    // Cek dahulu apakah foile ada   
    Word directory = Direc(foldername, "pengguna.config", 15); 
    if (fopen(wordToStr(directory), "r") == NULL) {
        return false;
    }

    STARTWORDFILE(wordToStr(directory));
    printf("Membuka file");

    if (pita == NULL) {
        return false;
    }
    (*U).Neff = strToInt(currentWord);
    // printf("Banyak User: %d\n", (*U).Neff);
    for (int i = 0; i < (*U).Neff; i++) {
        // Usernmae
        AdvSentence(); currentSentence.Length--;
        // printf("ElmtUsername: %s\n", currentSentence.TabSentence);
        ElmtUsername(*U, i) = currentSentence;

        // Password
        AdvSentence(); currentSentence.Length--;
        // printf("ElmtPassword: %s\n", currentSentence.TabSentence);
        ElmtPassword(*U, i) = currentSentence;

        // Bio
        AdvSentence(); currentSentence.Length--;
        ElmtBio(*U, i) = currentSentence;
        // printf("ElmtBio: %s\n", currentSentence.TabSentence);

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
        if (isWordStrEqual(currentWord, "Privat")) {
            ElmtPrivacy(*U, i) = PRIVAT;
        } else
        if (isWordStrEqual(currentWord, "Publik")) {
            ElmtPrivacy(*U, i) = PUBLIC;
        } else {
            return false;
        }

        // printf("Memuat gambar\n");

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
            // printf("\n");
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

#endif