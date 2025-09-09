#include <stdio.h>

#include "typedefs.h"
#include "instruction_set.h"

#include "memory.h"
#include "debug.h"
#include "addressing_modes.h"

void write_esf(A3000 *a3000, word format, word vector) { // write stack exception frame
    
    
    switch (format)
    {
        case 0:
            a3000->cpu.SSP -= 2;
            ww_mem(a3000, a3000->cpu.SSP, vector * 4);
            a3000->cpu.SSP -= 4;
            wl_mem(a3000, a3000->cpu.SSP, a3000->cpu.PC);
            a3000->cpu.SSP -= 2;
            ww_mem(a3000, a3000->cpu.SSP, get_SR(a3000));
            a3000->cpu.PC = vector * 4;
            break;
        
        case 1:
            // dont forget the format nibble

        
        default:
            break;
    }
}

void exception(A3000 *a3000, word vector) {
    switch (vector)
    {
    case VEC_ILLEGAL_INSTRUCTION:
        write_esf(a3000, 0, VEC_ILLEGAL_INSTRUCTION);
        // illegal instruction edge cases!
        break;
    
    default:
        break;
    }
}