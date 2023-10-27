/* ADT Word Machine */
/* Definisi Mesin Word: Model Akuisisi Versi I */

#ifndef __WORDMACHINE_H__
#define __WORDMACHINE_H__

#include "../CharMachine/charmachine.h"
#include <stdlib.h>

#define NMax 50
#define BLANK ' '
#define ENTER '\n'
#define MARKCOMMAND ';'

typedef struct
{
   char TabWord[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
   int Length;
} Word;

/* State Mesin Word */
static boolean EndWord;
static Word currentWord;

/* ********* AKUISISI ********* */
void IgnoreBlanks()
{
    /* Mengabaikan satu atau beberapa BLANK
       I.S. : currentChar sembarang
       F.S. : currentChar ≠ BLANK,currentChar = MARK, atau currentChar = ENTER */
    while ((currentChar == BLANK) || (currentChar == ENTER))
    {
        ADV();
    }
}

void CopyWord()
{
    /* Mengakuisisi kata, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari kata
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = BLANK atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
              Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
    currentWord.Length = 0;
    while (currentChar != BLANK && currentChar != MARK && currentChar != ENTER)
    {
        if (currentWord.Length < NMax)
        { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        }
        else
            break;
    }
}

void STARTWORD()
{
    /* I.S. : currentChar sembarang
       F.S. : EndWord = true, dan currentChar = MARK;
              atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
              currentChar karakter pertama sesudah karakter terakhir kata */
    START();
    IgnoreBlanks();
    EndWord = false;
    if (currentChar == MARK)
    {
        EndWord = true;
    }
    else
    {
        EndWord = false;
        CopyWord();
    }
}

void STARTWORDFILE(char filename[])
{
    /* I.S. : currentChar sembarang
       F.S. : EndWord = true, dan currentChar = MARK;
              atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
              currentChar karakter pertama sesudah karakter terakhir kata */
    STARTFILE(filename);
    IgnoreBlanks();
    EndWord = false;
    if (currentChar == MARK)
    {
        EndWord = true;
    }
    else
    {
        EndWord = false;
        CopyWord();
    }
}

void ADVWORD()
{
    /* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
       F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
              currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
              Jika currentChar = MARK, EndWord = true.
       Proses : Akuisisi kata menggunakan procedure CopyWord */
    IgnoreBlanks();
    if (currentChar == MARK)
    {
        EndWord = true;
    }
    else
    {
        // EndWord = false;
        CopyWord();
        IgnoreBlanks();
    }
}

/* ********* KELOMPOK OPERASI WORD ********* */
int strToInt(Word w)
/*
    I.S. w terdefinisi sebagai string angka
    F.S. Mengembalikan nilai integer dari hasil konversi w
*/
{
    int i, result = 0;
    for (i = w.Length-1; i >= 0; i--)
    {
        if (w.TabWord[i] >= '0' && w.TabWord[i] <= '9')
            result = result * 10 + (w.TabWord[i] - '0');
    }
    return result;
}

boolean isWordInt(Word w) {
/*
    I.S. w sembarang
    F.S. Mengembalikan true jika w adalah string angka, false jika tidak
*/
    for (int i = 0; i < w.Length; i++) {
        if (w.TabWord[i] < '0' || w.TabWord[i] > '9') {
            return false;
        }
    }

    return true;
}  

boolean isWordStrEqual(Word W, char s[], int len) 
/*
    I.S. W dan s terdefinisi
    F.S. Mengembalikan true jika W.TabWord dan s sama, false jika tidak
*/
{
    // Jika panjangnya berbeda, maka pasti tidak sama
    if (W.Length != len) {
        return false;
    }

    // Cek satu per satu setiap karakter pada W.TabWord dan s
    for (int i = 0; i < W.Length; i++) {
        if (W.TabWord[i] != s[i]) {
            return false;
        }
    }

    return true;
}

char* wordToStr(Word W)
/*
    I.S. W terdefinisi
    F.S. Mengembalikan string yang berisi W.TabWord
*/
{
    char* result = (char*) malloc(W.Length * sizeof(char));
    for (int i = 0; i < W.Length; i++) {
        result[i] = W.TabWord[i];
    }

    return result;
}

Word insertStrToWord(Word W, char str[], int lenStr, int idx)
/*
    I.S. W dan str terdefinisi
    F.S. Mengembalikan Word yang merupakan hasil penyisipan str pada W pada indeks idx
*/
{
    Word result;
    result.Length = W.Length + lenStr;

    for (int i = 0; i < idx; i++) {
        result.TabWord[i] = W.TabWord[i];
    }

    for (int i = 0; i < lenStr; i++) {
        result.TabWord[i + idx] = str[i];
    }

    for (int i = idx; i < W.Length; i++) {
        result.TabWord[i + lenStr] = W.TabWord[i];
    }

    return result;
}

Word mergeWord(Word wLeft, Word wRight)
/*
    I.S. wLeft dan wRight terdefinisi
    F.S. Mengembalikan Word yang merupakan hasil penggabungan wLeft dan wRight
*/
{
    Word result;
    result.Length = wLeft.Length + wRight.Length;

    for (int i = 0; i < wLeft.Length; i++) {
        result.TabWord[i] = wLeft.TabWord[i];
    }

    for (int i = 0; i < wRight.Length; i++) {
        result.TabWord[i + wLeft.Length] = wRight.TabWord[i];
    }

    return result;
}

/* ********* AKUISISI COMMAND ********* */
void CopyCommand() {
    /* Mengakuisisi kata, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari kata
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = BLANK atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
              Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
    currentWord.Length = 0;
    while (currentChar != MARKCOMMAND)
    {
        if (currentWord.Length < NMax)
        { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        }
        else
            break;
    }
}

void STARTCOMMAND() {
    START();
    IgnoreBlanks();

    if (currentChar == MARKCOMMAND) {
        EndWord = true;
    } else {
        EndWord = false;
        CopyCommand();
    }
}

/* ********* KELOMPOK OPERASI COMMAND ********* */
boolean isCommandExit() {
    // Command = "TUTUP_PROGRAM"
    char exitCommandStr[] = "TUTUP_PROGRAM";

    return isWordStrEqual(currentWord, exitCommandStr, 13);
}

boolean isCommandDaftar() {
    char daftarCommandStr[] = "DAFTAR";

    return isWordStrEqual(currentWord, daftarCommandStr, 6);
}

boolean isCommandMasuk() {
    return isWordStrEqual(currentWord, "MASUK", 5);
}

boolean isCommandKeluar() {
    return isWordStrEqual(currentWord, "KELUAR", 6);
}

boolean isCommandGantiProfil() {
    return isWordStrEqual(currentWord, "GANTI_PROFIL", 12);
}

boolean isCommandLihatProfil() {
    if (currentWord.Length < 12) {
        return false;
    } 

    char lihatProfilCommandStr[] = "LIHAT_PROFIL";
    for (int i = 0; i < 12; i++) {
        if (currentWord.TabWord[i] != lihatProfilCommandStr[i]) {
            return false;
        }
    }

    return true;
}

boolean isCommandAturJenisAkun() {
    return isWordStrEqual(currentWord, "ATUR_JENIS_AKUN", 15);
}

boolean isCommandUbahPotoProfil() {
    return isWordStrEqual(currentWord, "UBAH_POTO_PROFIL", 16);
}

boolean isCommandDaftarTeman() {
    return isWordStrEqual(currentWord, "DAFTAR_TEMAN", 12);
}

boolean isCommandHapusTeman() {
    return isWordStrEqual(currentWord, "HAPUS_TEMAN", 11);
}

boolean isCommandTambahTeman() {
    return isWordStrEqual(currentWord, "TAMBAH_TEMAN", 12);
}

boolean isCommandBatalTambahTeman() {
    return isWordStrEqual(currentWord, "BATAL_TAMBAH_TEMAN", 18);
}

boolean isCommandDaftarPermintaanTeman() {
    return isWordStrEqual(currentWord, "DAFTAR_PERMINTAAN_TEMAN", 23);
}

boolean isCommandSetujuiPertemanan() {
    return isWordStrEqual(currentWord, "SETUJUI_PERTEMANAN", 18);
}

boolean isCommandKicau() {
    return isWordStrEqual(currentWord, "KICAU", 5);
}

boolean isCommandHapusKicauan() {
    return isWordStrEqual(currentWord, "HAPUS_KICAUAN", 13);
}

boolean isCommandSukaKicauan() {
    if (currentWord.Length < 12) {
        return false;
    }

    char sukaKicauanCommandStr[] = "SUKA_KICAUAN";
    for (int i = 0; i < 12; i++) {
        if (currentWord.TabWord[i] != sukaKicauanCommandStr[i]) {
            return false;
        }
    }

    return true;
}

boolean isCommandUbahKicauan() {
    if (currentWord.Length < 12) {
        return false;
    }

    char ubahKicauanCommandStr[] = "UBAH_KICAUAN";

    for (int i = 0; i < 12; i++) {
        if (currentWord.TabWord[i] != ubahKicauanCommandStr[i]) {
            return false;
        }
    }

    return true;
}

boolean isCommandBalas() {
    if (currentWord.Length < 5) {
        return false;
    }

    char balasCommandStr[] = "BALAS";

    for (int i = 0; i < 5; i++) {
        if (currentWord.TabWord[i] != balasCommandStr[i]) {
            return false;
        }
    }

    return true;
}

boolean isCommandBalasan() {
    if (currentWord.Length < 7) {
        return false;
    }

    char balasanCommandStr[] = "BALASAN";

    for (int i = 0; i < 7; i++) {
        if (currentWord.TabWord[i] != balasanCommandStr[i]) {
            return false;
        }
    }

    return true;

} 

boolean isCommandHapusBalasan() {
    if (currentWord.Length < 13) {
        return false;
    }

    char hapusBalasanCommandStr[] = "HAPUS_BALASAN";

    for (int i = 0; i < 13; i++) {
        if (currentWord.TabWord[i] != hapusBalasanCommandStr[i]) {
            return false;
        }
    }

    return true;
}

boolean isCommandBuatDraf() {
    if (currentWord.Length < 9) {
        return false;
    }

    char buatDrafCommandStr[] = "BUAT_DRAF";

    for (int i = 0; i < 9; i++) {
        if (currentWord.TabWord[i] != buatDrafCommandStr[i]) {
            return false;
        }
    }

    return true;
}

boolean isCommandLihatDraf() {
    return isWordStrEqual(currentWord, "LIHAT_DRAF", 10);
}

boolean isCommandUtas() {
    if (currentWord.Length < 4) {
        return false;
    }

    char utasCommandStr[] = "UTAS";

    for (int i = 0; i < 4; i++) {
        if (currentWord.TabWord[i] != utasCommandStr[i]) {
            return false;
        }
    }

    return true;
}

boolean isCommandSambungUtas() {
    if (currentWord.Length < 12) {
        return false;
    }

    char sambungUtasCommandStr[] = "SAMBUNG_UTAS";

    for (int i = 0; i < 12; i++) {
        if (currentWord.TabWord[i] != sambungUtasCommandStr[i]) {
            return false;
        }
    }

    return true;
}

boolean isCommandHapusUtas() {
    if (currentWord.Length < 10) {
        return false;
    }

    char hapusUtasCommandStr[] = "HAPUS_UTAS";

    for (int i = 0; i < 10; i++) {
        if (currentWord.TabWord[i] != hapusUtasCommandStr[i]) {
            return false;
        }
    }

    return true;
}

boolean isCommandCetakUtas() {
    if (currentWord.Length < 10) {
        return false;
    }

    char cetakUtasCommandStr[] = "CETAK_UTAS";

    for (int i = 0; i < 10; i++) {
        if (currentWord.TabWord[i] != cetakUtasCommandStr[i]) {
            return false;
        }
    }

    return true;
}

boolean isCommandSimpan() {
    return isWordStrEqual(currentWord, "SIMPAN", 6);
}

boolean isCommandMuat() {
    return isWordStrEqual(currentWord, "MUAT", 4);
}

#endif