// ADT User

#ifndef USER_H_
#define USER_H_

#include "../sentencemachine/sentencemachine.h"
#include "../boolean/boolean.h"

#define MAX_LENGTH_USERNAME 20
#define MAX_LENGTH_PASSWORD 20

typedef struct {
    Sentence username;
    Sentence password;
} User;

#define Username(U) (U).username
#define Password(U) (U).password

void createUser(Sentence username, Sentence password, User *u)
// Membuat user baru
{
    Username(*u) = username;
    Password(*u) = password;
}

boolean isValidateUsername(Sentence username) {
    // Mengecek apakah username valid
    return (username.Length > 0 && username.Length <= MAX_LENGTH_USERNAME);
}

boolean isValidatePassword(Sentence password) {
    // Mengecek apakah password valid
    return (password.Length > 0 && password.Length <= MAX_LENGTH_PASSWORD);
}

boolean isSameUsername(Sentence username1, Sentence username2) {
    // Mengecek apakah username1 sama dengan username2
    if (username1.Length != username2.Length) {
        return false;
    } else {
        int i = 0;
        while (i < username1.Length && username1.TabSentence[i] == username2.TabSentence[i]) {
            i++;
        }
        return (i == username1.Length);
    }
}

boolean isSamePassword(Sentence password1, Sentence password2) {
    // Mengecek apakah password1 sama dengan password2
    if (password1.Length != password2.Length) {
        return false;
    } else {
        int i = 0;
        while (i < password1.Length && password1.TabSentence[i] == password2.TabSentence[i]) {
            i++;
        }
        return (i == password1.Length);
    }
}



#endif