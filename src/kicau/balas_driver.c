#include "balas.h"
#include "kicau.h"
#include "../wordmachine/wordmachine.h"
#include "../friendship/friendship.h"
#include "../userlist/userlist.h"
#include <stdio.h>

Friendship activeFriendshipForKicauan;
UserList activeUserListForKicauan;

int main(){

    UserList UList;
    Friendship FShip;

    User DummyUser;
    User DummyNewbie;


    CreateUserList(&activeFriendshipForKicauan);
    createEmptyFriendship(&activeUserListForKicauan);

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

    insertLastUser(&activeUserListForKicauan,DummyUser);
    insertLastUser(&activeUserListForKicauan,DummyNewbie);



    int idDummy = indexOfUser(activeUserListForKicauan, wordDummyUser);
    int idNewbie = indexOfUser(activeUserListForKicauan, wordDummyNewbie);
    FriendshipStatus(activeFriendshipForKicauan,idDummy,idNewbie) = 1;
    FriendshipStatus(activeFriendshipForKicauan,idNewbie,idDummy) = 1;

    BalasanList BL;
    createBalasanList(&BL);
    readBalasan(wordDummyUser,-1,&BL);
    readBalasan(wordDummyNewbie,1,&BL);
    printBalasanXasA(BL,1,wordDummyUser);
    printChildren(BL,1,wordDummyUser);
    
}