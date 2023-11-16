#include "../M0/alu.h"

void ASRS (uint32_t *Rt, uint32_t *Rn, uint32_t Operand)
{
    if((int32_t)*Rn < 0)
    {
        *Rt=(uint32_t)~0U;
        set_flags(*Rt, 1, 0);
    }
    else
    {
        uint32_t sign  = ((1<<(Operand + 1))-1);
        uint32_t carry = sign&(*Rn);
        *Rt=*Rn>>Operand;
        set_flags(*Rt, carry, 0);
    }
}


void    LSLS (uint32_t *Rt, uint32_t *Rn, uint32_t Operand);
void    LSRS (uint32_t *Rt, uint32_t *Rn, uint32_t Operand);
void    RORS (uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
