#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../../core/M0/alu.h"

#define NTESTS 5

typedef struct test_config{
    char name[50];
    int32_t expect;
    int32_t (* func)(void);
} test_config_t;

test_config_t config[NTESTS];

int32_t test_ANDS(void)
{
    int32_t sta;
    *X0=10;
    *X1=6;
    ANDS(X0, X1, *X0);
    sta = *X0;
    return sta;
}

int32_t test_OR(void)
{
    int32_t sta;
    *X0= 10;
    *X1= 6;
    OR(X0, X1, X0);
    sta = *X0;
    return sta;
}

int32_t test_EORS(void)
{
    int32_t sta;
    *X0= 10;
    *X1= 6;
    EORS(X0, X1, X0);
    sta = *X0;
    return sta;
}

int32_t test_MVNS(void)
{
    int32_t sta;
    *X0= 0;
    MVNS(X0, X0);
    sta = *X0;
    assert(*APSR == FLAG_N);
    return sta;
}

int32_t test_TST(void)
{
    int32_t sta;
    *X0= 1;
    *X1= 0;
    TST(X0, X1);
    sta=*APSR;
    return sta;
}

void initialize_tests(void)
{
    strcpy(config[0].name, "ANDS between two registers\t");
    config[0].expect = 2;
    config[0].func=test_ANDS;

    strcpy(config[1].name, "OR between two registers\t");
    config[1].expect = 14;
    config[1].func=test_OR;

    strcpy(config[2].name, "EORS between two registers\t");
    config[2].expect = 12;
    config[2].func=test_EORS;

    strcpy(config[3].name, "MVNS on a register\t\t");
    config[3].expect = -1;
    config[3].func=test_MVNS;

    strcpy(config[4].name, "TST between two register\t");
    config[4].expect = FLAG_Z;
    config[4].func=test_TST;
}

int32_t main(void)
{
    int32_t sta;
    int32_t errors = 0;
    initialize_tests();
    initialize_cores();
    for (uint8_t i = 0; i < NTESTS; i++)
    {
        printf("%s",config[i].name);
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
