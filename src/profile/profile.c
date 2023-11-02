#include "profile.h"
boolean LogIn = false; // Variabel Semesta

void GANTI_PROFIL(Profile *P, User CurrentUser)
{
    if (!LogIn)
    {
        printf("Anda belum Login\n");
    }

    else
    {
        printf("| Nama: ");
        PrintWord(CurrentUser.username);
        printf('\n');
        printf("| Bio Akun: ");
        PrintWord(P->bio);
        printf('\n');
        printf("| No HP: ");
        PrintWord(P->phoneNumber);
        printf('\n');
        printf("| Weton: ");
        PrintWord(P->weton);
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
        P->bio = bio;

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
        P->phoneNumber = currentWord;

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

        P->weton = currentWord;
        printf("Profil anda sudah berhasil diperbarui!\n");
        printf("\n");
    }
}

void LIHAT_PROFIL(Profile *P);

void ATUR_JENIS_AKUN(Profile *P)
{
    if (!LogIn)
    {
        printf("Anda belum Login\n");
    }

    else
    {
        Word Yes = {"YA", 2};
        Word No = {"TIDAK", 5};

        if (P->privacy == true)
        {
            printf("Saat ini, akun Anda adalah akun Publik. Ingin mengubah ke akun Privat? (YA/TIDAK) ");
            STARTCOMMAND();
            printf("\n");
            printf("\n");
            if (compareWord(currentWord, Yes))
            {
                P->privacy = false;
                printf("Akun anda sudah diubah menjadi akun Privat.\n");
                printf("\n");
            }
            else
            {
                P->privacy = true;
                printf("Pengubahan jenis akun dibatalkan\n");
                printf("\n");
            }
        }
        else
        {
            printf("Saat ini, akun Anda adalah akun Privat. Ingin mengubah ke akun Publik? (YA/TIDAK)");
            STARTCOMMAND();
            printf("\n");
            printf("\n");
            if (compareWord(currentWord, Yes))
            {
                P->privacy = true;
                printf("Akun anda sudah diubah menjadi akun Publik.\n");
                printf("\n");
            }
            else
            {
                P->privacy = false;
                printf("Pengubahan jenis akun dibatalkan\n");
                printf("\n");
            }
        }
    }
}

void UBAH_FOTO_PROFIL(Profile *P)
{
    int i;
    int j;
}

void PRINT_PROFIL(Profile P, User user)
{
    printf("| Nama: ");
    printWord(user.username);
    printf("\n");
    printf("| Bio Akun: ");
    printWord(P.bio);
    printf("\n");
    printf("| No HP: ");
    printWord(P.phoneNumber);
    printf("\n");
    printf("| Weton: ");
    printWord(P.weton);
    printf("\n\n");
    printf("Foto profil akun ");
    printWord(user.username);
    printf("\n");
    PRINT_PHOTO(P);
    printf("\n");
}