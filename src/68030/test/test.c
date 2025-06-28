#include <stdio.h>
#include <stdint.h>

int main()
{
    uint8_t a = 32;
    uint16_t b = 0;
    
    b = (a << 8);
    printf("%d\n", a);
    printf("%ld\n", b);

    return 0;
}