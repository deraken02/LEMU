#include "../M0/alu.h"

void CMN(uint32_t *Rn, uint32_t *Rm)
{
    uint32_t tmp = ~(*Rm);
    tmp++;
    CMP(Rn, tmp);
}

void CMP(uint32_t *Rn, uint32_t Operand)
{
    uint32_t cmp = 0;
    if(*Rn == Operand)
    {
        set_flags(&cmp, 0, 0);
    }
    else if(*Rn > Operand)
    {
        cmp++;
        set_flags(&cmp, 1, 0);
    }
    else
    {
        cmp=~cmp;
        set_flags(&cmp, 0, 0);
    }
}
