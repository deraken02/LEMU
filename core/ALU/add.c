#include "../M0/alu.h"

void ADDS(uint32_t *Rd, uint32_t *Rn, uint32_t Operand)
{
    uint64_t tmp = *Rn;
    tmp += Operand;
    *Rd = tmp&UINT32_MAX;
    set_flags(Rd, 0, tmp>>32);
}

void ADD(uint32_t *Rd, uint32_t *Rn, uint32_t Operand)
{
    uint32_t tmp=*APSR;
    ADDS(Rd, Rn, Operand);
    *APSR=tmp;
}

void ADDCS(uint32_t *Rd, uint32_t *Rn, uint32_t Operand)
{
    uint64_t tmp = *Rn;
    uint32_t carry = ((*APSR)&FLAG_C) ? 1 : 0;
    tmp += Operand + carry;
    *Rd = tmp&UINT32_MAX;
    set_flags(Rd, 0, tmp>>32);
}
