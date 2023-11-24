#include "photo.h"

int main()
{
    Photo p;

    createPhoto(&p);
    displayPhoto(p);

    printf("\n");

    changePhoto(&p);
    displayPhoto(p);

    return 0;
}
