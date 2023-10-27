#include "datetime/datetime.h"
#include "sentencemachine/sentencemachine.h"
#include "screen/screen.h"
#include "user/user.h"
#include "saveloadconfig/saveloadconfig.h"

#include<stdlib.h>

#define EXIT_PROGRAM printf("\nAnda telah keluar dari program BurBir.\nSampai jumpa di penjelajahan berikutnya.\n")

// KAMUS GLOBAL
UserList users;
Friendship friendship;

void startApp(char alertMessage[], boolean alert) {
    cls;

    displaySplashScreen();

    printf("-----------------------------| Selamat datang di Burbir. |-----------------------------\n\n");
    printf("                     Aplikasi ini "); print_blue('M'); print_blue('I'); print_blue('R'); print_blue('I'); print_blue('P'); 
    printf(" banget loh sama Twitter!\n\n");
    printf("Silahkan masukan folder konfigurasi untuk dimuat: ");
    START_YELLOW;
    STARTWORD();
    STOP_COLOR;

    printf("\nSedang memuat file (%s/pengguna.config)...\n", currentWord.TabWord);

    if (readDataUsers(&users, currentWord, &friendship)) {
        printf("Konfigurasi berhasil dimuat! Selamat berkicau\n");
    } else {
        startApp("Konfigurasi gagal dimuat. Silahkan coba lagi.\n", true);
    }
    

}

void inputCommand() {
    print_string_yellow(">> ");
    STARTCOMMAND();
}

int main () {
    startApp("", false);


    while (true) {
        inputCommand();

        if (isCommandDaftar()) {
            // Masukkan fungsi daftar disini
            printf("Perintah Daftar\n");            // Nanti hapus aja
        } else

        if (isCommandGantiProfil()) {
            // Masukkan fungsi ganti profil disini
            printf("Perintah Ganti Profil\n");      // Nanti hapus aja
        } else

        if (isCommandLihatProfil()) {
            // Masukkan fungsi lihat profil disini
            printf("Perintah Lihat Profil\n");      // Nanti hapus aja
        } else

        if (isCommandAturJenisAkun()) {
            // Masukkan fungsi atur profil disini
            printf("Perintah Atur Profil\n");       // Nanti hapus aja
        } else

        if (isCommandUbahPotoProfil()) {
            // Masukkan fungsi ubah poto profil disini
            printf("Perintah Ubah Poto Profil\n");  // Nanti hapus aja
        } else

        if (isCommandDaftarTeman()) {
            // Masukkan fungsi daftar teman disini
            printf("Perintah Daftar Teman\n");      // Nanti hapus aja
        } else

        if (isCommandHapusTeman()) {
            // Masukkan fungsi hapus teman disini
            printf("Perintah Hapus Teman\n");       // Nanti hapus aja
        } else

        if (isCommandTambahTeman()) {
            // Masukkan fungsi tambah teman disini
            printf("Perintah Tambah Teman\n");      // Nanti hapus aja
        } else

        if (isCommandBatalTambahTeman()) {
            // Masukkan fungsi batal tambah teman disini
            printf("Perintah Batal Tambah Teman\n"); // Nanti hapus aja
        } else

        if(isCommandDaftarPermintaanTeman()) {
            // Masukkan fungsi daftar permintaan teman disini
            printf("Perintah Daftar Permintaan Teman\n"); // Nanti hapus aja
        } else
        
        if (isCommandSetujuiPertemanan()) {
            // Masukkan fungsi setujui pertemanan disini
            printf("Perintah Setujui Pertemanan\n"); // Nanti hapus aja
        } else

        if (isCommandKicau()) {
            // Masukkan fungsi kicau disini
            printf("Perintah Kicau\n"); // Nanti hapus aja
        } else

        if (isCommandHapusKicauan()) {
            // Masukkan fungsi hapus kicauan disini
            printf("Perintah Hapus Kicauan\n"); // Nanti hapus aja
        } else

        if (isCommandSukaKicauan()) {
            // Masukkan fungsi suka kicauan disini
            printf("Perintah Suka Kicauan\n"); // Nanti hapus aja
        } else
        if (isCommandUbahKicauan()) {
            // Masukkan fungsi ubah kicauan disini
            printf("Perintah Ubah Kicauan\n"); // Nanti hapus aja
        } else

        if (isCommandBalas()) {
            // Masukkan fungsi balas disini
            printf("Perintah Balas\n"); // Nanti hapus aja
        } else

        if (isCommandBalasan()) {
            // Masukkan fungsi balasan disini
            printf("Perintah Balasan\n"); // Nanti hapus aja
        } else

        if (isCommandHapusBalasan()) {
            // Masukkan fungsi hapus balasan disini
            printf("Perintah Hapus Balasan\n"); // Nanti hapus aja
        } else

        if (isCommandBuatDraf()) {
            // Masukkan fungsi buat draf disini
            printf("Perintah Buat Draf\n"); // Nanti hapus aja
        } else

        if (isCommandBuatDraf()) {
            // Masukkan fungsi buat draf disini
            printf("Perintah Buat Draf\n"); // Nanti hapus aja
        } else

        if (isCommandLihatDraf()) {
            // Masukkan fungsi lihat draf disini
            printf("Perintah Lihat Draf\n"); // Nanti hapus aja
        } else

        if (isCommandUtas()) {
            // Masukkan fungsi utas disini
            printf("Perintah Utas\n"); // Nanti hapus aja
        } else

        if (isCommandSambungUtas()) {
            // Masukkan fungsi sambung utas disini
            printf("Perintah Sambung Utas\n"); // Nanti hapus aja
        } else

        if (isCommandHapusUtas()) {
            // Masukkan fungsi hapus utas disini
            printf("Perintah Hapus Utas\n"); // Nanti hapus aja
        } else

        if (isCommandCetakUtas()) {
            // Masukkan fungsi cetak utas disini
            printf("Perintah Cetak Utas\n"); // Nanti hapus aja
        } else

        if (isCommandSimpan()) {

        } else

        if (isCommandMuat()) {

        } else 

        if (isCommandExit()) {
            printf("Exit\n");
            break;
        } else {
            printf("Perintah tidak dikenali.\n");
        }

        
        // EndWord = false;
    }
    EXIT_PROGRAM;

    
    
    return 0;
}