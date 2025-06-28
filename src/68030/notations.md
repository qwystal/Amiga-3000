An = any address register, A7-A0
Dn = any data register, D7-D0
Rn = any address or data register
CCR = condition code register (lower byte of status register)
cc = condition codes from CCR
SR = status register
SP = active stack pointer
USP = user stack pointer
ISP = supervisor/interrupt stack pointer
MSP = supervisor/master stack pointer
SSP = supervisor (master or interrupt) stack pointer
DFC = destination function code register
SFC = source function code register
Rc = control register (VBR, SFC, DFC, CACR)
MRc = MMU control register (SRP, URP, TC, DTT0, DTT1, ITT0,
ITT1, MMUSR)
MMUSR = MMU status register
B, W, L = specifies a signed integer data type (twos complement) of byte, word, or long word
S = single-precision real data format (32 bits)
D = double-precision real data format (64 bits)
X = extended-precision real data format (96 bits, 16 bits unused)
P = packed BCD real data format (96 bits, 12 bytes)
FPm, FPn = any floating-point data register, FP7-FP0
PFcr = floating-point system control register (FPCR, FPSR, or FPIAR)
k = a twos-complement signed integer (-64 to +17) that specifies the format of a number to be stored in the packed BCD format
d = displacement; d16 is a 16-bit displacement
<ea> = effective address
list = list of registers, for example D3-D0
#<data> = immediate data; a literal integer
{offset:width} = bit field selection
label = assemble program label
[m] = bit m of an operand
[m:n] = bits m through n of operand
X = extend (X) bit in CCR
N = negative {N) bit in CCR
Z = Zero (Z) bit in CCR
V = overflow (V) bit in CCR
C = carry (C) bit in CCR
+ = arithmetic addition or postincrement indicator
- = arithmetic subtraction or predecrement indicator
x = arithmetic multiplication
÷ = arithmetic division or conjunction symbol
~ = invert; operand is logically complemented
∧ = logical AND
∨ = logical OR
⊕ = logical exclusive OR
Dc = data register, D7-D0 used during compare
Du = data register, D7-D0 used during update
Dr, Dq = data registers, remainder or quotient of divide
Dh, DI = data registers, high- or low-order 32 bits of product
MSW = most significant word
LSW = least significant word
MSB = most significant bit
FC = function code
{R/W} = read or write indicator
[An] = address extensions


Mode | Addressing Mode

D/A | Index Register Type
    0 = Dn
    1 = An
W/L | Word/Long-Word Index Size
    0 = Sign-Extended Word
    1 = Long Word
Scale | Scale Factor
    00 = 1
    01 = 2
    10 = 4
    11 = 8
BS | Base Register Suppress
    0 = Base Register Added
    1 = Base Register Suppressed
IS | Index Suppress
    0 = Evaluate and Add Index Operand
    1 = Suppress Index Operand
BD | SIZE Base Displacement Size
    00 = Reserved
    01 = Null Displacement
    10 = Word Displacement
    11 = Long Displacement
I/IS | Index/Indirect Selection
    Indirect and Indexing Operand Determined in Conjunction
    with Bit 6, Index Suppress