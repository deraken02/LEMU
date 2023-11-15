#include "../M0/alu.h"

void MOV(uint32_t *Rd, uint32_t *Rm)
{
    *Rd=*Rm;
}

void MOVS(uint32_t *Rd, uint16_t  Rm)
{
    *Rd=Rm;
}
