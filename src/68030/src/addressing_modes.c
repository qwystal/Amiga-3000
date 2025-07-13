#include "typedefs.h"
#include "memory.c"
#include "debug.c"

/* In the data register direct mode, the effective address field specifies the data register
containing the operand. */
word data_register_direct_mode(A3000 *a3000, byte n)
{
    return a3000->cpu.GPR.D[n];
}

/* In the address register direct mode, the effective address field specifies the address register
containing the operand. */
word address_register_direct_mode(A3000 *a3000, byte an)
{
    return a3000->cpu.GPR.A[an];
}

/* In the address register indirect mode, the operand is in memory. The effective address field
specifies the address register containing the address of the operand in memory. */
word data_register_indirect_mode(A3000 *a3000, byte dn)
{
    return rw_mem(a3000, a3000->cpu.GPR.D[dn]);
}

/* In the address register indirect with postincrement mode, the operand is in memory. The
effective address field specifies the address register containing the address of the operand
in memory. After the operand address is used, it is incremented by one, two, or four
depending on the size of the operand: byte, word, or long word, respectively. Coprocessors
may support incrementing for any operand size, up to 255 bytes. If the address register is
the stack pointer and the operand size is byte, the address is incremented by two to keep
the stack pointer aligned to a word boundary. */
word address_register_indirect_with_postincrement_mode(A3000 *a3000, byte an, byte size)
{
    if (an == 7 && size == 1) // only if address register is stack pointer
    {
        return rw_mem(a3000, (a3000->cpu.GPR.A[an]) + 2);
    }
    else
    {
        return rw_mem(a3000, (a3000->cpu.GPR.A[an]) + size);
    }
}


word address_register_indirect_with_predecrement_mode(A3000 *a3000, byte an, byte size)
{
    if (an == 7 && size == 1) // only if address register is stack pointer
    {
        return rw_mem(a3000, (a3000->cpu.GPR.A[an]) - 2);
    }
    else
    {
        return rw_mem(a3000, (a3000->cpu.GPR.A[an]) - size);
    }
}

word address_register_indirect_with_displacement_mode(A3000 *a3000, byte an, sword displacement)
{
    slword se_displacement = (slword)displacement; // sign extended displacement
    word ea = rw_mem(a3000, (se_displacement + a3000->cpu.GPR.A[an])); // signed + unsigned number
    return ea;
}

word address_register_indirect_with_index_8bit_mode(A3000 *a3000, byte an, sbyte displacement, byte index, byte scale)
{
    switch (scale)
    {
        case 0x1 || 0x2 || 0x4 || 0x8: // scale can only be 1, 2, 4 or 8
            slword se_displacement = (slword)displacement; // sign extended displacement
            word ea = rw_mem(a3000, (se_displacement + a3000->cpu.GPR.A[an] + (a3000->cpu.GPR.D[index] * scale))); // signed + unsigned number
            return ea;
        
        default:
            logError("Invalid scale value. Must be 1, 2, 4 or 8.", *a3000);
            return 0;
    }
}

word address_register_indirect_with_index_base_displacement_mode(A3000 *a3000, byte an, slword displacement, byte index, byte scale)
{
    switch (scale)
    {
        case 0x1 || 0x2 || 0x4 || 0x8: // scale can only be 1, 2, 4 or 8
            word ea = rw_mem(a3000, (displacement + a3000->cpu.GPR.A[an] + (a3000->cpu.GPR.D[index] * scale))); // signed + unsigned number
            return ea; // todo
        
        default:
            logError("Invalid scale value. Must be 1, 2, 4 or 8.", *a3000);
            return 0;
    }
}

word memory_indirect_postindexed_mode(A3000 *a3000, byte an, sword bd, byte xn, byte scale, sword od) {

}