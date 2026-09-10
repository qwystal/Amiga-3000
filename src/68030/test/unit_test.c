#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../src/typedefs.h"
#include "../src/memory.h"
#include "../src/instruction_set.h"
#include "../src/debug.h"
#include "../src/cpu.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

#define ASSERT(x, msg) \
if (x) {\
    success(msg);\
    tests++;\
}\
else {\
    error(msg);\
    tests++;\
    errors++;\
}\

size_t errors = 0;
size_t tests = 0;

void test_instructions(a3000_t *a3000) {
    size_t counter = 0;

    suppress_errors = 1;
    for (size_t i = 0; i <= 0xFFFF; i++)
    {
        a3000->opcode = i;
        if (look_up_instruction(a3000) != -404)
        {
            counter++;
        }
    }
    suppress_errors = 0;
    
    ASSERT(counter == 59128, "Instruction Decoder");
    internal_error = 0;
}

int main(int argc, char **argv) {

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--suppress-errors") == 0)
        {
            suppress_errors = 1;
        }
    }
    
    a3000_t *a3000 = init_cpu();

    test_instructions(a3000);

    if (errors)
    {
        printf("Total error count: %lld", errors);
    }
    else if (!errors)
    {
        printf("\n%sRan without errors.%s", COLOR_GREEN, COLOR_RESET);
    }

    free_cpu(a3000);
    
    return 0;
}