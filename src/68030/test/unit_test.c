#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../src/instruction_set.h"
#include "unit_test.h"

size_t errors = 0;
size_t tests = 0;

void error(const char *msg) {
    printf("%s [  %serror%s  ]\n", msg, COLOR_RED, COLOR_RESET);
    tests++;
    errors++;
}

void success(const char *msg) {
    printf("%s [  %sok%s  ]\n", msg, COLOR_GREEN, COLOR_RESET);
    tests++;
}

void test_instructions() {
    size_t counter = 0;
    A3000 a3000 = { 0 };
    a3000.memory = malloc(MAX_MEM_SIZE);

    mem_min = a3000.memory;
    d_reg_min = (byte *) &a3000.cpu.GPR.D[0];
    a_reg_min = (byte *) &a3000.cpu.GPR.A[0];
    mem_size = MAX_MEM_SIZE;

    for (size_t i = 0; i < (0xFFFF + 1); i++)
    {
        a3000.opcode = i;
        if (look_up_instruction(&a3000) != 4)
        {
            counter++;
        }
    }
    
    ASSERT(counter == 59128, "Instruction Decoder");
}

int main(int argc, char **argv) {
    test_instructions();
    
    
    
    return 0;
}