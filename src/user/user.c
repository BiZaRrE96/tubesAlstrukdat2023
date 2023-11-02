#include "../user/user.h"
boolean LogIn = false;

void DAFTAR(User *user, UserList *userlist)
{

    if (!LogIn)
    {
        boolean NameCheck = false;
        Word name;

        while (!NameCheck)
        {
            printf("Masukkan nama:\n");
            STARTCOMMAND();

            if (currentWord.Length <= 20)
            {
                name = currentWord;
                NameCheck = true;
            }
            else
            {
                NameCheck = false;
                printf("Username tidak valid. Masukkan lagi yuk!\n");
            }
        }

        user->username = name;

        int index = indexOfUser(*userlist, name);
        Word pass;
        boolean PassCheck = false;

        if (index != IDX_UNDEF)
        {
            printf("Wah, sayang sekali nama tersebut telah diambil.\n");
            DAFTAR(user, userlist);
        }

        else
        {
            while (!PassCheck)
            {
                printf("Masukkan kata sandi:\n");
                STARTCOMMAND();

                if (currentWord.Length <= 20)
                {
                    pass = currentWord;
                    PassCheck = true;
                }

                else
                {
                    printf("Password tidak valid. Masukkan lagi yuk!\n");
                    PassCheck = false;
                }
            }
            user->password = pass;
        }
        printf("\n");
        printf("Pengguna telah berhasil terdaftar. Masuk untuk menikmati fitur-fitur BurBir.\n");
        insertLastUser(userlist, user);
    }

    else
    {
        printf("Anda sudah masuk, keluar terlebih dahulu untuk mendaftar\n");
        printf("\n");
    }
}

void MASUK()
{
}

void KELUAR()
{
    if (!LogIn)
    {
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
        printf("\n");
    }
    else
    {
        LogIn = false;
        printf("Anda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
        printf("\n");
    }
}