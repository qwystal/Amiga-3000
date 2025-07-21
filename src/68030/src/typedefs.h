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
    byte pin[13]; // signal pins, only 101 out of the 104 (8 * 13) needed

    struct GPR // 32-bit General Purpose Registers
    {
        lword D[8];
        lword A[8]; // A[8] acts as the System Stack Pointer (SP)
    } GPR;
    
    lword PC; // 32-bit Program Counter
    
    lword SSP; // 32-bit System Stack Pointer
    
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

    lword USP; // 32-bit User Stack Pointer

    struct SR // 16-bit Status Register
    {
        word T1 : 1; // Trace mode
        word T0 : 1; // Trace mode
        word S : 1; // Supervisor/User state, Indicates active stack pointer
        word M : 1; // Master/Interrupt state, Indicates active stack pointer
        word ZERO : 1; // Always zero
        word I2 : 1; // Interrupt level 2
        word I1 : 1; // Interrupt level 1
        word I0 : 1; // Interrupt level 0

        struct CCR // Condition Code Register
        {
            word ZERO : 3; // Always zero
            word X : 1; // Extend flag
            word N : 1; // Negative flag
            word Z : 1; // Zero flag
            word V : 1; // Overflow flag
            word C : 1; // Carry flag
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
    word cycles;
} A3000;

typedef struct addressing_modes_arguments
{
    byte dn : 3; // data register
    byte an : 3; // address register
    byte xnsize : 1; // size of data, 0 for sign extended word, 1 for slword
    slword d16; // 16-bit displacement int
    slword d8; // 8-bit displacement int
    byte xn : 4; // index register, can either be one or zero for address register or data register respectively, and the id of the register
    byte scale : 2; // can only be 1, 2, 4 or 8
    slword bd; // base displacement, size defined by bits 4 and 5
    slword od; // outer displacement, size defined by IS - I/IS Encodings (Table 2-2 in PRM)
    slword ew1; // extension word 1
    slword ew2; // extension word 2
    byte size : 2; // size of operation (in byte), 00 = 1, 01 = 2, 10 = 4, 11 = undefined
    byte bs : 1; // base register suppress, 1 = suppressed
    byte is : 1; // index register suppress, 1 = suppressed
} AMA;


/* not required
// Four-Word Stack Frame
typedef struct stackframe_$0
{
    word SR; // Status Register
    lword PC; // Program Counter
    word fo; // Format/Offset
} SF$0;

// Throwaway Four-Word Stack Frame
typedef struct stackframe_$1
{
    word SR; // Status Register
    lword PC; // Program Counter
    word fo; // Format/Offset
} SF$1;

// Six-Word Stack Frame
typedef struct stackframe_$2
{
    word SR; // Status Register
    lword PC; // Program Counter
    word fo; // Format/Offset
    lword address;
} SF$2;

// Coprocessor Mid-Instruction Stack Frame
typedef struct stackframe_$9
{
    word SR; // Status Register
    lword PC; // Program Counter
    word fo; // Format/Offset
    lword ins_address; // Instruction Address
    word internal_registers[4];
} SF$9;

// Short Bus Cycle Stack Frame
typedef struct stackframe_$A
{
    word SR; // Status Register
    lword PC; // Program Counter
    word fo; // Format/Offset
    word internal_registers[5];
    word special_SR; // Special Status Register
    word ins_pipe_stage_c; // Instruction Pipe Stage C
    word ins_pipe_stage_b; // Instruction Pipe Stage C
    lword data_cyc_fault_address; // Data Cycle Fault Address
    lword data_output_buffer;
} SF$A;

// Long Bus Cycle Stack Frame
typedef struct stackframe_$B
{
    word SR; // Status Register
    lword PC; // Program Counter
    word fo; // Format/Offset
    word internal_registers[30];
    word special_SR; // Special Status Register
    word ins_pipe_stage_c; // Instruction Pipe Stage C
    word ins_pipe_stage_b; // Instruction Pipe Stage C
    lword data_cyc_fault_address; // Data Cycle Fault Address
    lword data_output_buffer;
    lword stage_b_address;
    lword data_input_buffer;
    word ver_info; // Version# / Internal Information
} SF$B;

// CPU32 Bus Error for Prefetches and Operands Stack Frame
typedef struct stackframe_$C0
{
    word SR;
    word PC_high;
    word PC_low;
    word fo; // Format/Offset
    word faulted_addr_high; // Faulted Address High
    word faulted_addr_low; // Faulted Address Low
    word DBUF_high;
    word DBUF_low;
    word CIPC_high; // Current Instruction Program Counter High
    word CIPC_low; // Current Instruction Program Counter Low
    word ITCR; // Internal Transfer Count Register
    word id_special_SW; // Identification for Format $C0 Stack Frame / Special Status Word
} SF$C0;

// CPU32 Bus Error on MOVEM Operand Stack Frame
typedef struct stackframe_$C1
{
    word SR;
    word PC_high;
    word PC_low;
    word fo; // Format/Offset
    word faulted_addr_high; // Faulted Address High
    word faulted_addr_low; // Faulted Address Low
    word DBUF_high;
    word DBUF_low;
    word CIPC_high; // Current Instruction Program Counter High
    word CIPC_low; // Current Instruction Program Counter Low
    word ITCR; // Internal Transfer Count Register
    word id_special_SW; // Identification for Format $C0 Stack Frame / Special Status Word
} SF$C1;

// CPU32 Four- and Six-Word Bus Error Stack Frame
typedef struct stackframe_$C2
{
    word SR;
    word PC_high;
    word PC_low;
    word fo; // Format/Offset
    word faulted_addr_high; // Faulted Address High
    word faulted_addr_low; // Faulted Address Low
    word DBUF_high;
    word DBUF_low;
    word CIPC_high; // Current Instruction Program Counter High
    word CIPC_low; // Current Instruction Program Counter Low
    word ITCR; // Internal Transfer Count Register
    word id_special_SW; // Identification for Format $C0 Stack Frame / Special Status Word
} SF$C2;
*/

#endif