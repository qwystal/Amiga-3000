/*
    This file includes:
        - all eighteen addressing modes
        - the effective address decoder (which selects the addressing mode to use)
*/

#include "typedefs.h"
#include "memory.c"
#include "debug.c"

/* this function returns the content of the index register */
static slword get_index(A3000 *a3000, AMA ama) {
    if (ama.is)
    {
        return 0;
    }
    
    if (ama.xn_size)
    {
        slword xn;
        if (ama.xn_type)
        {
            xn = a3000->cpu.GPR.A[ama.xn];
        }
        else
        {
            xn = a3000->cpu.GPR.D[ama.xn];
        }
        return ((slword) xn) * ama.scale;
    }
    else
    {
        sword xn;
        if (ama.xn_type)
        {
            xn = a3000->cpu.GPR.A[ama.xn] & 0xFFFF;
        }
        else
        {
            xn = a3000->cpu.GPR.D[ama.xn] & 0xFFFF;
        }
        return ((slword) xn) * ama.scale;
    }
}

/* this function returns the base displacement value */
static slword get_bd(AMA ama) {
    if (ama.bs)
    {
        return 0;
    }
    else
    {
        return ama.bd;
    }
}

/* this function returns the program counter value */
static slword get_PC(A3000 *a3000, AMA ama) {
    if (ama.bs)
    {
        return 0;
    }
    else
    {
        return a3000->cpu.PC;
    }
}

/* 
    since I began this project, the worst experience was writing 
    the eighteen addressing modes 
    - (23/07/2025)
*/
static lword data_register_direct_mode(A3000 *a3000, AMA ama)
{
    return a3000->cpu.GPR.D[ama.reg];
}

static lword address_register_direct_mode(A3000 *a3000, AMA ama)
{
    return a3000->cpu.GPR.A[ama.reg];
}

static lword address_register_indirect_mode(A3000 *a3000, AMA ama)
{
    return a3000->cpu.GPR.A[ama.reg];
}

static lword address_register_indirect_with_postincrement_mode(A3000 *a3000, AMA ama)
{
    if (ama.reg == 7 && ama.size == 1) // only if address register is stack pointer
    {
        return a3000->cpu.GPR.A[ama.reg] + 2;
    }
    else
    {
        return a3000->cpu.GPR.A[ama.reg] + ama.size;
    }
}

static lword address_register_indirect_with_predecrement_mode(A3000 *a3000, AMA ama)
{
    if (ama.reg == 7 && ama.size == 1) // only if address register is stack pointer
    {
        return a3000->cpu.GPR.A[ama.reg] - 2;
    }
    else
    {
        return a3000->cpu.GPR.A[ama.reg] - ama.size;
    }
}

static lword address_register_indirect_with_displacement_mode(A3000 *a3000, AMA ama)
{
    return ama.d16 + a3000->cpu.GPR.A[ama.reg]; // signed + unsigned number
}

static lword address_register_indirect_with_index_8bit_mode(A3000 *a3000, AMA ama)
{
    return ama.d8 + a3000->cpu.GPR.A[ama.reg] + get_index(a3000, ama); // signed + unsigned number
}

static lword address_register_indirect_with_index_base_displacement_mode(A3000 *a3000, AMA ama)
{
    return get_bd(ama) + a3000->cpu.GPR.A[ama.reg] + (get_index(a3000, ama)); // signed + unsigned number
}

static lword memory_indirect_postindexed_mode(A3000 *a3000, AMA ama) {
    return rl_mem(a3000, a3000->cpu.GPR.A[ama.reg] + get_bd(ama)) + get_index(a3000, ama) + ama.od;
}

static lword memory_indirect_preindexed_mode(A3000 *a3000, AMA ama) {
    return rl_mem(a3000, a3000->cpu.GPR.A[ama.reg] + get_bd(ama) + get_index(a3000, ama)) + ama.od;
}

static lword program_counter_indirect_with_displacement_mode(A3000 *a3000, AMA ama) {
    return a3000->cpu.PC + ama.d16; // only allowed for reads?
}

static lword program_counter_indirect_with_index_8bit_displacement_mode(A3000 *a3000, AMA ama) {
    return ama.d8 + a3000->cpu.PC + get_index(a3000, ama); // signed + unsigned number
}

static lword program_counter_indirect_with_index_base_displacement_mode(A3000 *a3000, AMA ama) {
    return a3000->cpu.PC + ama.bd + get_index(a3000, ama);
}

static lword program_counter_memory_indirect_postindexed_mode(A3000 *a3000, AMA ama) {
    return rl_mem(a3000, a3000->cpu.PC + ama.bd) + get_index(a3000, ama) + ama.od;
}

static lword program_counter_memory_indirect_preindexed_mode(A3000 *a3000, AMA ama) {
    return rl_mem(a3000, a3000->cpu.PC + ama.bd + get_index(a3000, ama)) + ama.od;
}

static lword absolute_short_addressing_mode(A3000 *a3000, AMA ama) {
    return ama.ew1;
}

static lword absolute_long_addressing_mode(A3000 *a3000, AMA ama) {
    return ama.ew1;
}

static lword immediate_data_mode(A3000 *a3000, AMA ama) {
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

/* 
    this function returns an
    (A)ddressing (M)ode (A)rguments struct. 
    everything that is needed for the addressing 
    modes to work is set here.
*/
static AMA get_AMA(A3000 *a3000) {
    word reg = a3000->cpu.PC & 0b111;
    a3000->cpu.PC += 2;
    word fw = rw_mem(a3000, a3000->cpu.PC); // format word

    if ((fw >> 8) & 0b1) // if it's brief or full format
    {
        AMA ama = { // full format
            .IIS = fw & 0b111,
            .is = (fw >> 6) & 1,
            .bs = (fw >> 7) & 1,
            .scale = (fw >> 9) & 0b11,
            .xn_size = (fw >> 11) & 1,
            .xn = (fw >> 12) & 0b111,
            .xn_type = (fw >> 15) & 1,
            .reg = reg,
            .format = 1,
            .fw = fw,
            .ew1 = rw_mem(a3000, a3000->cpu.PC + 2),
            .ew2 = rw_mem(a3000, a3000->cpu.PC + 4)
        };

        switch ((fw >> 4) & 0b11) // find out size of base displacement
        {
            case 0b10:
                a3000->cpu.PC += 2;
                ama.bd = (slword) rw_mem(a3000, a3000->cpu.PC);
                break;

            case 0b11:
                a3000->cpu.PC += 4;
                ama.bd = rl_mem(a3000, a3000->cpu.PC);
                break;
            
            default:
                break;
        }
        return ama;
    }
    else
    {
        AMA ama = { // brief format
            .d8 = (slword) (fw & 0b11111111),
            .scale = (fw >> 9) & 0b11,
            .xn_size = (fw >> 11) & 1,
            .xn = (fw >> 12) & 0b111,
            .xn_type = (fw >> 15) & 1,
            .reg = reg,
            .format = 0
        };
        return ama;
    }
}

/* this function selects the addressing mode to use and returns the effective address */
lword get_ea(A3000 *a3000) {
    word mode = (a3000->cpu.PC >> 3) & 0b111;
    AMA ama = get_AMA(a3000);

    switch (mode)
    {
        case 0b000:
            return data_register_direct_mode(a3000, ama);

        case 0b001:
            return address_register_direct_mode(a3000, ama);

        case 0b010:
            return address_register_indirect_mode(a3000, ama);

        case 0b011:
            return address_register_indirect_with_postincrement_mode(a3000, ama);

        case 0b100:
            return address_register_indirect_with_predecrement_mode(a3000, ama);

        case 0b101:
            return address_register_indirect_with_displacement_mode(a3000, ama);

        case 0b110:
            if (ama.format) // find out the extension word format
            {
                switch (ama.fw & 0b111) // find out memory indirection
                {
                        case 0b001:
                        case 0b010:
                        case 0b011:
                            return memory_indirect_preindexed_mode(a3000, ama);
                            break;
                    
                        case 0b101:
                        case 0b110:
                        case 0b111:
                            return memory_indirect_postindexed_mode(a3000, ama);
                            break;

                        case 0b000:
                            return address_register_indirect_with_index_base_displacement_mode(a3000, ama);
                            break;
                    
                        default:
                            break;
                }
            }
            else
            {
                return address_register_indirect_with_index_8bit_mode(a3000, ama);
            }

        case 0b111:
            switch (ama.reg) // here the register decides the mode to use
            {
                case 0b000:
                    return absolute_short_addressing_mode(a3000, ama);
                    break;

                case 0b001:
                    return absolute_long_addressing_mode(a3000, ama);
                    break;

                case 0b010:
                    return program_counter_indirect_with_displacement_mode(a3000, ama);
                    break;

                case 0b011:
                    if (ama.format) // find out the extension word format
                    {
                        switch (ama.fw & 0b111) // find out memory indirection
                        {
                                case 0b001:
                                case 0b010:
                                case 0b011:
                                    return program_counter_memory_indirect_preindexed_mode(a3000, ama);
                                    break;

                                case 0b101:
                                case 0b110:
                                case 0b111:
                                    return program_counter_memory_indirect_postindexed_mode(a3000, ama);
                                    break;
                        
                                case 0b000:
                                    return program_counter_indirect_with_index_base_displacement_mode(a3000, ama);
                                    break;

                                default:
                                    break;
                        }
                    }
                    else
                    {
                        return program_counter_indirect_with_index_8bit_displacement_mode(a3000, ama);
                    }
                    break;

                case 0b100:
                    return immediate_data_mode(a3000, ama);
                    break;
                
                default:
                    break;
            }
        
        default:
            break;
    }
}