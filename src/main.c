#include "datetime/datetime.h"
#include "sentencemachine/sentencemachine.h"
#include "screen/screen.h"
#include "user/user.h"
#include "saveloadconfig/saveloadconfig.h"
#include "commandmachine/commandmachine.h"
#include "prioqueuechar/prioqueuechar.h"

#include<stdlib.h>

#define ENDL printf("\n")

// KAMUS GLOBAL
UserList users;             // Daftar pengguna dalam bentuk listStatik of User (userlist.h)
Friendship friendship;      // Daftar pertemanan dalam bentuk adjacency matriks (friendship.h)
User currentUser;           // User yang sedang login (user.h)
// prioqueue listRequest;      // Daftar permintaan pertemanan yang belum disetujui (prioqueuechar.h)


boolean isLogin = false;    // Apakah program sedang dalam keadaan login

// boolean isLogin = false;    // Apakah program sedang dalam keadaan login

// FUNGSI DAN PROSEDUR
void startApp() 
/*
    I.S. Sembarang
    F.S. Aplikasi BurBir dimulai
*/
{
    cls;    // Membersihkan layar
    displaySplashScreen();

    printf("-----------------------------| Selamat datang di Burbir. |-----------------------------\n\n");
    printf("                     Aplikasi ini "); print_blue('M'); print_blue('I'); print_blue('R'); print_blue('I'); print_blue('P'); 
    printf(" banget loh sama Twitter!\n\n");
    printf("Silahkan masukan folder konfigurasi untuk dimuat: ");

    // Program akan meminta input folder konfigurasi dengan mesin kata
    START_YELLOW;   // Membuat hasil output sebelum perintah `STOP_COLOR` menjadi kuning
    STARTWORD();
    STOP_COLOR;

    printf("\n");

    // Note : Untuk sementara loadConfig hanya akan memuat pengguna.config
    if (loadConfig(currentWord, &users, &friendship))
    // Jika konfigurasi berhasil dimuat, program akan berlanjut ke menu utama
    {
        print_string_green("Konfigurasi berhasil dimuat. ");
        printf("Selamat berkicau\n\n");
    } else
    // Jika konfigurasi gagal dimuat, program akan meminta input folder konfigurasi kembali
    {
        print_string_red("\nKonfigurasi gagal dimuat. ");
        printf("Tekan apa saja untuk melanjutkan lalu ENTER.\n");
        STARTWORD();
        startApp();
    }
    

}

void inputCommand()
/*
    I.S. Sembarang
    F.S. Perintah yang dimasukkan oleh pengguna akan di proses
*/
{
    print_string_yellow(">> ");
    STARTCOMMAND();
}


void errorCommand(char message[], char usage[]) {
    ENDL;
    print_string_red(message); ENDL;
    START_YELLOW;
    printf("Usage: ");
    STOP_COLOR;
    printf("%s\n", usage);
    ENDL;
}

int main ()
/*
    I.S. Sembarang
    F.S. Aplikasi BurBir dimulai setelah memuat konfigurasi
*/
{
    startApp();

    while (true) {
        inputCommand();

        if (isCommandMasuk()) {
            if (isLogin) {
                printf("Anda sudah login! Keluar terlebih dahulu untuk mengganti akun\n");
                continue;
            }
            
            MASUK(users, &currentUser, &isLogin);
        } else
        if (isCommandKeluar()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
            } else {
                KELUAR(&isLogin);
            }
        } else

        if (isCommandDaftar()) {
            if (isLogin) {
                printf("Anda sudah login! Keluar terlebih dahulu untuk mendaftar akun baru\n");
                continue;
            }
            // Masukkan fungsi daftar disini
            DAFTAR(&users, &friendship);            // Nanti hapus aja
        } else

        if (isCommandGantiProfil()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi ganti profil disini
            printf("Perintah Ganti Profil\n");      // Nanti hapus aja
        } else

        if (isCommandLihatProfil()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            Word username;

            if (!getNama(&username)) {
                errorCommand("Tidak dapat memuat username", "LIHAT_PROFIL <nama>");
                continue;
            }
            
            // Masukkan fungsi lihat profil disini
            LIHAT_PROFIL(users, username, currentUser, friendship); 
            
        } else

        if (isCommandAturJenisAkun()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            
            // Masukkan fungsi atur profil disini
            ATUR_JENIS_AKUN(&currentUser);
            ElmtPrivacy(users, indexOfUser(users, currentUser.username)) = currentUser.privacy;
            
        } else

        if (isCommandUbahPotoProfil()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi ubah poto profil disini
            UBAH_FOTO_PROFIL(&currentUser);
            ElmtPhoto(users, indexOfUser(users, currentUser.username)) = currentUser.photo;
        } else

        if (isCommandDaftarTeman()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi daftar teman disini
            daftarTeman(currentUser, users, friendship);
        } else

        if (isCommandHapusTeman()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi hapus teman disini
            hapusTeman(currentUser, &users, &friendship);
        } else

        if (isCommandTambahTeman()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi tambah teman disini

            tambahteman(currentUser, &users, friendship);
        } else

        if (isCommandBatalTambahTeman()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi batal tambah teman disini
            printf("Perintah Batal Tambah Teman\n"); // Nanti hapus aja
        } else

        if(isCommandDaftarPermintaanTeman()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi daftar permintaan teman disini
            printf("Perintah Daftar Permintaan Teman\n"); // Nanti hapus aja
        } else
        
        if (isCommandSetujuiPertemanan()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi setujui pertemanan disini
            printf("Perintah Setujui Pertemanan\n"); // Nanti hapus aja
        } else

        if (isCommandKicau()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi kicau disini
            printf("Perintah Kicau\n"); // Nanti hapus aja
        } else

        if (isCommandHapusKicauan()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi hapus kicauan disini
            printf("Perintah Hapus Kicauan\n"); // Nanti hapus aja
        } else

        if (isCommandSukaKicauan()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            int idKicau; 

            if (!getParamInt(&idKicau)) {
                errorCommand("Perintah SUKA_KICAUAN tidak valid", "SUKA_KICAUAN <id_kicau>");
                continue;
            }

            printf("idKicau = %d\n", idKicau);
            // Masukkan fungsi suka kicauan disini
            printf("Perintah Suka Kicauan\n"); // Nanti hapus aja
        } else
        if (isCommandUbahKicauan()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            int idKicau;

            if (!getParamInt(&idKicau)) {
                errorCommand("Perintah UBAH_KICAUAN tidak valid", "UBAH_KICAUAN <id_kicau>");
                continue;
            }
            
            // Masukkan fungsi ubah kicauan disini
            printf("Perintah Ubah Kicauan\n"); // Nanti hapus aja
        } else

        if (isCommandBalas()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            int idKicau, idBalasan;

            if (!getTwoParamInt(&idKicau, &idBalasan)) {
                errorCommand("Perintah BALAS tidak valid", "BALAS <id_kicau> <id_balasan>");
                continue;
            }

            // Masukkan fungsi balas disini
            printf("Perintah Balas\n"); // Nanti hapus aja
        } else

        if (isCommandBalasan()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            int idKicau;

            if (!getParamInt(&idKicau)) {
                errorCommand("Perintah BALASAN tidak valid", "BALASAN <id_kicau>");
                continue;
            }
            
            // Masukkan fungsi balasan disini
            printf("Perintah Balasan\n"); // Nanti hapus aja
        } else

        if (isCommandHapusBalasan()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            int idKicau, idBalasan;

            if (!getTwoParamInt(&idKicau, &idBalasan)) {
                errorCommand("Perintah HAPUS_BALASAN tidak valid", "HAPUS_BALASAN <id_kicau> <id_balasan>");
                continue;
            }

        } else

        if (isCommandBuatDraf()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi buat draf disini
            printf("Perintah Buat Draf\n"); // Nanti hapus aja
        } else

        if (isCommandBuatDraf()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi buat draf disini
            printf("Perintah Buat Draf\n"); // Nanti hapus aja
        } else

        if (isCommandLihatDraf()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            // Masukkan fungsi lihat draf disini
            printf("Perintah Lihat Draf\n"); // Nanti hapus aja
        } else

        if (isCommandUtas()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            int idKicau;

            if (!getParamInt(&idKicau)) {
                errorCommand("Perintah UTAS tidak valid", "UTAS <id_kicau>");
                continue;
            }

            // Masukkan fungsi utas disini
            printf("Perintah Utas\n"); // Nanti hapus aja
        } else

        if (isCommandSambungUtas()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            int idUtas, index;

            if (!getTwoParamInt(&idUtas, &index)) {
                errorCommand("Perintah SAMBUNG_UTAS tidak valid", "HAPUS_BALASAN <id_utas> <index>");
                continue;
            }

            // Masukkan fungsi sambung utas disini
            printf("Perintah Sambung Utas\n"); // Nanti hapus aja
        } else

        if (isCommandHapusUtas()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }
            int idUtas, index;

            if (!getTwoParamInt(&idUtas, &index)) {
                errorCommand("Perintah SAMBUNG_UTAS tidak valid", "HAPUS_BALASAN <id_utas> <index>");
                continue;
            }

            printf("idUtas = %d, idx = %d\n", idUtas, index);

            // Masukkan fungsi hapus utas disini
            printf("Perintah Hapus Utas\n"); // Nanti hapus aja
        } else

        if (isCommandCetakUtas()) {
            if (!isLogin) {
                printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
                continue;
            }

            int idUtas;

            if (!getParamInt(&idUtas)) {
                errorCommand("Perintah CETAK_UTAS tidak valid", "CETAK_UTAS <id_utas>");
                continue;
            } else

            // Masukkan fungsi cetak utas disini
            printf("Perintah Cetak Utas\n"); // Nanti hapus aja
        } else

        if (isCommandSimpan()) {

        } else

        if (isCommandMuat()) {

        } else 
        

        if (isCommandExit()) {
            break;
        } else {
            printf("Perintah tidak dikenali.\n");
        }
        // EndWord = false;
    }

    printf("\nAnda telah keluar dari program BurBir.\nSampai jumpa di penjelajahan berikutnya.\n\n");
    return 0;
}