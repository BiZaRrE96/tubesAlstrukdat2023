
#include <stdio.h>
#include "prioqueuechar.h"

int main() {
    prioqueue Q;
    MakeEmptyPrioQueue(&Q, 10);

    friend f1 = {1, 5};
    friend f2 = {2, 3};
    friend f3 = {3, 7};

    EnqueuePrioQueue(&Q, f1);
    EnqueuePrioQueue(&Q, f2);
    EnqueuePrioQueue(&Q, f3);

    printf("Queue Length: %d\n", PrioQueueLength(Q));

    friend dequeuedFriend;
    DequeuePrioQueue(&Q, &dequeuedFriend);
    printf("Dequeued Friend: ID = %d, Friend Count = %d\n", dequeuedFriend.IDrecieve, dequeuedFriend.Friendcount);

    printf("Queue Length: %d\n", PrioQueueLength(Q));
    
    return 0;
}
