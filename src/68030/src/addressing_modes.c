#include "typedefs.h"
#include "memory.c"
#include "debug.c"

slword get_index_reg(A3000 *a3000, AMA ama) {
    if (ama.xnsize)
    {
        slword xn;
        if (ama.xn & 1)
        {
            xn = a3000->cpu.GPR.A[ama.xn >> 3];
        }
        else
        {
            xn = a3000->cpu.GPR.D[ama.xn >> 3];
        }
        return ((slword) xn) * ama.scale;
    }
    else
    {
        sword xn;
        if (ama.xn & 1)
        {
            xn = a3000->cpu.GPR.A[ama.xn >> 3] & 0xFFFF;
        }
        else
        {
            xn = a3000->cpu.GPR.D[ama.xn >> 3] & 0xFFFF;
        }
        return ((slword) xn) * ama.scale;
    }
}

lword data_register_direct_mode(A3000 *a3000, AMA ama)
{
    return a3000->cpu.GPR.D[ama.dn];
}

lword address_register_direct_mode(A3000 *a3000, AMA ama)
{
    return a3000->cpu.GPR.A[ama.an];
}

lword address_register_indirect_mode(A3000 *a3000, AMA ama)
{
    return a3000->cpu.GPR.A[ama.an];
}

lword address_register_indirect_with_postincrement_mode(A3000 *a3000, AMA ama)
{
    if (ama.an == 7 && ama.size == 1) // only if address register is stack pointer
    {
        return a3000->cpu.GPR.A[ama.an] + 2;
    }
    else
    {
        return a3000->cpu.GPR.A[ama.an] + ama.size;
    }
}

lword address_register_indirect_with_predecrement_mode(A3000 *a3000, AMA ama)
{
    if (ama.an == 7 && ama.size == 1) // only if address register is stack pointer
    {
        return a3000->cpu.GPR.A[ama.an] - 2;
    }
    else
    {
        return a3000->cpu.GPR.A[ama.an] - ama.size;
    }
}

lword address_register_indirect_with_displacement_mode(A3000 *a3000, AMA ama)
{
    return ama.d16 + a3000->cpu.GPR.A[ama.an]; // signed + unsigned number
}

lword address_register_indirect_with_index_8bit_mode(A3000 *a3000, AMA ama)
{
    return ama.d8 + a3000->cpu.GPR.A[ama.an] + get_index_reg(a3000, ama); // signed + unsigned number
}

lword address_register_indirect_with_index_base_displacement_mode(A3000 *a3000, AMA ama)
{
    return ama.bd + a3000->cpu.GPR.A[ama.an] + (get_index_reg(a3000, ama)); // signed + unsigned number
}

lword memory_indirect_postindexed_mode(A3000 *a3000, AMA ama) {
    return rl_mem(a3000, a3000->cpu.GPR.A[ama.an] + ama.bd) + get_index_reg(a3000, ama) + ama.od;
}

lword memory_indirect_preindexed_mode(A3000 *a3000, AMA ama) {
    return rl_mem(a3000, a3000->cpu.GPR.A[ama.an] + ama.bd + get_index_reg(a3000, ama)) + ama.od;
}

lword program_counter_indirect_with_displacement_mode(A3000 *a3000, AMA ama) {
    return a3000->cpu.PC + ama.d16; // only allowed for reads?
}

lword program_counter_indirect_with_index_8bit_displacement_mode(A3000 *a3000, AMA ama) {
    return ama.d8 + a3000->cpu.PC + get_index_reg(a3000, ama); // signed + unsigned number
}

lword program_counter_indirect_with_index_base_displacement_mode(A3000 *a3000, AMA ama) {
    return a3000->cpu.PC + ama.bd + get_index_reg(a3000, ama);
}

lword program_counter_memory_indirect_postindexed_mode(A3000 *a3000, AMA ama) {
    return rl_mem(a3000, a3000->cpu.PC + ama.bd) + get_index_reg(a3000, ama) + ama.od;
}

lword program_counter_memory_indirect_preindexed_mode(A3000 *a3000, AMA ama) {
    return rl_mem(a3000, a3000->cpu.PC + ama.bd + get_index_reg(a3000, ama)) + ama.od;
}

lword absolute_short_addressing_mode(A3000 *a3000, AMA ama) {
    return ama.ew1;
}

lword absolute_long_addressing_mode(A3000 *a3000, AMA ama) {
    return ama.ew1;
}

lword immediate_data(A3000 *a3000, AMA ama) {
    switch (ama.size)
    {
        case 0:
            return ama.ew1 & 0xFF;

        case 1:
            return ama.ew1;
        
        case 2:
            return (ama.ew1 << 16) & ama.ew2;
    }
}