#include "core.h"

#define select_reg( n ) (X##n)
uint32_t *X0;
uint32_t *X1;
uint32_t *X2;
uint32_t *X3;
uint32_t *X4;
uint32_t *X5;
uint32_t *X6;
uint32_t *X7;
uint32_t *X8;
uint32_t *X9;
uint32_t *X10;
uint32_t *X11;
uint32_t *X12; /* MSP */
uint32_t *X13; /* PSP */
uint32_t *X14; /* LR  */
uint32_t *X15; /* PC  */
uint32_t *PRIMASK;
uint32_t *CONTROL;

void initialize_cores(void)
{
    X0 = calloc(1, sizeof(X0));
    X1 = calloc(1, sizeof(X1));
    X2 = calloc(1, sizeof(X2));
    X3 = calloc(1, sizeof(X3));
    X4 = calloc(1, sizeof(X4));
    X5 = calloc(1, sizeof(X5));
    X6 = calloc(1, sizeof(X6));
    X7 = calloc(1, sizeof(X7));
    X8 = calloc(1, sizeof(X8));
    X9 = calloc(1, sizeof(X9));
    X10 = calloc(1, sizeof(X10));
    X11 = calloc(1, sizeof(X11));
    X12 = calloc(1, sizeof(X12));
    X13 = calloc(1, sizeof(X13));
    X14 = calloc(1, sizeof(X14));
    X15 = calloc(1, sizeof(X15));
    PRIMASK = calloc(1, sizeof(PRIMASK));
    CONTROL = calloc(1, sizeof(CONTROL));
}

void free_cores(void)
{
    free(X0);
    free(X1);
    free(X2);
    free(X3);
    free(X4);
    free(X5);
    free(X6);
    free(X7);
    free(X8);
    free(X9);
    free(X10);
    free(X11);
    free(X12);
    free(X13);
    free(X14);
    free(X15);
    free(PRIMASK);
    free(CONTROL);
}
