#include "../M0/alu.h"


void ANDS(uint32_t *Rd, uint32_t *Rn, uint32_t Operand)
{
    *Rd=(*Rn & Operand);
    set_flags(Rd, 0, 0);
}

void EORS(uint32_t *Rd, uint32_t *Rn, uint32_t *Rm)
{
    *Rd=(*Rn ^ *Rm);
    set_flags(Rd, 0, 0);
}

void OR(uint32_t *Rd, uint32_t *Rn, uint32_t *Rm)
{
    *Rd=(*Rn | *Rm);
    set_flags(Rd, 0, 0);
}

void BICS(uint32_t *Rd, uint32_t *Rn, uint32_t Operand)
{
    *Rd=(*Rn & (~Operand));
    set_flags(Rd, 0, 0);
}

void MVNS(uint32_t *Rd, uint32_t *Rm)
{
    *Rd=(~*Rm);
    set_flags(Rd, 0, 0);
}

void TST(uint32_t *Rn, uint32_t *Rm)
{
    uint32_t test=(*Rn & *Rm);
    set_flags(&test, 0, 0);
}
