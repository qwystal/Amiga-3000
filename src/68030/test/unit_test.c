#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../src/typedefs.h"
#include "../src/memory.h"
#include "../src/instruction_set.h"
#include "../src/debug.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

#define ASSERT(x, msg) \
if (x) {\
    success(msg);\
    tests++;\
}\
else {\
    error(ASSERT_FAILURE);\
    tests++;\
    errors++;\
}\

size_t errors = 0;
size_t tests = 0;

extern size_t internal_error;
extern byte suppress_errors;
extern size_t error_types[256];
extern const char *error_msgs[3];

extern byte *d_reg_min;
extern byte *a_reg_min;
extern byte *mem_min;
extern size_t mem_size;

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

    if (internal_error)
    {
        printf("\nError count details:\n");
        printf("=========================\n\n");

        for (size_t i = 0; i < 3; i++)
        {
            if (error_types[i])
            {
                printf("%s%s%s   :   %lld\n", COLOR_RED, error_msgs[i], COLOR_RESET, error_types[i]);
            }
        }

        printf("\n=========================\n");
        printf("Total error count: %lld", internal_error);
    }
    else
    {
        printf("\n%sRan without errors.%s", COLOR_GREEN, COLOR_RESET);
    }
    
    
    

    free(a3000.memory);
    
    return 0;
}