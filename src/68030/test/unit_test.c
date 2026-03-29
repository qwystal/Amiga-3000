#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../src/instruction_set.h"
#include "unit_test.h"

size_t errors = 0;
size_t tests = 0;

void test_instructions(A3000 *a3000) {
    size_t counter = 0;

    for (size_t i = 0; i <= 0xFFFF; i++)
    {
        a3000->opcode = i;
        if (look_up_instruction(a3000) != 4)
        {
            counter++;
        }
    }
    
    ASSERT(counter == 59128, "Instruction Decoder");

}

int main(int argc, char **argv) {

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--suppress-errors") == 0)
        {
            suppress_errors = 1;
        }
    }
    

    A3000 a3000 = { 0 };
    a3000.memory = malloc(MAX_MEM_SIZE);

    mem_min = a3000.memory;
    d_reg_min = (byte *) &a3000.cpu.GPR.D[0];
    a_reg_min = (byte *) &a3000.cpu.GPR.A[0];
    mem_size = MAX_MEM_SIZE;

    test_instructions(&a3000);
    printf("error count: %lld\n", internal_error);

    free(a3000.memory);
    
    return 0;
}