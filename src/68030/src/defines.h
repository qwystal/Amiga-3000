#ifndef DEFINES_H
#define DEFINES_H

#define MAX_MEM_SIZE 0xFFFFFFFF // 4 GB
#define DEFAULT_MEM_SIZE 0x0200000 // 2 MB (configured as 1 MB "chip" and 1 MB "fast" RAM)

// signals
#define SIG_RSTO 1

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
#define INS_RTR 14

// Exception vectors
#define EXC_VEC_PRIVILEGE_VIOLATION 8

#endif