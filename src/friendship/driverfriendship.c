#include <stdio.h>
#include "friendship.h"

int main() {
    Friendship friendship;
    createEmptyFriendship(&friendship);
    
    // Add some friendships
    FriendshipStatus(friendship, 0, 1) = 1;
    FriendshipStatus(friendship, 1, 0) = 1;
    FriendshipStatus(friendship, 1, 2) = 1;
    FriendshipStatus(friendship, 2, 1) = 1;
    FriendshipStatus(friendship, 2, 3) = 1;
    FriendshipStatus(friendship, 3, 2) = 1;
    
    // Display the friendship matrix
    displayFriendship(friendship);
    
    // Check if a user is empty
    int user = 0;
    if (isEmptyFriend(friendship, user)) {
        printf("User %d tidak memiliki teman.\n", user);
    } else {
        printf("User %d memiliki teman.\n", user);
    }
    
    // Count the number of friends for a user
    int friendCount = countFriend(friendship, user);
    printf("User %d memiliki %d banyak teman.\n", user, friendCount);
    
    return 0;
}
