#ifndef MEMORY_H
#define MEMORY_H

#include "typedefs.h"

extern byte *d_reg_min; // lower bounds of the data registers in memory
extern byte *a_reg_min; // lower bounds of the address registers in memory
extern byte *mem_min;   // lower bounds of the memory in memory
extern size_t mem_size;    // memory size

// read from the provided memory address
byte rb_mem(a3000_t *a3000, lword address);
word rw_mem(a3000_t *a3000, lword address);
lword rl_mem(a3000_t *a3000, lword address);

// write to the provided memory address
void wb_mem(a3000_t *a3000, lword address, byte data);
void ww_mem(a3000_t *a3000, lword address, word data);
void wl_mem(a3000_t *a3000, lword address, lword data);

// read directly from the data behind the provided pointer
byte rb_ptr(byte *address);
word rw_ptr(byte *address);
lword rl_ptr(byte *address);

// write directly to the data behind the provided pointer
void wb_ptr(byte *address, byte data);
void ww_ptr(byte *address, word data);
void wl_ptr(byte *address, lword data);

// convert the provided pointer to a virtual address
lword get_virt_addr(byte *address);

// memory management unit
byte *mmu(a3000_t *a3000, lword logical_addr);

#endif