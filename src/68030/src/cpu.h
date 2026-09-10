#ifndef CPU_H
#define CPU_H

#include "typedefs.h"

lword exception_vector_lookup(byte *mem, byte vector_number);
a3000_t *init_cpu();
void free_cpu(a3000_t *a3000);

#endif