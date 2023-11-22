// ADT User

#ifndef USER_H_
#define USER_H_

#include "../commandmachine/commandmachine.h"
#include "../boolean/boolean.h"
#include "../photo/photo.h"
#include "../friendship/friendship.h"

#define PRIVATE false
#define PUBLIC true

#define MAX_LENGTH_USERNAME 20
#define MAX_LENGTH_PASSWORD 20

typedef struct
{
    Word username;
    Word password;
    Word bio;
    Word phoneNumber;
    Word weton; // Weton lahir (Pahing, Kliwon, Wage, Pon, dan Legi (case insensitive))
    Photo photo;
    boolean privacy; // false = privat, true = public;
} User;

#define Username(U) (U).username
#define Password(U) (U).password
#define Bio(U) (U).bio
#define PhoneNumber(U) (U).phoneNumber
#define Weton(U) (U).weton
#define Photo(U) (U).photo
#define Privacy(U) (U).privacy

extern boolean isLogin = false;
extern User currentUser;
extern UserList users;

void GANTI_PROFIL(User *currentUser)
{
    if (!isLogin)
    {
        printf("Anda belum Login\n");
    }

    else
    {
        printf("| Nama: ");
        PrintWord(currentUser->username);
        printf("\n");
        printf("| Bio Akun: ");
        PrintWord(currentUser->bio);
        printf("\n");
        printf("| No HP: ");
        PrintWord(currentUser->phoneNumber);
        printf("\n");
        printf("| Weton: ");
        PrintWord(currentUser->weton);
        printf("\n");

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
        currentUser->bio = bio;

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
        currentUser->phoneNumber = currentWord;

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

        currentUser->weton = currentWord;
        printf("Profil anda sudah berhasil diperbarui!\n");
        printf("\n");
    }
}

void LIHAT_PROFIL(User user)
{
    if (!isLogin)
    {
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
        printf("\n");
    }
    else
    {
        if (user.privacy == true || user.privacy == true && FriendshipStatus(currentUser, user) == 1)
        {
            printf("| Nama: %s\n", wordToStr(Username(user)));
            printf("| Bio Akun: %s\n", wordToStr(Bio(user)));
            printf("| No HP: %s\n", wordToStr(PhoneNumber(user)));
            printf("| Weton: %s\n", wordToStr(Weton(user)));
            printf("\nFoto profil akun %s\n", wordToStr(Username(user)));
            displayPhoto(Photo(user));
        }
    }
}

void ATUR_JENIS_AKUN(User *currentUser)
{
    if (!isLogin)
    {
        printf("Anda belum Login\n");
    }

    else
    {
        Word Yes = {"YA", 2};
        Word No = {"TIDAK", 5};

        if (currentUser->privacy == true)
        {
            printf("Saat ini, akun Anda adalah akun Publik. Ingin mengubah ke akun Privat? (YA/TIDAK) ");
            STARTCOMMAND();
            printf("\n");
            printf("\n");
            if (compareWord(currentWord, Yes))
            {
                currentUser->privacy = false;
                printf("Akun anda sudah diubah menjadi akun Privat.\n");
                printf("\n");
            }
            else
            {
                currentUser->privacy = true;
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
                currentUser->privacy = true;
                printf("Akun anda sudah diubah menjadi akun Publik.\n");
                printf("\n");
            }
            else
            {
                currentUser->privacy = false;
                printf("Pengubahan jenis akun dibatalkan\n");
                printf("\n");
            }
        }
    }
}

void UBAH_FOTO_PROFIL(User *currentUser)
{
    if (!isLogin)
    {
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir\n");
    }

    else
    {
        printf("\nFoto profil Anda saat ini adalah\n");
        PRINT_FOTO(*currentUser);

        printf("\n\nMasukkan foto profil yang baru\n");
        Photo M;
        createPhoto(&M);
        changePhoto(&M);
        currentUser->photo = M;
        printf("\n");
        printf("Foto profil anda sudah berhasil diganti!\n\n");
        PRINT_FOTO(*currentUser);
    }
}

void PRINT_PROFIL(User currentUser)
{
    printf("| Nama: ");
    PrintWord(currentUser.username);
    printf("\n");
    printf("| Bio Akun: ");
    PrintWord(currentUser.bio);
    printf("\n");
    printf("| No HP: ");
    PrintWord(currentUser.phoneNumber);
    printf("\n");
    printf("| Weton: ");
    PrintWord(currentUser.weton);
    printf("\n\n");
    printf("Foto profil akun ");
    PrintWord(currentUser.username);
    printf("\n");
    PRINT_FOTO(currentUser);
    printf("\n");
}

void PRINT_FOTO(User currentUser)
{
    Photo M = currentUser.photo;
    displayPhoto(M);
}

#endif