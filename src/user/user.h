// ADT User

#ifndef USER_H_
#define USER_H_

#include "../sentencemachine/sentencemachine.h"
#include "../boolean/boolean.h"
#include "../profile/profile.h"

#define MAX_USERS 20
#define MAX_LENGTH_USERNAME 20
#define MAX_LENGTH_PASSWORD 20

typedef struct {
    Sentence username;
    Sentence password;
    Profile profile;
} User;

#define Username(U) (U).username
#define Password(U) (U).password

typedef struct {
    User TabUser[100];
    int Neff;
} UserList;

#define User(U, i) (U).TabUser[(i)]



#endif