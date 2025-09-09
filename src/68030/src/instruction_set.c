/*
    This file contains:
        - the function to decode the opcode
        - every single instruction of the cpu
*/

#include <stdio.h>

#include "typedefs.h"
#include "instruction_set.h"

#include "memory.h"
#include "debug.h"
#include "addressing_modes.h"

/*  
    I put static on all the function that aren't intended 
    to be used by C files that include this file to hide them
*/

/* get the value of the Status Register */
static word get_SR(A3000 *a3000) 
{
    word SR = 0;
    SR |= a3000->cpu.SR.CCR.C;
    SR |= (a3000->cpu.SR.CCR.V << 1);
    SR |= (a3000->cpu.SR.CCR.Z << 2);
    SR |= (a3000->cpu.SR.CCR.N << 3);
    SR |= (a3000->cpu.SR.CCR.X << 4);
    SR |= (a3000->cpu.SR.I0 << 8);
    SR |= (a3000->cpu.SR.I1 << 9);
    SR |= (a3000->cpu.SR.I2 << 10);
    SR |= (a3000->cpu.SR.M << 12);
    SR |= (a3000->cpu.SR.S << 13);
    SR |= (a3000->cpu.SR.T0 << 14);
    SR |= (a3000->cpu.SR.T1 << 15);
    return SR;
}

/* set the value of the Status Register */
static void set_SR(A3000 *a3000, word SR) 
{
    a3000->cpu.SR.CCR.C = (SR & 0x01);
    a3000->cpu.SR.CCR.V = !!(SR & 0x02);
    a3000->cpu.SR.CCR.Z = !!(SR & 0x04);
    a3000->cpu.SR.CCR.N = !!(SR & 0x08);
    a3000->cpu.SR.CCR.X = !!(SR & 0x10);
    a3000->cpu.SR.I0 = !!(SR & 0x100);
    a3000->cpu.SR.I1 = !!(SR & 0x200);
    a3000->cpu.SR.I2 = !!(SR & 0x400);
    a3000->cpu.SR.M = !!(SR & 0x1000);
    a3000->cpu.SR.S = !!(SR & 0x2000);
    a3000->cpu.SR.T0 = !!(SR & 0x4000);
    a3000->cpu.SR.T1 = !!(SR & 0x8000);
}

/* get the value of the Condition Code Register (the operation flags reside there) */
static word get_CCR(A3000 *a3000) { 
    word CCR = 0;
    CCR |= a3000->cpu.SR.CCR.C;
    CCR |= (a3000->cpu.SR.CCR.V << 1);
    CCR |= (a3000->cpu.SR.CCR.Z << 2);
    CCR |= (a3000->cpu.SR.CCR.N << 3);
    CCR |= (a3000->cpu.SR.CCR.X << 4);
    return CCR;
}

/* set the value of the Condition Code Register (the operation flags reside there) */
static void set_CCR(A3000 *a3000, word CCR) { 
    a3000->cpu.SR.CCR.C = (CCR & 0x01);
    a3000->cpu.SR.CCR.V = !!(CCR & 0x02);
    a3000->cpu.SR.CCR.Z = !!(CCR & 0x04);
    a3000->cpu.SR.CCR.N = !!(CCR & 0x08);
    a3000->cpu.SR.CCR.X = !!(CCR & 0x10);
}

/* 

    this giant mess basically just splits the opcode into chunks and uses them
    to find a specific instruction, which then gets called.
    (this doesn't look elegant to me)

*/

/* here begins the implementation of the actual instructions */

void signal(word signal) {

}

static sword call_TRAP(A3000 *a3000) {
    return 0;
}

static sword call_ORI_to_CCR(A3000 *a3000) {
    a3000->cpu.PC += 2;

    if (!a3000->cpu.SR.S)
    {
        exception(a3000, VEC_PRIVILEGE_VIOLATION);
        return -INS_ORI_TO_CCR;
    }

    word immediate = rw_mem(a3000, a3000->cpu.PC);
    a3000->cpu.PC += 2;

    a3000->cpu.SR.CCR.C |= (immediate & 0x01);
    a3000->cpu.SR.CCR.V |= !!(immediate & 0x02);
    a3000->cpu.SR.CCR.Z |= !!(immediate & 0x04);
    a3000->cpu.SR.CCR.N |= !!(immediate & 0x08);
    a3000->cpu.SR.CCR.X |= !!(immediate & 0x10);

    return INS_ORI_TO_CCR;
}

static sword call_ORI_to_SR(A3000 *a3000) {
    a3000->cpu.PC += 2;

    if (!a3000->cpu.SR.S)
    {
        exception(a3000, VEC_PRIVILEGE_VIOLATION);
        return -INS_ORI_TO_SR;
    }

    word immediate = rw_mem(a3000, a3000->cpu.PC);
    a3000->cpu.PC += 2;

    a3000->cpu.SR.CCR.C |= (immediate & 0x01);
    a3000->cpu.SR.CCR.V |= !!(immediate & 0x02);
    a3000->cpu.SR.CCR.Z |= !!(immediate & 0x04);
    a3000->cpu.SR.CCR.N |= !!(immediate & 0x08);
    a3000->cpu.SR.CCR.X |= !!(immediate & 0x10);
    a3000->cpu.SR.I0 |= !!(immediate & 0x100);
    a3000->cpu.SR.I1 |= !!(immediate & 0x200);
    a3000->cpu.SR.I2 |= !!(immediate & 0x400);
    a3000->cpu.SR.M |= !!(immediate & 0x1000);
    a3000->cpu.SR.S |= !!(immediate & 0x2000);
    a3000->cpu.SR.T0 |= !!(immediate & 0x4000);
    a3000->cpu.SR.T1 |= !!(immediate & 0x8000);

    return INS_ORI_TO_SR;
}

static sword call_ANDI_to_CCR(A3000 *a3000) {
    a3000->cpu.PC += 2;

    if (!a3000->cpu.SR.S)
    {
        exception(a3000, VEC_PRIVILEGE_VIOLATION);
        return -INS_ANDI_TO_CCR;
    }

    word immediate = rw_mem(a3000, a3000->cpu.PC);
    a3000->cpu.PC += 2;

    a3000->cpu.SR.CCR.C &= (immediate & 0x01);
    a3000->cpu.SR.CCR.V &= !!(immediate & 0x02);
    a3000->cpu.SR.CCR.Z &= !!(immediate & 0x04);
    a3000->cpu.SR.CCR.N &= !!(immediate & 0x08);
    a3000->cpu.SR.CCR.X &= !!(immediate & 0x10);

    return INS_ANDI_TO_CCR;
}

static sword call_ANDI_to_SR(A3000 *a3000) {
    a3000->cpu.PC += 2;

    if (!a3000->cpu.SR.S)
    {
        exception(a3000, VEC_PRIVILEGE_VIOLATION);
        return -INS_ANDI_TO_SR;
    }

    word immediate = rw_mem(a3000, a3000->cpu.PC);
    a3000->cpu.PC += 2;

    a3000->cpu.SR.CCR.C &= (immediate & 0x01);
    a3000->cpu.SR.CCR.V &= !!(immediate & 0x02);
    a3000->cpu.SR.CCR.Z &= !!(immediate & 0x04);
    a3000->cpu.SR.CCR.N &= !!(immediate & 0x08);
    a3000->cpu.SR.CCR.X &= !!(immediate & 0x10);
    a3000->cpu.SR.I0 &= !!(immediate & 0x100);
    a3000->cpu.SR.I1 &= !!(immediate & 0x200);
    a3000->cpu.SR.I2 &= !!(immediate & 0x400);
    a3000->cpu.SR.M &= !!(immediate & 0x1000);
    a3000->cpu.SR.S &= !!(immediate & 0x2000);
    a3000->cpu.SR.T0 &= !!(immediate & 0x4000);
    a3000->cpu.SR.T1 &= !!(immediate & 0x8000);

    return INS_ANDI_TO_SR;
}

static sword call_EORI_to_CCR(A3000 *a3000) {
    a3000->cpu.PC += 2;

    if (!a3000->cpu.SR.S)
    {
        exception(a3000, VEC_PRIVILEGE_VIOLATION);
        return -INS_EORI_TO_CCR;
    }

    word immediate = rw_mem(a3000, a3000->cpu.PC);
    a3000->cpu.PC += 2;

    a3000->cpu.SR.CCR.C ^= (immediate & 0x01);
    a3000->cpu.SR.CCR.V ^= !!(immediate & 0x02);
    a3000->cpu.SR.CCR.Z ^= !!(immediate & 0x04);
    a3000->cpu.SR.CCR.N ^= !!(immediate & 0x08);
    a3000->cpu.SR.CCR.X ^= !!(immediate & 0x10);

    return INS_EORI_TO_CCR;
}

static sword call_EORI_to_SR(A3000 *a3000) {
    a3000->cpu.PC += 2;

    if (!a3000->cpu.SR.S)
    {
        exception(a3000, VEC_PRIVILEGE_VIOLATION);
        return -INS_EORI_TO_SR;
    }

    word immediate = rw_mem(a3000, a3000->cpu.PC);
    a3000->cpu.PC += 2;

    a3000->cpu.SR.CCR.C ^= (immediate & 0x01);
    a3000->cpu.SR.CCR.V ^= !!(immediate & 0x02);
    a3000->cpu.SR.CCR.Z ^= !!(immediate & 0x04);
    a3000->cpu.SR.CCR.N ^= !!(immediate & 0x08);
    a3000->cpu.SR.CCR.X ^= !!(immediate & 0x10);
    a3000->cpu.SR.I0 ^= !!(immediate & 0x100);
    a3000->cpu.SR.I1 ^= !!(immediate & 0x200);
    a3000->cpu.SR.I2 ^= !!(immediate & 0x400);
    a3000->cpu.SR.M ^= !!(immediate & 0x1000);
    a3000->cpu.SR.S ^= !!(immediate & 0x2000);
    a3000->cpu.SR.T0 ^= !!(immediate & 0x4000);
    a3000->cpu.SR.T1 ^= !!(immediate & 0x8000);

    return INS_EORI_TO_SR;
}

static sword call_ILLEGAL(A3000 *a3000) {
    exception(a3000, VEC_ILLEGAL_INSTRUCTION);

    return INS_ILLEGAL;
}

static sword call_RESET(A3000 *a3000) {
    a3000->cpu.PC += 2;

    if (!a3000->cpu.SR.S)
    {
        exception(a3000, VEC_PRIVILEGE_VIOLATION);
        return -INS_RESET;
    }
    
    signal(0); // RSTO asserted for 512 clock periods, probably RESET?

    return INS_RESET;
}

static sword call_NOP(A3000 *a3000) {
    a3000->cpu.PC += 2;

    // NOP instruction does not begin execution, until all pending bus cycles have completed to synchronize the pipeline

    return INS_NOP;
}

static sword call_STOP(A3000 *a3000) {
    a3000->cpu.PC += 2;
    if (!a3000->cpu.SR.S)
    {
        exception(a3000, VEC_PRIVILEGE_VIOLATION);
        call_TRAP(a3000);
        return -INS_STOP;
    }
    
    set_SR(a3000, rw_mem(a3000, a3000->cpu.PC));

    return INS_STOP;
}

static sword call_RTE(A3000 *a3000) {
    a3000->cpu.PC += 2;

    if (!a3000->cpu.SR.S)
    {
        exception(a3000, VEC_PRIVILEGE_VIOLATION);
        call_TRAP(a3000);
        return -INS_RTE;
    }
    
    set_SR(a3000, rw_mem(a3000, a3000->cpu.GPR.A[7]));
    a3000->cpu.GPR.A[7] += 2;
    a3000->cpu.PC = rl_mem(a3000, a3000->cpu.GPR.A[7]);
    a3000->cpu.GPR.A[7] += 4;

    switch (rw_mem(a3000, a3000->cpu.GPR.A[7]) >> 12) // Find out the Stack Frame using the Format/Offset word and deallocate it.
    {
        case 0b0000:
            break;
        
        case 0b0001:
            break;

        case 0b0010:
            a3000->cpu.GPR.A[7] += 4;
            break;

        case 0b1001:
            a3000->cpu.GPR.A[7] += 8;
            break;

        case 0b1010:
            a3000->cpu.GPR.A[7] += 24;
            break;

        case 0b1011:
            a3000->cpu.GPR.A[7] += 84;
            break;

        case 0b1100:
            a3000->cpu.GPR.A[7] += 16;
            break;
        
        default:
            logError("Unsupported Stack Exception Frame", *a3000);
            break;
    }

    return INS_RTE;
}

static sword call_RTD(A3000 *a3000) {
    a3000->cpu.PC += 2;

    slword displacement = (slword) rw_mem(a3000, a3000->cpu.PC);
    a3000->cpu.PC += 2;

    a3000->cpu.PC = rl_mem(a3000, a3000->cpu.GPR.A[7]);
    a3000->cpu.GPR.A[7] += 4 + displacement;

    return INS_RTD;
}

static sword call_RTS(A3000 *a3000) {
    a3000->cpu.PC += 2;

    a3000->cpu.PC = rl_mem(a3000, a3000->cpu.GPR.A[7]);
    a3000->cpu.GPR.A[7] += 4;

    return INS_RTS;
}

static sword call_TRAPV(A3000 *a3000) {
    a3000->cpu.PC += 2;

    if (a3000->cpu.SR.CCR.V)
    {
        exception(a3000, VEC_TRAP_INSTRUCTION);
        call_TRAP(a3000);
    }

    return;
}

static sword call_RTR(A3000 *a3000) {
    set_CCR(a3000, rw_mem(a3000, a3000->cpu.GPR.A[7]));
    a3000->cpu.GPR.A[7] += 2;
    a3000->cpu.PC = rl_mem(a3000, a3000->cpu.GPR.A[7]);
    a3000->cpu.GPR.A[7] += 4;

    return INS_RTR;
}

static sword call_ORI(A3000 *a3000) {

    return INS_ORI;
}

static sword call_CAS2(A3000 *a3000) {
    return 0;
}

static sword call_CAS(A3000 *a3000) {
    return 0;
}

static sword call_CHK2_CMP2(A3000 *a3000) {
    return 0;
}

static sword call_ANDI(A3000 *a3000) {
    return 0;
}

static sword call_SUBI(A3000 *a3000) {
    return 0;
}

static sword call_ADDI(A3000 *a3000) {
    return 0;
}

static sword call_EORI(A3000 *a3000) {
    return 0;
}

static sword call_CMPI(A3000 *a3000) {
    return 0;
}

static sword call_BTST(A3000 *a3000) {
    return 0;
}

static sword call_BCHG(A3000 *a3000) {
    return 0;
}

static sword call_BCLR(A3000 *a3000) {
    return 0;
}

static sword call_BSET(A3000 *a3000) {
    return 0;
}

static sword call_MOVES(A3000 *a3000) {
    return 0;
}

static sword call_MOVEP(A3000 *a3000) {
    return 0;
}

static sword call_MOVEA(A3000 *a3000) {
    return 0;
}

static sword call_MOVE(A3000 *a3000) {
    return 0;
}

static sword call_MOVE_from_SR(A3000 *a3000) {
    return 0;
}

static sword call_NEGX(A3000 *a3000) {
    return 0;
}

static sword call_MOVE_from_CCR(A3000 *a3000) {
    return 0;
}

static sword call_CLR(A3000 *a3000) {
    return 0;
}

static sword call_MOVE_to_CCR(A3000 *a3000) {
    return 0;
}

static sword call_NEG(A3000 *a3000) {
    return 0;
}

static sword call_MOVE_to_SR(A3000 *a3000) {
    return 0;
}

static sword call_NOT(A3000 *a3000) {
    return 0;
}

static sword call_EXT(A3000 *a3000) {
    return 0;
}

static sword call_NBCD(A3000 *a3000) {
    return 0;
}

static sword call_SWAP(A3000 *a3000) {
    return 0;
}

static sword call_BKPT(A3000 *a3000) {
    return 0;
}

static sword call_PEA(A3000 *a3000) {
    return 0;
}

static sword call_TAS(A3000 *a3000) {
    return 0;
}

static sword call_TST(A3000 *a3000) {
    return 0;
}

static sword call_DIVSL_DIVUL(A3000 *a3000) {
    return 0;
}

static sword call_LINK(A3000 *a3000) {
    return 0;
}

static sword call_UNLK(A3000 *a3000) {
    return 0;
}

static sword call_MOVE_USP(A3000 *a3000) {
    return 0;
}

static sword call_MOVEC(A3000 *a3000) {
    return 0;
}

static sword call_JMP(A3000 *a3000) {
    return 0;
}

static sword call_JSR(A3000 *a3000) {
    return 0;
}

static sword call_MOVEM(A3000 *a3000) {
    return 0;
}

static sword call_LEA(A3000 *a3000) {
    return 0;
}

static sword call_CHK(A3000 *a3000) {
    return 0;
}

static sword call_DBcc(A3000 *a3000) {
    return 0;
}

static sword call_TRAPcc(A3000 *a3000) {
    return 0;
}

static sword call_Scc(A3000 *a3000) {
    return 0;
}

static sword call_SUBQ(A3000 *a3000) {
    return 0;
}

static sword call_ADDQ(A3000 *a3000) {
    return 0;
}

static sword call_BRA(A3000 *a3000) {
    return 0;
}

static sword call_BSR(A3000 *a3000) {
    return 0;
}

static sword call_Bcc(A3000 *a3000) {
    return 0;
}

static sword call_MOVEQ(A3000 *a3000) {
    return 0;
}

static sword call_PACK(A3000 *a3000) {
    return 0;
}

static sword call_UNPK(A3000 *a3000) {
    return 0;
}

static sword call_DIVU(A3000 *a3000) {
    return 0;
}

static sword call_DIVS(A3000 *a3000) {
    return 0;
}

static sword call_SBCD(A3000 *a3000) {
    return 0;
}

static sword call_OR(A3000 *a3000) {
    return 0;
}

static sword call_SUBA(A3000 *a3000) {
    return 0;
}

static sword call_SUBX(A3000 *a3000) {
    return 0;
}

static sword call_SUB(A3000 *a3000) {
    return 0;
}

static sword call_CMPA(A3000 *a3000) {
    return 0;
}

static sword call_CMPM(A3000 *a3000) {
    return 0;
}

static sword call_EOR(A3000 *a3000) {
    return 0;
}

static sword call_CMP(A3000 *a3000) {
    return 0;
}

static sword call_MULU(A3000 *a3000) {
    return 0;
}

static sword call_MULS(A3000 *a3000) {
    return 0;
}

static sword call_ABCD(A3000 *a3000) {
    return 0;
}

static sword call_EXG(A3000 *a3000) {
    return 0;
}

static sword call_AND(A3000 *a3000) {
    return 0;
}

static sword call_ADDA(A3000 *a3000) {
    return 0;
}

static sword call_ADDX(A3000 *a3000) {
    return 0;
}

static sword call_ADD(A3000 *a3000) {
    

    // set flag
    return 0;
}

static sword call_ASd(A3000 *a3000) {
    return 0;
}

static sword call_LSd(A3000 *a3000) {
    return 0;
}

static sword call_ROXd(A3000 *a3000) {
    return 0;
}

static sword call_ROd(A3000 *a3000) {
    return 0;
}

static sword call_BFFFO_BFEXTU(A3000 *a3000) {
    return 0;
}

static sword call_BFEXTS(A3000 *a3000) {
    return 0;
}

static sword call_BFINS(A3000 *a3000) {
    return 0;
}

static sword call_BFTST(A3000 *a3000) {
    return 0;
}

static sword call_BFCHG(A3000 *a3000) {
    return 0;
}

static sword call_BFCLR(A3000 *a3000) {
    return 0;
}

static sword call_BFSET(A3000 *a3000) {
    return 0;
}

static sword call_P(A3000 *a3000) {
    return 0;
}

static sword call_cpGEN(A3000 *a3000) {
    return 0;
}

static sword call_cpDBcc(A3000 *a3000) {
    return 0;
}

static sword call_cpTRAPcc(A3000 *a3000) {
    return 0;
}

static sword call_cpScc(A3000 *a3000) {
    return 0;
}

static sword call_cpSAVE(A3000 *a3000) {
    return 0;
}

static sword call_cpRESTORE(A3000 *a3000) {
    return 0;
}

sword look_up_instruction(A3000 *a3000) {
    a3000->opcode = rw_mem(a3000, a3000->cpu.PC);
    word chunk_1 = (a3000->opcode >> 12) & 0b1111; // Extract the 1st-4th bits
    word chunk_2 = (a3000->opcode >> 9) & 0b111; // Extract the 5th-7th bits
    word chunk_3 = (a3000->opcode >> 8) & 0b1; // Extract the 8th bit
    word chunk_3_5 = (a3000->opcode >> 7) & 0b11; // Extract the 8th and 9th bits
    word chunk_4 = (a3000->opcode >> 6) & 0b11; // Extract the 9th and 10th bits
    word chunk_4_5 = (a3000->opcode >> 4) & 0b111; // Extract the 10th-12th bits
    word chunk_4_5_5 = (a3000->opcode >> 4) & 0b11111; // Extract the 8th-12th bits
    word chunk_5 = (a3000->opcode >> 3) & 0b111; // Extract the 11th-13th bits
    word chunk_5_5 = (a3000->opcode >> 3) & 0b11; // Extract the 11th and 12th bits
    // isnt it the other way around, the 1st bit is 12th and so on? lol
    // return after every call?
    
    switch (a3000->opcode) // Switch-statement for completely pre-defined a3000->opcodes
    {
        case 0b0000000000111100:
            return call_ORI_to_CCR(a3000);
            break;

        case 0b0000000001111100:
            return call_ORI_to_SR(a3000);
            break;

        case 0b0000001000111100:
            return call_ANDI_to_CCR(a3000);
            break;

        case 0b0000001001111100:
            return call_ANDI_to_SR(a3000);
            break;

        case 0b0000101000111100:
            return call_EORI_to_CCR(a3000);
            break;

        case 0b0000101001111100:
            return call_EORI_to_SR(a3000);
            break;

        case 0b0100101011111100:
            return call_ILLEGAL(a3000);
            break;

        case 0b0100111001110000:
            return call_RESET(a3000);
            break;

        case 0b0100111001110001:
            return call_NOP(a3000);
            break;

        case 0b0100111001110010:
            return call_STOP(a3000);
            break;

        case 0b0100111001110011:
            return call_RTE(a3000);
            break;

        case 0b0100111001110100:
            return call_RTD(a3000);
            break;

        case 0b0100111001110101:
            return call_RTS(a3000);
            break;

        case 0b0100111001110110:
            return call_TRAPV(a3000);
            break;

        case 0b0100111001110111:
            return call_RTR(a3000);
            break;

        default:
            break;
    }
    // and here begins the mess
    switch (chunk_1)
    {
        case 0b0000:
            switch (chunk_3)
            {
                case 0b0:
                    if (chunk_4 == 0b11)
                    {
                        if ((chunk_2 >> 2) == 0b1)
                        {
                            if (chunk_5 == 0b111 && (a3000->opcode & 0b111) == 0b100)
                            {
                                return call_CAS2(a3000);
                                break;
                            }
                            else
                            {
                                return call_CAS(a3000);
                                break;
                            }
                        }
                        else
                        {
                            return call_CHK2_CMP2(a3000);
                            break;
                        }
                    }
                    
                    switch (chunk_2)
                    {
                        case 0b000:
                            return call_ORI(a3000);
                            break;

                        case 0b001:
                            return call_ANDI(a3000);
                            break;

                        case 0b010:
                            return call_SUBI(a3000);
                            break;

                        case 0b011:
                            return call_ADDI(a3000);
                            break;

                        case 0b101:
                            return call_EORI(a3000);
                            break;

                        case 0b110:
                            return call_CMPI(a3000);
                            break;

                        case 0b100:
                            switch (chunk_4)
                            {
                                case 0b00:
                                    return call_BTST(a3000);
                                    break;

                                case 0b01:
                                    return call_BCHG(a3000);
                                    break;

                                case 0b10:
                                    return call_BCLR(a3000);
                                    break;

                                case 0b11:
                                    return call_BSET(a3000);
                                    break;
                                
                                default:
                                    break;
                            }

                        case 0b111:
                            return call_MOVES(a3000);
                            break;

                        default:
                            break;
                    }
                    break;
                
                case 0b1:
                    if (chunk_5 == 0b001)
                    {
                        return call_MOVEP(a3000);
                        break;
                    }
                    
                    switch(chunk_4)
                    {
                        case 0b00:
                            return call_BTST(a3000);
                            break;
                        
                        case 0b01:
                            return call_BCHG(a3000);
                            break;

                        case 0b10:
                            return call_BCLR(a3000);
                            break;

                        case 0b11:
                            return call_BSET(a3000);
                            break;
                        
                        default:
                            break;
                    }
                
                default:
                    break;
            }
            break;

        /*
            does this work as intended? before, I used case 0b0001 || 0b0010 etc., 
            but I found out C first evaluates the two values (combines them), and
            only after that execute the case statement.
        */
        case 0b0001:
        case 0b0010:
        case 0b0011:
            if (chunk_3 == 0b0 && chunk_4 == 0b001)
            {
                return call_MOVEA(a3000);
                break;
            }
            else
            {
                return call_MOVE(a3000);
                break;
            }
            break;

        case 0b0100:
            switch (chunk_2)
            {
                case 0b000:
                    if (chunk_4 == 0b11)
                    {
                        return call_MOVE_from_SR(a3000);
                    }
                    else
                    {
                        return call_NEGX(a3000);
                    }
                    break;

                case 0b001:
                    if (chunk_4 == 0b11)
                    {
                        return call_MOVE_from_CCR(a3000);
                    }
                    else
                    {
                        return call_CLR(a3000);
                    }
                    break;

                case 0b010:
                    if (chunk_4 == 0b11)
                    {
                        return call_MOVE_to_CCR(a3000);
                    }
                    else
                    {
                        return call_NEG(a3000);
                    }
                    break;

                case 0b011:
                    if (chunk_4 == 0b11)
                    {
                        return call_MOVE_to_SR(a3000);
                    }
                    else
                    {
                        return call_NOT(a3000);
                    }
                    break;

                case 0b100:
                    if ((chunk_4 >> 1) == 0b1)
                    {
                        return call_EXT(a3000);
                        break;
                    }
                    else if (chunk_4 == 0b00)
                    {
                        return call_NBCD(a3000);
                        break;
                    }
                    else if (chunk_4 == 0b01)
                    {
                        if (chunk_5 == 0b000)
                        {
                            return call_SWAP(a3000);
                        }
                        else if (chunk_5 == 0b001)
                        {
                            return call_BKPT(a3000);
                        }
                        else
                        {
                            return call_PEA(a3000);
                        }
                        break;
                    }
                    break;

                case 0b101:
                    if (chunk_4 == 0b11)
                    {
                        return call_TAS(a3000);
                    }
                    else
                    {
                        return call_TST(a3000);
                    }
                    break;

                case 0b110:
                    return call_DIVSL_DIVUL(a3000);
                    break;
                    
                case 0b111:
                    switch (chunk_3_5)
                    {
                        case 0b00:
                            switch (chunk_4_5)
                            {
                                case 0b100:
                                    return call_TRAP(a3000);
                                    break;

                                case 0b101:
                                    if ((a3000->opcode >> 3) & 0b1)
                                    {
                                        return call_LINK(a3000);
                                    }
                                    else
                                    {
                                        return call_UNLK(a3000);
                                    }
                                    break;

                                case 0b110:
                                    return call_MOVE_USP(a3000);
                                    break;

                                case 0b111:
                                    call_MOVEC(a3000);
                                    break;
                                
                                default:
                                    break;
                            }
                            break;
                        
                        case 0b01:
                            if ((a3000->opcode >> 6) & 0b1)
                            {
                                return call_JMP(a3000);
                            }
                            else
                            {
                                return call_JSR(a3000);
                            }
                            break;

                        default:
                            break;
                    }
                    
                    
                default:
                    break;
            }
            if (((a3000->opcode >> 11) & 0b1) == 0b1 && ((a3000->opcode >> 7) & 0b111) == 0b001)
            {
                return call_MOVEM(a3000);
                break;
            }
            if (chunk_3 == 0b1 && chunk_4 == 0b11)
            {
                return call_LEA(a3000);
                break;
            }
            if (chunk_3 == 0b1 && chunk_4 == 0b10)
            {
                return call_CHK(a3000);
                break;
            }
            break;

        case 0b0101:
            if (chunk_4 == 0b11)
            {
                if (chunk_5 == 0b001)
                {
                    return call_DBcc(a3000);
                    break;
                }
                else if (chunk_5 == 0b111)
                {
                    return call_TRAPcc(a3000);
                }
                else
                {
                    return call_Scc(a3000);
                    break;
                }
            }

            if (chunk_3 == 0b1)
            {
                return call_SUBQ(a3000);
                break;
            }
            else
            {
                return call_ADDQ(a3000);
                break;
            }
            break;
            
        case 0b0110:
            if (chunk_2 == 0b000 && chunk_3 == 0b0)
            {
                return call_BRA(a3000);
                break;
            }
            else if (chunk_2 == 0b000 && chunk_3 == 0b1)
            {
                return call_BSR(a3000);
                break;
            }
            else
            {
                return call_Bcc(a3000);
                break;
            }
            break;

        case 0b0111:
            return call_MOVEQ(a3000);
            break;

        case 0b1000:
            switch (chunk_4_5_5)
            {
                case 0b10100:
                    return call_PACK(a3000);
                    break;

                case 0b11000:
                    return call_UNPK(a3000);
                    break;
                
                default:
                    break;
            }
            if (chunk_4 == 0b11)
            {
                if (chunk_3 == 0b0)
                {
                    return call_DIVU(a3000);
                    break;
                }
                else
                {
                    return call_DIVS(a3000);
                    break;
                }
            }
            if (chunk_4_5_5 == 0b10000)
            {
                return call_SBCD(a3000);
                break;
            }
            else
            {
                return call_OR(a3000);
                break;
            }
            break;
            
        case 0b1001:
            if (chunk_4 == 0b11)
            {
                return call_SUBA(a3000);
                break;
            }
            else if (chunk_3 == 0b1 && (chunk_5 == 0b001 || chunk_5 == 0b000))
            {
                return call_SUBX(a3000);
                break;
            }
            else
            {
                return call_SUB(a3000);
                break;
            }
            break;
            
        case 0b1011:
            if (chunk_4 == 0b11)
            {
                return call_CMPA(a3000);
                break;
            }
            else if (chunk_3 == 0b1 && (chunk_5 == 0b001 || chunk_5 == 0b000))
            {
                return call_CMPM(a3000);
                break;
            }
            else if (chunk_3 == 0b1)
            {
                return call_EOR(a3000);
                break;
            }
            else
            {
                return call_CMP(a3000);
                break;
            }
            break;
            
        case 0b1100:
            if (chunk_4 == 0b11)
            {
                if (chunk_3 == 0b0)
                {
                    return call_MULU(a3000);
                    break;
                }
                else
                {
                    return call_MULS(a3000);
                    break;
                }
            }
            if (chunk_4_5_5 == 0b10000)
            {
                return call_ABCD(a3000);
                break;
            }
            else if (chunk_4_5_5 == 0b10100 || chunk_4_5_5 == 0b11000)
            {
                return call_EXG(a3000);
                break;
            }
            else
            {
                return call_AND(a3000);
                break;
            }
            break;

        case 0b1101:
            if (chunk_4 == 0b11)
            {
                return call_ADDA(a3000);
                break;
            }
            else if (chunk_3 == 0b1 && (chunk_5 == 0b001 || chunk_5 == 0b000))
            {
                return call_ADDX(a3000);
                break;
            }
            else
            {
                return call_ADD(a3000);
                break;
            }
            break;

        case 0b1110:
            if (chunk_4 == 0b11)
            {
                switch (chunk_2)
                {
                    case 0b000:
                        return call_ASd(a3000); // ASL, ASR
                        break;

                    case 0b001:
                        return call_LSd(a3000); // LSL, LSR
                        break;

                    case 0b010:
                        return call_ROXd(a3000);
                        break;

                    case 0b011:
                        return call_ROd(a3000); // ROL, ROR
                        break;
                    
                    default:
                        break;
                }

                if (chunk_3 == 0b1)
                {
                    switch (chunk_2)
                    {
                    case 0b100:
                        return call_BFFFO_BFEXTU(a3000);
                        break;

                    case 0b101:
                        return call_BFEXTS(a3000);
                        break;

                    case 0b111:
                        return call_BFINS(a3000);
                        break;
                    
                    default:
                        break;
                    }
                }
                else
                {
                    switch (chunk_2)
                    {
                    case 0b100:
                        return call_BFTST(a3000);
                        break;

                    case 0b101:
                        return call_BFCHG(a3000);
                        break;

                    case 0b110:
                        return call_BFCLR(a3000);
                        break;

                    case 0b111:
                        return call_BFSET(a3000);
                        break;
                    
                    default:
                        break;
                    }
                }
                
            }
            else
            {
                switch (chunk_5_5)
                {
                    case 0b00:
                        return call_ASd(a3000);
                        break;

                    case 0b01:
                        return call_LSd(a3000);
                        break;

                    case 0b10:
                        return call_ROXd(a3000);
                        break;

                    case 0b11:
                        return call_ROd(a3000);
                        break;
                    
                    default:
                        break;
                }
            }
            
        case 0b1111:
            word chunk = (a3000->opcode >> 6) & 0b111; // 8th-10th bit for special case
            switch (chunk)
            {
                case 0b000:
                    if (chunk_2 == 0b000)
                    {
                        return call_P(a3000); // PFLUSH, PFLUSHA, PLOAD, PMOVE, PTEST
                        break;
                    }
                    else
                    {
                        return call_cpGEN(a3000);
                        break;
                    }
                    
                case 0b001:
                    if (chunk_5 == 0b001)
                    {
                        return call_cpDBcc(a3000);
                        break;
                    }
                    else if (chunk_5 == 0b111)
                    {
                        return call_cpTRAPcc(a3000);
                        break;
                    }
                    else
                    {
                        return call_cpScc(a3000);
                        break;
                    }
                
                case 0b100:
                    return call_cpSAVE(a3000);
                    break;

                case 0b101:
                    return call_cpRESTORE(a3000);
                    break;

                default:
                    break;
            }
            

        default:
            exception(a3000, VEC_ILLEGAL_INSTRUCTION);
            break;
    }

    return a3000->opcode;
}
