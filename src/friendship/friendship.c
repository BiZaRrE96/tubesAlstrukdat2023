#include "../friendship/friendship.h"

#include <stdio.h>

void createEmptyFriendship(Friendship *friendship) {
    int i, j;
    for (i = 0; i < ROW_FRIENDSHIP; i++){
        for (j = 0; j < COLUMN_FRIENDSHIP; j++){
            FriendshipStatus(*friendship, i, j) = MARKFRIENDSHIP;
        }
    }
}

void createListFriendship(ListFriendship *l) {
    for (int i = 0; i <= CAPACITY-1; i++) {
            FriendshipELMT(*l, i) = MARKLISTFRIENDSHIP;
        }
}

boolean noFriendship(ListFriendship l) {
    return (countFriendship(l) == 0); 
}

int countFriendship(ListFriendship l) {
    int countFriend = 0;
    for (int i = 0; i <= FRIENDSHIPCAPACITY-1; i++) {
        if(ELMTLISTGRAF(l, i) != MARKLISTFRIENDSHIP)
        {
            countFriend++;
        }
    }
    return countFriend;
}

void displayFriendship(Friendship friendship, int count) {
    int i, j;
    for (i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            printf("%d", FriendshipStatus(friendship, i, j));
            if (j != count - 1) {
                printf(" ");
            }
        }
        if (i != count - 1) {
            printf("\n");
        }
    }
    printf("\n");
}

void daftarTeman(boolean isLogin, User currentUser, UserList *userList, Friendship friendship) {
    ListFriendship friendshipList;
    UserList users;
    createListFriendship(&friendshipList);
    if (!isLogin) 
    {
        printf("Anda belum login !\n");
        printf("Silahkan Login terlebih dahulu sebelum menggunakan fungsi ini.\n");
    } else 
    {
        if (noFriendship(friendshipList))
        {
            printf("%s belum mempunyai teman\n", currentUser.username);
        } else
        {
            int UserId = indexOfUser(users, currentUser.username);
            printf("%s memiliki %d teman\n", currentUser.username, countFriendship(friendshipList));
            printf("Daftar teman %s :\n",currentUser.username);
            for (int i = 0; i < FRIENDSHIPCAPACITY; i++)
            {
                int j = 1;
                if (FriendshipStatus(friendship, UserId, i) == 1) 
                {
                    printf("%d. %s\n",j, userList->TabUser[i].username);
                    j++;
                }
            }
        }
    }
}

void hapusTeman(boolean isLogin, User currentUser, UserList *usersList, Friendship *friendship) {
    ListFriendship friendshipList;
    Word currentWord;
    UserList users;
    createListFriendship(&friendshipList);

    if (!isLogin) {
        printf("Anda belum login!\n");
        printf("Silahkan Login terlebih dahulu sebelum menggunakan fungsi ini.\n");
    } else {
        if (noFriendship(friendshipList)) {
            printf("%s belum mempunyai teman\n", currentUser.username);
        } else {
            printf("Masukan nama teman yang ingin dihapus.");
            STARTWORD();
            for (int i = 0;i < FRIENDSHIPCAPACITY;i++) 
            {
                if (isWordEqual(currentWord,ElmtUsername(users,i)))  
                {
                    printf("Apakah anda ingin benar-benar menghapus pertemanan ? (Yes/No)");
                    STARTWORD();
                    int UserId = indexOfUser(users, currentUser.username);
                    int TargetId = indexOfUser(users, currentWord);
                    if (currentWord.TabWord[0] == 'Y') 
                    {
                        FriendshipStatus(*friendship, UserId, TargetId) = 0;
                        FriendshipStatus(*friendship, TargetId, UserId) = 0;
                    } else {
                        printf("Teman batal dihapuskan.");
                    }
                } else {
                    printf("Nama yang diinput tidak ada di daftar teman.");
                }
            }
        }
    }
}