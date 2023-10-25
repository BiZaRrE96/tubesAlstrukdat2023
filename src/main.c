#include "datetime/datetime.h"
#include "sentencemachine/sentencemachine.h"
#include "screen/screen.h"

#include<stdlib.h>

// KAMUS GLOBAL

void startApp() {
    printf("\nSelamat datang di Burbir.\n\n");
    printf("Aplikasi untuk studi kualitatif mengenai perilaku manusia dengan menggunakan metode (pengambilan data berupa) Focused Group Discussion kedua di zamannya.\n\n");
    printf("Silahkan masukan folder konfigurasi untuk dimuat: ");
    StartSentence();

    printf("\nSedang memuat konfigurasi... (%s)\n", currentSentence.TabSentence);
}

int main () {
    cls;
    displaySplashScreen();
    startApp();

    
    return 0;
}