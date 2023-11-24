#include <stdio.h>
#include "userlist.h"

int main()
{
    UserList userList;
    Friendship friendship;

    createEmptyFriendship(&friendship);
    CreateUserList(&userList);

    Word username = {"John", 4};
    Word password = {"password", 8};
    Word username2 = {"Jane", 4};
    Word password2 = {"password2", 9};
    Word username3 = {"Mike", 4};
    Word password3 = {"password3", 9};

    User user1 = {username, password};
    User user2 = {username2, password2};
    User user3 = {username3, password3};

    DAFTAR(&userList, &friendship);
    insertLastUser(&userList, user1);
    insertLastUser(&userList, user2);
    insertLastUser(&userList, user3);

    printf("Panjang user list: %d\n", listLengthUserlist(userList));
    printf("Cari indeks username pada list user:\n");
    STARTCOMMAND();
    printf("Username tersebut terletak pada indeks ke-%d\n", indexOfUser(userList, currentWord));
    printf("User List:\n");
    printListUser(userList);
    daftarTeman(user1, userList, friendship);

    return 0;
}
