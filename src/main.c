#include "datetime/datetime.h"
#include "sentencemachine/sentencemachine.h"
#include "screen/screen.h"
#include "user/user.h"
#include "saveloadconfig/saveloadconfig.h"

#include<stdlib.h>

// KAMUS GLOBAL
UserList users;
Friendship friendship;

void startApp() {
    printf("\nSelamat datang di Burbir.\n\n");
    printf("Aplikasi untuk studi kualitatif mengenai perilaku manusia dengan menggunakan metode (pengambilan data berupa) Focused Group Discussion kedua di zamannya.\n\n");
    printf("Silahkan masukan folder konfigurasi untuk dimuat: ");
    STARTWORD();

    printf("\nSedang memuat file (%s/pengguna.config)...\n", currentWord.TabWord);

    if (readDataUsers(&users, currentWord, &friendship)) {
        printf("Konfigurasi berhasil dimuat.\n");
    } else {
        printf("Konfigurasi gagal dimuat.\n");
    }
    

}

int main () {
    cls;
    displaySplashScreen();
    startApp();

    
    return 0;
}