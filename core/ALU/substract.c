#include "../M0/alu.h"

void SUBS(uint32_t *Rd, uint32_t *Rn, uint32_t Operand)
{
    *Rd = *Rn;
    *Rd -= Operand;
    uint32_t carry= (*Rn<Operand);
    set_flags(Rd, carry , 0);
}

void SUB(uint32_t *Rd, uint32_t *Rn, uint32_t Operand)
{
    uint32_t tmp=*APSR;
    SUBS(Rd, Rn, Operand);
    *APSR=tmp;
}

void SUBCS(uint32_t *Rd, uint32_t *Rn, uint32_t Operand)
{
    uint32_t carry = ((*APSR)&FLAG_C) ? 1 : 0;
    *Rd = *Rn;
    *Rd -= Operand;
    *Rd -= carry;
    carry = (*Rn<Operand);
    set_flags(Rd, carry, 0);
}
