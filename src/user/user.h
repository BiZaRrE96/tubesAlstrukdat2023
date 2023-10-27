// ADT User

#ifndef USER_H_
#define USER_H_

#include "../boolean/boolean.h"
#include "../profile/profile.h"

#define MAX_LENGTH_USERNAME 20
#define MAX_LENGTH_PASSWORD 20

typedef struct {
    Sentence username;
    Sentence password;
    Profile profile;
} User;


#define Username(U) (U).username
#define Password(U) (U).password
#define Profile(U) (U).profile



#endif