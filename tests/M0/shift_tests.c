#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../../core/M0/alu.h"

#define NTESTS 5

typedef struct test_config{
    char name[50];
    int32_t expect;
    int32_t (* func)(void);
} test_config_t;

test_config_t config[NTESTS];

int32_t LSLS_test(void)
{
    int32_t sta;
    *X1=31;
    LSLS(X0, X1, 3);
    sta = *X0;
    return sta;
}

int32_t LSLS_ovf_neg_test(void)
{
    int32_t sta;
    *X1=3;
    LSLS(X0, X1, 31);
    assert((int32_t)*X0 < 0);
    sta = *APSR;
    return sta;
}

int32_t LSRS_test(void)
{
    int32_t sta;
    *X1=0xFBFFFFFF;
    LSRS(X3, X1, 24);
    assert(*APSR == FLAG_C);
    sta = *X3;
    return sta;
}


int32_t ASRS_test(void)
{
    int32_t sta;
    *X1=0xFBFFFFFF;
    ASRS(X3, X1, 24);
    assert(*APSR == FLAG_C + FLAG_N);
    sta = *X3;
    return sta;
}

int32_t RORS_test(void)
{
    int32_t sta;
    *X2=123456789;
    RORS(X4, X2, 4);
    sta = *X4;
    return sta;
}

void initialize_tests(void)
{
    strcpy(config[0].name, "Logical shift left\t");
    config[0].expect = 248;
    config[0].func=LSLS_test;

    strcpy(config[1].name, "Logical left overflow negative");
    config[1].expect = FLAG_N + FLAG_V;
    config[1].func=LSLS_ovf_neg_test;

    strcpy(config[2].name, "Logical shift right\t");
    config[2].expect = 0xFB;
    config[2].func=LSRS_test;

    strcpy(config[3].name, "Arithmetic shift right\t");
    config[3].expect = 0xFFFFFFFB;
    config[3].func=ASRS_test;

    strcpy(config[4].name, "Rotate right\t\t");
    config[4].expect = 1349893329;
    config[4].func=RORS_test;
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
