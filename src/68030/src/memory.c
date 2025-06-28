#include "typedefs.h"

// Read byte from memory
byte rb_mem(A3000 *a3000, lword address) 
{
    a3000->cpu.cycles--;
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

// Write byte to memory
void wb_mem(A3000 *a3000, lword address, byte data) 
{
    a3000->memory[address] = data;
    a3000->cpu.cycles--;
}

// Write word to memory
void ww_mem(A3000 *a3000, lword address, word data) 
{
    wb_mem(a3000, address, data & 0xFF); // writes the low byte using a bitwise AND to mask the high byte
    wb_mem(a3000, address + 1, data >> 8); // writes the high byte and shifts it to the right
}
