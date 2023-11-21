#include <stdio.h>
#include <string.h>

#include "../../core/M0/alu.h"

#define NTESTS 6

typedef struct test_config{
    char name[50];
    int32_t expect;
    int32_t (* func)(void);
} test_config_t;

test_config_t config[NTESTS];

int32_t CMP_equal_test(void)
{
    int32_t sta;
    *X4=1234;
    CMP(X4, 1234);
    sta=*APSR;
    return sta;
}

int32_t CMP_sup_test(void)
{
    int32_t sta;
    *X4=1234;
    CMP(X4, 0);
    sta=*APSR;
    return sta;
}

int32_t CMP_inf_test(void)
{
    int32_t sta;
    *X4=0;
    CMP(X4, 1234);
    sta=*APSR;
    return sta;
}

int32_t CMS_equal_test(void)
{
    int32_t sta;
    *X4=1;
    CMP(X4, 0xFFFFFFFF);
    sta=*APSR;
    return sta;
}

int32_t CMS_sup_test(void)
{
    int32_t sta;
    *X4=1234;
    CMP(X4, 0xFFFFFFFF);
    sta=*APSR;
    return sta;
}

int32_t CMS_inf_test(void)
{
    int32_t sta;
    *X4=0;
    CMP(X4, 0xFFFFFFFF);
    sta=*APSR;
    return sta;
}

void initialize_tests(void)
{
    strcpy(config[0].name, "CMN equal\t\t");
    config[0].expect = FLAG_Z;
    config[0].func=CMP_equal_test;

    strcpy(config[1].name, "CMN sup\t\t\t");
    config[1].expect = FLAG_C;
    config[1].func=CMP_sup_test;

    strcpy(config[2].name, "CMN inf\t\t\t");
    config[2].expect = FLAG_N;
    config[2].func=CMP_inf_test;

    strcpy(config[3].name, "CMS equal\t\t");
    config[3].expect = FLAG_Z;
    config[3].func=CMP_equal_test;

    strcpy(config[4].name, "CMS sup\t\t\t");
    config[4].expect = FLAG_C;
    config[4].func=CMP_sup_test;

    strcpy(config[5].name, "CMS inf\t\t\t");
    config[5].expect = FLAG_N;
    config[5].func=CMP_inf_test;

}

int32_t main(void)
{
    int32_t sta;
    int32_t errors = 0;
    initialize_tests();
    initialize_cores();
    for (uint8_t i = 0; i < NTESTS; i++)
    {
        printf("%s\t",config[i].name);
        sta = config[i].func();
        if (sta == config[i].expect)
        {
            puts("OK");
        }
        else
        {
            errors++;
            printf("NG Return value was %d expected %d\n", sta, config[i].expect);
        }
    }
    free_cores();

    return errors;
}
