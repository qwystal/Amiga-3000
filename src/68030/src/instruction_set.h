#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include "typedefs.h"
#include "defines.h"

#include "instruction_set.c"

void signal(word signal); // in or out?

word get_SR(A3000 *a3000);
void set_SR(A3000 *a3000, word SR);

word get_CCR(A3000 *a3000);
void set_CCR(A3000 *a3000, word CCR);

sword look_up_instruction(A3000 *a3000);

static sword call_ORI_to_CCR(A3000 *a3000);
static sword call_ORI_to_SR(A3000 *a3000);
static sword call_ANDI_to_CCR(A3000 *a3000);
static sword call_ANDI_to_SR(A3000 *a3000);
static sword call_EORI_to_CCR(A3000 *a3000);
static sword call_EORI_to_SR(A3000 *a3000);
static sword call_ILLEGAL(A3000 *a3000);
static sword call_RESET(A3000 *a3000);
static sword call_NOP(A3000 *a3000);
static sword call_STOP(A3000 *a3000);
static sword call_RTE(A3000 *a3000);
static sword call_RTD(A3000 *a3000);
static sword call_RTS(A3000 *a3000);
static sword call_TRAPV(A3000 *a3000);
static sword call_RTR(A3000 *a3000);

static sword call_CAS2(A3000 *a3000);
static sword call_CAS(A3000 *a3000);
static sword call_CHK2_CMP2(A3000 *a3000);

static sword call_ORI(A3000 *a3000);

static sword call_ANDI(A3000 *a3000);
static sword call_SUBI(A3000 *a3000);
static sword call_ADDI(A3000 *a3000);
static sword call_EORI(A3000 *a3000);
static sword call_CMPI(A3000 *a3000);
static sword call_BTST(A3000 *a3000);
static sword call_BCHG(A3000 *a3000);
static sword call_BCLR(A3000 *a3000);
static sword call_BSET(A3000 *a3000);
static sword call_MOVES(A3000 *a3000);
static sword call_MOVEP(A3000 *a3000);
static sword call_MOVEA(A3000 *a3000);
static sword call_MOVE(A3000 *a3000);
static sword call_MOVE_from_SR(A3000 *a3000);
static sword call_NEGX(A3000 *a3000);
static sword call_MOVE_from_CCR(A3000 *a3000);
static sword call_CLR(A3000 *a3000);
static sword call_MOVE_to_CCR(A3000 *a3000);
static sword call_NEG(A3000 *a3000);
static sword call_MOVE_to_SR(A3000 *a3000);
static sword call_NOT(A3000 *a3000);
static sword call_EXT(A3000 *a3000);
static sword call_NBCD(A3000 *a3000);
static sword call_SWAP(A3000 *a3000);
static sword call_BKPT(A3000 *a3000);
static sword call_PEA(A3000 *a3000);
static sword call_TAS(A3000 *a3000);
static sword call_TST(A3000 *a3000);
static sword call_DIVSL_DIVUL(A3000 *a3000);
static sword call_TRAP(A3000 *a3000);
static sword call_LINK(A3000 *a3000);
static sword call_UNLK(A3000 *a3000);
static sword call_MOVE_USP(A3000 *a3000);
static sword call_MOVEC(A3000 *a3000);
static sword call_JMP(A3000 *a3000);
static sword call_JSR(A3000 *a3000);
static sword call_MOVEM(A3000 *a3000);
static sword call_LEA(A3000 *a3000);
static sword call_CHK(A3000 *a3000);
static sword call_DBcc(A3000 *a3000);
static sword call_TRAPcc(A3000 *a3000);
static sword call_Scc(A3000 *a3000);
static sword call_SUBQ(A3000 *a3000);
static sword call_ADDQ(A3000 *a3000);
static sword call_BRA(A3000 *a3000);
static sword call_BSR(A3000 *a3000);
static sword call_Bcc(A3000 *a3000);
static sword call_MOVEQ(A3000 *a3000);
static sword call_PACK(A3000 *a3000);
static sword call_UNPK(A3000 *a3000);
static sword call_DIVU(A3000 *a3000);
static sword call_DIVS(A3000 *a3000);
static sword call_SBCD(A3000 *a3000);
static sword call_OR(A3000 *a3000);
static sword call_SUBA(A3000 *a3000);
static sword call_SUBX(A3000 *a3000);
static sword call_SUB(A3000 *a3000);
static sword call_CMPA(A3000 *a3000);
static sword call_CMPM(A3000 *a3000);
static sword call_EOR(A3000 *a3000);
static sword call_CMP(A3000 *a3000);
static sword call_MULU(A3000 *a3000);
static sword call_MULS(A3000 *a3000);
static sword call_ABCD(A3000 *a3000);
static sword call_EXG(A3000 *a3000);
static sword call_AND(A3000 *a3000);
static sword call_ADDA(A3000 *a3000);
static sword call_ADDX(A3000 *a3000);
static sword call_ADD(A3000 *a3000);
static sword call_ASd(A3000 *a3000);
static sword call_LSd(A3000 *a3000);
static sword call_ROXd(A3000 *a3000);
static sword call_ROd(A3000 *a3000);
static sword call_BFFFO_BFEXTU(A3000 *a3000);
static sword call_BFEXTS(A3000 *a3000);
static sword call_BFINS(A3000 *a3000);
static sword call_BFTST(A3000 *a3000);
static sword call_BFCHG(A3000 *a3000);
static sword call_BFCLR(A3000 *a3000);
static sword call_BFSET(A3000 *a3000);
static sword call_P(A3000 *a3000);
static sword call_cpGEN(A3000 *a3000);
static sword call_cpDBcc(A3000 *a3000);
static sword call_cpTRAPcc(A3000 *a3000);
static sword call_cpScc(A3000 *a3000);
static sword call_cpSAVE(A3000 *a3000);
static sword call_cpRESTORE(A3000 *a3000);

#endif