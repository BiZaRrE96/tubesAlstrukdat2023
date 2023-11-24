#include <stdio.h>
#include "user.h"

int main()
{
    User currentUser;

    Word username = {"Tuan Bri", 8};
    Word password = {"password", 8};
    Word bio = {"Hello, I'm Tuan Bri", 20};
    Word phoneNumber = {"1234567890", 10};
    Word weton = {"Pahing", 6};
    Photo photo;
    createPhoto(&photo);
    boolean privacy = PUBLIC;
    prioqueue friendRequest;
    // Initialize other fields as needed

    // Assign values to currentUser
    Username(currentUser) = username;
    Password(currentUser) = password;
    Bio(currentUser) = bio;
    PhoneNumber(currentUser) = phoneNumber;
    Weton(currentUser) = weton;
    Photo(currentUser) = photo;
    Privacy(currentUser) = privacy;
    FriendRequest(currentUser) = friendRequest;

    // Test the functions
    PRINT_FOTO(currentUser);
    GANTI_PROFIL(&currentUser);
    ATUR_JENIS_AKUN(&currentUser);
    UBAH_FOTO_PROFIL(&currentUser);
    PRINT_PROFIL(currentUser);

    return 0;
}
