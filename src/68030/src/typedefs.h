#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdint.h>

#include "defines.h"

typedef uint8_t byte; // unsigned 8-bit
typedef int8_t sbyte; // signed 8-bit
typedef uint16_t word; // unsigned 16-bit
typedef int16_t sword; // signed 16-bit
typedef uint32_t lword; // unsigned 32-bit (long word)
typedef int32_t slword; // signed 32-bit (long word)
typedef uint64_t qword; // unsigned 64-bit (quad word)
typedef int64_t sqword; // signed 64-bit (quad word)

typedef struct MC68030
{   
    byte pin[13]; // signal pins, only 101 bits out of the 104 bits (8 bit * 13) are needed

    struct GPR // 32-bit General Purpose Registers
    {
        lword D[8];
        lword A[8]; // A[8] acts as the System Stack Pointer (SP), it doesn't matter what SP is active, it always contains the SP
    } GPR;
    
    lword PC; // 32-bit Program Counter
    
    lword SSP; // 32-bit System Stack Pointer
    
    lword MSP; // 32-bit Supervisor Stack Pointer
    
    lword VBR; // 32-bit Vector Base Register
    
    lword SFC; // 32-bit Source Function Code Register though only three bits are used, contains FC0-FC2
    
    lword DFC; // 32-bit Destination Function Code Register though only three bits are used, contains FC0-FC2
    
    lword CACR; // 32-bit Cache Control Register
    
    lword CAAR; // 32-bit Cache Address Register

    struct CRP 
    {
        byte LU : 1; // Lower/Upper, limit value is unsigned upper(0)/lower(1) limit of indexes
        word limit : 15; // Limit, lower or upper value limit for the index to be used at the next level of table search
        word : 14; // always zero
        byte DT : 2; // Descriptor Table, specifies the type of descriptor in the root pointer or in the 1st level of the translation table 
        lword table_address : 28; // Table Address, physical base address of the translation table
        byte unused : 4; // unused and must be ignored when written, apparently different than always zero?
    } CRP; // 64-bit CPU Root Pointer

    struct SRP
    {
        byte LU : 1; // Lower/Upper, limit value is unsigned upper(0)/lower(1) limit of indexes
        word limit : 15; // Limit, lower or upper value limit for the index to be used at the next level of table search
        word : 14; // always zero
        byte DT : 2; // Descriptor Table, specifies the type of descriptor in the root pointer or in the 1st level of the translation table 
        lword table_address : 28; // Table Address, physical base address of the translation table
        byte unused : 4; // unused and must be ignored when written, apparently different than always zero?
    } SRP; // 64-bit Supervisor Root Pointer

    struct TC 
    {
        byte E : 1; // Enable, address translation switch, cleared on RESET
        byte : 5; // always zero
        byte SRE : 1; // Supervisor Root Pointer Enable
        byte FCL : 1; // Function Code Lookup
        byte PS : 4; // Page Size
        byte IS : 4; // Inital Shift
        byte TIA : 4; // Table Index
        byte TIB : 4; // Table Index
        byte TIC : 4; // Table Index
        byte TID : 4; // Table Index
    } TC; // 32-bit Translation Control Register

    struct TT0 
    {
        byte la_base; // Logical Address Base
        byte la_mask; // Logical Address Mask
        byte E : 1; // Enable, transparent translation switch
        byte : 4; // always zero
        byte CI : 1; // Cache Inhibit
        byte RW : 1; // Read/Write
        byte RWM : 1; // Read/Write Mask
        byte : 1; // always zero
        byte fc_base : 3; // Function Code Base
        byte : 1; // always zero
        byte fc_mask : 3; // Function Code Mask
    } TT0; // 32-bit Transprent Translation Register
    
    struct TT1
    {
        byte la_base; // Logical Address Base
        byte la_mask; // Logical Address Mask
        byte E : 1; // Enable, transparent translation switch
        byte : 4; // always zero
        byte CI : 1; // Cache Inhibit
        byte RW : 1; // Read/Write
        byte RWM : 1; // Read/Write Mask
        byte : 1; // always zero
        byte fc_base : 3; // Function Code Base
        byte : 1; // always zero
        byte fc_mask : 3; // Function Code Mask
    } TT1; // 32-bit Transprent Translation Register

    struct MMUSR 
    {
        byte B : 1; // bus error
        byte L : 1; // limit violation
        byte S : 1; // supervisor-only
        byte : 1;   // always zero
        byte W : 1; // write-protected
        byte I : 1; // invalid
        byte M : 1; // modified
        byte : 2;   // always zero
        byte T : 1; // transparent access
        byte : 3;   // always zero
        byte N : 3; // number of levels
    } MMUSR; // 16-bit MMU Status Register

    lword USP; // 32-bit User Stack Pointer

    struct SR // 16-bit Status Register
    {
        word T1 : 1; // Trace mode
        word T0 : 1; // Trace mode
        word S : 1; // Supervisor/User state, Indicates active stack pointer
        word M : 1; // Master/Interrupt state, Indicates active stack pointer
        word : 1; // Always zero
        word I2 : 1; // Interrupt level 2
        word I1 : 1; // Interrupt level 1
        word I0 : 1; // Interrupt level 0

        struct CCR // Condition Code Register
        {
            word : 3; // Always zero
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
    byte *memory;
    word opcode;
    word rom_opcode;
    byte debugLevel;
    word cycles;
} A3000;

typedef struct addressing_modes_arguments
{
    byte reg : 3; // register
    byte xn_size : 1; // size of data, 0 for sign extended word, 1 for slword
    slword d16; // 16-bit displacement int
    slword d8; // 8-bit displacement int
    byte xn : 3; // index register
    byte xn_type : 1; // type of index register, can either be one or zero for address register or data register respectively
    byte scale : 2; // can only be 1, 2, 4 or 8
    slword bd; // base displacement, size defined by bits 4 and 5
    slword od; // outer displacement, size defined by IS - I/IS Encodings (Table 2-2 in PRM)
    lword fw; // format word
    lword ew1; // extension word 1
    lword ew2; // extension word 2
    byte size : 2; // size of operation (in byte), 00 = 1, 01 = 2, 10 = 4, 11 = undefined
    byte bs : 1; // base register suppress, 1 = suppressed, hopefully also works for PC
    byte is : 1; // index register suppress, 1 = suppressed
    byte IIS : 3; // Index/Indirect for Memory Indirection encodings
    byte format : 1; // extension word format, 0 for brief, 1 for full
} AMA;

typedef enum {
    MEMORY_ACCESS_VIOLATION,
    UNSUPPORTED_SEF,
    ASSERT_FAILURE
} error_type;

typedef enum {
    U_BYTE,
    U_WORD,
    U_LWORD,
    U_QWORD,
    S_BYTE,
    S_WORD,
    S_LWORD,
    S_QWORD
} data_type;

typedef struct {
    enum type{
        BYTE,
        WORD,
        LWORD,
        QWORD
    } type;

    void *data;
} data;

/* NOT REQUIRED
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