#include "stack.h"
#include <stdio.h>

int main()
{
    Stack S;
    stackinfotype val;

    // inisialisasi stack
    CreateEmptyStack(&S);

    // Menampilkan stack kosong, penuh, atau tidak keduanya
    printf("Stack kosong? %d\n", IsEmptyStack(S));
    printf("Stack penuh? %d\n", IsFullStack(S));

    // Menambahkan elemen ke dalam stack
    int EOP = -9999;
    stackinfotype N = 0;
    printf("Masukkan angka ke dalam stack (-9999 jika berhenti): \n");
    while (N != EOP && !IsFullStack(S))
    {
        scanf("%d", &N);
        if (N != EOP)
        {
            PushStack(&S, N);
        }
    }

    // Melakukan print stack
    printf("[");
    while (!IsEmptyStack(S))
    {
        PopStack(&S, &val);
        printf("%d", val);
        if (!IsEmptyStack(S))
        {
            printf(",");
        }
    }
    printf("]");

    return 0;
}
