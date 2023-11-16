#include <stdint.h>
#include <stdlib.h>

#define FLAG_N   1 /* Negative                    */
#define FLAG_Z   2 /* Zero  (for the comparisons) */
#define FLAG_C   4 /* Carry (or Unsigned Overflow)*/
#define FLAG_V   8 /* (Signed) Overflow           */


extern uint32_t *X0;
extern uint32_t *X1;
extern uint32_t *X2;
extern uint32_t *X3;
extern uint32_t *X4;
extern uint32_t *X5;
extern uint32_t *X6;
extern uint32_t *X7;
extern uint32_t *X8;
extern uint32_t *X9;
extern uint32_t *X10;
extern uint32_t *X11;
extern uint32_t *X12; /* MSP */
extern uint32_t *X13; /* PSP */
extern uint32_t *X14; /* LR  */
extern uint32_t *X15; /* PC  */
extern uint32_t *PRIMASK;
extern uint32_t *CONTROL;
extern uint32_t *APSR;

void initialize_cores(void);
void free_cores(void);
void set_flags(uint32_t *Rn, uint32_t carry, uint32_t overflow);
