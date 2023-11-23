#include "../M0/alu.h"

void MULS (uint32_t *Rd, uint32_t *Rn, uint32_t *Rm)
{
    uint64_t tmp = *Rn;
    tmp *= *Rm;
    *Rd = tmp&UINT32_MAX;
    set_flags(Rd, 0, tmp>>32);
}
