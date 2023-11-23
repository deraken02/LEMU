#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../../core/M0/alu.h"

#define NTESTS 4

typedef struct test_config{
    char name[50];
    int32_t expect;
    int32_t (* func)(void);
} test_config_t;

test_config_t config[NTESTS];

int32_t SUB_test(void)
{
    uint32_t sta = *APSR;
    *X1=31;
    SUB(X0, X1, 3);
    assert(*APSR==sta);
    sta = *X0;
    return (int32_t)sta;
}

int32_t SUBS_test(void)
{
    int32_t sta;
    *X1=0;
    SUBS(X0, X1, 1);
    assert(*APSR==(FLAG_N+FLAG_C));
    sta = *X0;
    return sta;
}

int32_t SUBCS_carry_test(void)
{
    int32_t sta;
    *X1=3;
    *APSR=FLAG_C;
    SUBCS(X3, X1, 1);
    sta = *X3;
    return sta;
}


int32_t SUBCS_no_carry_test(void)
{
    int32_t sta;
    *X1=3;
    *APSR=0;
    SUBCS(X3, X1, 1);
    sta = *X3;
    return sta;
}

void initialize_tests(void)
{
    strcpy(config[0].name, "Arithmetic SUB\t\t");
    config[0].expect = 28;
    config[0].func=SUB_test;

    strcpy(config[1].name, "Arithmetic SUBS\t\t");
    config[1].expect = ~0;
    config[1].func=SUBS_test;

    strcpy(config[2].name, "Arithmetic SUBCS with carry");
    config[2].expect = 1;
    config[2].func=SUBCS_carry_test;

    strcpy(config[3].name, "Arithmetic SUBCS with no carry");
    config[3].expect = 2;
    config[3].func=SUBCS_no_carry_test;
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
