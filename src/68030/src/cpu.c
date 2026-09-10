#include "typedefs.h"
#include "memory.h"
#include "debug.h"
#include <strings.h>
#include <stdlib.h>

a3000_t *init_cpu()
{
    a3000_t *a3000 = malloc(sizeof(a3000_t));
    if (a3000 == nullptr)
    {
        error("failed memory allocation");
    }

    a3000->memory = malloc(MAX_MEM_SIZE);
    if (a3000->memory == nullptr)
    {
        error("failed memory allocation");
    }
    

    mem_min = a3000->memory;
    d_reg_min = (byte *) &a3000->cpu.GPR.D[0];
    a_reg_min = (byte *) &a3000->cpu.GPR.A[0];
    mem_size = MAX_MEM_SIZE;

    return a3000;
}

void free_cpu(a3000_t *a3000)
{
    free(a3000->memory);
    free(a3000);
}