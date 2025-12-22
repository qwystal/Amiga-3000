/*
    This file contains:
        - functions to read and write to memory
*/

#include "typedefs.h"

byte *d_reg_min = NULL;
byte *a_reg_min = NULL;
byte *mem_min = NULL;
size_t mem_size = 0;

// Read byte from memory
byte rb_mem(A3000 *a3000, lword address) 
{
    return a3000->memory[address];
}

// Read word from memory
word rw_mem(A3000 *a3000, lword address) 
{
    word data = 0;
    data |= rb_mem(a3000, address + 1); // Gets the low byte
    data |= (rb_mem(a3000, address) << 8); // Gets the high byte and shifts it to the left
    return data;
}

// Read long word from memory
word rl_mem(A3000 *a3000, lword address) 
{
    word data = 0;
    data |= rb_mem(a3000, address + 4); // Gets the low byte
    data |= (rb_mem(a3000, address + 3) << 8);
    data |= (rb_mem(a3000, address + 2) << 16);
    data |= (rb_mem(a3000, address) << 24); // Gets the high byte and shifts it to the left
    return data;
}

// Write byte to memory
void wb_mem(A3000 *a3000, lword address, byte data)
{
    a3000->memory[address] = data;
}

// Write word to memory
void ww_mem(A3000 *a3000, lword address, word data)
{
    wb_mem(a3000, address, data & 0xFF); // writes the low byte using a bitwise AND to mask the high byte
    wb_mem(a3000, address + 1, data >> 8); // writes the high byte and shifts it to the right
}

// Write long word to memory
void wl_mem(A3000 *a3000, lword address, lword data)
{
    wb_mem(a3000, address, data & 0xFF); // writes the low byte using a bitwise AND to mask the high byte
    wb_mem(a3000, address + 1, (data >> 8) & 0xFF); // writes the high byte and shifts it to the right
    wb_mem(a3000, address + 2, (data >> 16) & 0xFF);
    wb_mem(a3000, address + 3, data >> 24);
}

// Read byte behind a pointer, could be register or memory
byte rb_ptr(byte *address)
{
    // memory bounds check
    if ((address >= d_reg_min && address < (d_reg_min + 32)) || (address >= a_reg_min && address < (a_reg_min + 32)) || (address >= mem_min && address < (mem_min + mem_size)))
        return (byte) *address;
    else
        return 0;
}

// Read word behind a pointer, could be register or memory
word rw_ptr(byte *address) 
{
    word data = 0;
    data |= rb_ptr(address + 1); // Gets the low byte
    data |= (rb_ptr(address) << 8); // Gets the high byte and shifts it to the left
    return data;
}

// Read long word behind a pointer, could be register or memory
word rl_ptr(byte *address) 
{
    word data = 0;
    data |= rb_ptr(address + 4); // Gets the low byte
    data |= (rb_ptr(address + 3) << 8);
    data |= (rb_ptr(address + 2) << 16);
    data |= (rb_ptr(address) << 24); // Gets the high byte and shifts it to the left
    return data;
}

// Write byte to the pointed space, could be register or memory
void wb_ptr(byte *address, byte data)
{
    // memory bounds check
    if ((address >= d_reg_min && address < (d_reg_min + 32)) || (address >= a_reg_min && address < (a_reg_min + 32)) || (address >= mem_min && address < (mem_min + mem_size)))
        *address = data;
}

// Write word to the pointed space, could be register or memory
void ww_ptr(byte *address, word data)
{
    wb_ptr(address, data & 0xFF); // writes the low byte using a bitwise AND to mask the high byte
    wb_ptr(address + 1, data >> 8); // writes the high byte and shifts it to the right
}

// Write long word to the pointed space, could be register or memory
void wl_ptr(byte *address, lword data)
{
    wb_ptr(address, data & 0xFF); // writes the low byte using a bitwise AND to mask the high byte
    wb_ptr(address + 1, (data >> 8) & 0xFF); // writes the high byte and shifts it to the right
    wb_ptr(address + 2, (data >> 16) & 0xFF);
    wb_ptr(address + 3, data >> 24);
}