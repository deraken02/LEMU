#include "core.h"

/**
 * Shift(immediate), add, substract, move, and compare
 * |15|14|13-9|8-0|
 * |:-:|:-:|:-:|:-:|
 * |0|0|opcode||
 *
 * |Opcode|Instruction|Note|
 * |:-:|:-:|:-:|
 * |000xx|LSLS|immediate|
 * |001xx|LSRS|immediate|
 * |010xx|ASRS|immediate|
 * |01100|ADD|register|
 * |01101|SUB|register|
 * |01110|ADD|3-bit immediate|
 * |01111|SUB|3-bit immediate|
 * |100xx|MOV|immediate|
 * |101xx|CMP|immediate|
 * |110xx|ADD|8-bit immediate|
 * |111xx|SUB|8-bit immediate|
 *
 * Data processing
 * |15|14|13|12|11|10|9-6|5-0|
 * |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
 * |0|1|0|0|0|0|opcode||
 *
 * |Opcode|Instruction|Note|
 * |:-:|:-:|:-:|
 * |0000|ANDS|register|
 * |0001|EORS|register|
 * |0010|LSLS|register|
 * |0011|LSRS|register|
 * |0100|ASRS|register|
 * |0101|ADDS|register|
 * |0110|SUBCS|register|
 * |0111|RORS|register|
 * |1000|TST|register|
 * |1001|RSB|immediate|
 * |1010|CMP|register|
 * |1011|CMN|register|
 * |1100|OR|register|
 * |1101|MULS||
 * |1110|BIC|register|
 * |1111|MVN|register|
 *
 * Special data instruction, branch, exchange
 * |15|14|13|12|11|10|9-6|5-0|
 * |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
 * |0|1|0|0|0|1|opcode||
 *
 * |Opcode|Instruction|Note|
 * |:-:|:-:|:-:|
 * |00xx|ADD|register|
 * |0100|Unpredictable||
 * |0101|CMP|register|
 * |011x|CMP|register|
 * |10xx|MOV|register|
 * |110x|BX||
 * |111x|BLX|register|
 *
 * Load/store single data item
 * |15-12|11-9|8-0|
 * |:-:|:-:|:-:|
 * |opA|opB||
 *
 * |opA|opB|Instruction|Note|
 * |:-:|:-:|:-:|:-:|
 * |0101|000|STR|register|
 * |0101|001|STRH|register|
 * |0101|010|STRB|register|
 * |0101|011|LDRSB|register|
 * |0101|100|LDR|register|
 * |0101|101|LDRH|register|
 * |0101|110|LDRB|register|
 * |0101|111|LDRSH|register|
 * |0110|0xx|STR|immediate|
 * |0110|1xx|LDR|immediate|
 * |0111|0xx|STRB|immediate|
 * |0111|1xx|LDRB|immediate|
 * |1000|0xx|STRH|immediate|
 * |1000|1xx|LDRH|immediate|
 * |1001|0xx|STR|immediate|
 * |1001|1xx|LDR|immediate|
 *
 * Some 16-bit instructions
 * |15|14|13|12|11-5|4-0|
 * |:-:|:-:|:-:|:-:|:-:|:-:
 * |1|0|1|1|opcode||
 *
 * |Opcode|Instruction|Note|
 * |:-:|:-:|:-:|
 * |00000xx|ADD|SP + immediate|
 * |00001xx|SUB|SP - immediate|
 * |001000x|SXTH||
 * |001001x|SXTB||
 * |001010x|UXTH||
 * |001011x|UXTB||
 * |010xxxx|PUSH||
 * |0110011|CPS||
 * |101000x|REV||
 * |101001x|REV16||
 * |101011x|REVSH||
 * |1110xxx|BRPT||
 *
 * Conditional branch, supervisor call
 * |15|14|13|12|11-5|4-0|
 * |:-:|:-:|:-:|:-:|:-:|:-:
 * |1|1|0|1|opcode||
 *
 * |Opcode|Instruction|Note|
 * |:-:|:-:|:-:|
 * |not 111x|B||
 * |1110|UDF||
 * |1111|SVC|immediate|
 */
void ADD  (uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
void ADDCS(uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
void ADDS (uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
void ADDR (uint32_t *Rd, uint32_t Operand);
void ANDS (uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
void ASRS (uint32_t *Rt, uint32_t *Rn, uint32_t Operand);
void B    (uint32_t cc);
void BICS (uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
void BKPT (uint32_t imm);
void BL   (void     *label);
void BLX  (uint32_t *Rm);
void BX   (uint32_t *Rm);
void CMN  (uint32_t *Rn, uint32_t *Rm);
void CMP  (uint32_t *Rn, uint32_t Operand);
void CPS  (void);/*see documentation to verify if cortex M0 support this opcode*/
void CPSID(uint32_t i);
void CPSIE(uint32_t i);
void DMB  (void);
void DSB  (void);
void EORS (uint32_t *Rd, uint32_t *Rn, uint32_t *Rm);
void ISB  (void);
void LDM  (uint32_t *Rt, uint32_t **reglist);
void LDR  (uint32_t *Rt, void     *label);
void LDRB (uint32_t *Rt, uint32_t *Rn, void     *label);
void LDRH (uint32_t *Rt, uint32_t *Rn, void     *label);
void LDRSB(uint32_t *Rt, uint32_t *Rn, void     *label);
void LDRSH(uint32_t *Rt, uint32_t *Rn, void     *label);
void LSLS (uint32_t *Rt, uint32_t *Rn, uint32_t Operand);
void LSRS (uint32_t *Rt, uint32_t *Rn, uint32_t Operand);
void MOV  (uint32_t *Rd, uint32_t *Rm);
void MOVS (uint32_t *Rd, uint16_t  Rm);
void MRS  (uint32_t *Rd, uint32_t *spec_reg);
void MSR  (uint32_t *Rd, uint32_t *spec_reg);
void MULS (uint32_t *Rd, uint32_t *Rn, uint32_t *Rm);
void MVNS (uint32_t *Rd, uint32_t *Rm);
void NOP  (void);
void OR   (uint32_t *Rd, uint32_t *Rn, uint32_t *Rm);
void POP  (uint32_t **reglist);
void PUSH (uint32_t **reglist);
void REV  (uint32_t *Rd, uint32_t *Rm);
void REV16(uint32_t *Rd, uint32_t *Rm);
void REVSH(uint32_t *Rd, uint32_t *Rm);
void RORS (uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
void RSUBS(uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
void SEV  (void);
void STM  (uint32_t *Rt, uint32_t **reglist);
void STR  (uint32_t *Rt, uint32_t **reglist);
void STRB (uint32_t *Rt, uint32_t **reglist);
void STRH (uint32_t *Rt, uint32_t **reglist);
void SUB  (uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
void SUBCS(uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
void SUBS (uint32_t *Rd, uint32_t *Rn, uint32_t Operand);
void SVC  (uint16_t imm);
void SXTB (uint32_t *Rd, uint32_t *Rm);
void SXTH (uint32_t *Rd, uint32_t *Rm);
void TST  (uint32_t *Rn, uint32_t *Rm);
void UDF  (void);/*see documentation to verify if cortex M0 support this opcode*/
void UXTB (uint32_t *Rd, uint32_t *Rm);
void UXTH (uint32_t *Rd, uint32_t *Rm);
void WFE  (void);
void WFI  (void);
