// ADT User

#ifndef USER_H_
#define USER_H_

#include "../boolean/boolean.h"
#include "../photo/photo.h"
#include "../matrix/matrixchar.h"

#define PRIVATE false
#define PUBLIC true

#define MAX_LENGTH_USERNAME 20
#define MAX_LENGTH_PASSWORD 20

typedef struct
{
    Word username;
    Word password;
    Profile profile;
} User;

User currentUser;
boolean isLogin = false;

#define Username(U) (U).username
#define Password(U) (U).password
#define Profile(U) (U).profile


#endif