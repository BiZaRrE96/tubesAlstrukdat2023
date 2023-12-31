/* ADT Save and load Config */

#ifndef _SAVELOADCONFIG_H_
#define _SAVELOADCONFIG_H_

#include "../userlist/userlist.h"
#include "../friendship/friendship.h"
// #include "../pcolor/pcolor.h"
#include "../screen/screen.h"
#include "../kicau/kicau.h"
#include "../kicau/draf.h"
#include "../kicau/utas.h"
#include "../prioqueuechar/prioqueuechar.h"
#include <sys/stat.h>

extern UserList users;
extern Friendship friendship;
extern KicauList kicauan;
extern DrafList drafList;
extern ListUtas utasList;

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
        CreateEmpty(&ElmtDrafList(drafList, i));
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
}

boolean readDataKicauan(Word foldername) {
    Word directory = Direc(foldername, "kicauan.config", 14); 
    if (fopen(wordToStr(directory), "r") == NULL) {
        return false;
    }

    STARTWORDFILE(wordToStr(directory));

    createKicauList(&kicauan, 100);
    Count(kicauan) = wordToInt(currentWord);

    for (int i = Count(kicauan); i > 0; i--) {
        createBalasanList(&GetBalasan(kicauan, i));
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

boolean readDataBalasan(Word foldername) {
    Word directory = Direc(foldername, "balasan.config", 14); 
    if (fopen(wordToStr(directory), "r") == NULL) {
        return false;
    }

    STARTWORDFILE(wordToStr(directory));

    int N = wordToInt(currentWord);

    while (N--) {
        ADVWORD(); currentWord.Length--;
        int idKicau = wordToInt(currentWord);
        // printf("idKicau: %d\n", idKicau);

        ADVWORD(); currentWord.Length--;
        int M = wordToInt(currentWord);
        // printf("M: %d\n", M);

        while (M--) {
            // Proses pengambilan data
            ADVWORD();
            int parent = wordToInt(currentWord);
            // printf("parent: %d\n", parent);
            
            ADVWORD(); currentWord.Length--;
            int idBalasan = wordToInt(currentWord);
            // printf("idBalasan: %d\n", idBalasan);

            AdvSentence(); currentWord.Length--;
            Word text = currentWord;
            // printf("text: %s\n", wordToStr(text));

            AdvSentence(); currentWord.Length--;
            Word author = currentWord;
            // printf("author: %s\n", wordToStr(author));

            AdvSentence(); currentWord.Length--;
            DATETIME time;
            if (!parseWordToDatetime(currentWord, &time)) {
                return false;
            }
            // printf("time: "); TulisDATETIME(time); printf("\n");

            // BalasanList balasan = GetBalasan(kicauan, idKicau);
            readBalasanFile(&GetBalasan(kicauan, idKicau), author, text, time, parent, idBalasan);
            
        }
    }
    return true;
}

boolean readDataDraf(Word foldername) {
    Word directory = Direc(foldername, "draf.config", 11); 
    if (fopen(wordToStr(directory), "r") == NULL) {
        printf("File tidak ditemukan\n");
        return false;
    }

    STARTWORDFILE(wordToStr(directory));


    // if (!isWordInt(currentWord))
    //     return false;

    int N = wordToInt(currentWord);

    while (N--) {
        AdvSentence(); currentWord.Length--;
        // Ambil sebuah integer pada elemen paling kiri currentWord
        Word M; M.Length = 0;
        int itr = currentWord.Length - 1;
        // printf("currentWord: %s\n", wordToStr(currentWord));

        while (currentWord.TabWord[itr] != ' ') {
            M.TabWord[M.Length] = currentWord.TabWord[itr];
            M.Length++;
            itr--;
            currentWord.Length--;
        }

        // Membalikkan M
        for (int i = 0; i < M.Length/2; i++) {
            char temp = M.TabWord[i];
            M.TabWord[i] = M.TabWord[M.Length - i - 1];
            M.TabWord[M.Length - i - 1] = temp;
        }
        

        int nDraf = wordToInt(M);

        currentWord.Length--;
        Word username = currentWord;
        int idxUser = indexOfUser(users, username);

        KICAU k[nDraf];

        for (int i = 0; i < nDraf; i++) {
            AdvSentence(); currentWord.Length--;
            Word text = currentWord;

            AdvSentence(); currentWord.Length--;
            DATETIME time;

            if (!parseWordToDatetime(currentWord, &time)) {
                return false;
            }

            k[i].Text = text;
            k[i].Time = time;
            k[i].Author = username;

        }

        for (int i = nDraf - 1; i >= 0; i--) {
            Push(&ElmtDrafList(drafList, idxUser), k[i]);
        }
        // KICAU k;
        // k.Text = text;
        // k.Time = time;
        // k.Author = username;

        // Push(&ElmtDrafList(drafList, idxUser), k);
    }

    return true;

}

boolean readDataUtas(Word foldername) {
    Word directory = Direc(foldername, "utas.config", 11); 
    if (fopen(wordToStr(directory), "r") == NULL) {
        printf("File tidak ditemukan\n");
        return false;
    }

    STARTWORDFILE(wordToStr(directory));

    int N = wordToInt(currentWord);
    // printf("N = %d\n", N);
    for (int i = 0; i < N; i++) {
        ADVWORD(); currentWord.Length--;
        int idKicau = wordToInt(currentWord);
        // printf("idKicau: %d\n", idKicau);

        ADVWORD(); currentWord.Length--;
        int M = wordToInt(currentWord);
        // printf("M: %d\n", M);

        Utas utas;
        utas.IDKicau = idKicau;
        utas.IDUtas = i;
        createEmptyUtas(&utas);

        insertFirstUtas(&utas, GetKicauan(kicauan, idKicau));

        for (int j = 0; j < M; j++) {
            KICAU k;
            AdvSentence(); currentWord.Length--;
            // printf("currentWord: %s\n", wordToStr(currentWord));
            k.Text = currentWord;

            AdvSentence(); currentWord.Length--;
            k.Author = currentWord;

            AdvSentence(); currentWord.Length--;
            DATETIME time;
            if (!parseWordToDatetime(currentWord, &time)) {
                return false;
            }
            k.Time = time;

            insertLastUtas(&utas, k);
        }

        insertUtas(&utasList, utas);
        // CETAK_UTAS(utasList, i+1, Pengguna(users, indexOfUser(users, utas.p->info.Author)));

        
    }

    return true;
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

boolean writeDataUsers(Word foldername) {
    Word directory = Direc(foldername, "pengguna.config", 15);
    FILE *f = fopen(wordToStr(directory), "w");
    // printf("directory: %s\n", wordToStr(directory));

    // Cek apakah file sudah ada, jika sudah ada maka ganti dengan yang baru
    if (f == NULL) {
        return false;
    }

    fprintf(f, "%d\n", (users).Neff);
    // print("users.Neff: %d\n", (users).Neff);

    for (int i = 0; i < (users).Neff; i++) {
        // print("User : %s\n", wordToStr(ElmtUsername(users, i)));
        fprintf(f, "%s\n", wordToStr(ElmtUsername(users, i)));
        fprintf(f, "%s\n", wordToStr(ElmtPassword(users, i)));
        fprintf(f, "%s\n", wordToStr(ElmtBio(users, i)));
        fprintf(f, "%s\n", wordToStr(ElmtPhoneNumber(users, i)));
        fprintf(f, "%s\n", wordToStr(ElmtWeton(users, i)));
        if (ElmtPrivacy(users, i) == PRIVATE) {
            fprintf(f, "Privat\n");
        } else {
            fprintf(f, "Publik\n");
        }

        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (k == 4) {
                    fprintf(f, "%c %c", PhotoColor(ElmtPhoto(users, i), j, k), PhotoCharacter(ElmtPhoto(users, i), j, k));
                } else {
                    fprintf(f, "%c %c ", PhotoColor(ElmtPhoto(users, i), j, k), PhotoCharacter(ElmtPhoto(users, i), j, k));
                }
            }
            fprintf(f, "\n");
        }

        
    }

    // Friendship Matrix
    for (int j = 0; j < (users).Neff; j++) {
        for (int k = 0; k < (users).Neff; k++) {
            if (k == (users).Neff - 1) {
                fprintf(f, "%d", FriendshipStatus(friendship, j, k));
            } else {
                fprintf(f, "%d ", FriendshipStatus(friendship, j, k));
            }
        }
        fprintf(f, "\n");
    }

    // print("Pembacaan friendSHIP\n");
    // Jelajahi masing-masing elemen FriendRequest pada user
    int n = 0;
    int sender[10000];
    int receiver[10000];
    int numFriend[10000];

    for (int i = 0; i < (users).Neff; i++) {
        prioqueue temp = ElmtFriendRequest(users, i);
        while (!IsEmptyPrioQueue(temp)) {
            friend request;
            DequeuePrioQueue(&temp, &request);
            sender[n] = request.IDrecieve;
            receiver[n] = i;
            numFriend[n] = request.Friendcount;

            n++;
        }
    }

    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d %d %d\n", sender[i], receiver[i], numFriend[i]);
    }

    fprintf(f, ";");
    fclose(f);
    return true;
}

boolean writeDataKicauan(Word foldername) {
    Word directory = Direc(foldername, "kicauan.config", 14);
    FILE *f = fopen(wordToStr(directory), "w");
    // print("directory: %s\n", wordToStr(directory));

    // Cek apakah file sudah ada, jika sudah ada maka ganti dengan yang baru
    if (f == NULL) {
        return false;
    }

    fprintf(f, "%d\n", Count(kicauan));
    // print("Count(kicauan): %d\n", Count(kicauan));

    for (int i = 1; i <= Count(kicauan); i++) {
        fprintf(f, "%d\n", i);
        fprintf(f, "%s\n", wordToStr(GetText(kicauan, i)));
        fprintf(f, "%d\n", GetLike(kicauan, i));
        fprintf(f, "%s\n", wordToStr(GetAuthor(kicauan, i)));
        fprintf(f, "%s\n", wordToStr(parseDatetimeToWord(GetTime(kicauan, i))));
    }

    fprintf(f, ";");
    fclose(f);
    return true;
}

boolean writeDataBalasan(Word foldername) {
    Word directory = Direc(foldername, "balasan.config", 14);
    FILE *f = fopen(wordToStr(directory), "w");
    // print("directory: %s\n", wordToStr(directory));

    // Cek apakah file sudah ada, jika sudah ada maka ganti dengan yang baru
    if (f == NULL) {
        return false;
    }

    // Count balasan yang tidak kosong
    int N = 0;
    for (int i = 1; i <= Count(kicauan); i++) {
        if (GetBalasan(kicauan, i).countEvo > 0) 
            N++;
    }

    fprintf(f, "%d\n", N);

    for (int i = 1; i <= Count(kicauan); i++) {
        if (GetBalasan(kicauan, i).countEvo > 0) {
            fprintf(f, "%d\n", i);
            fprintf(f, "%d\n", GetBalasan(kicauan, i).countEvo);

            for (int j = 1; j <= GetBalasan(kicauan, i).countEvo; j++) {
                BALASAN *b = getBalasan(GetBalasan(kicauan, i), j);
                fprintf(f, "%d %d\n", b->parentID, b->IdBalas);
                fprintf(f, "%s\n", wordToStr(b->Text));
                fprintf(f, "%s\n", wordToStr(b->Author));
                fprintf(f, "%s\n", wordToStr(parseDatetimeToWord(b->Time)));
            }
        }
    }

    fprintf(f, ";");
    fclose(f);
    return true;
}

boolean writeDataUtas(Word foldername) {
    Word directory = Direc(foldername, "utas.config", 11);

    FILE *f = fopen(wordToStr(directory), "w");

    if (f == NULL) {
        return false;
    }

    fprintf(f, "%d\n", len(utasList));

    for (int i = 0; i < len(utasList); i++) {
        Utas utas = GetUtas(utasList, i);
        fprintf(f, "%d\n", utas.IDKicau);
        
        fprintf(f, "%d\n", lengthUtas(utas)-1);
        AddressUtas p = utas.p->next;
        for (int j = 1; j < lengthUtas(utas); j++) {
            fprintf(f, "%s\n", wordToStr(p->info.Text));
            fprintf(f, "%s\n", wordToStr(p->info.Author));
            fprintf(f, "%s\n", wordToStr(parseDatetimeToWord(p->info.Time)));
            
        }
    }

    fprintf(f, ";");
    fclose(f);

    return true;

}

boolean writeDataDraf(Word foldername) {
    Word directory = Direc(foldername, "draf.config", 11);

    FILE *f = fopen(wordToStr(directory), "w");

    if (f == NULL) {
        return false;
    }

    int N;
    for (int i = 0; i < (users).Neff; i++) {
        if (!IsEmptyDraf(ElmtDrafList(drafList, i))) {
            N++;
        }
    }

    fprintf(f, "%d\n", N);

    for (int i = 0; i < (users).Neff; i++) {
        if (!IsEmptyDraf(ElmtDrafList(drafList, i))) {
            fprintf(f, "%s", wordToStr(ElmtUsername(users, i)));
            
            int len = 0;

            DrafStack temp = ElmtDrafList(drafList, i);
            while (!IsEmptyDraf(temp)) {
                len++;
                KICAU k;
                Pop(&temp, &k);
            }

            fprintf(f, " %d\n", len);

            temp = ElmtDrafList(drafList, i);
            while (!IsEmptyDraf(temp)) {
                KICAU k;
                Pop(&temp, &k);
                fprintf(f, "%s\n", wordToStr(k.Text));
                fprintf(f, "%s\n", wordToStr(parseDatetimeToWord(k.Time)));
            }
        }
    }

    fprintf(f, ";");
    fclose(f);

    return true;

}

boolean saveConfig(Word foldername) {
    START_YELLOW;
    for (int i = 0; i < (42 + foldername.Length); i++) {
        printf("-");
    }

    // Jika folder belum ada, maka buat folder
    Word folderdirectory = Direc(foldername, "", 0);
    if (fopen(wordToStr(folderdirectory), "r") == NULL) {
        mkdir(wordToStr(folderdirectory), 0777);
    }

    // Jika sudah ada folder, maka replace file dengan data yang baru
    // Memuat pengguna.config
    printf("\n| Menyimpan file `config/%s/pengguna.config |\n", wordToStr(foldername));
    if (!writeDataUsers(foldername)) {
        errorLog(foldername.Length);
        return false;
    }

    // Memuat kicauan.config
    printf("| Menyimpan file `config/%s/kicauan.config  |\n", wordToStr(foldername));
    if (!writeDataKicauan(foldername)) {
        errorLog(foldername.Length);
        return false;
    }

    // Memuat balasan.config
    printf("| Menyimpan file `config/%s/balasan.config  |\n", wordToStr(foldername));
    if (!writeDataBalasan(foldername)) {
        errorLog(foldername.Length);
        return false;
    }

    // Memuat draf.config
    printf("| Menyimpan file `config/%s/draf.config     |\n", wordToStr(foldername));
    if (!writeDataDraf(foldername)) {
        errorLog(foldername.Length);
        return false;
    }

    // Memuat utas.config
    printf("| Menyimpan file `config/%s/utas.config     |\n", wordToStr(foldername));
    if (!writeDataUtas(foldername)) {
        errorLog(foldername.Length);
        return false;
    }

    for (int i = 0; i < (42 + foldername.Length); i++) {
        printf("-");
    }
    printf("\n\n");
    return true;

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
    if (!readDataBalasan(foldername)) {
        errorLog(foldername.Length);
        return false;
    }

    // Memuat draf.config
    printf("| Memuat file `config/%s/draf.config     |\n", wordToStr(foldername));
    if (!readDataDraf(foldername)) {
        errorLog(foldername.Length);
        return false;
    }

    // Memuat utas.config
    printf("| Memuat file `config/%s/utas.config     |\n", wordToStr(foldername));
    if (!readDataUtas(foldername)) {
        errorLog(foldername.Length);
        return false;
    }

    for (int i = 0; i < (40 + foldername.Length); i++) {
        printf("-");
    }
    printf("\n\n");

    STOP_COLOR;
    return true;
}


void Simpan() {
    Word foldername;
    printf("Masukkan nama folder yang hendak disimpan: ");
    STARTCOMMAND();
    foldername = currentWord;
    printf("\n");
    if (!saveConfig(foldername)) {
        printf("Gagal meyimpan\n");
    } else {
        printf("Penyimpanan selesai!\n");
    }
    printf("\n\n");
    // saveConfig(foldername, users, friendship, kicauan);

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