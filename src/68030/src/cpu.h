#ifndef CPU_H
#define CPU_H

#include "typedefs.h"

lword exception_vector_lookup(byte *mem, byte vector_number);
void initialize_cpu(CPU *cpu, byte *mem);

#endif