#include "../datetime/datetime.h"

int main()
{
    DATETIME T1, T2;
    printf("BACA TIME\n");
    BacaDATETIME(&T1);
    BacaDATETIME(&T2);

    // TULIS TIME
    printf("TULIS TIME\n");
    printf("T1 = ");
    TulisDATETIME(T1);
    printf("\nT2 = ");
    TulisDATETIME(T2);
    printf("\n");

    // DEQ
    printf("DEQ\n");
    if (DEQ(T1, T2))
    {
        printf("T1 = T2\n");
    }
    else
    {
        printf("T1 != T2\n");
    }

    // DNEQ
    printf("DNEQ\n");
    if (DNEQ(T1, T2))
    {
        printf("T1 != T2\n");
    }
    else
    {
        printf("T1 = T2\n");
    }

    // DLT
    printf("DLT\n");
    if (DLT(T1, T2))
    {
        printf("T1 < T2\n");
    }
    else
    {
        printf("T1 > T2\n");
    }

    // DGT
    printf("DGT\n");
    if (DGT(T1, T2))
    {
        printf("T1 > T2\n");
    }
    else
    {
        printf("T1 < T2\n");
    }

    // Next 10 Detik
    printf("Next N Detik\n");
    printf("T1 = ");
    TulisDATETIME(DATETIMENextNDetik(T1, 10));
    printf("\nT2 = ");
    TulisDATETIME(DATETIMENextNDetik(T2, 10));
    printf("\n");

    // Prev 10 Detik
    printf("Prev N Detik\n");
    printf("T1 = ");
    TulisDATETIME(DATETIMEPrevNDetik(T1, 10));
    printf("\nT2 = ");
    TulisDATETIME(DATETIMEPrevNDetik(T2, 10));
    printf("\n");

    // Durasi
    printf("Durasi\n");
    printf("T1-T2 = %ld detik\n", DATETIMEDurasi(T1, T2));
    printf("T2-T1 = %ld detik\n", DATETIMEDurasi(T2, T1));

    return 0;
}