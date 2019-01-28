#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv)
{
    uint32_t i = 0x12345678;
    uint8_t* cp = (uint8_t*) &i;

    printf("\n0x%x\n", *cp);


    uint32_t num = 0xa & ~0;

    printf("\n%d\n", num);
    return 0;
}
