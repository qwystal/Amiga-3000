#include "typedefs.h"

lword exception_vector_lookup(byte *mem, byte vector_number)
{
    return (mem[vector_number * 4] << 24) | (mem[vector_number * 4 + 1] << 16) | (mem[vector_number * 4 + 2] << 8) | mem[vector_number * 4 + 3];
}

void initialize_cpu(CPU *cpu, byte *mem)
{
    memset(cpu, 0, sizeof(CPU));
    cpu->SSP = exception_vector_lookup(mem, 0);
    cpu->PC = exception_vector_lookup(mem, 1);
}