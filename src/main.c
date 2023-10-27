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
        printf("\nCurrentWord: %s\n", wordToStr(currentWord));
        if (isCommandExit()) {
            printf("Exit\n");
            break;
        }
        // EndWord = false;
    }
    EXIT_PROGRAM;

    
    
    return 0;
}