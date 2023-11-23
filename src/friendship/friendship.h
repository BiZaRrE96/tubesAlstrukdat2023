// ADT Pertemanan menggunakan matrix of boolean (adjacency matrix)

#ifndef _FRINEDSHIP_H_
#define _FRINEDSHIP_H_

#include "../boolean/boolean.h"
// #include "../userlist/userlist.h"
#include "../matrix/matrix.h"

#define ROW_FRIENDSHIP 20
#define COLUMN_FRIENDSHIP 20
#define MARKFRIENDSHIP 0
#define FRIENDSHIPCAPACITY 20
#define MARKLISTFRIENDSHIP -9999

typedef struct {
    Matrix friends;
} Friendship;

typedef struct {
   int content[FRIENDSHIPCAPACITY];
} ListFriendship;

#define FriendshipStatus(friendship, i, j) ELMT_MATRIX((friendship).friends, (i), (j))
#define FriendshipELMT(l, i) (l).content[(i)]
#define FreindshipNeff(friendship) (friendship).friends.rowEff

//boolean isEmpty(ListFriendship l);
boolean isEmptyFriend(Friendship friendship, int i) {
    for (int j = 0; j < FRIENDSHIPCAPACITY; j++) {
        if ((FriendshipStatus(friendship, i, j) == 1) && i != j) {
            return false;
        }
    }
    return true;

}

void createEmptyFriendship(Friendship *friendship) {
    int i, j;
    for (i = 0; i < ROW_FRIENDSHIP; i++){
        for (j = 0; j < COLUMN_FRIENDSHIP; j++){
            FriendshipStatus(*friendship, i, j) = MARKFRIENDSHIP;
        }
    }
}

void displayFriendship(Friendship friendship) {
    int i, j;
    for (i = 0; i < ROW_FRIENDSHIP; i++){
        for (j = 0; j < COLUMN_FRIENDSHIP; j++){
            printf("%d ", FriendshipStatus(friendship, i, j));
        }
        printf("\n");
    }
}

void createListFriendship(ListFriendship *l) {
    for (int i = 0; i <= 20; i++) {
            FriendshipELMT(*l, i) = MARKLISTFRIENDSHIP;
        }
}


int countFriend(Friendship friendship, int i) {
    int count = 0;
    for (int j = 0; j < FRIENDSHIPCAPACITY; j++) {
        if (FriendshipStatus(friendship, i, j) == 1) {
            count++;
        }
    }
    return count;
}


#endif