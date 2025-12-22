#ifndef DEFINES_H
#define DEFINES_H

#define BYTE_MAX 0xFF
#define WORD_MAX 0xFFFF
#define LWORD_MAX 0xFFFFFFFF
#define QWORD_MAX 0xFFFFFFFFFFFFFFFF

#define MAX_MEM_SIZE 0xFFFFFFFF // 4 GB
#define DEFAULT_MEM_SIZE 0x0200000 // 2 MB (configured as 1 MB "chip" and 1 MB "fast" RAM)

#define SET_V a3000->cpu.SR.CCR.V = 1
#define SET_C a3000->cpu.SR.CCR.C = 1
#define SET_Z a3000->cpu.SR.CCR.Z = 1
#define SET_N a3000->cpu.SR.CCR.N = 1
#define SET_X a3000->cpu.SR.CCR.X = 1
#define CLEAR_V a3000->cpu.SR.CCR.V = 0
#define CLEAR_C a3000->cpu.SR.CCR.C = 0
#define CLEAR_Z a3000->cpu.SR.CCR.Z = 0
#define CLEAR_N a3000->cpu.SR.CCR.N = 0
#define CLEAR_X a3000->cpu.SR.CCR.X = 0
// cpu pins
// function code signals
#define FC0 0
#define FC1 1
#define FC2 2

// address bus
#define A0 3
#define A0 3
#define A1 4
#define A2 5
#define A3 6
#define A4 7
#define A5 8
#define A6 9
#define A7 10
#define A8 11
#define A9 12
#define A10 13
#define A11 14
#define A12 15
#define A13 16
#define A14 17
#define A15 18
#define A16 19
#define A17 20
#define A18 21
#define A19 22
#define A20 23
#define A21 24
#define A22 25
#define A23 26
#define A24 27
#define A25 28
#define A26 29
#define A27 30
#define A28 31
#define A29 32
#define A30 33
#define A31 34

// data bus
#define D0 35
#define D1 36
#define D2 37
#define D3 38
#define D4 39
#define D5 40
#define D6 41
#define D7 42
#define D8 43
#define D9 44
#define D10 45
#define D11 46
#define D12 47
#define D13 48
#define D14 49
#define D15 50
#define D16 51
#define D17 52
#define D18 53
#define D19 54
#define D20 55
#define D21 56
#define D22 57
#define D23 58
#define D24 59
#define D25 60
#define D26 61
#define D27 62
#define D28 63
#define D29 64
#define D30 65
#define D31 66

// transfer size signal
#define SIZ0 67
#define SIZ1 68

// bus control signals

// operand cycle start
#define OCS 69
// External Cycle Start
#define ECS 70
// Read/Write
#define RW 71
// Read-Modify-Write Cycle
#define RMC 72
// Address Strobe
#define AS 73
// Data Strobe
#define DS 74
// Data Buffer Enable
#define DBEN 75
// Data Transfer and Size Acknowledge
#define DSACK0 76
// Data Transfer and Size Acknowledge
#define DSACK1 77
// Synchronous Termination
#define STERM 78

// CACHE CONTROL SIGNALS

// Cache Inhibit Input
#define CIIN 79
// Cache Inhibit Output
#define CIOUT 80
// Cache Burst Request
#define CBREQ 81
// Cache Burst Acknowledge
#define CBACK 82

// INTERRUPT CONTROL SIGNALS

// Interrupt Priority Level Signals
#define IPL0 83
#define IPL1 84
#define IPL2 85
// Interrupt Pending
#define IPEND 86
// Autovector
#define AVEC 87

// BUS ARBITRATION CONTROL SIGNALS

// Bus Request
#define BR 88
// Bus Grant
#define BG 89
// Bus Grant Acknowledge
#define BGACK 90

// BUS EXCEPTION CONTROL SIGNALS

// Reset
#define RESET 91
// Halt
#define HALT 92
// Bus Error
#define BERR 93

// EMULATOR SUPPORT SIGNALS

// Cache Disable
#define CDIS 94
// MMU Disable
#define MMUDIS 95
// Pipeline Refill
#define REFILL 96
// Internal Microsequencer Status
#define STATUS 97

// Clock
#define CLK 98

// Power Supply
#define VCC 99
// Ground
#define GND 100

// self assigned uids for each instruction
#define INS_ORI_TO_CCR 1
#define INS_ORI_TO_SR 2
#define INS_ANDI_TO_CCR 3
#define INS_ANDI_TO_SR 4
#define INS_EORI_TO_CCR 5
#define INS_EORI_TO_SR 6
#define INS_ILLEGAL 7
#define INS_RESET 8
#define INS_NOP 9
#define INS_STOP 10
#define INS_RTE 11
#define INS_RTD 12
#define INS_RTS 13
#define INS_TRAPV 14
#define INS_RTR 15
#define INS_CAS2 16
#define INS_CAS 17
#define INS_CHK2_CMP2 18
#define INS_ORI 19
#define INS_ANDI 20
#define INS_SUBI 21
#define INS_ADDI 22
#define INS_EORI 23
#define INS_CMPI 24
#define INS_BTST 25
#define INS_BCHG 26
#define INS_BCLR 27
#define INS_BSET 28
#define INS_MOVES 29
#define INS_MOVEP 30
#define INS_MOVEA 31
#define INS_MOVE 32
#define INS_MOVE_FROM_SR 33
#define INS_NEGX 34
#define INS_MOVE_FROM_CCR 35
#define INS_CLR 36
#define INS_MOVE_TO_CCR 37
#define INS_NEG 38
#define INS_MOVE_TO_SR 39
#define INS_NOT 40
#define INS_EXT 41
#define INS_NBCD 42
#define INS_SWAP 43
#define INS_BKPT 44
#define INS_PEA 45
#define INS_TAS 46
#define INS_TST 47
#define INS_DIVSL_DIVUL 48
#define INS_TRAP 49
#define INS_LINK 50
#define INS_UNLK 51
#define INS_MOVE_USP 52
#define INS_MOVEC 53
#define INS_JMP 54
#define INS_JSR 55
#define INS_MOVEM 56
#define INS_LEA 57
#define INS_CHK 58
#define INS_DBCC 59
#define INS_TRAPCC 60
#define INS_SCC 61
#define INS_SUBQ 62
#define INS_ADDQ 63
#define INS_BRA 64
#define INS_BSR 65
#define INS_BCC 66
#define INS_MOVEQ 67
#define INS_PACK 68
#define INS_UNPK 69
#define INS_DIVU 70
#define INS_DIVS 71
#define INS_SBCD 72
#define INS_OR 73
#define INS_SUBA 74
#define INS_SUBX 75
#define INS_SUB 76
#define INS_CMPA 77
#define INS_CMPM 78
#define INS_EOR 79
#define INS_CMP 80
#define INS_MULU 81
#define INS_MULS 82
#define INS_ABCD 83
#define INS_EXG 84
#define INS_AND 85
#define INS_ADDA 86
#define INS_ADDX 87
#define INS_ADD 88
#define INS_ASD 89
#define INS_LSD 90
#define INS_ROXD 91
#define INS_ROD 92
#define INS_BFFFO_BFEXTU 93
#define INS_BFEXTS 94
#define INS_BFINS 95
#define INS_BFTST 96
#define INS_BFCHG 97
#define INS_BFCLR 98
#define INS_BFSET 99
#define INS_P 100
#define INS_CPGEN 101
#define INS_CPDBCC 102
#define INS_CPTRAPCC 103
#define INS_CPSCC 104
#define INS_CPSAVE 105
#define INS_CPRESTORE 106

// Exception vectors
#define VEC_ILLEGAL_INSTRUCTION 4
#define VEC_TRAP_INSTRUCTION 7
#define VEC_PRIVILEGE_VIOLATION 8

// addressing mode categories
#define AMC_DATA 1
#define AMC_MEMORY 2
#define AMC_CONTROL 4
#define AMC_ALTERABLE 8
#define AMC_ALL 16

#endif