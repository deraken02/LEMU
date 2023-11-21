#include "../M0/alu.h"

/**
 * Arithmetic Shift Right shifts a register value right by an immediate or a variable number of bits, shifting in copies
 * of its sign bit, and writes the result to the destination register. It updates the condition flags based on the result.
 */
void ASRS(uint32_t *Rt, uint32_t *Rn, uint32_t Operand)
{
    uint64_t tmp = *Rn;
    tmp = tmp << 32;
    asm("sar %[shift], %[result]" : [result] "=r" (tmp) : "[result]" (tmp), [shift] "c" (Operand));
    *Rt=tmp>>32;
    set_flags(Rt, (tmp&UINT32_MAX), 0);
}

/**
 * Logical Shift Left (register) shifts a register value left by a variable number of bits, shifting in zeros,
 * and writes the result to the destination register. The variable number of bits is read from the bottom byte of a register.
 * The condition flags are updated based on the result.
 */
void LSLS(uint32_t *Rt, uint32_t *Rn, uint32_t Operand)
{
    uint64_t tmp = *Rn;
    asm("shl %[shift], %[result]" : [result] "=r" (tmp) : "[result]" (tmp), [shift] "c" (Operand));
    *Rt=tmp&UINT32_MAX;
    set_flags(Rt, 0, (tmp>>32));
}

/**
 * Logical Shift Right shifts a register value right by an immediate or a variable number of bits, shifting in zeros,
 * and writes the result to the destination register. The condition flags are updated based on the result.
 */
void LSRS(uint32_t *Rt, uint32_t *Rn, uint32_t Operand)
{
    uint64_t tmp = *Rn;
    tmp = tmp<<32;
    asm("shr %[shift], %[result]" : [result] "=r" (tmp) : "[result]" (tmp), [shift] "c" (Operand));
    *Rt=tmp>>32;
    set_flags(Rt, (tmp&UINT32_MAX), 0);
}

/**
 * Rotate Right provides the value of the contents of a register rotated by an immediate or a variable number of bits.
 * The bits that are rotated off the right end are inserted into the vacated bit positions on the left.
 * The variable number of bits is read from the bottom byte of a register.
 * The condition flags are updated based on the result.
 */
void RORS(uint32_t *Rd, uint32_t *Rn, uint32_t Operand)
{
    *Rd = *Rn;
    asm("ror %[shift], %[result]"
        : [result] "=r" (*Rd)
        : "[result]" (*Rd), [shift] "c" (Operand));
    set_flags(Rd, 0, 0);
}
