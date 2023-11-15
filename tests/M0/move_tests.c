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

int32_t movs_X0(void)
{
    int32_t sta;
    MOVS(X0, 3);
    sta = *X0;
    return sta;
}

int32_t movs_X1(void)
{
    int32_t sta;
    MOVS(X1, 65535);
    sta = *X1;
    return sta;
}

int32_t mov_X0_X1(void)
{
    int32_t sta;
    MOV(X0, X1);
    sta = *X0;
    return sta;
}

void initialize_tests(void)
{
    strcpy(config[0].name, "Set X0 to 3\t\t");
    config[0].expect = 3;
    config[0].func=movs_X0;

    strcpy(config[1].name, "Set X1 to UINT16_MAX\t");
    config[1].expect = 65535;
    config[1].func=movs_X1;

    strcpy(config[2].name, "Move X1 in X0\t\t");
    config[2].expect = 65535;
    config[2].func=mov_X0_X1;
}

int32_t main(void)
{
    initialize_tests();
    initialize_cores();
    int32_t sta;
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
            printf("NG Return value was %d expected %d\n", sta, config[i].expect);
        }
    }
    free_cores();

    return 0;
}
