#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../../core/M0/alu.h"

#define NTESTS 3

typedef struct test_config{
    char name[50];
    int32_t expect;
    int32_t (* func)(void);
} test_config_t;

test_config_t config[NTESTS];

int32_t MULS_test(void)
{
    int32_t sta;
    *X0 = 5;
    *X1 = 10;
    MULS(X2, X1, X0);
    sta = *X2;
    return sta;
}

int32_t MULS_overflow(void)
{
    int32_t sta;
    *X0 = ~0U;
    *X1 = ~0U;
    MULS(X2, X1, X0);
    assert(*X2 == 1);
    sta = *APSR;
    return sta;
}

int32_t MULS_neg(void)
{
    int32_t sta;
    *X0 = ~0U;
    *X1 = 1;
    MULS(X2, X1, X0);
    assert(*X2 == ~0U);
    sta = *APSR;
    return sta;
}


void initialize_tests(void)
{
    strcpy(config[0].name, "MULS\t\t\t");
    config[0].expect = 50;
    config[0].func=MULS_test;

    strcpy(config[1].name, "MULS overflow\t\t");
    config[1].expect = FLAG_V;
    config[1].func=MULS_overflow;

    strcpy(config[2].name, "MULS negative\t\t");
    config[2].expect = FLAG_N;
    config[2].func=MULS_neg;
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
