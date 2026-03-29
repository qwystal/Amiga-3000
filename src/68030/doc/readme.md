# Documentation of the implementation of a Motorola MC68030 Emulator

## An overview of the relevant specifications and features of the MC68030

The emulator uses the Motorola MC68030 as the main CPU. It's a 32-bit microprocessor with a maximum clock rate of 16 MHz to 50 MHz, albeit it's designed for speeds beyond 20 MHz.

It combines a central processing unit, a memory management unit (MMU), an enhanced bus controller, and a 256 byte data and 256 byte instruction cache into a single VLSI device. The MC68030 has 32-bit addresses, registers and data paths as well as a coprocessor interface (e.g. floating-point coprocessors).

Since the processor has a 32-bit addressing capabilities, it has a logical and physical memory addressing range of 4 GiB ($4 * 2^{30}$ bytes)

## Code Structure

The source files are roughly divided into three parts: The fetching, the decoding, and the executing elements.

The [defines.h](../src/defines.h) header file contains definitions for the whole project and [typedefs.h](../src/typedefs.h) typedefs (e.g. structs and types) for the whole project. The other header files are only there as include controllers for their respective source files to make sure every source file only gets included once.

## Definitions

Byte: a size of 8 bits
Word: a size of 16 bits
Long-word: a size of 32 bits
Quad-word: a size of 64 bits

## Programming model

All the registers are implemented in [typedefs.h](../src/typedefs.h) via a single struct called MC68030.

The user programming model has 16 32-bit general-purpose registers and two control registers.

- 16 32-bit General-Purpose registers (D0-D7, A0-A7)
- 32-bit Program Counter (PC)
- 8-bit Condition Code Register (CCR)

The supervisor programming model contains all the registers available to the user programming model plus an additional fourteen control registers.

- Sixteen 32-bit General-Purpose Registers (D0-D7, A0-A7)
- 32-bit Program Counter (PC)
- 8-bit Condition Code Register (CCR)
- Two 32-bit Supervisor Stack Pointers (ISP and MSP)
- 16-bit Status Register (SR)
- 32-bit Vector Base Register (VBR)
- 32-Bit Alternate Function Code Registers (SFC and DFC)
- 32-Bit Cache Control Register (CACR)
- 32-Bit Cache Address Register (CAAR)
- 64-Bit CPU Root Pointer (CRP)
- 64-Bit Supervisor Root Pointer (SRP)
- 32-Bit Translation Control Register (TC)
- 32-Bit Transparent Translation Registers (TT0 and TT1)
- 16-Bit MMU Status Register (MMUSR)
