## Terms/Skills to know from week 2 Bit Manipulation

C Bitwise Operators:

    ~ : Unary Not Operator
    & : Binary AND Operator
    | : Binary OR Operator

Bit Masking:

    We can keep only the trailing/leading bits of a 
    number by using a mask.

    A Mask is a number where 1 is the bits to be kept
    and 0 is the bits to be discarded

    ex. Keep the lower 3 bits of an 8-bit value:
        
        0b01001101
      & 0b00000111
      ------------
        0b00000111

Bit Shifting:

    '<<' fills with zeros to the right

    i.e. 0b01 << 3 = 0b01000;

    '>>' Fill with zeros for unsigned types

    i.e. 0b01 >> 2 = 0b0001;

    and sign extends for signed types

    i.e. 0b1001 >> 2 = 0b1111

Bit Shifts for Mask Construction:

    See slides, and studies





