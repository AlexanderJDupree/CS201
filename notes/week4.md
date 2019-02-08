## Terms/Skills to know from week 4 C Specifics (cont'd) 

Core Dump:
    
    Learn core files
    
    compile with -g

    then run: 

    gdb ./[program] core 

 Structs and Padding:

     struct s {
         uint8_t x; // 7 bytes of padding added

         uint64_t y; // 8 byte integer, no padding needed

         uint8_t z; // 7 more bytes of padding
     };

     sizeof(s) should return 24 bytes, depends on hardware

     padding is so each field of the struct is aligned properly.
     Meaning each field is addressed to a multiple of 8. 0x0, 0x8, 0x10, etc.

     The fields will be offset from the struct based on the order they are
     defined in. It is not optimized. So it is beneficial to group attributes
     together such that they fill each others padding requirements.

C Storage:

    C program generally has 5 kinds of memory:

    Read-only fixed "text" memory loaded from your program file by the OS at program startup. 
    This is where your program and strings live

    Writable fixed "bss" memory "initialized to zero" by the OS at program startup. 
    This is where your "uninitialized" global variables live

    Writable fixed "data" memory loaded from your program file by the OS at program startup. 
    This is where your initialized global variable live

    Writable "stack" memory allocated for a function's local variables and parameters when the function is called. 
    It disappears when the function exits

    Writable "heap" memory, which you can get from explicit calls to the C library routine malloc() and "return"  
    to the heap with free() when done with it

Floating Point:

    See book to actually understand this 

CPP Preprocessor

    #include <f.h> looks in standard system directories
    #include "f.h" looks in current directory

    compiling with -Idir will add dir to search path

    #define SOMETHING 'value' will replace textually any matching tokens with 
    the indicated value.

    compiling with -D SYMBOL = VALUE will define the symbol before compilation

