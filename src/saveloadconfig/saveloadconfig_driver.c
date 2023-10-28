#include "saveloadconfig.h"
#include "../friendship/friendship.h"
#include "../userlist/userlist.h"

int main () {
    STARTWORD();

    UserList users;
    Friendship friendship;

    loadConfig(currentWord, &users, &friendship);

    for (IdxType i = 0; i < Neff(users); i++) {
        printf("USER_%d\n", i);
        printf("Nama : %s\n", wordToStr(ElmtUsername(users, i)));
        printf("--------------------------\n");
    }
}