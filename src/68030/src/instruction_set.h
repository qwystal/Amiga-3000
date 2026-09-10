#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

void signal(word signal); // in or out?

word get_SR(a3000_t *a3000);
void set_SR(a3000_t *a3000, word SR);

word get_CCR(a3000_t *a3000);
void set_CCR(a3000_t *a3000, word CCR);

sword look_up_instruction(a3000_t *a3000);

sword call_ORI_to_CCR(a3000_t *a3000);
sword call_ORI_to_SR(a3000_t *a3000);
sword call_ANDI_to_CCR(a3000_t *a3000);
sword call_ANDI_to_SR(a3000_t *a3000);
sword call_EORI_to_CCR(a3000_t *a3000);
sword call_EORI_to_SR(a3000_t *a3000);
sword call_ILLEGAL(a3000_t *a3000);
sword call_RESET(a3000_t *a3000);
sword call_NOP(a3000_t *a3000);
sword call_STOP(a3000_t *a3000);
sword call_RTE(a3000_t *a3000);
sword call_RTD(a3000_t *a3000);
sword call_RTS(a3000_t *a3000);
sword call_TRAPV(a3000_t *a3000);
sword call_RTR(a3000_t *a3000);

sword call_CAS2(a3000_t *a3000);
sword call_CAS(a3000_t *a3000);
sword call_CHK2_CMP2(a3000_t *a3000);

sword call_ORI(a3000_t *a3000);

sword call_ANDI(a3000_t *a3000);
sword call_SUBI(a3000_t *a3000);
sword call_ADDI(a3000_t *a3000);
sword call_EORI(a3000_t *a3000);
sword call_CMPI(a3000_t *a3000);
sword call_BTST(a3000_t *a3000);
sword call_BCHG(a3000_t *a3000);
sword call_BCLR(a3000_t *a3000);
sword call_BSET(a3000_t *a3000);
sword call_MOVES(a3000_t *a3000);
sword call_MOVEP(a3000_t *a3000);
sword call_MOVEA(a3000_t *a3000);
sword call_MOVE(a3000_t *a3000);
sword call_MOVE_from_SR(a3000_t *a3000);
sword call_NEGX(a3000_t *a3000);
sword call_MOVE_from_CCR(a3000_t *a3000);
sword call_CLR(a3000_t *a3000);
sword call_MOVE_to_CCR(a3000_t *a3000);
sword call_NEG(a3000_t *a3000);
sword call_MOVE_to_SR(a3000_t *a3000);
sword call_NOT(a3000_t *a3000);
sword call_EXT(a3000_t *a3000);
sword call_NBCD(a3000_t *a3000);
sword call_SWAP(a3000_t *a3000);
sword call_BKPT(a3000_t *a3000);
sword call_PEA(a3000_t *a3000);
sword call_TAS(a3000_t *a3000);
sword call_TST(a3000_t *a3000);
sword call_DIVSL_DIVUL(a3000_t *a3000);
sword call_TRAP(a3000_t *a3000);
sword call_LINK(a3000_t *a3000);
sword call_UNLK(a3000_t *a3000);
sword call_MOVE_USP(a3000_t *a3000);
sword call_MOVEC(a3000_t *a3000);
sword call_JMP(a3000_t *a3000);
sword call_JSR(a3000_t *a3000);
sword call_MOVEM(a3000_t *a3000);
sword call_LEA(a3000_t *a3000);
sword call_CHK(a3000_t *a3000);
sword call_DBcc(a3000_t *a3000);
sword call_TRAPcc(a3000_t *a3000);
sword call_Scc(a3000_t *a3000);
sword call_SUBQ(a3000_t *a3000);
sword call_ADDQ(a3000_t *a3000);
sword call_BRA(a3000_t *a3000);
sword call_BSR(a3000_t *a3000);
sword call_Bcc(a3000_t *a3000);
sword call_MOVEQ(a3000_t *a3000);
sword call_PACK(a3000_t *a3000);
sword call_UNPK(a3000_t *a3000);
sword call_DIVU(a3000_t *a3000);
sword call_DIVS(a3000_t *a3000);
sword call_SBCD(a3000_t *a3000);
sword call_OR(a3000_t *a3000);
sword call_SUBA(a3000_t *a3000);
sword call_SUBX(a3000_t *a3000);
sword call_SUB(a3000_t *a3000);
sword call_CMPA(a3000_t *a3000);
sword call_CMPM(a3000_t *a3000);
sword call_EOR(a3000_t *a3000);
sword call_CMP(a3000_t *a3000);
sword call_MULU(a3000_t *a3000);
sword call_MULS(a3000_t *a3000);
sword call_ABCD(a3000_t *a3000);
sword call_EXG(a3000_t *a3000);
sword call_AND(a3000_t *a3000);
sword call_ADDA(a3000_t *a3000);
sword call_ADDX(a3000_t *a3000);
sword call_ADD(a3000_t *a3000);
sword call_ASd(a3000_t *a3000);
sword call_LSd(a3000_t *a3000);
sword call_ROXd(a3000_t *a3000);
sword call_ROd(a3000_t *a3000);
sword call_BFFFO_BFEXTU(a3000_t *a3000);
sword call_BFEXTS(a3000_t *a3000);
sword call_BFINS(a3000_t *a3000);
sword call_BFTST(a3000_t *a3000);
sword call_BFCHG(a3000_t *a3000);
sword call_BFCLR(a3000_t *a3000);
sword call_BFSET(a3000_t *a3000);
sword call_P(a3000_t *a3000);
sword call_cpGEN(a3000_t *a3000);
sword call_cpDBcc(a3000_t *a3000);
sword call_cpTRAPcc(a3000_t *a3000);
sword call_cpScc(a3000_t *a3000);
sword call_cpSAVE(a3000_t *a3000);
sword call_cpRESTORE(a3000_t *a3000);


#endif