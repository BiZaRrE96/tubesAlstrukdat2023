#include "kicau.h"
#include "../wordmachine/wordmachine.h"
#include "../friendship/friendship.h"
#include "../userlist/userlist.h"

Friendship activeFriendshipForKicauan;
UserList activeUserListForKicauan;

int main(){
    UserList UList;
    Friendship FShip;

    User DummyUser;
    User DummyNewbie;


    CreateUserList(&UList);
    createEmptyFriendship(&FShip);

    Word wordDummyUser;
    wordDummyUser.TabWord[0] = 'D';
    wordDummyUser.TabWord[1] = 'U';
    wordDummyUser.TabWord[2] = 'M';
    wordDummyUser.TabWord[3] = 'M';
    wordDummyUser.TabWord[4] = 'Y';
    wordDummyUser.Length = 5;

    Word wordDummyNewbie;
    wordDummyNewbie.TabWord[0] = 'N';
    wordDummyNewbie.TabWord[1] = 'E';
    wordDummyNewbie.TabWord[2] = 'W';
    wordDummyNewbie.TabWord[3] = 'B';
    wordDummyNewbie.TabWord[4] = 'I';
    wordDummyNewbie.TabWord[5] = 'E';
    wordDummyNewbie.Length = 6;

    DummyUser.username = wordDummyUser;
    DummyNewbie.username = wordDummyNewbie;

    //True public, False private
    DummyUser.privacy = true;
    DummyNewbie.privacy = false;

    insertLastUser(&UList,DummyUser);
    insertLastUser(&UList,DummyNewbie);

    activeUserListForKicauan = UList;
    activeFriendshipForKicauan = FShip;

    int frenStats = FriendshipStatus(FShip,indexOfUser(UList, wordDummyUser),indexOfUser(UList, wordDummyNewbie));

    //START
    KicauList KL;
    createKicauList(&KL, 10);

    Kicau(&KL, wordDummyUser);
    Kicau(&KL, wordDummyNewbie);
    
    printf("\n\nView recent\n\n");
    //printKicauXasA(KL,1,69);
    viewRecentAsA(KL,wordDummyNewbie);
}