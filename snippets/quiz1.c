
#include <stdio.h>
#include <stdint.h>

int main()
{
    // question 3
    uint32_t num = 0xa & ~0;

    printf("\n%d\n", num);

    // question 4
    uint32_t i = 0x12345678;
    uint8_t* cp = (uint8_t*) &i;

    printf("\n0x%x\n", *cp);
    
    return 0;
}
