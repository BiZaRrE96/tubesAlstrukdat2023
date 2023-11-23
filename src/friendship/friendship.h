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

#define FriendshipStatus(friendship, i, j) ELMT((friendship).friends, (i), (j))
#define FriendshipELMT(l, i) (l).content[(i)]

//boolean isEmpty(ListFriendship l);

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
        if(FriendshipELMT(l, i) != MARKLISTFRIENDSHIP)
        {
            countFriend++;
        }
    }
    return countFriend;
}



#endif