#ifndef DEFINES_H
#define DEFINES_H

#define MAX_MEM_SIZE 0xFFFFFFFF // 4 GB
#define DEFAULT_MEM_SIZE 0x0200000 // 2 MB (configured as 1 MB "chip" and 1 MB "fast" RAM)

// cpu pins
// function code signals
#define FC0 0
#define FC1 1
#define FC2 2

// address bus
#define A0 3
#define A0 3
#define A1 4
#define A2 5
#define A3 6
#define A4 7
#define A5 8
#define A6 9
#define A7 10
#define A8 11
#define A9 12
#define A10 13
#define A11 14
#define A12 15
#define A13 16
#define A14 17
#define A15 18
#define A16 19
#define A17 20
#define A18 21
#define A19 22
#define A20 23
#define A21 24
#define A22 25
#define A23 26
#define A24 27
#define A25 28
#define A26 29
#define A27 30
#define A28 31
#define A29 32
#define A30 33
#define A31 34

// data bus
#define D0 35
#define D1 36
#define D2 37
#define D3 38
#define D4 39
#define D5 40
#define D6 41
#define D7 42
#define D8 43
#define D9 44
#define D10 45
#define D11 46
#define D12 47
#define D13 48
#define D14 49
#define D15 50
#define D16 51
#define D17 52
#define D18 53
#define D19 54
#define D20 55
#define D21 56
#define D22 57
#define D23 58
#define D24 59
#define D25 60
#define D26 61
#define D27 62
#define D28 63
#define D29 64
#define D30 65
#define D31 66

// transfer size signal
#define SIZ0 67
#define SIZ1 68

// bus control signals

// operand cycle start
#define OCS 69
// External Cycle Start
#define ECS 70
// Read/Write
#define RW 71
// Read-Modify-Write Cycle
#define RMC 72
// Address Strobe
#define AS 73
// Data Strobe
#define DS 74
// Data Buffer Enable
#define DBEN 75
// Data Transfer and Size Acknowledge
#define DSACK0 76
// Data Transfer and Size Acknowledge
#define DSACK1 77
// Synchronous Termination
#define STERM 78

// CACHE CONTROL SIGNALS

// Cache Inhibit Input
#define CIIN 79
// Cache Inhibit Output
#define CIOUT 80
// Cache Burst Request
#define CBREQ 81
// Cache Burst Acknowledge
#define CBACK 82

// INTERRUPT CONTROL SIGNALS

// Interrupt Priority Level Signals
#define IPL0 83
#define IPL1 84
#define IPL2 85
// Interrupt Pending
#define IPEND 86
// Autovector
#define AVEC 87

// BUS ARBITRATION CONTROL SIGNALS

// Bus Request
#define BR 88
// Bus Grant
#define BG 89
// Bus Grant Acknowledge
#define BGACK 90

// BUS EXCEPTION CONTROL SIGNALS

// Reset
#define RESET 91
// Halt
#define HALT 92
// Bus Error
#define BERR 93

// EMULATOR SUPPORT SIGNALS

// Cache Disable
#define CDIS 94
// MMU Disable
#define MMUDIS 95
// Pipeline Refill
#define REFILL 96
// Internal Microsequencer Status
#define STATUS 97

// Clock
#define CLK 98

// Power Supply
#define VCC 99
// Ground
#define GND 100

// self assigned uids for each instruction
#define INS_ORI_TO_CCR 1
#define INS_ORI_TO_SR 2
#define INS_ANDI_TO_CCR 3
#define INS_ANDI_TO_SR 4
#define INS_EORI_TO_CCR 5
#define INS_EORI_TO_SR 6
#define INS_ILLEGAL 7
#define INS_RESET 8
#define INS_NOP 9
#define INS_STOP 10
#define INS_RTE 11
#define INS_RTD 12
#define INS_RTS 13
#define INS_RTR 14

// Exception vectors
#define EXC_VEC_PRIVILEGE_VIOLATION 8

#endif