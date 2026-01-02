## An overview of the relevant specifications and features of the MC68030

The emulator uses the Motorola MC68030 as the main CPU. It's a 32-bit microprocessor with a maximum clock rate of 16 MHz to 50 MHz, albeit it's designed for speeds beyond 20 MHz.

It combines a central processing unit, a memory management unit (MMU), an enhanced bus controller, and a 256 byte data and 256 byte instruction cache into a single VLSI device. The MC68030 has 32-bit addresses, registers and data paths as well as a coprocessor interface (e.g. floating-point coprocessors). 

Since the processor has a 32-bit addressing capabilities, it has a logical and physical memory addressing range of 4 GiB ($4 * 2^{30}$ bytes)


## Programming model

The user programming model has 16 32-bit general-purpose registers and two control registers.

<details>
<summary>Registers
</summary>
<p>32-bit General</p>
</details>

The code is roughly divided into three parts. The fetching, the decoding, and the executing.