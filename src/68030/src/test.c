#include <stdio.h>
#define HELLO 4

int main() {
    int a = 0b1000100101001110;
    printf("The value of a is: 1000100101001110\n");
    int b = (a >> 13) & 0b111; // AND, 0x0F = 0000 1111
    printf("The value of b is: %d\n", b);
    if (b == 0b100 || b == 0b101) {
        printf("b is either 100 or 101\n");
    } else {
        printf("b is neither 100 nor 101\n");
    }

    int c = HELLO;
    int d = -HELLO;

    printf("c: %d\nd: %d\n", c, d);

    return 0;
}