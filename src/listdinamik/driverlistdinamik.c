#include "listdinamik.h"

int main()
{
    ListDin L;
    CreateListDin(&L, 5);
    readListDin(&L);
    printListDin(L);
    printf("Panjang List: %d\n", listLengthDin(L));
    dealocateListDin(&L);
    printListDin(L);
    printf("Panjang List: %d\n", listLengthDin(L));
}