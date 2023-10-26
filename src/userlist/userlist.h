#ifndef _USERLIST_H_
#define _USERLIST_H_

#include "../user/user.h"

#define MAX_USERS 20

typedef struct {
    User TabUser[MAX_USERS];
    int Neff;
} UserList;

#define User(U, i) (U).TabUser[(i)]
#define Neff(U) (U).Neff
#define ElmtUsername(U, i) (U).TabUser[(i)].username
#define ElmtPassword(U, i) (U).TabUser[(i)].password
#define ElmtBio(U, i) (U).TabUser[(i)].profile.bio
#define ElmtPhoneNumber(U, i) (U).TabUser[(i)].profile.phoneNumber
#define ElmtWeton(U, i) (U).TabUser[(i)].profile.weton
#define ElmtPhoto(U, i) (U).TabUser[(i)].profile.photo
#define ElmtPrivacy(U, i) (U).TabUser[(i)].profile.privacy


#endif