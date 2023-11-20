// ADT Pertemanan menggunakan matrix of boolean (adjacency matrix)

#ifndef _FRINEDSHIP_H_
#define _FRINEDSHIP_H_

#include "../src/boolean/boolean.h"
#include "../src/userlist/userlist.h"
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

void createEmptyFriendship(Friendship *friendship);

void createListFriendship(ListFriendship *l);

boolean isEmpty(ListFriendship l);

int countFriendship(ListFriendship l);

void displayFriendship(Friendship friendship, int count);

void daftarTeman(boolean isLogin, User currentUser, UserList* users, Friendship friendship);

void hapusTeman(boolean isLogin, User currentUser, UserList* users, Friendship* friendship);

#endif