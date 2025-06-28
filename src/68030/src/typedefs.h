#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdint.h>

#include "defines.h"

typedef uint8_t byte;
typedef int8_t sbyte;
typedef uint16_t word;
typedef int16_t sword;
typedef uint32_t lword;
typedef int32_t slword;
typedef uint64_t qword;
typedef int64_t sqword;

typedef struct MC68030
{   
    sqword cycles;
    
    struct GPR // 32-bit General Purpose Registers
    {
        lword D[8];
        lword A[8]; // A[7] acts as the System Stack Pointer (SP)
    } GPR;
    
    lword PC; // 32-bit Program Counter
    
    lword ISP; // 32-bit Supervisor and Interrupt Stack Pointer
    
    lword MSP; // 32-bit Supervisor Stack Pointer
    
    lword VBR; // 32-bit Vector Base Register
    
    lword SFC; // 32-bit Alternate Function Code Register
    
    lword DFC; // 32-bit Alternate Function Code Register
    
    lword CACR; // 32-bit Cache Control Register
    
    lword CAAR; // 32-bit Cache Address Register

    qword CRP; // 64-bit CPU Root Pointer

    qword SRP; // 64-bit Supervisor Root Pointer

    lword TC; // 32-bit Translation Control Register

    lword TT0; // 32-bit Transprent Translation Register
    
    lword TT1; // 32-bit Transprent Translation Register

    word MMUSR; // 16-bit MMU Status Register

    struct SR // 16-bit Status Register
    {
        word I0 : 1; // Interrupt level 0
        word I1 : 1; // Interrupt level 1
        word I2 : 1; // Interrupt level 2
        word M : 1; // Master/Interrupt state, Indicates active stack pointer
        word S : 1; // Supervisor/User state, Indicates active stack pointer
        word T0 : 1; // Trace mode
        word T1 : 1; // Trace mode

        struct CCR // Condition Code Register
        {
            word C : 1; // Carry flag
            word V : 1; // Overflow flag
            word Z : 1; // Zero flag
            word N : 1; // Negative flag
            word X : 1; // Extend flag
        } CCR;
    } SR;
    
    // reset vectors??

} CPU;


typedef struct Amiga_3000
{
    CPU cpu;
    byte memory[DEFAULT_MEM_SIZE];
    word opcode;
    byte debugLevel;
} A3000;



#endif