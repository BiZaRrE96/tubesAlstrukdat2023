#include "../user/user.h"
#include <stdio.h>

int main()
{
    User currentUser;
    UserList users;
    CreateUserList(&users);
    DAFTAR();
    MASUK();
    KELUAR();
}