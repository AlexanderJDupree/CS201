## Terms/Skills to know from week 1 Number Systems

Base Conversion (dec to binary to hex)

Twos-complement for signed bytes

Size of each data type:
    char - 8 bits
    short - 16 bits
    int - 32 bits
    long - 64 bits

Prefix for bytes

    8 bits = 1 byte
    1000 bytes = 1 megabyte 
    1000 megabytes = 1 gigabyte

Twos-Complement for signed bytes

    If the leftmost bit is 1, the number is negative.
    Change every 0 to a 1, and 1 to 0
    Subtract 1

Sign Extension
    
    Take an 8 bit signed number and exapand it to 16-bit
    
    If leading bit is 0, then add 8 zeros
    If leading bit is 1, i.e. the byte is signed then add 8 1's

Inttypes/stdint

    c code - #include <stdint>
    
    int8: 1 bytes
    uint8: 1 bytes
    int32: 4 bytes 
    etc.

Endianness

    16bit, 32bit, 64bit number occupy bytes at consecutive addresses.
    I.E. uint16_t takes occupies two addresses. 

    so if uint16_t num = 0x0102

    we break it up into it's bits 0x01 (leading bits) and 0x02 (trailing bits).

    The scheme of storing these bytes are "Big-endian" (leading bits first):
        address contents: 0x124 : 0x01
                          0x125 : 0x02

     and "Little-endian" (trailing bits first):
        address contents: 0x124 : 0x02
                          0x125 : 0x01
                            
Alignment
    
    A number is aligned if its bytes start at an address that is a multiple of its size 
    in bytes.

Promotion
    
    Combining different size types and signed/unsigned numbers will convert the smaller type
    to a larger. This will happen a lot, and sneakily.

