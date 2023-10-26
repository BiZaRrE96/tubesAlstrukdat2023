// ADT Pertemanan menggunakan matrix of boolean (adjacency matrix)

#ifndef _FRINEDSHIP_H_
#define _FRINEDSHIP_H_

#include "../boolean/boolean.h"
#include "../userlist/userlist.h"
#include "../matrix/matrix.h"

typedef struct {
    Matrix friends;
} Friendship;

#define FriendshipStatus(friendship, i, j) ELMT((friendship).friends, (i), (j))


#endif