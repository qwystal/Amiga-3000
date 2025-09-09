#include <stdio.h>
#include <stdlib.h>
#include "../src/instruction_set.h"

int main()
{
    
    printf("hi");
    A3000 a3000 = {0};
    a3000.memory = malloc(DEFAULT_MEM_SIZE);
    printf("hi");
    a3000.memory[0] = 0b10111011;
    printf("hi");
    a3000.memory[1] = 0b10001101;
    printf("hi");
    //look_up_instruction(&a3000);
    printf("hi");

    printf("return value: %d\n", look_up_instruction(&a3000));
    printf("return value: %d\n", look_up_instruction(&a3000));

    printf("hi");

    return 0;
}