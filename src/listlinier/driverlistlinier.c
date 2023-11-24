#include "listlinier.h"

int main()
{
    List L, M;
    ElType_Linked val;

    CreateListLinked(&L);

    printf("List kosong? %d\n", isEmptyLinked(L));
    insertFirst_Linked(&L, 1);
    insertLastLinked(&L, 3);
    insertAtLinked(&L, 2, 1);
    displayListLinked(L);

    printf("panjang list : %d\n", lengthLinked(L));
    deleteAtLinked(&L, 1, &val);
    printf("val : %d\n", val);
    displayListLinked(L);
    deleteLastLinked(&L, &val);
    printf("val : %d\n", val);
    displayListLinked(L);
    deleteFirst_Linked(&L, &val);
    printf("val : %d\n", val);
    displayListLinked(L);

    insertFirst_Linked(&L, 1);
    insertLastLinked(&L, 3);
    insertAtLinked(&L, 2, 1);
    displayListLinked(L);

    CreateListLinked(&M);
    insertFirst_Linked(&M, 4);
    insertLastLinked(&M, 6);
    insertAtLinked(&M, 5, 1);
    displayListLinked(M);

    List N = concatLinked(L, M);
    displayListLinked(N);
    displayListLinked(L);
    displayListLinked(M);
    val = getElmtLinked(N, 2);
    printf("idx 2 di N: %d\n", val);
    setElmtLinked(&N, 1, 10);
    displayListLinked(N);
    printf("6 ada di idx ke-%d\n", indexOfLinked(N, 6));

    return 0;
}