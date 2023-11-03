#include "../user/user.h"

void DAFTAR()
{
    if (!LogIn)
    {
        boolean NameCheck = false;
        Word name;

        while (!NameCheck)
        {
            printf("\n\nMasukkan nama:\n");
            STARTCOMMAND();

            if (currentWord.Length <= 20)
            {
                name = currentWord;
                NameCheck = true;
            }
            else
            {
                NameCheck = false;
                printf("Username tidak valid karena kepanjangan. Masukkan lagi yuk!");
            }
        }

        int index = indexOfUser(USERLIST, name);
        Word pass;
        boolean PassCheck = false;

        if (index != IDX_UNDEF)
        {
            printf("Wah, sayang sekali nama tersebut telah diambil.");
            DAFTAR();
        }

        else
        {
            while (!PassCheck)
            {
                printf("\nMasukkan kata sandi:\n");
                STARTCOMMAND();

                if (currentWord.Length <= 20)
                {
                    pass = currentWord;
                    PassCheck = true;
                }

                else
                {
                    printf("Password tidak valid karena kepanjangan. Masukkan lagi yuk!");
                    PassCheck = false;
                }
            }
        }
        User NewUser = {name, pass};
        printf("\nPengguna telah berhasil terdaftar. Masuk untuk menikmati fitur-fitur BurBir.\n");
        insertLastUser(&USERLIST, NewUser);
    }

    else
    {
        printf("\nAnda sudah masuk, keluar terlebih dahulu untuk mendaftar\n");
    }
}

void MASUK()
{
    if (LogIn)
    {
        printf("\nAnda sudah masuk, keluar terlebih dahulu untuk mendaftar\n");
    }

    else
    {
        printf("\n\nMasukkan Nama:\n");
        STARTCOMMAND();

        Word nama = currentWord;
        int IndexUser = indexOfUser(USERLIST, nama);

        if (IndexUser == IDX_UNDEF)
        {
            printf("Wah, nama yang Anda cari tidak ada. Masukkan nama lain!\n");
            MASUK();
        }
        else
        {
            User terdaftar = Pengguna(USERLIST, IndexUser);
            Word CorrectPass = terdaftar.password;
            boolean PassCheck = false;

            while (!PassCheck)
            {
                printf("\nMasukkan kata sandi:\n");
                STARTCOMMAND();

                Word Inputpass = currentWord;
                if (compareWord(CorrectPass, Inputpass))
                {
                    PassCheck = true;
                }
                else
                {
                    PassCheck = false;
                    printf("Wah, kata sandi yang Anda masukkan belum tepat. Periksa kembali kata sandi Anda!");
                }
            }
            printf("Anda telah berhasil masuk dengan nama pengguna ");
            PrintWord(terdaftar.username);
            printf(". Mari menjelajahi BurBir bersama Ande-Ande Lumut!");
            CURRENTUSER = terdaftar;
        }
    }
}

void KELUAR()
{
    if (!LogIn)
    {
        printf("\nAnda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
    }
    else
    {
        LogIn = false;
        printf("\nAnda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
    }
}

void GANTI_PROFIL(User *CurrentUser)
{
    if (!LogIn)
    {
        printf("Anda belum Login\n");
    }

    else
    {
        printf("| Nama: ");
        PrintWord(CurrentUser->username);
        printf('\n');
        printf("| Bio Akun: ");
        PrintWord(CurrentUser->bio);
        printf('\n');
        printf("| No HP: ");
        PrintWord(CurrentUser->phoneNumber);
        printf('\n');
        printf("| Weton: ");
        PrintWord(CurrentUser->weton);
        printf('\n');

        Word EmptyWord = {';', 1};
        Word bio;
        boolean BioCheck = false;

        while (BioCheck != true)
        {
            printf("Masukkan Bio Akun:\n");
            STARTCOMMAND();

            if (currentWord.Length <= 135)
            {
                BioCheck = true;
                bio = currentWord;
            }

            else
            {
                printf("\n");
                printf("Bio tidak valid karena kepanjangan, Masukkan lagi yuk!\n");
                printf("\n");
            }
        }
        CurrentUser->bio = bio;

        boolean PhoneCheck = false;
        while (PhoneCheck != true)
        {
            printf("Masukkan No HP:\n");
            STARTCOMMAND();

            if (compareWord(currentWord, EmptyWord))
            {
                PhoneCheck = true;
            }

            else
            {
                int i;
                for (i = 0; i < currentWord.Length; i++)
                {
                    if (currentWord.TabWord[i] >= '0' && currentWord.TabWord[i] <= '9')
                    {
                        PhoneCheck = true;
                    }

                    else
                    {
                        PhoneCheck = false;
                        break;
                    }
                }

                if (PhoneCheck == false)
                {
                    printf("\n");
                    printf("No HP tidak valid, Masukkan lagi yuk!\n");
                    printf("\n");
                }
            }
        }
        CurrentUser->phoneNumber = currentWord;

        boolean WetonCheck = false;
        Word ValidWeton[] = {{"Pahing", 6}, {"Kliwon", 6}, {"Wage", 4}, {"Pon", 3}, {"Legi", 4}};
        while (WetonCheck != true)
        {
            printf("Masukkan Weton:\n");
            int i;
            STARTCOMMAND();

            if (compareWord(currentWord, EmptyWord))
            {
                WetonCheck = true;
            }

            else
            {
                for (i = 0; i < 5; i++)
                {
                    if (compareWord(currentWord, ValidWeton[i]))
                    {
                        WetonCheck = true;
                    }
                }

                if (WetonCheck == false)
                {
                    printf("\n");
                    printf("Weton tidak valid, Masukkan lagi yuk!\n");
                    printf("\n");
                }
            }
        }

        CurrentUser->weton = currentWord;
        printf("Profil anda sudah berhasil diperbarui!\n");
        printf("\n");
    }
}

void LIHAT_PROFIL(User Currentuser)
{
    if (!LogIn)
    {
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
        printf("\n");
    }
    else
    {
        STARTCOMMAND();
        Word NamaOtherUser = currentWord;
    }
}

void ATUR_JENIS_AKUN(User *Currentuser)
{
    if (!LogIn)
    {
        printf("Anda belum Login\n");
    }

    else
    {
        Word Yes = {"YA", 2};
        Word No = {"TIDAK", 5};

        if (Currentuser->privacy == true)
        {
            printf("Saat ini, akun Anda adalah akun Publik. Ingin mengubah ke akun Privat? (YA/TIDAK) ");
            STARTCOMMAND();
            printf("\n");
            printf("\n");
            if (compareWord(currentWord, Yes))
            {
                Currentuser->privacy = false;
                printf("Akun anda sudah diubah menjadi akun Privat.\n");
                printf("\n");
            }
            else
            {
                Currentuser->privacy = true;
                printf("Pengubahan jenis akun dibatalkan\n");
                printf("\n");
            }
        }
        else
        {
            printf("Saat ini, akun Anda adalah akun Privat. Ingin mengubah ke akun Publik? (YA/TIDAK) ");
            STARTCOMMAND();
            printf("\n");
            printf("\n");
            if (compareWord(currentWord, Yes))
            {
                Currentuser->privacy = true;
                printf("Akun anda sudah diubah menjadi akun Publik.\n");
                printf("\n");
            }
            else
            {
                Currentuser->privacy = false;
                printf("Pengubahan jenis akun dibatalkan\n");
                printf("\n");
            }
        }
    }
}

void UBAH_FOTO_PROFIL(User *Currentuser)
{
}

void PRINT_PROFIL(User Currentuser)
{
    printf("| Nama: ");
    printWord(Currentuser.username);
    printf("\n");
    printf("| Bio Akun: ");
    printWord(Currentuser.bio);
    printf("\n");
    printf("| No HP: ");
    printWord(Currentuser.phoneNumber);
    printf("\n");
    printf("| Weton: ");
    printWord(Currentuser.weton);
    printf("\n\n");
    printf("Foto profil akun ");
    printWord(Currentuser.username);
    printf("\n");
    PRINT_FOTO(Currentuser);
    printf("\n");
}

void PRINT_FOTO(User Currentuser)
{
    Matrixchar M = Currentuser.photo;
    for (int i = 0; i < M.rowEff; i++)
    {
        for (int j = 0; j < M.colEff; j += 2)
        {
            if (MELMT(M, i, j) == 'R')
            {
                print_red(MELMT(M, i, j + 1));
            }
            else if (MELMT(M, i, j) == 'G')
            {
                print_blue(MELMT(M, i, j + 1));
            }
            else
            {
                print_blue(MELMT(M, i, j + 1));
            }
        }
        printf("\n");
    }
}
